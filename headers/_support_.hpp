// #include <cstdio>
// #include "_converter_.hpp"

// inline namespace Support
// {

//     /*
//      * This function is used to check if the passed string is a number or not.
//      * It will specify the SRON's Executor to execute that particular line.
//      */
//     inline static bool CHECK_IF_ATTRIBUTE_IS_NUMBER(std::string str)
//     {
//         for (std::string::iterator it = str.begin(); it < str.end(); ++it)
//         {
//             if ((int)*it >= 48 && (int)*it <= 57)
//             {
//                 continue;
//             }
//             return false;
//         }
//         return true;
//     }
//     /*
//      * This function is used to check if the passes string is a valid variable name or not.

//      * The conditions for a valid variable name are as follows:
//      * 1. First letter of the variable can only be an alphabet or an underscore.
//      * 2. variable name can only contain alphabetic characters, numbers and underscores.
//      * 3. length of the variable cannot exceed limit of 32 characters.
//     */
//     inline static bool CHECK_VALID_VARIABLE_NAME(string str)
//     {
//         if (!(str[0] == '_' || isalpha(str[0]) > 0 || str.length() <= 32))
//         {
//             DISPLAY_EXCEPTION("creating a variable.", 2);
//         }
//         for (string::iterator it = str.begin() + 1; it < str.end(); ++it)
//         {
//             if (!(*it == '_' || isalpha(*it) > 0 || ((int)*it >= 48 && (int)*it <= 57)))
//             {
//                 DISPLAY_EXCEPTION("creating a variable.", 2);
//             }
//         }
//         return true;
//     }

//     /*
//      * This function will check if the given string is eligible to become an Int value.
//      */
//     inline static bool CHECK_VALID_INT_VALUE(string str)
//     {
//         return CHECK_IF_ATTRIBUTE_IS_NUMBER(str);
//     }

//     /*
//      * This function will check if the given string is eligible to become a Double value.
//      */
//     inline static bool CHECK_VALID_DOUBLE_VALUE(string str)
//     {
//         try
//         {
//             bool flag = false;
//             for (auto it = str.begin(); it != str.end(); ++it)
//             {
//                 if (*it == '.')
//                 {
//                     if (flag)
//                     {
//                         return false;
//                     }
//                     flag = true;
//                 }
//                 if ( ( (int)*it >= 48 && (int)*it <= 57 )  || *it == '.' )
//                 {
//                     continue;
//                 }
//                 return false;
//             }
//             return true;
//         }
//         catch (const std::exception &)
//         {
//             DISPLAY_EXCEPTION("validating a Double value.", 15);
//         }
//         return true;
//     }

//     /*
//      * This function will check if the given string is eligible to become a Char value.
//      */
//     inline static bool CHECK_VALID_CHAR_VALUE(string str)
//     {
//         if (!((str.length() == 2 && str[0] == '\'' && str[1] == '\'') || (str.length() == 3 && str[0] == '\'' && str[2] == '\'')))
//         {
//             DISPLAY_EXCEPTION("validating a Char value.", 15);
//         }
//         return true;
//     }

//     /*
//      * This function will check if the given string is eligible to become a String value.
//      */
//     inline static bool CHECK_VALID_STRING_VALUE(string str)
//     {
//         if (!((str.length() == 2 && str[0] == '\"' && str[1] == '\"') || (str.length() > 2 && str[0] == '\"' && str[str.length() - 1] == '\"')))
//         {
//             DISPLAY_EXCEPTION("validating a String value.", 15);
//         }
//         return true;
//     }

//     /*
//      * This function will check if the given string is eligible to become a Bool value.
//      */
//     inline static bool CHECK_VALID_BOOL_VALUE(string str)
//     {
//         if (!(str == "true" || str == "false"))
//         {
//             DISPLAY_EXCEPTION("validating a Bool value.", 15);
//         }
//         return true;
//     }

//     /*
//      * This function will identify the type of passed string.

//      * This function will be used by executor when user provides direct const values to functions.
//     */
//     inline static string IDENTIFY_TYPE_FROM_STRING(string str)
//     {
//         if (CHECK_VALID_INT_VALUE(str))
//         {
//             return "Int";
//         }
//         else if (CHECK_VALID_DOUBLE_VALUE(str))
//         {
//             return "Double";
//         }
//         else if (str.length() >= 1 && str[0] == '\"' && str[str.length() - 1] == '\"')
//         {
//             return "String";
//         }
//         else if ((str.length() == 3 || str.length() == 2) && str[0] == '\'' && str[str.length() - 1] == '\'')
//         {
//             return "Char";
//         }
//         else if (str == "true" || str == "false")
//         {
//             return "Bool";
//         }
//         str = "identifying the value \'" + str + '\'';
//         DISPLAY_EXCEPTION(str.c_str(), 26);
//         return " ";
        
//     }
// }

#ifndef SUPPORT_H
#define SUPPORT_H


inline static bool IS_ATTRIBUTE(std::string word){
     return (word == "name" || word == "type" || word == "args" || word == "variables" || word == "if" || word == "elif" || word == "else"
     || word == "condition" || word == "comment" || word == "return" || word == "for" || word == "range" || word == "while");
}

inline static bool IS_DATATYPE(std::string word){
    return (word == "Any" || word == "Int" || word == "List" || word == "String" || word == "Double" || word == "Char"  || word == "Bool");
}

inline static bool IS_KEYWORD(std::string word){
     return (IS_ATTRIBUTE(word) || IS_DATATYPE(word) || word == "main" || word == "PRINT" || word == "PRINTLN" || word == "LEN" || 
     word == "SIZE_OF" || word == "TYPE" || word == "TO_STRING");
}

inline static bool IS_CURLY_BRACES(char ch){
    return (ch == '{' || ch == '}');
}

inline static bool is_number(int ch){
    return (ch>=48 && ch<=57);
}
inline static bool is_alphabet(int ch){
    return ((ch >=97 && ch <= 122) || (ch>= 65 && ch <= 90));
}
inline static bool is_alpha_number(int ch){
    return (is_number(ch) || is_alphabet(ch));
}

#endif