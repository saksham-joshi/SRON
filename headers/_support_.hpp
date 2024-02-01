#include "_exception_.hpp"

#ifndef SUPPORT_H
#define SUPPORT_H


inline namespace Support
{

    inline static bool IS_ATTRIBUTE(std::string &word)
    {
        return (word == "name" || word == "type" || word == "args" || word == "variables" || word == "if" || word == "elif" || word == "else" || word == "condition" || word == "comment" || word == "return" || word == "for" || word == "range" || word == "while");
    }

    inline static bool IS_DATATYPE(std::string &word)
    {
        return (word == "Any" || word == "Int" || word == "List" || word == "String" || word == "Double" || word == "Char" || word == "Bool");
    }

    inline static bool IS_KEYWORD(std::string &word)
    {
        return (IS_ATTRIBUTE(word) || IS_DATATYPE(word) || word == "main" || word == "PRINT" || word == "PRINTLN" || word == "LEN" ||
                word == "SIZE_OF" || word == "TYPE" || word == "TO_STRING");
    }

    inline static bool IS_CURLY_BRACES(char &ch)
    {
        return (ch == '{' || ch == '}');
    }
    inline static bool IS_SQUARE_BRACKET(char &ch){
        return (ch == '[' || ch == ']');
    }
    inline static bool IS_SCOPE_OPERATOR(char &ch){
        return (IS_CURLY_BRACES(ch) || IS_SQUARE_BRACKET(ch) || ch == '(' || ch == ')');
    }

    inline static bool IS_INNER_SCOPE_ATTRIBUTE(std::string &str)
    {
        return (str == "if" || str == "elif" || str == "else" || str == "for" || str == "while");
    }

    inline static bool IS_MATH_OPERATOR(std::string str){
        return (str == "+" || str == "-" || str == "*" || str == "/" || str == "%" || str == "^" || str == "(" || str == ")");
    }

    inline static bool IS_LOGICAL_OPERATOR(char ch){
        return (ch == '<' || ch == '>' );
    }
    inline static bool IS_LOGICAL_OPERATOR(std::string str){
        return (str == "&&" || str == "||" || str == "<" || str == ">" || str == "<=" || str == ">=");
    }
    inline static bool IS_OPERATOR(char ch){
        return ( IS_MATH_OPERATOR((std::string)""+ch) || IS_LOGICAL_OPERATOR((std::string)""+ch) || ch == ':' || ch == '!' || ch == '=' || ch == '~' || ch == ',' );
    }

    inline static bool is_number(int ch)
    {
        return (ch >= 48 && ch <= 57);
    }
    inline static bool is_alphabet(int ch)
    {
        return ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90));
    }
    inline static bool is_alpha_number(int ch)
    {
        return (is_number(ch) || is_alphabet(ch));
    }

    /*
     * This function is used to check if the passes string is a valid variable name or not.

     * The conditions for a valid variable name are as follows:
     * 1. First letter of the variable can only be an alphabet or an underscore.
     * 2. variable name can only contain alphabetic characters, numbers and underscores.
     * 3. length of the variable cannot exceed limit of 32 characters.
    */
    inline static bool CHECK_VALID_IDENTIFIER_NAME(std::string& str)
    {
        if (!(str[0] == '_' || isalpha(str[0]) > 0 || str.length() <= 32))
        {
            DISPLAY_EXCEPTION("creating a variable named as '"+str+"'.", InvalidVariableNameException);
        }
        for (const auto& it : str)
        {
            if (!(it == '_' || is_alphabet(it) || is_number(it) ))
            {
                DISPLAY_EXCEPTION("creating a variable as '"+str+"'.", InvalidVariableNameException);
            }
        }
        return true;
    }

    /*
     * This function will extract the possible type of variable.
    */
    // inline static const unsigned short int IDENTIFY_TYPE_FROM_STRING(std::string& str){
    //     if(str.length() == 1 && str[0] == '['){
    //         return TYPE_LIST;
    //     }
    //     else if(str.length() > 1 && str[0] == '"'){
    //         return TYPE_STRING;
    //     }
    //     else if(str.length() == 3 && str[0] == '\''){
    //         return TYPE_CHAR;
    //     }
    //     else if(str == "true" || str == "false"){
    //         return TYPE_BOOL;
    //     }
    //     else if(str.length() > 0 && (is_number(str[0]) || str[0] == '.' || str[0] == '-' )){

    //         for(const auto& i : str){
    //             if(i == '.'){
    //                 return TYPE_DOUBLE;
    //             }
    //             else if(!is_number(i)){
    //                 DISPLAY_EXCEPTION("allocating memory for the variables.",InvalidValueException);
    //             }
    //         }
    //         return TYPE_INT;
    //     }
    //     return IDENTIFIER;
    // }
}

#endif