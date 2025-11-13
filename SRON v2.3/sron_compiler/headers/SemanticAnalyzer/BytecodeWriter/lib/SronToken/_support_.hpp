
#pragma once

#ifndef SUPPORT_H
#define SUPPORT_H

#include "_sron_token_.hpp"

namespace Support
{

    inline static bool COMPARE_STRING_WITHOUT_CASE ( const char* , const char* );

    inline static bool CHECK_VALID_VARIABLE_NAME(const std::string &);

    inline static char GET_RESPECTIVE_CLOSING_CHAR(char);

    inline static BytecodeFlags GET_RESPECTIVE_ENDING_FLAG(BytecodeFlags);

    inline static int HANDLE_CMD_ARGUMENTS(int, char **);

    inline static bool HAS_SUFFIX(const char*, unsigned int, const char*, unsigned int);

    inline static bool IS_HALT_TYPE_FUNCTION(SronToken::TokenElement_t&);

    inline static bool IS_OPERATOR(const char &ch) noexcept;

    inline static bool IS_MATH_OPERATOR(const char &ch) noexcept;

    inline static bool IS_MAIN(SronToken::TokenElement_t&);

    inline static bool IS_NUMBER(int ch) noexcept;

    inline static bool IS_UNARY_OPERATOR(BytecodeFlags) noexcept;

    inline static bool IS_RESERVED_FILENAME(const std::string &__str) noexcept;

    inline static bool IS_SCOPE_OPERATOR(char ch) noexcept;

    inline static bool IS_VALID_END(const unsigned short int type) noexcept;

    inline static bool IS_VALUE_TYPE(const unsigned short int &_type) noexcept;

    inline static unsigned int REPLACE_CHAR_IN_CHAR_STR(char*, char, char);

    inline static void REPLACE_CHAR_IN_STRING(std::string&, char, char);

    inline static char TO_LOWER(char val) noexcept;

    inline static std::string TO_LOWER(const std::string &) noexcept;

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

    inline static bool IS_VALID_END(const SronTokenType type) noexcept
    {
        return (type == SronTokenType::TYPE_NEWLINE || type == SronTokenType::TYPE_FUNCTION_SCOPE_CLOSE);
    }

    inline static bool IS_UNARY_OPERATOR(const BytecodeFlags __flag) noexcept
    {
        return ((__flag == BytecodeFlags::Flag_BitwiseNot ) || (__flag == BytecodeFlags::Flag_Not) || (__flag == BytecodeFlags::Flag_Negate));
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

    inline static bool IS_VALUE_TYPE(const SronTokenType _type) noexcept
    {

        return ( _type == SronTokenType::TYPE_VOID || _type == SronTokenType::TYPE_INT || _type == SronTokenType::TYPE_DOUBLE || 
                 _type == SronTokenType::TYPE_CHAR || _type == SronTokenType::TYPE_STRING || _type == SronTokenType::TYPE_LIST_OPEN || 
                 _type == SronTokenType::TYPE_BOOL || _type == SronTokenType::TYPE_IDENTIFIER || _type == SronTokenType::TYPE_FUNCTION_CALL 
                 || _type == SronTokenType::TYPE_MATH_BLOCK
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

    inline static BytecodeFlags GET_RESPECTIVE_ENDING_FLAG(BytecodeFlags __flag)
    {
        switch(__flag){

            case BytecodeFlags::Flag_IfScopeStart : return BytecodeFlags::Flag_IfScopeEnd;

            case BytecodeFlags::Flag_ElifScopeStart : return BytecodeFlags::Flag_ElifScopeEnd;

            case BytecodeFlags::Flag_ElseScopeStart : return BytecodeFlags::Flag_ElseScopeEnd;

            case BytecodeFlags::Flag_WhileScopeStart : return BytecodeFlags::Flag_WhileScopeEnd;

            case BytecodeFlags::Flag_ForScopeStart : return BytecodeFlags::Flag_ForScopeEnd;

            default : throw ThrowException("retrieving ending flag for flag '" + std::string(SronSupport::flagToString(__flag)) +"'");
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
                std::printf( CLI_COLOR_BRIGHT_CYAN CLI_DESIGN_BOLD SRON_VERSION_MESSAGE CLI_DESIGN_RESET "\n");

                return 1;
            }
        
            else source_file_name = argv[1];
                        
        }
        else  throw SronError::FileNameNotProvidedToCompiler();

        // checking if the extension of the file is .sron or not!
        if (!Support::HAS_SUFFIX(source_file_name.data(), source_file_name.length(), ".sron", 5))
        {
            std::printf("\n =| Only files with extension '.sron'  can be compiled!! |= \n\n");
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


    

    inline static BytecodeFlags GET_EQUIVALENT_DATATYPE_EXTRACTOR( BytecodeFlags __flag){

        switch(__flag){

            case BytecodeFlags::Flag_Int : return BytecodeFlags::Flag_IntExtractor;

            case BytecodeFlags::Flag_Double : return BytecodeFlags::Flag_DoubleExtractor;

            case BytecodeFlags::Flag_Char : return BytecodeFlags::Flag_CharExtractor;

            case BytecodeFlags::Flag_Bool : return BytecodeFlags::Flag_BoolExtractor;

            case BytecodeFlags::Flag_String : return BytecodeFlags::Flag_StringExtractor;

            case BytecodeFlags::Flag_List : return BytecodeFlags::Flag_ListExtractor;

            case BytecodeFlags::Flag_Any : return BytecodeFlags::Flag_Any;

            default : throw ThrowException("extracting the extractor-flag for flag '"+std::string(SronSupport::flagToString(__flag))+"'");
        }

        return __flag;
    }

    inline static const char* TYPE_TO_STRING(const SronTokenType __type) noexcept{

        switch(__type){

            case SronTokenType::TYPE_VOID : return "<Void>";
            case SronTokenType::TYPE_INT : return "<Int>";
            case SronTokenType::TYPE_DOUBLE : return "<Double>";
            case SronTokenType::TYPE_BOOL : return "<Bool>";
            case SronTokenType::TYPE_CHAR : return "<Char>";
            case SronTokenType::TYPE_STRING : return "<String>";

            case SronTokenType::TYPE_LIST_OPEN : return "<List-open>";
            case SronTokenType::TYPE_LIST_CLOSE : return "<List-close>";

            case SronTokenType::TYPE_FUNCTION_CALL : return "<FunctionCall>";

            case SronTokenType::TYPE_MATH_BLOCK : return "<Math-block>";

            case SronTokenType::TYPE_IDENTIFIER : return "<Identifier>";
            case SronTokenType::TYPE_IDENTIFIER_WITH_DOT : return "<Identifier-with-dot>";

            case SronTokenType::TYPE_DATATYPE : return "<Data-Type>";

            case SronTokenType::TYPE_OPERATOR : return "<Operator>";
            case SronTokenType::TYPE_ATTRIBUTE : return "<Attribute>";
            case SronTokenType::TYPE_KEYWORD : return "<Keyword>";

            case SronTokenType::TYPE_OPENING_BRACKETS : return "<OpeningBracket>";
            case SronTokenType::TYPE_CLOSING_BRACKETS : return "<ClosingBrackets>";

            case SronTokenType::TYPE_FUNCTION_SCOPE_START : return "<FunctionStart>";
            case SronTokenType::TYPE_FUNCTION_SCOPE_CLOSE : return "<FunctionClose>";

            case SronTokenType::TYPE_COMMA : return "<Comma>";
            case SronTokenType::TYPE_ASSIGN : return "<Assign>";
            case SronTokenType::TYPE_STRICT_TYPE : return "<Strict-type>";

            case SronTokenType::TYPE_NEWLINE : return "<Newline>";

            case SronTokenType::TYPE_COLON : return "<Colon>";
            
            case SronTokenType::TYPE_CALC_ASSIGN : return "<CalcAssign>";

            default: { }

        }
        return "<Unknown-Type>";
    }

    namespace ImplicitConversion
    {
        constexpr inline static bool VOID_WITH( BytecodeFlags __flag )
        {
            return ( __flag == BytecodeFlags::Flag_Void );
        }

        constexpr inline static bool INT_WITH( BytecodeFlags __flag )
        {
            return ( __flag == BytecodeFlags::Flag_Int_Value || __flag == BytecodeFlags::Flag_Double_Value || __flag == BytecodeFlags::Flag_Char_Value || __flag == BytecodeFlags::Flag_True || __flag == BytecodeFlags::Flag_False );
        }
        
        constexpr inline static bool DOUBLE_WITH( BytecodeFlags __flag )
        {
            return ( __flag == BytecodeFlags::Flag_Double_Value || __flag == BytecodeFlags::Flag_Int_Value || __flag == BytecodeFlags::Flag_True || __flag == BytecodeFlags::Flag_False );
        }

        constexpr inline  static bool CHAR_WITH( BytecodeFlags __flag )
        {
            return ( __flag == BytecodeFlags::Flag_Char_Value || __flag == BytecodeFlags::Flag_Int_Value || __flag == BytecodeFlags::Flag_String_Value );
        }

        constexpr inline static bool BOOL_WITH( BytecodeFlags __flag )
        {
            return ( __flag == BytecodeFlags::Flag_Int_Value || __flag == BytecodeFlags::Flag_True || __flag == BytecodeFlags::Flag_False);
        }

        constexpr inline static bool STRING_WITH( BytecodeFlags __flag )
        {
            return ( __flag == BytecodeFlags::Flag_String_Value );
        }

        constexpr inline static bool LIST_WITH( BytecodeFlags __flag )
        {
            return ( __flag == BytecodeFlags::Flag_ListStart );
        }

        constexpr inline static bool matchImplicitConversion ( BytecodeFlags __datatype , BytecodeFlags __value_to_match_with )
        {
            switch ( __datatype )
            {
                case BytecodeFlags::Flag_Void    :    return ImplicitConversion::VOID_WITH     ( __value_to_match_with );

                case BytecodeFlags::Flag_Int     :    return ImplicitConversion::INT_WITH      ( __value_to_match_with );

                case BytecodeFlags::Flag_Double  :    return ImplicitConversion::DOUBLE_WITH   ( __value_to_match_with );

                case BytecodeFlags::Flag_Char    :    return ImplicitConversion::CHAR_WITH     ( __value_to_match_with ); 

                case BytecodeFlags::Flag_Bool    :    return ImplicitConversion::BOOL_WITH     ( __value_to_match_with ); 

                case BytecodeFlags::Flag_String  :    return ImplicitConversion::STRING_WITH   ( __value_to_match_with ); 

                case BytecodeFlags::Flag_List    :    return ImplicitConversion::LIST_WITH     ( __value_to_match_with );

                default : { }
            }

            throw ThrowException("analyzing the code. [Compiler-Issue] The 'SemanticAnalyzer::fncReturnType' has a invalid datatype flag '" + std::string( SronSupport::flagToString(__datatype) ) + "'");
        }

        inline static void THROW_EXCEPTION_IF_RETURNED_VALUE_DOESNOT_MATCH_WITH_RETURN_TYPE ( BytecodeFlags __return_type , SronTokenType __type , BytecodeFlags __flag , FilePos_t __file_index )
        {
            // by default, the function can return any type of value
            // also checking the return value is a indefinite type of value like function call, identifier, Math block
            // whose final type cannot be detected in a interpreted language like SRON
            if ( __return_type == BytecodeFlags::Flag_bydefault || __return_type == BytecodeFlags::Flag_Any ||
                __type == SronTokenType::TYPE_FUNCTION_CALL || __type == SronTokenType::TYPE_MATH_BLOCK || __type == SronTokenType::TYPE_IDENTIFIER
                ) return;

            else if ( !ImplicitConversion::matchImplicitConversion ( __return_type, __flag ) )
            {
                throw ThrowException( "analyzing the code. The returned value which is of type '" + std::string( SronSupport::flagToString( __flag ) ) +"' neither matches with the return type '" + std::string( SronSupport::flagToString( __return_type) ) +"' nor is convertible" , __file_index );
            }
        }
    }
}

#endif
