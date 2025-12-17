
#include "_type_analyzer_.hpp"


// if the in built function exists, it throws the error
inline static void SemanticAnalyzer::THROW_ERROR_IF_IN_BUILT_FUNCTION_EXISTS(SronToken &__token)
{
    using SemanticAnalyzer::inbuiltFncSet;

    const auto it = inbuiltFncSet.find( SronHasher(__token._token.c_str() ).GET() ) ;

    if (it != inbuiltFncSet.end())
    {
        throw ThrowException("analysing the code. Found declaration of function '" + std::string(SemanticAnalyzer::iterator->_token.c_str()) + "' which is already an in-built function");
    }
}

inline static void SemanticAnalyzer::THROW_ERROR_IF_USER_DEFINED_FUNCTION_NOT_EXISTS(SronToken::TokenElement_t &__fnc_name)
{
    using SemanticAnalyzer::userDefinedFncSet;

    if ( userDefinedFncSet.find( __fnc_name.c_str()) != userDefinedFncSet.end() ) return;

    SemanticAnalyzer::THROW_ERROR_IF_VALID_BYTECODE_FILE_NOT_EXISTS( __fnc_name.c_str());
}

/*
 * This function is used to check if the passes string is a valid variable name or not.

 The conditions for a valid variable name are as follows:
 * 1. First letter of the variable can only be an alphabet or an underscore.
 * 2. variable name can only contain alphabetic characters, numbers and underscores.
 * 3. length of the variable cannot exceed limit of 32 characters.
*/
inline static void SemanticAnalyzer::THROW_ERROR_IF_INVALID_VARIABLE_NAME(bool dot_present_or_not, const std::string &variable_name)
{
    if (dot_present_or_not || variable_name.length() >= 32)
    {
        throw ThrowException("checking the validity of a variable '" + variable_name + "'", SronError::InvalidVariableNameError);
    }
}

// this function is called when ':' is found, it throws the error if the passed token is not an attribute
inline static void SemanticAnalyzer::THROW_ERROR_IF_NOT_ATTRIBUTE(SronToken &__last_token)
{

    if (__last_token._type != TYPE_ATTRIBUTE)
    {
        throw ThrowException("tokenizing the code. Expected an attribute before ':' but found '" + std::string(__last_token._token.c_str()) + "' which is not a valid attribute", SronError::DefaultError);
    }
}

inline static void SemanticAnalyzer::THROW_ERROR_IF_INSIDE_MATH_BLOCK(const unsigned short int __type, bool __inside_math_expression)
{
    if (__inside_math_expression)
    {
        throw ThrowException("analyzing the code. Found '" + std::string(Support::TYPE_TO_STRING(__type)) + "' inside math block which is not allowed as per the syntax");
    }
}

inline static void SemanticAnalyzer::THROW_ERROR_IF_NUMBER_OVERFLOWS(bool dot_present, std::string &__num)
{
    if (dot_present)
        SemanticAnalyzer::THROW_ERROR_IF_DOUBLE_OVERFLOW(__num);
    else
        SemanticAnalyzer::THROW_ERROR_IF_INT_OVERFLOW(__num);
}

inline static void SemanticAnalyzer::THROW_ERROR_IF_INT_OVERFLOW(std::string &__num)
{
    using SemanticAnalyzer::iterator;

    const char *SRON_INT_MAX = "9223372036854775807";
    const char *SRON_INT_MIN = "-9223372036854775808";

    if ((__num[0] == '-' && !(std::strcmp(__num.c_str() + 1, SRON_INT_MIN) < 0)) || (__num > SRON_INT_MAX))
    {
        throw ThrowException("analysing the code. Found '" + __num + "' which overflow the limit of 'Int' type values", SronError::IntegerOverflowError, iterator->_file_index);
    }
}

inline static void SemanticAnalyzer::THROW_ERROR_IF_DOUBLE_OVERFLOW(std::string &__num)
{
    const char *SRON_DOUBLE_MAX = "179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368";
    const char *SRON_DOUBLE_MIN = "-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858367";

    if ((__num[0] == '-' && !(std::strcmp(__num.c_str() + 1, SRON_DOUBLE_MIN) < 0)) || (__num > SRON_DOUBLE_MAX))
    {
        throw ThrowException("analysing the code. Found '" + __num + "' which overflow the limit of 'Double' type values", SronError::DoubleOverflowError, iterator->_file_index);
    }
}

inline static void SemanticAnalyzer::THROW_ERROR_IF_DIVISION_BY_ZERO_FOUND(std::string& __str , unsigned long __file_index)
{

    if (Converter::TO_DOUBLE(__str) == 0)
    {
        throw ThrowException("analyzing the code. Found Division/Mod with zero", SronError::DivisionByZeroError, __file_index);
    }
}

inline static void SemanticAnalyzer::THROW_ERROR_IF_ITERATOR_NOT_WITHIN_BOUND(){

    if(SemanticAnalyzer::iterator < SemanticAnalyzer::tokenVectorEnd){
        return;
    }

    throw ThrowException("analyzing the code. Expected some tokens but found nothing here. Look at the end of the code");
}

inline static void SemanticAnalyzer::THROW_ERROR_IF_VALID_BYTECODE_FILE_NOT_EXISTS(const char* __fnc_name )
{
    auto code = SemanticAnalyzer::VERIFY_BYTECODE_FILE( __fnc_name );

    switch ( code )
    {
        case 1 : throw ThrowException("analyzing the code. Cannot find function '" + std::string( __fnc_name ) + "'", SronError::FunctionNotFoundError, SemanticAnalyzer::iterator->_file_index);

        case 2 : throw ThrowException( "analyzing the code. Found '" + std::string( __fnc_name ) + "' function but its meta doesn't matches", SronError::BytecodeMetaNotValidError , SemanticAnalyzer::iterator->_file_index );
    }
}