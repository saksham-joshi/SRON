

#include "_throw_methods_.hpp"

/*
 * Above declared function are defined below...
 */
inline static bool SemanticAnalyzer::IS_A_DECLARED_VARIABLE(const std::string &variable_name) noexcept
{
    return (SemanticAnalyzer::variableSet.find(SronHasher::HashFunction()(variable_name.c_str())) != SemanticAnalyzer::variableSet.end());
}

inline static bool SemanticAnalyzer::CHECK_IF_IN_BUILT_FUNCTION_EXISTS(const SronToken::TokenElement_t &fnc_name) noexcept
{
    using SemanticAnalyzer::inbuiltFncSet;

    return inbuiltFncSet.find(SronHasher::HashFunction()(fnc_name)) != inbuiltFncSet.end();
}

// returns true if function exists else returns false
inline static bool SemanticAnalyzer::CHECK_IF_USER_DEFINED_FUNCTION_EXISTS(const SronToken::TokenElement_t &__fnc_name) noexcept
{
    using SemanticAnalyzer::userDefinedFncSet;

    // checking if the function is=available in the set of user defined functions....
    if ( userDefinedFncSet.find(__fnc_name.c_str()) != userDefinedFncSet.end() ) return true;

    auto code = SemanticAnalyzer::VERIFY_BYTECODE_FILE( __fnc_name.c_str() );

    if ( code != 0 ) return false;

    userDefinedFncSet.insert( __fnc_name );

    return true;
}

/*
 Throws error if the variable is already declared.
 and if not, returns the hash of the passed variable.
*/
inline static size_t SemanticAnalyzer::SHOW_WARNING_IF_VARIABLE_ALREADY_DECLARED(const char *__variable)
{
    SronHasher obj( __variable );

    if (SemanticAnalyzer::variableSet.find(obj) != SemanticAnalyzer::variableSet.end() )
    {
        throw ThrowException("analysing the code. Redeclaration of variable '" + std::string( __variable) + "' will reduce the performance and efficiency of program. Also, sometimes debugging becomes confusing!", iterator->_file_index);
    }

    return obj.GET();
}

inline static void SemanticAnalyzer::ANALYZE(TokenVector &__tokenVector)
{

    using SemanticAnalyzer::iterator;

    
        SemanticAnalyzer::tokenVectorBegin = SemanticAnalyzer::iterator = __tokenVector.begin();

        SemanticAnalyzer::tokenVectorEnd = __tokenVector.end();

        SemanticAnalyzer::variableSet.addLayer();

        for (; iterator < SemanticAnalyzer::tokenVectorEnd; ++iterator)
        {

            #ifdef SRON_DEVELOPMENT_PHASE
                std::printf ("\n <[  %s    ]>", iterator->_token.c_str());
            #endif

            switch (iterator->_type)
            {

                case SronTokenType::TYPE_ATTRIBUTE:
                    SemanticAnalyzer::FOUND_TYPE_ATTRIBUTE();
                    break;

                case SronTokenType::TYPE_FUNCTION_CALL:
                    SemanticAnalyzer::FOUND_TYPE_FUNCTION_CALL();
                    break;

                case SronTokenType::TYPE_MATH_BLOCK:
                    SemanticAnalyzer::FOUND_TYPE_MATH_BLOCK();
                    break;

                case SronTokenType::TYPE_DATATYPE:
                    SemanticAnalyzer::FOUND_TYPE_DATATYPE();
                    break;

                case SronTokenType::TYPE_IDENTIFIER:
                    SemanticAnalyzer::FOUND_TYPE_IDENTIFIER();
                    break;

                case SronTokenType::TYPE_ASSIGN:
                case SronTokenType::TYPE_CALC_ASSIGN:
                    SemanticAnalyzer::FOUND_TYPE_ASSIGN();
                    break;

                case SronTokenType::TYPE_KEYWORD:
                    SemanticAnalyzer::FOUND_TYPE_KEYWORD();
                    break;

                case SronTokenType::TYPE_FUNCTION_SCOPE_START:
                    SemanticAnalyzer::scope_stack.push(SemanticAnalyzer::SRON_FNC_SCOPE);
                    break;

                case SronTokenType::TYPE_FUNCTION_SCOPE_CLOSE:

                    if ( SemanticAnalyzer::scope_stack.size() == 0 ) throw ThrowException("analyzing the code. There is some issue related to scope handling", SronError::ScopeBasedError, iterator->_file_index);

                    SemanticAnalyzer::__loop_count -= (SemanticAnalyzer::scope_stack.top() == SemanticAnalyzer::SRON_LOOP) ? 1 : 0;

                    SemanticAnalyzer::scope_stack.pop();

                    SemanticAnalyzer::variableSet.popLayer();

                    break;

                case SronTokenType::TYPE_OPERATOR : throw ThrowException("analysing the code. Found '" + std::string(iterator->_token.c_str()) + "' operator outside the mathematical block", iterator->_file_index);

                case SronTokenType::TYPE_STRICT_TYPE : throw ThrowException("analysing the code. Found '"+std::string(iterator->_token.c_str())+"' which can only be write in 'args' attribute", iterator->_file_index);
                
                case SronTokenType::TYPE_NEWLINE:

                case SronTokenType::TYPE_COMMA:
                    break;

                default:
                    throw ThrowException("analyzing the code. Found '" + std::string(iterator->_token.c_str()) + "' which is performing no tasks", iterator->_file_index);
            }
        }

        if (ByteCodeWriter::fnc_name == nullptr)
        {
            throw ThrowException("analysing the code. *Fatal Error*: Cannot find 'name' attribute", SronError::DefaultError);
        }

        // storing the name of the current function so that after the
        // bytecode is generated successfully, it will be inserted to
        // SemanticAnalyzer::userDefinedFncSet
        const char*const fnc_name = ByteCodeWriter::fnc_name->c_str();
        
        #ifdef SRON_DEVELOPMENT_PHASE
            for(const auto& i : __tokenVector){
                std::printf ("\n--{ Token= '%s'     Flag='%s'    }--", i._token.c_str() , SronSupport::flagToString(i._flag));
            }
        #endif
        
        // sending the tokenVector for phase 3rd!
        ByteCodeWriter::GENERATE(__tokenVector , SemanticAnalyzer::variableSet.totalVariables());
        
        SemanticAnalyzer::userDefinedFncSet.insert( fnc_name );
}

inline static void SemanticAnalyzer::RESET() noexcept
{
    SemanticAnalyzer::__loop_count = 0;

    SemanticAnalyzer::variableSet.clear();

    while( !SemanticAnalyzer::scope_stack.empty() ) SemanticAnalyzer::scope_stack.pop();

    SemanticAnalyzer::fncReturnType = BytecodeFlags::Flag_bydefault;
}

inline static void SemanticAnalyzer::VALUE_TYPE_CHECK()
{

    using SemanticAnalyzer::iterator;

    if ( iterator >= SemanticAnalyzer::tokenVectorEnd ) throw ThrowException("analyzing the code. Expecting a value but nothing is found");

    switch (iterator->_type)
    {

        case SronTokenType::TYPE_INT: SemanticAnalyzer::FOUND_TYPE_INT(); break;

        case SronTokenType::TYPE_DOUBLE: SemanticAnalyzer::FOUND_TYPE_DOUBLE(); break;

        case SronTokenType::TYPE_BOOL:

        case SronTokenType::TYPE_VOID:

        case SronTokenType::TYPE_CHAR:

        case SronTokenType::TYPE_STRING:
            break;

        case SronTokenType::TYPE_LIST_OPEN:
            SemanticAnalyzer::FOUND_TYPE_LIST_OPEN();
            break;

        case SronTokenType::TYPE_IDENTIFIER:
            SemanticAnalyzer::FOUND_TYPE_IDENTIFIER();
            break;

        case SronTokenType::TYPE_MATH_BLOCK:
            SemanticAnalyzer::FOUND_TYPE_MATH_BLOCK();
            break;

        case SronTokenType::TYPE_FUNCTION_CALL:
            SemanticAnalyzer::FOUND_TYPE_FUNCTION_CALL();
            break;

        case SronTokenType::TYPE_IDENTIFIER_WITH_DOT:
            throw ThrowException("analysing the code. '" + std::string(iterator->_token.c_str()) + "' is expected to be a function call but used as an identifier", iterator->_file_index);

        case SronTokenType::TYPE_KEYWORD:
            if ( iterator->_flag == BytecodeFlags::Flag_OBuffer ) throw ThrowException("analyzing the code. Found '" + std::string( iterator->_token.c_str()) + "' which cannot be used as a value. It's a 'Keyword'", SronError::InvalidOBufferSyntaxError, iterator->_file_index);
        default:
        
            throw ThrowException("analyzing the code. Expected a value type but found '" + std::string(iterator->_token.c_str()) + "'. If the mentioned value is an operator, then try to put the value inside the math block", iterator->_file_index);
    }
}

/*
   - returns 0: if everything is okay
   - returns 1: if cannot find the bytecode file
   - returns 2: if meta is incorrect
*/
inline static unsigned short int SemanticAnalyzer::VERIFY_BYTECODE_FILE( const char* __fnc_name ) noexcept
{
    using SemanticAnalyzer::iterator;

    std::string str = __fnc_name;

    auto fnc_name_exclude_dir_path = Support::REPLACE_CHAR_IN_CHAR_STR( str.data() , '.' , '/' );

    fnc_name_exclude_dir_path += ( fnc_name_exclude_dir_path == 0 ? 0 : 1 );

    str += SRON_BYTECODE_FILE_EXTENSION;

    FILE* file = nullptr;

    SronSupport::safeOpenFile( &file , ( Logs::directory_path + str ).c_str() , "rb");

    // if the file doesn't exists, then the user is calling an unknown function
    if ( ! file ) return 1; 

    // now verifying the bytecode file
    SronBytecodeMeta meta = { 0 , 0 };

    std::fread( &meta, sizeof(meta), 1, file);

    if (! meta.matchMeta( { SRON_VERSION , SronHasher( str.c_str() + fnc_name_exclude_dir_path).GET() }))
    {
        return 2;
    }

    return 0;
}