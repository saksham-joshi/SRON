
#pragma once

#ifndef SUPPORT_H
#define SUPPORT_H

#include "_sron_token_.hpp"

namespace Support
{

    inline static bool COMPARE_STRING_WITHOUT_CASE ( const char* , const char* );

    inline static bool CHECK_VALID_VARIABLE_NAME(const std::string &);

    inline static char GET_RESPECTIVE_CLOSING_CHAR(char);

    inline static Flag_t GET_RESPECTIVE_ENDING_FLAG(Flag_t);

    inline static int HANDLE_CMD_ARGUMENTS(int, char **);

    inline static bool HAS_SUFFIX(const char*, unsigned int, const char*, unsigned int);

    inline static bool IS_HALT_TYPE_FUNCTION(SronToken::TokenElement_t&);

    inline static bool IS_OPERATOR(const char &ch) noexcept;

    inline static bool IS_MATH_OPERATOR(const char &ch) noexcept;

    inline static bool IS_MAIN(SronToken::TokenElement_t&);

    inline static bool IS_NUMBER(int ch) noexcept;

    inline static bool IS_UNARY_OPERATOR(Flag_t) noexcept;

    inline static bool IS_RESERVED_FILENAME(const std::string &__str) noexcept;

    inline static bool IS_SCOPE_OPERATOR(char ch) noexcept;

    inline static bool IS_VALID_END(const unsigned short int type) noexcept;

    inline static bool IS_VALUE_TYPE(const unsigned short int &_type) noexcept;

    inline static unsigned int REPLACE_CHAR_IN_CHAR_STR(char*, char, char);

    inline static void REPLACE_CHAR_IN_STRING(std::string&, char, char);

    inline static char TO_LOWER(char val) noexcept;

    inline static std::string TO_LOWER(const std::string &) noexcept;

    inline static const char *FLAG_TO_STRING(Flag_t) noexcept;

    inline static const char* TYPE_TO_STRING(unsigned short int __type) noexcept;

    /*


     Implementation starts from here ================================>


    */

    inline static bool COMPARE_STRING_WITHOUT_CASE ( const char* __str1 , const char* __str2 )
    {
        while( *__str1 && *__str2 )
        {
            if ( std::tolower(*__str1) != std::tolower(*__str2 ) ) return false;

            ++__str1;
            ++__str2;
        }

        return *__str1 == *__str2;
    }

    inline static bool IS_MAIN(SronToken::TokenElement_t& __str){

        return Support::COMPARE_STRING_WITHOUT_CASE( __str.c_str() , SRON_MAIN );
    }

    inline static bool IS_HALT_TYPE_FUNCTION(SronToken::TokenElement_t& __str)
    {
        static size_t __function_exit__ = SronHasher("exit").GET();
        static size_t __function_display_exception__ = SronHasher("display_exception").GET();

        size_t hash__ = SronHasher(__str.c_str()).GET();
        
        return (hash__ == __function_exit__  || hash__ == __function_display_exception__);
    }

    inline static bool IS_NUMBER(int ch) noexcept
    {
        return (ch >= 48 && ch <= 57);
    }

    inline static bool IS_ALPHABET(int ch) noexcept
    {
        return ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90));
    }
    inline static bool IS_ALPHA_NUMBER(int ch) noexcept
    {
        return (IS_NUMBER(ch) || IS_ALPHABET(ch));
    }

    inline static bool IS_SCOPE_OPERATOR(char ch) noexcept
    {
        return (ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')');
    }
    inline static bool IS_MATH_OPERATOR(const char &ch) noexcept
    {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^');
    }

    inline static bool IS_OPERATOR(const char &ch) noexcept
    {
        return (IS_MATH_OPERATOR(ch) || ch == '<' || ch == '>' || ch == '!' || ch == ',' || ch == '&' || ch == '|' || ch == '.');
    }

    inline static bool IS_VALID_END(const unsigned short int type) noexcept
    {
        return (type == TYPE_NEWLINE || type == TYPE_FUNCTION_SCOPE_CLOSE);
    }

    inline static bool IS_UNARY_OPERATOR(Flag_t __flag) noexcept
    {
        return ((__flag == Flag_BitwiseNot ) || (__flag == Flag_Not) || (__flag == Flag_Negate));
    }

    /*
    This function returns if the std::string is a reserved file and folder name in
    windows or not. This function will be used by Semantic Analyzer to determine
    a valid file name must be there so that any OS Exception while saving the
    bytecode will not generate.
    */
    inline static bool IS_RESERVED_FILENAME(const std::string &__str) noexcept
    {
        auto str = Support::TO_LOWER(__str);

        return (
            str == "con" || str == "prn" || str == "aux" || str == "nul" || 
            str == "com0" || str == "com1" || str == "com2" || str == "com3" || 
            str == "com4" || str == "com5" || str == "com6" || str == "com7" || 
            str == "com8" || str == "com9" || str == "lpt0" || str == "lpt1" || 
            str == "lpt2" || str == "lpt3" || str == "lpt4" || str == "lpt5" || 
            str == "lpt6" || str == "lpt7" || str == "lpt8" || str == "lpt9"
        );
    }

    inline static bool IS_VALUE_TYPE(const unsigned short int &_type) noexcept
    {

        return ( _type == TYPE_VOID || _type == TYPE_INT || _type == TYPE_DOUBLE || 
                 _type == TYPE_CHAR || _type == TYPE_STRING || _type == TYPE_LIST_OPEN || 
                 _type == TYPE_BOOL || _type == TYPE_IDENTIFIER || _type == TYPE_FUNCTION_CALL 
                 || _type == TYPE_MATH_BLOCK
        );
    }

    /*
     * This function is used to check if the passes string is a valid variable name or not.

     The conditions for a valid variable name are as follows:
     * 1. First letter of the variable can only be an alphabet or an underscore.
     * 2. variable name can only contain alphabetic characters, numbers and underscores.
     * 3. length of the variable cannot exceed limit of 32 characters.
    */
    inline static bool CHECK_VALID_VARIABLE_NAME(const std::string &str)
    {

        if (str.empty() || (!(str[0] == '_' || isalpha(str[0]) > 0 || str.length() <= 32)))
        {
            return false;
        }
        for (const auto &ch : str)
        {
            if (!(ch == '_' || Support::IS_ALPHABET(ch) || Support::IS_NUMBER(ch)))
            {
                return false;
            }
        }
        return true;
    }

    inline static char GET_RESPECTIVE_CLOSING_CHAR(char __ch){

        switch(__ch){

            case '[' : return ']';

            case '{' : return '}';

            case '(' : return ')';
        }

        return '#';
    }

    inline static char GET_RESPECTIVE_OPENING_CHAR(char __ch){

        switch(__ch){

            case ']' : return '[';

            case '}' : return '{';

            case ')' : return '(';
        }

        return '#';
    }

    inline static Flag_t GET_RESPECTIVE_ENDING_FLAG(Flag_t __flag)
    {
        switch(__flag){

            case Flag_IfScopeStart : return Flag_IfScopeEnd;

            case Flag_ElifScopeStart : return Flag_ElifScopeEnd;

            case Flag_ElseScopeStart : return Flag_ElseScopeEnd;

            case Flag_WhileScopeStart : return Flag_WhileScopeEnd;

            case Flag_ForScopeStart : return Flag_ForScopeEnd;

            default : throw ThrowException("retrieving ending flag for flag '" + std::to_string(__flag) +"'");
        }
    }

    // returns 0 if execution needs to start otherwise returns 1
    inline static int HANDLE_CMD_ARGUMENTS(int argc, char **argv)
    {
        std::string_view source_file_name;

        if (argc > 1)
        {
            // checking if the terminal is passed with --version parameter: sronc --version
            if ( std::strcmp(argv[1], "--version") == 0)
            {
                puts(SRON_VERSION_MESSAGE);

                return 1;
            }
        
            else source_file_name = argv[1];
                        
        }
        else  throw SronError::FileNameNotProvidedToCompiler();

        // checking if the extension of the file is .sron or not!
        if (!Support::HAS_SUFFIX(source_file_name.data(), source_file_name.length(), ".sron", 5))
        {
            printf_s("\n =| Only files with extension '.sron'  can be compiled!! |= \n\n");
            return 1;
        }

        Logs::mainfile = new std::ifstream( source_file_name.data());

        if (Logs::mainfile->fail()) throw SronError::SourceCodeFileNotFound();

        Logs::filename= source_file_name;
        
        return 0;
    }

    inline static bool HAS_SUFFIX(const char* __search_on, unsigned int __len1 , const char* __suffix_to_search , unsigned int __len2)
    {
        if (__len1 < __len2) return false;

        const char* it = __search_on + __len1 - __len2;

        while ( *it && *__suffix_to_search )
        {
            if ( *it != *__suffix_to_search ) return false;

            ++it;
            ++__suffix_to_search;
        }

        return *it == *__suffix_to_search;
    }

    // returns the last index of where change is made
    inline static unsigned int REPLACE_CHAR_IN_CHAR_STR(char* __str, char __value_to_be_replaced, char __replacement)
    {
        unsigned int last_index = 0;

        unsigned int current_index = 0;

        while (*__str)
        {
            if ( *__str == __value_to_be_replaced ) 
            {
                *__str = __replacement;

                last_index = current_index;
            }

            ++__str;

            ++current_index;
        }

        return last_index;
    }

    inline static void REPLACE_CHAR_IN_STRING(std::string& __str, char __value_to_be_replaced, char __replacement)
    {
        for(auto& ch : __str ) if ( ch == __value_to_be_replaced ) ch = __replacement;
    }

    // this function returns the lowercase of the character type value
    inline static char TO_LOWER(char ch) noexcept
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            return ch + 32;
        }
        return ch;
    }

    // this function returns the lowercase of the string
    inline static std::string TO_LOWER(const std::string &str) noexcept
    {
        std::string fin = "";

        for (auto i : str)
        {
            fin += std::tolower(i);
        }

        return fin;
    }


    inline static const char* FLAG_TO_STRING(Flag_t __flag) noexcept
    {

        switch(__flag){

            case Flag_Void : return "Void";

            case Flag_Any : return "Any";

            case Flag_Int : return "Int";

            case Flag_Double : return "Double";

            case Flag_Char : return "Char";

            case Flag_String : return "String";

            case Flag_Bool : return "Bool";

            case Flag_List : return "List";

            case Flag_Int_Value : return "Int-value";

            case Flag_Double_Value : return "Double-value";

            case Flag_Char_Value : return "Char-value";

            case Flag_String_Value : return "String-value";

            case Flag_Assign : return "Assign";

            case Flag_Char_Print : return "Console-Char-Print";

            case Flag_String_Print : return "Console-String-Print";

            case Flag_InBuiltFunctionCall : return "In-built Fnc";

            case Flag_FunctionParamScopeStart : return "args{";

            case Flag_FunctionParamScopeEnd : return "args}";

            case Flag_Break : return "break";

            case Flag_Continue : return "continue";

            case Flag_Args_Start : return "(";

            case Flag_Args_End : return ")";

            case Flag_ListStart : return "List-start[";
            
            case Flag_ListEnd : return "]List-end";

            case Flag_Return : return "return";

            case Flag_Identifier_Variable : return "identifier";

            case Flag_RangeScopeStart : return "range{";

            case Flag_RangeScopeEnd : return "range}";

            case Flag_Condition : return "condition";

            case Flag_ForScopeStart : return "for{";

            case Flag_ForScopeEnd : return "for}";

            case Flag_WhileScopeStart : return "while{";

            case Flag_WhileScopeEnd : return "while}";

            case Flag_IfScopeStart : return "if{";

            case Flag_IfScopeEnd : return "if}";

            case Flag_ElifScopeStart : return "elif{";

            case Flag_ElifScopeEnd : return "elif}";

            case Flag_ElseScopeStart : return "else{";

            case Flag_ElseScopeEnd : return "else}";

            case Flag_EvalStart : return "Eval-start";

            case Flag_EvalEnd : return "Eval-End";

            case Flag_RotateScopeStart : return "rotate{";

            case Flag_RotateScopeEnd : return "rotate}";

            case Flag_ConsoleStart : return "console{";

            case Flag_ConsoleEnd : return "console}";

            case Flag_Operator : return "operator";

            case Flag_Add : return "+";

            case Flag_Minus : return "-";

            case Flag_Mult : return "*";

            case Flag_Div : return "/";

            case Flag_Mod : return "%";

            case Flag_Pow : return "^";

            case Flag_And : return "&&";

            case Flag_Or : return "||";

            case Flag_Not : return "!";

            case Flag_NotEqual : return "!=";

            case Flag_Compare : return "==";

            case Flag_LessThan : return "<";

            case Flag_LessThanEqual : return "<=";

            case Flag_MoreThan : return ">";

            case Flag_MoreThanEqual : return ">=";

            case Flag_StrictCompare : return "===";

            case Flag_AddAssign : return "+=";

            case Flag_MinusAssign : return "-=";

            case Flag_MultAssign : return "*=";

            case Flag_DivAssign : return "/=";

            case Flag_ModAssign : return "%=";

            case Flag_PowAssign : return "^=";

            case Flag_UserDefinedFunctionCall : return "user-defined-FNC";

            case Flag_Negate : return "Negate";

            case Flag_IntExtractor : return "Int-Extractor";

            case Flag_DoubleExtractor : return "Double-Extractor";

            case Flag_CharExtractor : return "Char-Extractor";

            case Flag_BoolExtractor : return "Bool-Extractor";

            case Flag_StringExtractor : return "String-Extractor";

            case Flag_ListExtractor : return "List-Extractor";

            case Flag_UnaryOperator : return "Unary-Operator";

            case Flag_CodeCompleted : return "Code-done";

            case Flag_True : return "true";

            case Flag_False : return "false";

            case Flag_StrictInt : return "StrictInt";

            case Flag_StrictDouble : return "StrictDouble";

            case Flag_StrictChar : return "StrictChar";

            case Flag_StrictBool : return "StrictBool";

            case Flag_StrictString : return "StrictString";

            case Flag_StrictList : return "StrictList";

            case Flag_BitwiseAnd : return "Bitwise-and";

            case Flag_BitwiseOr : return "Bitwise-or";

            case Flag_BitwiseNot : return "Bitwise-not";

            case Flag_Lshift : return "Bitwise-LeftShift";

            case Flag_Rshift : return "Bitwise-RightShift";

            case Flag_Xor : return "Bitwise-Xor";

            case Flag_FunctionName : return "Function-name";

            case Flag_ReturnType : return "return-type";

            case Flag_ForeachScopeStart : return "foreach{";

            case Flag_ForeachScopeEnd : return "foreach}";

            case Flag_ForeachOn : return "foreach-ON";

            case Flag_OBuffer : return "Obuffer";

            case Flag_bydefault : return "default-flag";
        
        }
        return "Unidentified-Flag";
    }

    inline static Flag_t GET_EQUIVALENT_DATATYPE_EXTRACTOR(Flag_t __flag){

        switch(__flag){

            case Flag_Int : return Flag_IntExtractor;

            case Flag_Double : return Flag_DoubleExtractor;

            case Flag_Char : return Flag_CharExtractor;

            case Flag_Bool : return Flag_BoolExtractor;

            case Flag_String : return Flag_StringExtractor;

            case Flag_List : return Flag_ListExtractor;

            case Flag_Any : return Flag_Any;

            default : throw ThrowException("extracting the extractor-flag for flag '"+std::to_string(__flag)+"'");
        }

        return __flag;
    }

    inline static const char* TYPE_TO_STRING(unsigned short int __type) noexcept{

        switch(__type){

            case TYPE_VOID : return "<Void>";
            case TYPE_INT : return "<Int>";
            case TYPE_DOUBLE : return "<Double>";
            case TYPE_BOOL : return "<Bool>";
            case TYPE_CHAR : return "<Char>";
            case TYPE_STRING : return "<String>";

            case TYPE_LIST_OPEN : return "<List-open>";
            case TYPE_LIST_CLOSE : return "<List-close>";

            case TYPE_FUNCTION_CALL : return "<FunctionCall>";

            case TYPE_MATH_BLOCK : return "<Math-block>";

            case TYPE_IDENTIFIER : return "<Identifier>";
            case TYPE_IDENTIFIER_WITH_DOT : return "<Identifier-with-dot>";

            case TYPE_DATATYPE : return "<Data-Type>";

            case TYPE_OPERATOR : return "<Operator>";
            case TYPE_ATTRIBUTE : return "<Attribute>";
            case TYPE_KEYWORD : return "<Keyword>";

            case TYPE_OPENING_BRACKETS : return "<OpeningBracket>";
            case TYPE_CLOSING_BRACKETS : return "<ClosingBrackets>";

            case TYPE_FUNCTION_SCOPE_START : return "<FunctionStart>";
            case TYPE_FUNCTION_SCOPE_CLOSE : return "<FunctionClose>";

            case TYPE_COMMA : return "<Comma>";
            case TYPE_ASSIGN : return "<Assign>";
            case TYPE_STRICT_TYPE : return "<Strict-type>";

            case TYPE_NEWLINE : return "<Newline>";

            case TYPE_COLON : return "<Colon>";
            
            case TYPE_CALC_ASSIGN : return "<CalcAssign>";

        }
        return "<Unknown-Type>";
    }

    namespace ImplicitConversion
    {
        constexpr inline static bool VOID_WITH( Flag_t __flag )
        {
            return ( __flag == Flag_Void );
        }

        constexpr inline static bool INT_WITH( Flag_t __flag )
        {
            return ( __flag == Flag_Int_Value || __flag == Flag_Double_Value || __flag == Flag_Char_Value || __flag == Flag_True || __flag == Flag_False );
        }
        
        constexpr inline static bool DOUBLE_WITH( Flag_t __flag )
        {
            return ( __flag == Flag_Double_Value || __flag == Flag_Int_Value || __flag == Flag_True || __flag == Flag_False );
        }

        constexpr inline  static bool CHAR_WITH( Flag_t __flag )
        {
            return ( __flag == Flag_Char_Value || __flag == Flag_Int_Value || __flag == Flag_String_Value );
        }

        constexpr inline static bool BOOL_WITH( Flag_t __flag )
        {
            return ( __flag == Flag_Int_Value || __flag == Flag_True || __flag == Flag_False);
        }

        constexpr inline static bool STRING_WITH( Flag_t __flag )
        {
            return ( __flag == Flag_String_Value );
        }

        constexpr inline static bool LIST_WITH( Flag_t __flag )
        {
            return ( __flag == Flag_ListStart );
        }

        constexpr inline static bool matchImplicitConversion ( Flag_t __datatype , Flag_t __value_to_match_with )
        {
            switch ( __datatype )
            {
                case Flag_Void    :    return ImplicitConversion::VOID_WITH     ( __value_to_match_with );

                case Flag_Int     :    return ImplicitConversion::INT_WITH      ( __value_to_match_with );

                case Flag_Double  :    return ImplicitConversion::DOUBLE_WITH   ( __value_to_match_with );

                case Flag_Char    :    return ImplicitConversion::CHAR_WITH     ( __value_to_match_with ); 

                case Flag_Bool    :    return ImplicitConversion::BOOL_WITH     ( __value_to_match_with ); 

                case Flag_String  :    return ImplicitConversion::STRING_WITH   ( __value_to_match_with ); 

                case Flag_List    :    return ImplicitConversion::LIST_WITH     ( __value_to_match_with );
            }

            throw ThrowException("analyzing the code. [Compiler-Issue] The 'SemanticAnalyzer::fncReturnType' has a invalid datatype flag '" + std::to_string( __datatype ) + "'");
        }

        inline static void THROW_EXCEPTION_IF_RETURNED_VALUE_DOESNOT_MATCH_WITH_RETURN_TYPE ( Flag_t __return_type , SronTokenType_t __type , Flag_t __flag , unsigned long __file_index )
        {
            // by default, the function can return any type of value
            // also checking the return value is a indefinite type of value like function call, identifier, Math block
            // whose final type cannot be detected in a interpreted language like SRON
            if ( __return_type == Flag_bydefault || __return_type == Flag_Any ||
                __type == TYPE_FUNCTION_CALL || __type == TYPE_MATH_BLOCK || __type == TYPE_IDENTIFIER
                ) return;

            else if ( !ImplicitConversion::matchImplicitConversion ( __return_type, __flag ) )
            {
                throw ThrowException( "analyzing the code. The returned value which is of type '" + std::string( Support::FLAG_TO_STRING( __flag ) ) +"' neither matches with the return type '" + std::string( Support::FLAG_TO_STRING( __return_type) ) +"' nor is convertible" , __file_index );
            }
        }
    }
}

#endif
