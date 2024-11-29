
#include "_attribute_analyzer_.hpp"

inline static void SemanticAnalyzer::FOUND_TYPE_INT()
{
    using SemanticAnalyzer::iterator;

    if(iterator->_token.LEN() > 19){
        throw ThrowException("analyzing the code. Found a very very long integer '"+ std::string(iterator->_token.GET()) +"'. The value will change during runtime", iterator->_file_index);
    } 
}

inline static void SemanticAnalyzer::FOUND_TYPE_DOUBLE()
{
    using SemanticAnalyzer::iterator;

    if(iterator->_token.LEN() > 20){
        throw ThrowException("analyzing the code. Found a very very long double value '"+ std::string(iterator->_token.GET()) +"'. The value may change during runtime", iterator->_file_index);
    } 
}

inline static void SemanticAnalyzer::FOUND_TYPE_ATTRIBUTE()
{
    using SemanticAnalyzer::iterator;

    ++iterator;

    if (iterator->_type != TYPE_COLON)
    {

        throw ThrowException("analysing the code. Found attribute '" + std::string((iterator - 1)->_token.GET()) + "' without colon", InvalidAttributeSyntaxException,iterator->_file_index);
    }

    // current position of iterator is ':' ...
    if (iterator >= SemanticAnalyzer::tokenVectorEnd - 2)
    {
        throw ThrowException("analysing the code. Found no instruction inside '" + std::string((iterator - 1)->_token.GET()) + "' attribute", InvalidAttributeSyntaxException,iterator->_file_index);
    }

    --iterator;

    switch(iterator->_flag){

        case Flag_FunctionArgsScopeStart : SemanticAnalyzer::FOUND_ARGS_ATTRIBUTE(); break;

        case Flag_Free : SemanticAnalyzer::FOUND_FREE_ATTRIBUTE(); break;

        case Flag_FunctionName : SemanticAnalyzer::FOUND_NAME_ATTRIBUTE(); break;

        case Flag_ReturnType : SemanticAnalyzer::FOUND_ATTRIBUTE_TYPE(); break;

        case Flag_RotateScopeStart : SemanticAnalyzer::FOUND_ROTATE_ATTRIBUTE(); break;

        case Flag_ForScopeStart : 

        case Flag_WhileScopeStart :

        case Flag_ForeachScopeStart : SemanticAnalyzer::FOUND_LOOP_ATTRIBUTE(); break;

        case Flag_IfScopeStart : 

        case Flag_ElifScopeStart : 

        case Flag_ElseScopeStart : SemanticAnalyzer::FOUND_IF_ELIF_ELSE_ATTRIBUTE(); break;

        case Flag_Return : SemanticAnalyzer::FOUND_RETURN_ATTRIBUTE(); break;

        case Flag_ConsoleStart : SemanticAnalyzer::FOUND_CONSOLE_ATTRIBUTE(); break;

        case Flag_RangeScopeStart : throw ThrowException("analyzing the code. Found 'range' attribute but not just after 'for' attribute", iterator->_file_index);

        case Flag_Condition : throw ThrowException("analysing the code. Found 'condition' attribute but not just after 'while', 'if' or 'elif' attributes", iterator->_file_index);

        case Flag_ForeachOn : throw ThrowException("analyzing the code. Found 'on' attribute but not just after 'foreach' attribute", iterator->_file_index);

        default: throw ThrowException("\n\n---------------| No Semantic Analyzer Method found for attribute '" + std::string( iterator->_token.GET()) + "'.\n---------------------", iterator->_file_index);
    }

    // incrementing the iterator to the end of the attribute's instruction
    ++iterator;

    // after the checking of the attribute is done, now
    // it is required to check if there is a valid end
    if (!Support::IS_VALID_END(iterator->_type))
    {
        throw ThrowException("analysing the code. Expected a valid end but found '" + std::string(iterator->_token.GET()) + "'");
    }
}
inline static void SemanticAnalyzer::FOUND_TYPE_ASSIGN()
{
    // This code is not open sourced for security reasons
}

inline static void SemanticAnalyzer::FOUND_TYPE_IDENTIFIER()
{
    // This code is not open sourced for security reasons
}

/*
 * If these datatype: Int, Double, Char, Bool, String, List
 * are found then this function is called. It checks if there
 * is a valid variable after the datatype or not.
 */
inline static void SemanticAnalyzer::FOUND_TYPE_DATATYPE()
{
    // This code is not open sourced for security reasons

}

/*
 * When a a function is called!
 */
inline static void SemanticAnalyzer::FOUND_TYPE_FUNCTION_CALL()
{
    // This code is not open sourced for security reasons
}

inline static void SemanticAnalyzer::FOUND_TYPE_KEYWORD()
{

   // This code is not open sourced for security reasons
}

inline static void SemanticAnalyzer::FOUND_TYPE_MATH_BLOCK()
{

    using SemanticAnalyzer::iterator;
    using SemanticAnalyzer::tokenVectorEnd;

    try
    {

        auto switch_tree = []()
        {
            switch (iterator->_type)
            { // operand only
                case TYPE_INT: SemanticAnalyzer::FOUND_TYPE_INT(); break;
                case TYPE_DOUBLE: SemanticAnalyzer::FOUND_TYPE_DOUBLE(); break;
                case TYPE_VOID :
                case TYPE_CHAR:
                case TYPE_STRING:
                case TYPE_BOOL: break;
                case TYPE_IDENTIFIER: SemanticAnalyzer::FOUND_TYPE_IDENTIFIER(); break;
                case TYPE_FUNCTION_CALL: SemanticAnalyzer::FOUND_TYPE_FUNCTION_CALL();break;
                case TYPE_LIST_OPEN: SemanticAnalyzer::FOUND_TYPE_LIST_OPEN(); break;
                case TYPE_MATH_BLOCK : SemanticAnalyzer::FOUND_TYPE_MATH_BLOCK(); break;
                case TYPE_IDENTIFIER_WITH_DOT: throw ThrowException("analysing the mathematical block. '" + std::string(iterator->_token.GET()) + "' is expected to be a function call but used as an identifier" , SemanticAnalyzer::iterator->_file_index);

                default: throw " ";
            }

        };

        // inside math block any operation need 3 values:
        // Two OPERAND and One OPERATOR between them. (eg:  ~{ a + b }~)
        // Their can be opening bracket after OPERATOR and
        // Their can be closing bracket after OPERAND.

        // ~{ - + - ( ( ( - - ( - ... }~
        while ((++iterator)->_type == TYPE_OPERATOR || iterator->_type == TYPE_OPENING_BRACKETS);

        // first operand
        switch_tree();

        
        // // case TYPE_OPERATOR:  will return false (eg: ~{ + + }~ )
        // // case TYPE_CLOSING_BRACKETS eg: ~{ () }~  or  ~{ ((())) }~

        // second value always operator and third value always operand
        while ((++iterator)->_flag != Flag_EvalEnd)
        {

            while (iterator->_type == TYPE_CLOSING_BRACKETS)
            { // ~ ( a ) ~   or   ~(a + (c + b))~
                if ((++iterator)->_flag == Flag_EvalEnd)
                    return;
            }

            // a + b  (atleast one operator should be between )
            if (iterator->_type != TYPE_OPERATOR)
                throw " ";

            // ~{ ( a ) + - ( + ((( - + ... }~
            while ((++iterator)->_type == TYPE_OPERATOR || iterator->_type == TYPE_OPENING_BRACKETS)
            {
            }

            // operand only
            switch_tree();
        }
    }
    catch (const char *excep)
    {
        throw ThrowException("analyzing the mathematical block. Found '" + std::string(iterator->_token.GET()) + "' of type '" + std::string(Support::TYPE_TO_STRING(iterator->_type)) + "' which makes the mathematical expression invalid", MathematicalBlockSyntaxException, iterator->_file_index);
    }
}

// this method is called when '[' is found which as per the syntax of SRON is used to create a list
// this method checks if only the valid values exists inside the list ...
inline static void SemanticAnalyzer::FOUND_TYPE_LIST_OPEN()
{
    // This code is not open sourced for security reasons
}