

#include "_throw_methods_.hpp"

/*
 * Above declared function are defined below...
 */
inline static bool SemanticAnalyzer::IS_A_DECLARED_VARIABLE(const std::string &variable_name) noexcept
{
    return (SemanticAnalyzer::variableSet.find(SronHasher::HashFunction()(variable_name.c_str())) != SemanticAnalyzer::variableSet.end());
}

inline static bool SemanticAnalyzer::CHECK_IF_IN_BUILT_FUNCTION_EXISTS(const SronTokenString &fnc_name) noexcept
{
    using SemanticAnalyzer::inbuiltFncSet;

    return inbuiltFncSet.find(SronTokenString::HashFunction()(fnc_name)) != inbuiltFncSet.end();
}

// returns true if function exists else returns false
inline static bool SemanticAnalyzer::CHECK_IF_USER_DEFINED_FUNCTION_EXISTS(const SronTokenString &__fnc_name) noexcept
{

    std::string fnc_name = __fnc_name.GET();

    Support::REPLACE_CHAR_IN_STRING_WITH_LOWER_CASE(fnc_name, '.', '\\');

    // checking if the function is=available in the set of user defined functions....
    using SemanticAnalyzer::userDefinedFncSet;

    if (userDefinedFncSet.find(SronHasher(fnc_name).GET()) != userDefinedFncSet.end())
    {
        return true;
    }

    // if it is not a user-defined function, then we should search on file directories....
    std::ifstream file(Logs::directory_path + fnc_name + ".srb");

    if (!file.fail())
    {
        userDefinedFncSet.insert(SronHasher(fnc_name).GET());
        return true;
    }

    return false;
}

inline static bool SemanticAnalyzer::CHECK_IF_FUNCTION_EXISTS(const SronTokenString &__str) noexcept
{
    return SemanticAnalyzer::CHECK_IF_IN_BUILT_FUNCTION_EXISTS(__str) || SemanticAnalyzer::CHECK_IF_USER_DEFINED_FUNCTION_EXISTS(__str);
}

/*
 Throws error if the variable is already declared.
 and if not, returns the hash of the passed variable.
*/
inline static size_t SemanticAnalyzer::SHOW_WARNING_IF_VARIABLE_ALREADY_DECLARED(const char *str)
{
    size_t variable_hash = SronHasher::HashFunction()(str);

    if (SemanticAnalyzer::variableSet.find(variable_hash) != SemanticAnalyzer::variableSet.end())
    {
        throw ThrowException("analysing the code. Redeclaration of variable '" + std::string(str) + "' will reduce the performance and efficiency of program. Also, sometimes debugging becomes confusing!", iterator->_file_index);
    }

    return variable_hash;
}

inline static void SemanticAnalyzer::ANALYZE(TokenVector &__tokenVector)
{

    using SemanticAnalyzer::iterator;

    
        SemanticAnalyzer::tokenVectorBegin = SemanticAnalyzer::iterator = __tokenVector.begin();

        SemanticAnalyzer::tokenVectorEnd = __tokenVector.end();

        for (; iterator < SemanticAnalyzer::tokenVectorEnd; ++iterator)
        {

            switch (iterator->_type)
            {

                case TYPE_ATTRIBUTE:
                    SemanticAnalyzer::FOUND_TYPE_ATTRIBUTE();
                    break;

                case TYPE_FUNCTION_CALL:
                    SemanticAnalyzer::FOUND_TYPE_FUNCTION_CALL();
                    break;

                case TYPE_MATH_BLOCK:
                    SemanticAnalyzer::FOUND_TYPE_MATH_BLOCK();
                    break;

                case TYPE_DATATYPE:
                    SemanticAnalyzer::FOUND_TYPE_DATATYPE();
                    break;

                case TYPE_IDENTIFIER:
                    SemanticAnalyzer::FOUND_TYPE_IDENTIFIER();
                    break;

                case TYPE_ASSIGN:
                case TYPE_CALC_ASSIGN:
                    SemanticAnalyzer::FOUND_TYPE_ASSIGN();
                    break;

                case TYPE_KEYWORD:
                    SemanticAnalyzer::FOUND_TYPE_KEYWORD();
                    break;

                case TYPE_FUNCTION_SCOPE_START:
                    SemanticAnalyzer::scope_stack.push(SemanticAnalyzer::SRON_FNC_SCOPE);
                    break;

                case TYPE_FUNCTION_SCOPE_CLOSE:

                    SemanticAnalyzer::__loop_count -= (SemanticAnalyzer::scope_stack.top() == SemanticAnalyzer::SRON_LOOP) ? 1 : 0;

                    SemanticAnalyzer::scope_stack.pop();

                    break;

                case TYPE_OPERATOR : throw ThrowException("analysing the code. Found '" + std::string(iterator->_token.GET()) + "' operator outside the mathematical block", iterator->_file_index);

                case TYPE_STRICT_TYPE : throw ThrowException("analysing the code. Found '"+std::string(iterator->_token.GET())+"' which can only be write in 'args' attribute", iterator->_file_index);
                
                case TYPE_NEWLINE:

                case TYPE_COMMA:
                    break;

                default:
                    throw ThrowException("analyzing the code. Found '" + std::string(iterator->_token.GET()) + "' which is performing no tasks", iterator->_file_index);
            }
        }

        if (ByteCodeWriter::fnc_name == nullptr)
        {
            throw ThrowException("analysing the code. *Fatal Error*: Cannot find 'name' attribute", NoException);
        } 
        
        #ifdef SRON_DEVELOPMENT_PHASE
            for(auto& i : __tokenVector){
                std::cout << "\n--{ '" << i._token << "'    '" << Support::FLAG_TO_STRING(i._flag) << "'  }--";
            }
        #endif
        
        // sending the tokenVector for phase 3rd!
        ByteCodeWriter::GENERATE(__tokenVector);
    
}

inline static void SemanticAnalyzer::VALUE_TYPE_CHECK()
{

    using SemanticAnalyzer::iterator;

    switch (iterator->_type)
    {

        case TYPE_INT: SemanticAnalyzer::FOUND_TYPE_INT(); break;

        case TYPE_DOUBLE: SemanticAnalyzer::FOUND_TYPE_DOUBLE(); break;

        case TYPE_BOOL:

        case TYPE_VOID:

        case TYPE_CHAR:

        case TYPE_STRING:
            break;

        case TYPE_LIST_OPEN:
            SemanticAnalyzer::FOUND_TYPE_LIST_OPEN();
            break;

        case TYPE_IDENTIFIER:
            SemanticAnalyzer::FOUND_TYPE_IDENTIFIER();
            break;

        case TYPE_MATH_BLOCK:
            SemanticAnalyzer::FOUND_TYPE_MATH_BLOCK();
            break;

        case TYPE_FUNCTION_CALL:
            SemanticAnalyzer::FOUND_TYPE_FUNCTION_CALL();
            break;

        case TYPE_IDENTIFIER_WITH_DOT:
            throw ThrowException("analysing the code. '" + std::string(iterator->_token.GET()) + "' is expected to be a function call but used as an identifier", iterator->_file_index);

        default:
        
            throw ThrowException("analyzing the code. Expected a value type but found '" + std::string(iterator->_token.GET()) + "'. If the mentioned value is an operator, then try to put the value inside the math block", iterator->_file_index);
    }
}

inline static void SemanticAnalyzer::LOAD_IN_BUILT_SET()
{

    std::ifstream file(Logs::executable_path + std::string("meta\\__function__lib"), std::ios::binary);

    if (file.fail())
    {
        if (std::system("start sron-FncList") != 0)
        {
            throw ThrowException("loading the in built function set. Cannot find 'sron-FncList' executable which is required for compilation process. Reinstall SRON to fix this!", SourceCodeChangedException, false);
        }

        file = std::ifstream(Logs::executable_path + std::string("meta\\function_list"), std::ios::binary);

        if (file.fail())
        {
            throw ThrowException("loading the in built function set. Source Code changed", SourceCodeChangedException);
        }
    }

    size_t temp = 0;

    while (file.read(reinterpret_cast<char *>(&temp), sizeof(size_t)))
    {
        SemanticAnalyzer::inbuiltFncSet.insert(temp);
    }
}
