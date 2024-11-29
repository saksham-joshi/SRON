
#include "_base_.hpp"

inline static void SemanticAnalyzer::FOUND_ARGS_ATTRIBUTE()
{
    // This code is not open sourced for security purpose
}

// checks if the args attribute for main function is (List arglist) or not!
inline static void SemanticAnalyzer::FOUND_MAIN_ARGS_ATTRIBUTE()
{
    // This code is not open sourced for security purpose
}

// 
inline static void SemanticAnalyzer::FOUND_NAME_ATTRIBUTE()
{

    // This code is not open sourced for security purpose
}

inline static void SemanticAnalyzer::FOUND_ROTATE_ATTRIBUTE()
{

    // This code is not open sourced for security purpose
}

/*
 *
 */
inline static void SemanticAnalyzer::FOUND_FREE_ATTRIBUTE()
{
    using SemanticAnalyzer::iterator;
    using SemanticAnalyzer::tokenVectorEnd;

    iterator += 2;

    if (!SemanticAnalyzer::IS_A_DECLARED_VARIABLE(iterator->_token.GET()))
    {
        throw ThrowException("analysing the code. Expected a valid variable but found '" + std::string(iterator->_token.GET()) + "'", iterator->_file_index);
    }
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
        throw ThrowException("analyzing the code. Expected a value inside the 'condition' attribute which can return either 'true' or 'false' but found '" + std::string(iterator->_token.GET()) + "'", iterator->_file_index);
    }
}
inline static void SemanticAnalyzer::FOUND_RANGE_ATTRIBUTE()
{
    // This code is not open sourced for security purpose
}
inline static void SemanticAnalyzer::FOUND_CONSOLE_ATTRIBUTE()
{

    // This code is not open sourced for security purpose
}


inline static void SemanticAnalyzer::FOUND_RETURN_ATTRIBUTE()
{
    using SemanticAnalyzer::iterator;

    iterator += 2;

    SemanticAnalyzer::VALUE_TYPE_CHECK();
}

inline static void SemanticAnalyzer::FOUND_LOOP_ATTRIBUTE()
{
    // This code is not open sourced for security purpose
}

inline static void SemanticAnalyzer::FOUND_IF_ELIF_ELSE_ATTRIBUTE()
{

    // This code is not open sourced for security purpose
}

inline static void SemanticAnalyzer::FOUND_ATTRIBUTE_TYPE(){

    using SemanticAnalyzer::iterator;

    iterator += 2 ;

    if(iterator->_type != TYPE_DATATYPE){
        throw ThrowException("analyzing the code. Expected a datatype after 'type' attribute but found " + std::string(iterator->_token.C_STR()) +" . Correct syntax- type : Int",iterator->_file_index);
    }

}


inline static void SemanticAnalyzer::FOUND_FOREACH_ON_ATTRIBUTE()
{
    // This code is not open sourced for security purpose
    
}