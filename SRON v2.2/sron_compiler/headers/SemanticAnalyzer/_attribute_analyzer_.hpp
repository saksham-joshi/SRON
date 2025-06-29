
#include "_base_.hpp"

inline static void SemanticAnalyzer::FOUND_ARGS_ATTRIBUTE()
{
    using SemanticAnalyzer::iterator;
    using SemanticAnalyzer::tokenVectorEnd;


    int __iterator_diff = iterator - SemanticAnalyzer::tokenVectorBegin;

    if (!((__iterator_diff == 6) || ( __iterator_diff == 5) || (__iterator_diff == 7)))
    {
        throw ThrowException("analysing the code. 'args' attribute needs to be declared just after 'name' attribute", iterator->_file_index);
    }

    iterator += 2;

    if(ByteCodeWriter::fnc_name != nullptr && Support::IS_MAIN(*ByteCodeWriter::fnc_name))
    {
        SemanticAnalyzer::FOUND_MAIN_ARGS_ATTRIBUTE();
        return;
    }

    // current position of iterator must be (

    auto __expected_type1 = TYPE_OPENING_BRACKETS;
    auto __expected_type2 = SRON_NO_TYPE;

    ArgListLen_t count_of_parameter = 0;

    while (iterator < tokenVectorEnd)
    {

        if (iterator->_type == __expected_type1 || iterator->_type == __expected_type2)
        {

            switch (iterator->_type)
            {

                case TYPE_OPENING_BRACKETS:
                    __expected_type1 = TYPE_STRICT_TYPE;
                    __expected_type2 = TYPE_DATATYPE;
                    break;

                case TYPE_DATATYPE:
                case TYPE_STRICT_TYPE :
                    __expected_type1 = TYPE_IDENTIFIER;
                    __expected_type2 = SRON_NO_TYPE;
                    break;

                case TYPE_IDENTIFIER: ++count_of_parameter;
                    iterator->_cache_value = SemanticAnalyzer::variableSet.insert(SronHasher(iterator->_token.c_str()));
                    __expected_type1 = TYPE_COMMA;
                    __expected_type2 = TYPE_CLOSING_BRACKETS;
                    break;

                case TYPE_COMMA:
                    __expected_type1 = TYPE_DATATYPE;
                    __expected_type2 = TYPE_STRICT_TYPE;
                    break;

                case TYPE_CLOSING_BRACKETS:
                    return;
            }
        }
        else
        {
            throw ThrowException("analysing the code. 'args' attribute has invalid syntax. Expected a value of type '" + std::string(Support::TYPE_TO_STRING(__expected_type1)) + "' but found '" + std::string(iterator->_token.c_str()) + "'", SronError::InvalidArgsSyntaxError, iterator->_file_index);
        }

        if ( count_of_parameter > ARGUMENT_LIST_MAX_LEN ) throw ThrowException("analyzing the 'args' attribute. Found more parameters than limit", SronError::TooMuchParametersInFunctionError , iterator->_file_index ); 

        ++iterator;
    }
}

// checks if the args attribute for main function is (List arglist) or not!
inline static void SemanticAnalyzer::FOUND_MAIN_ARGS_ATTRIBUTE()
{
    using SemanticAnalyzer::tokenVectorEnd;
    using SemanticAnalyzer::iterator;
    // current position of the iterator must be (

    if(iterator < tokenVectorEnd-4 && (iterator->_type == TYPE_OPENING_BRACKETS 
                                   && ((iterator+1)->_type == TYPE_DATATYPE && (iterator+1)->_token == "List") 
                                   && (iterator+2)->_type == TYPE_IDENTIFIER 
                                   && (iterator+3)->_type == TYPE_CLOSING_BRACKETS))
    {

            (iterator+2)->_cache_value = SemanticAnalyzer::variableSet.insert(SronHasher((iterator+2)->_token.c_str()));
            iterator+=3;
            return; 
    }

    throw ThrowException("analysing the code. Found invalid 'args' attribute's syntax for function 'Main'. The correct syntax is- args : (List arglist)", SronError::DefaultError, iterator->_file_index);

}

// 
inline static void SemanticAnalyzer::FOUND_NAME_ATTRIBUTE()
{

    using SemanticAnalyzer::iterator;

    if (ByteCodeWriter::fnc_name != nullptr)
    {
        throw ThrowException("analysing the code. Redeclaration of 'name' attribute within a single scope is found");
    }

    if (!(((iterator - SemanticAnalyzer::tokenVectorBegin) != 2) || ((iterator - SemanticAnalyzer::tokenVectorBegin) != 3)))
    {
        throw ThrowException("analysing the code. The first expected attribute in a function is 'name'");
    }

    iterator += 2;

    if (iterator->_type != TYPE_IDENTIFIER)
    {
        throw ThrowException("analyzing the code. Expected a valid function name but found '" + std::string(iterator->_token.c_str()) + "'");
    }

    // checking if the function name is 'main' , 'Main' , 'MAIN', 'mAIN' etc...
    if( Support::COMPARE_STRING_WITHOUT_CASE( iterator->_token.c_str() , SRON_MAIN) )
    {
        // now checking the correct form of 'Main' function
        if ( iterator->_token != SRON_MAIN ) throw ThrowException("analyzing the code. Found '"+ std::string( iterator->_token.c_str()) + "' which is not the correct case to write 'Main' function name. Keep it exactly 'Main'", iterator->_file_index);
    }

    // if the function is a in built function
    SemanticAnalyzer::THROW_ERROR_IF_IN_BUILT_FUNCTION_EXISTS(*iterator);

    // checking if the function name is a reserved function name...
    if (Support::IS_RESERVED_FILENAME(iterator->_token.c_str()))
    {
        throw ThrowException("analysing the code. The function name '" + std::string(iterator->_token.c_str()) + "' is a reserved file name in windows system", SronError::InvalidFunctionNameError, iterator->_file_index);
    }

    SemanticAnalyzer::userDefinedFncSet.insert( iterator->_token.c_str() );

    ByteCodeWriter::fnc_name = &(iterator->_token);
}

inline static void SemanticAnalyzer::FOUND_ROTATE_ATTRIBUTE()
{

    using SemanticAnalyzer::iterator;
    using SemanticAnalyzer::tokenVectorEnd;

    auto it = iterator;

    iterator += 2;

    // current position of the iterator is '(' ....

    auto __expected_type1 = TYPE_OPENING_BRACKETS;
    auto __expected_type2 = SRON_NO_TYPE;

    // as per the SRON language syntax rules, there must be minimum of 2 
    // identifiers inside the rotate attribute therefore it can't be left empty
    BytecodeCount_t count_of_identifiers_inside_rotate_attribute = 0;

    while (iterator < tokenVectorEnd && iterator->_type != TYPE_CLOSING_BRACKETS)
    {

        if (iterator->_type == __expected_type1 || iterator->_type == __expected_type2)
        {

            switch (iterator->_type)
            {

            case TYPE_OPENING_BRACKETS:
                __expected_type1 = TYPE_IDENTIFIER;
                __expected_type2 = TYPE_CLOSING_BRACKETS;
                break;

            case TYPE_IDENTIFIER:
                ++count_of_identifiers_inside_rotate_attribute;
                __expected_type1 = TYPE_COMMA;
                __expected_type2 = TYPE_CLOSING_BRACKETS;
                SemanticAnalyzer::FOUND_TYPE_IDENTIFIER();
                break;

            case TYPE_COMMA:
                __expected_type1 = TYPE_IDENTIFIER;
                __expected_type2 = SRON_NO_TYPE;
                break;
            }
        }
        else
        {
            throw ThrowException("analysing the code. Found invalid syntax of 'rotate' attribute. 'Rotate' expects only variables separated by comma(,)", iterator->_file_index);
        }

        ++iterator;

        if ( count_of_identifiers_inside_rotate_attribute > MAX_VARIABLE_IN_ROTATE_ATTRIBUTE )
        {
            throw ThrowException("analyzing the code. You cannot have more than 32 variable inside 'rotate' attribute", iterator->_file_index);
        }
    }

    if ( count_of_identifiers_inside_rotate_attribute < 2 )
    {
        throw ThrowException("analyzing the code. There must be minimum 2 and max 32 variables inside the 'rotate' attribute but '" + std::to_string(count_of_identifiers_inside_rotate_attribute) + "' variables found", iterator->_file_index);
    }

    // during the bytecode generation, it will be very helpful to optimize the generation of the bytecode
    it->_cache_value = count_of_identifiers_inside_rotate_attribute;
}

/*
 *
 */
inline static void SemanticAnalyzer::FOUND_CONDITION_ATTRIBUTE()
{

    using SemanticAnalyzer::iterator;

    iterator += 2;

    // current position is a value type after ':' :
    switch (iterator->_type)
    {

    case TYPE_INT:

    case TYPE_DOUBLE:

    case TYPE_BOOL:
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

    default:
        throw ThrowException("analyzing the code. Expected a value inside the 'condition' attribute which can return either 'true' or 'false' but found '" + std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }
}
inline static void SemanticAnalyzer::FOUND_RANGE_ATTRIBUTE()
{
    using SemanticAnalyzer::iterator;

    iterator += 2;

    try{
        // current position of the iterator is at '(' ...

        if (iterator->_type != TYPE_OPENING_BRACKETS)
        {
            //throw ThrowException("analysing the 'range' attribute. Found '" + std::string(iterator->_token.c_str()) + "' but expected an opening round bracket", InvalidRangeSyntax);
            throw "analysing the 'range' attribute. Found '" + std::string(iterator->_token.c_str()) + "' but expected an opening round bracket";
        }

        ++iterator;

        // the first token after '(' must be either a identifier or
        // a variable declaration.
        if (iterator->_type == TYPE_DATATYPE)
        {
            SemanticAnalyzer::FOUND_TYPE_DATATYPE();
        }
        else if (iterator->_type == TYPE_IDENTIFIER)
        {
            SemanticAnalyzer::FOUND_TYPE_IDENTIFIER();
        }
        else
        {
            throw "analyzing the code, Expected an identifier or a variable declaration but found '" + std::string(iterator->_token.c_str()) + "'";
            //throw ThrowException("analyzing the code, Expected an identifier or a variable declaration but found '" + std::string(iterator->_token.c_str()) + "'", InvalidRangeSyntax);
        }

        ++iterator;

        // after the identifier o variable declaration, the expected token
        // is either a comma or assign

        if (iterator->_type == TYPE_COMMA)
        {
            // nothing to do
        }
        else if (iterator->_type == TYPE_ASSIGN)
        {
            SemanticAnalyzer::FOUND_TYPE_ASSIGN();

            ++iterator;

            if (iterator->_type != TYPE_COMMA)
            {
                throw "analyzing the code. Expected a comma(,) but found '"+ std::string(iterator->_token.c_str()) +"'";
                
            }
        }
        else
        {
            throw "analyzing the code, Expected an comma(,) or a assign(=) but found '" + std::string(iterator->_token.c_str()) + "'";
        }

        ++iterator;

        // after comma, there must be a value type....
        SemanticAnalyzer::VALUE_TYPE_CHECK();

        ++iterator;

        if (iterator->_type == TYPE_CLOSING_BRACKETS)
        {
            return;
        }
        else if (iterator->_type == TYPE_COMMA)
        {
            ++iterator;

            // check if value type
            SemanticAnalyzer::VALUE_TYPE_CHECK();
        }

        ++iterator;

        if (iterator->_type != TYPE_CLOSING_BRACKETS)
        {
            throw "analyzing the code. Expected an closing bracket ')' but found '" + std::string(iterator->_token.c_str()) + "'";
        }

    }
    catch(const std::string& excep){
        throw ThrowException(excep, SronError::InvalidRangeSyntaxError, iterator->_file_index);
    }
}
inline static void SemanticAnalyzer::FOUND_CONSOLE_ATTRIBUTE()
{

    using SemanticAnalyzer::iterator;

    iterator += 2;

    if (iterator->_type != TYPE_OPENING_BRACKETS)
    {
        throw ThrowException("analysing the code. Expected a '(' but found '" + std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }

    ++iterator;

    while (iterator < SemanticAnalyzer::tokenVectorEnd && iterator->_type != TYPE_CLOSING_BRACKETS)
    {
        if ( iterator->_flag == Flag_OBuffer ) { }
        
        else SemanticAnalyzer::VALUE_TYPE_CHECK();

        ++iterator;

        if (iterator->_type == TYPE_COMMA)
        {
            ++iterator;
            continue;
        }
        else if (iterator->_type == TYPE_CLOSING_BRACKETS)
            break;

        throw ThrowException("analysing the code. Expected a ',' or ')' but found '" + std::string(iterator->_token.c_str()) + "'. A better syntax can help you to debug any unexpected errors during compilation or runtime", iterator->_file_index);
    }
}


inline static void SemanticAnalyzer::FOUND_RETURN_ATTRIBUTE()
{
    using SemanticAnalyzer::iterator;

    iterator += 2;

    Support::ImplicitConversion::THROW_EXCEPTION_IF_RETURNED_VALUE_DOESNOT_MATCH_WITH_RETURN_TYPE( SemanticAnalyzer::fncReturnType , iterator->_type , iterator->_flag , iterator->_file_index);

    SemanticAnalyzer::VALUE_TYPE_CHECK();
}

inline static void SemanticAnalyzer::FOUND_LOOP_ATTRIBUTE()
{
    using SemanticAnalyzer::iterator;

    const Flag_t _attribute_flag = iterator->_flag;

    iterator += 2;

    SemanticAnalyzer::THROW_ERROR_IF_ITERATOR_NOT_WITHIN_BOUND();

    if (iterator->_type != TYPE_FUNCTION_SCOPE_START)
    {
        throw ThrowException("analysing the code. Expected a scope opening '{' after '" + std::string((iterator - 2)->_token.c_str()) + "' attribute but found '" + std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }

    SemanticAnalyzer::scope_stack.push(SemanticAnalyzer::SRON_LOOP);

    SemanticAnalyzer::variableSet.addLayer();

    ++SemanticAnalyzer::__loop_count;

    // current position of the iterator = '{' ...
    ++iterator;

    SemanticAnalyzer::THROW_ERROR_IF_ITERATOR_NOT_WITHIN_BOUND();

    if (iterator->_type == TYPE_NEWLINE)
    {
        iterator += 1;
        SemanticAnalyzer::THROW_ERROR_IF_ITERATOR_NOT_WITHIN_BOUND();
    }

    if (_attribute_flag == Flag_ForScopeStart)
    {
        if (iterator->_flag == Flag_RangeScopeStart)
        {
            SemanticAnalyzer::FOUND_RANGE_ATTRIBUTE();
            return;
        }

        throw ThrowException("analysing the code. Expected 'range' attribute after 'for' but found '" + std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }
    else if (_attribute_flag == Flag_WhileScopeStart)
    {
        if (iterator->_flag == Flag_Condition)
        {
            SemanticAnalyzer::FOUND_CONDITION_ATTRIBUTE();
            return;
        }
        throw ThrowException("analysing the code. Expected 'condition' attribute after 'while' but found '" + std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }
    else if(_attribute_flag == Flag_ForeachScopeStart)
    {
        if (iterator->_flag == Flag_ForeachOn){
            SemanticAnalyzer::FOUND_FOREACH_ON_ATTRIBUTE();
            return;
        }
        throw ThrowException("analysing the code. Expected 'on' attribute after 'foreach' but found '" + std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }
}

inline static void SemanticAnalyzer::FOUND_IF_ELIF_ELSE_ATTRIBUTE()
{

    using SemanticAnalyzer::iterator;

    const auto &__attribute_name = iterator->_token;

    iterator += 2;

    if (iterator->_type != TYPE_FUNCTION_SCOPE_START)
    {
        throw ThrowException("analysing the code. Expected a scope opening '{' after '" + std::string((iterator - 2)->_token.c_str()) + "' attribute but found '" + std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }

    SemanticAnalyzer::scope_stack.push(SemanticAnalyzer::SRON_IF);

    SemanticAnalyzer::variableSet.addLayer();

    // current position of iterator is '{' ...

    if (__attribute_name == AttributeElse)
    {
        return;
    }
    else if (__attribute_name == AttributeElif || __attribute_name == AttributeIf)
    {
        ++iterator;

        if (iterator->_type == TYPE_NEWLINE)
        {
            iterator += 1;
        }

        if (iterator->_type == TYPE_ATTRIBUTE && iterator->_token == AttributeCondition)
        {
            SemanticAnalyzer::FOUND_CONDITION_ATTRIBUTE();

            return;
        }

        throw ThrowException("analysing the code. Expected 'condition' attribute but found '" + std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }
}

inline static void SemanticAnalyzer::FOUND_ATTRIBUTE_TYPE(){

    using SemanticAnalyzer::iterator;

    // checking if the 'type' attribute came for the first time
    if ( SemanticAnalyzer::fncReturnType != Flag_bydefault )
    {
        throw ThrowException("analyzing the code. Found 'type' more than once. The 'type' attribute can only be used once in a function to specify the return type of the function");
    }

    // checking if the 'type' attribute is used only within the function scope but not withing if-elif-else, for or while
    if ( SemanticAnalyzer::scope_stack.size() != 1 )
    {
        throw ThrowException("analyzing the code. Found 'type' within another scope which is not allowed. 'type' attribute can only be used within function's scope but not within if, elif, else, for, while etc");
    }

    iterator += 2 ;

    // checking if the token is a datatype or not
    if(iterator->_type != TYPE_DATATYPE)
    {
        throw ThrowException("analyzing the code. Expected a datatype after 'type' attribute but found " + std::string(iterator->_token.c_str()) +" . Correct syntax- type : Int",iterator->_file_index);
    }

    SemanticAnalyzer::fncReturnType = iterator->_flag ;

}


inline static void SemanticAnalyzer::FOUND_FOREACH_ON_ATTRIBUTE()
{
    using SemanticAnalyzer::iterator;

    // current position of the iterator is the 'on'
    iterator+=2;

    if(iterator < SemanticAnalyzer::tokenVectorEnd && iterator->_type != TYPE_OPENING_BRACKETS){
        throw ThrowException("analyzing the code. Expected a '(' after 'on : ' but found '"+ std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }

    ++iterator;

    // expected position must be either datatype or variable

    if(iterator->_type == TYPE_DATATYPE)
    {
        SemanticAnalyzer::FOUND_TYPE_DATATYPE();
    }
    else if(iterator->_type == TYPE_IDENTIFIER)
    {
        SemanticAnalyzer::FOUND_TYPE_IDENTIFIER();
    }
    else{
        throw ThrowException("analyzing the code. Expected a variable but found '"+std::string (iterator->_token.c_str()) + "'", iterator->_file_index);
    }

    ++iterator;

    if(iterator->_type != TYPE_COMMA){
        throw ThrowException("analyzing the code. Expected a comma (,) but found '" + std::string (iterator->_token.c_str()) + "'", iterator->_file_index);
    }

    ++iterator;

    switch(iterator->_type){

        case TYPE_LIST_OPEN : SemanticAnalyzer::FOUND_TYPE_LIST_OPEN(); break;

        case TYPE_STRING : break;

        case TYPE_IDENTIFIER : SemanticAnalyzer::FOUND_TYPE_IDENTIFIER(); break;

        case TYPE_FUNCTION_CALL : SemanticAnalyzer::FOUND_TYPE_FUNCTION_CALL(); break;

        case TYPE_MATH_BLOCK : SemanticAnalyzer::FOUND_TYPE_MATH_BLOCK(); break;

        default : throw ThrowException("analyzing the code. Expected a collective type value (eg. String or List) but found '" + std::string(iterator->_token.c_str()) +"'", iterator->_file_index);
    }

    ++iterator;

    

    if(iterator->_type != TYPE_CLOSING_BRACKETS){
        throw ThrowException("analyzing the code. Expected a ')' at the end of 'on : ' but found '"+ std::string(iterator->_token.c_str()) + "'", iterator->_file_index);
    }
    
}