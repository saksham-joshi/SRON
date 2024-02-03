#include "_flags_.hpp"
#include "_exception_.hpp"

#ifndef SUPPORT_H
#define SUPPORT_H


inline namespace Support
{

    inline static const bool IS_INNER_SCOPE_ATTRIBUTE(std::string&);
    inline static const bool IS_INBUILT_ATTRIBUTE(std::string&);
    inline static const bool IS_ATTRIBUTE(std::string &);
    inline static const bool IS_DATATYPE(std::string &);
    inline static const bool IS_KEYWORD(std::string &);
    inline static const bool IS_LOGICAL_OPERATOR(std::string&);
    inline static bool CHECK_VALID_IDENTIFIER_NAME(std::string& );


    inline static const bool is_number(int ch)
    {
        return (ch >= 48 && ch <= 57);
    }

    inline static const bool IS_NUMBER(std::string& str){
        for(const auto& i : str){
            if(!(is_number(i))){
                return false;
            }
        }
        return true;
    }

    inline static const bool is_alphabet(int ch)
    {
        return ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90));
    }
    inline static const bool is_alpha_number(int ch)
    {
        return (is_number(ch) || is_alphabet(ch));
    }

    inline static const bool IS_INNER_SCOPE_ATTRIBUTE(std::string &str)
    {
        return (str == AttributeIf || str == AttributeElif || str == AttributeElse || str == AttributeFor || str == AttributeWhile);
    }

    inline static const bool IS_INBUILT_ATTRIBUTE(std::string &str){
        return (IS_INNER_SCOPE_ATTRIBUTE(str) || str == AttributeName || str == AttributeType || str == AttributeArgs 
        || str == AttributeComment || str == AttributeCondition || str == AttributeRange || AttributeReturn || AttributeVariables);
    }

    inline static const bool IS_ATTRIBUTE(std::string &word)
    {
        if(IS_INBUILT_ATTRIBUTE(word)){
            return true;
        }
        return IS_NUMBER(word);
    }

    inline static const bool IS_DATATYPE(std::string &word)
    {
        return (word == "Any" || word == "Int" || word == "List" || word == "String" || word == "Double" || word == "Char" || word == "Bool");
    }

    inline static const bool IS_KEYWORD(std::string &word)
    {
        return (IS_INBUILT_ATTRIBUTE(word) || IS_DATATYPE(word) || IS_LOGICAL_OPERATOR(word) || word == "MAIN" || word == "PRINT" || word == "PRINTLN" || word == "LEN" ||
                word == "SIZE_OF" || word == "TYPE" || word == "TO_STRING");
    }

    inline static const bool IS_CURLY_BRACES(char &ch)
    {
        return (ch == '{' || ch == '}');
    }
    inline static const bool IS_CURLY_BRACES(std::string& str){
        return (str == "{" || str == "}");
    }

    inline static const bool IS_SQUARE_BRACKET(char &ch){
        return (ch == '[' || ch == ']');
    }

    inline static const bool IS_SCOPE_OPERATOR(char &ch){
        return (IS_CURLY_BRACES(ch) || IS_SQUARE_BRACKET(ch) || ch == '(' || ch == ')');
    }
    inline static const bool IS_MATH_OPERATOR(char &ch){
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '(' || ch == ')');
    }
    inline static const bool IS_MATH_OPERATOR(std::string& str){
        return (str.length()==1)?IS_MATH_OPERATOR(str[0]):false ;
    }
    
    inline static const bool IS_LOGICAL_OPERATOR(std::string& str){
        return (str == "and" || str == "or" || str == "not");
    }

    inline static const bool IS_COMPARISON_OPERATOR(std::string& str){
        return (str == "==" || str == "<" || str == ">" || str == "<=" || str == ">=");
    }
    inline static const bool IS_OPERATOR(char& ch){
        return (IS_MATH_OPERATOR(ch) || ch == ':' || ch =='=' || ch == '~' || ch == ',' );
    }
    inline static const bool IS_OPERATOR(std::string& str){
        return (IS_MATH_OPERATOR(str) || IS_LOGICAL_OPERATOR(str) || IS_COMPARISON_OPERATOR(str)  || IS_OPERATOR(str[0]));
    }
    

    
    /*
     * This function is used to check if the passes string is a valid variable name or not.

     The conditions for a valid variable name are as follows:
     * 1. First letter of the variable can only be an alphabet or an underscore.
     * 2. variable name can only contain alphabetic characters, numbers and underscores.
     * 3. length of the variable cannot exceed limit of 32 characters.
    */
    inline static bool CHECK_VALID_IDENTIFIER_NAME(std::string& str)
    {
        try{
            if(IS_KEYWORD(str)){
                DISPLAY_EXCEPTION("creating a variable named as '"+str+"'.",InvalidVariableNameException);
            }
            if (!(str[0] == '_' || isalpha(str[0]) > 0 || str.length() <= 32))
            {
                throw "creating a variable named as '"+str+"'.";
            }
            for (const auto& it : str)
            {
                if (!(it == '_' || is_alphabet(it) || is_number(it) ))
                {
                    throw "creating a variable named as '"+str+"'.";
                }
            }
            return true;
        }
        catch(const std::string& str){
            DISPLAY_EXCEPTION(str, InvalidVariableNameException);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("verifying the identifier.",SystemOutofMemoryException);
        }
        return false;
    }

    /*
     * This function will extract the possible type of variable.
    */
    inline static const unsigned short int IDENTIFY_TYPE_FROM_STRING(const std::string& str){
        if(str.length() == 1 && str[0] == '['){
            return TYPE_LIST;
        }
        else if(str.length() > 1 && str[0] == '"'){
            return TYPE_STRING;
        }
        else if(str.length() == 3 && str[0] == '\''){
            return TYPE_CHAR;
        }
        else if(str == "true" || str == "false"){
            return TYPE_BOOL;
        }
        else if(str.length() > 0 && (is_number(str[0]) || str[0] == '.' || (str[0] == '-' && str.length() >1 && (is_number(str[1]) || str[1] == '.')) )){
             auto it = str.begin();
            if(*it == '-'){
                ++it;
            }
            for(; it < str.end() ; ++it){
                if(*it == '.'){
                    return TYPE_DOUBLE;
                }
            }
            return TYPE_INT;
        }
        return IDENTIFIER;
    }

    inline static const bool IS_VALID_END(std::string& str){
        return (str == "\n" || str == "}");
    }
    inline static const bool IS_VALID_END(char &ch){
        return (ch == '\n' || ch == '}');
    }

    inline static const unsigned short int GET_TYPE_NUMBER(std::string& str){
        if(str == "Int"){
            return TYPE_INT;
        }
        else if(str == "Double"){
            return TYPE_DOUBLE;
        }
        else if(str == "Char"){
            return TYPE_CHAR;
        }
        else if(str == "String"){
            return TYPE_STRING;
        }
        else if(str == "Bool"){
            return TYPE_BOOL;
        }
        else if(str == "List"){
            return TYPE_LIST;
        }
        return IDENTIFIER;
    }
}

#endif