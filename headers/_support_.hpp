#ifndef SUPPORT_H
#define SUPPORT_H

#include "_flags_.hpp"
#include "_exception_.hpp"

inline namespace Support
{
    inline static bool IS_INNER_SCOPE_ATTRIBUTE(std::string &);
    inline static bool IS_INBUILT_ATTRIBUTE(std::string &);
    inline static bool IS_ATTRIBUTE(std::string &);
    inline static bool IS_DATATYPE(std::string &);
    inline static bool IS_KEYWORD(std::string &);
    inline static bool IS_LOGICAL_OPERATOR(std::string &);
    inline static bool CHECK_VALID_IDENTIFIER_NAME(std::string &);
    inline static unsigned short int IDENTIFY_TYPE_FROM_STRING(std::string &);
    inline static bool IS_UNSIGNED_INTEGER(std::string &);

    inline static char TO_LOWER(char &);
    inline static std::string TO_LOWER(std::string);

    inline static bool is_number(int ch)
    {
        return (ch >= 48 && ch <= 57);
    }

    inline static bool IS_NUMBER(std::string &str)
    {
        for (const auto &i : str)
        {
            if (!(is_number(i)))
            {
                return false;
            }
        }
        return true;
    }

    // This will return true if the string is number. Even if it is not decimal, it will return true
    inline static bool IS_DECIMAL_NUMBER(const std::string &str)
    {
        char ch = str[0];
        if ((ch >= '0' && ch <= '9'))
        {
            return true;
        }
        else if ((ch == '.' || ch == '-') && str.length() > 1 && ((str[1] >= '0' && str[1] <= '9') || str[1] == '.'))
        {
            return true;
        }
        return false;
    }

    inline static bool is_alphabet(int ch)
    {
        return ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90));
    }
    inline static bool is_alpha_number(int ch)
    {
        return (is_number(ch) || is_alphabet(ch));
    }

    inline static bool IS_INNER_SCOPE_ATTRIBUTE(std::string &str)
    {
        return (str == AttributeIf || str == AttributeElif || str == AttributeElse || str == AttributeFor || str == AttributeWhile);
    }

    inline static bool IS_INBUILT_ATTRIBUTE(std::string &str)
    {
        return (IS_INNER_SCOPE_ATTRIBUTE(str) || str == AttributeName || str == AttributeType || str == AttributeArgs || str == AttributeComment || str == AttributeCondition || str == AttributeRange || AttributeReturn || AttributeVariables);
    }

    inline static bool IS_ATTRIBUTE(std::string &word)
    {
        if (IS_INBUILT_ATTRIBUTE(word))
        {
            return true;
        }
        return IS_NUMBER(word);
    }

    inline static bool IS_DATATYPE(std::string &word)
    {
        return (word == "Any" || word == "Int" || word == "List" || word == "String" || word == "Double" || word == "Char" || word == "Bool");
    }

    inline static bool IS_KEYWORD(std::string &word)
    {
        return (IS_INBUILT_ATTRIBUTE(word) || IS_DATATYPE(word) || IS_LOGICAL_OPERATOR(word) || word == "MAIN" || word == "PRINT" || word == "PRINTLN" || word == "LEN" ||
                word == "SIZE_OF" || word == "TYPE" || word == "TO_STRING" || word == "break" || word == "continue");
    }

    inline static bool IS_CURLY_BRACES(char &ch)
    {
        return (ch == '{' || ch == '}');
    }
    inline static bool IS_CURLY_BRACES(std::string &str)
    {
        return (str == "{" || str == "}");
    }

    inline static bool IS_IDENTIFIER(const std::string &str)
    {
        return str.length() > 0 && (str[0] == '_' || is_alphabet(str[0]));
    }

    inline static bool IS_SQUARE_BRACKET(char &ch)
    {
        return (ch == '[' || ch == ']');
    }

    inline static bool IS_SCOPE_OPERATOR(char &ch)
    {
        return (IS_CURLY_BRACES(ch) || IS_SQUARE_BRACKET(ch) || ch == '(' || ch == ')');
    }
    inline static bool IS_MATH_OPERATOR(const char &ch)
    {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '(' || ch == ')');
    }
    inline static bool IS_MATH_OPERATOR(const std::string &str)
    {
        return (str.length() == 1) ? IS_MATH_OPERATOR(str[0]) : false;
    }

    inline static bool IS_LOGICAL_OPERATOR(std::string &str)
    {
        return (str == "&&" || str == "||" || str == "!");
    }
    inline static bool IS_COMPARISON_OPERATOR(std::string &str)
    {
        return (str == "==" || str == "!=" || str == "<" || str == ">" || str == "<=" || str == ">=");
    }
    inline static bool IS_OPERATOR(char &ch)
    {
        return (IS_MATH_OPERATOR(ch) || ch == ':' || ch == '=' || ch == '~' || ch == ',' || ch == '!');
    }
    inline static bool IS_OPERATOR(std::string &str)
    {
        return (IS_MATH_OPERATOR(str) || IS_LOGICAL_OPERATOR(str) || IS_COMPARISON_OPERATOR(str) || IS_OPERATOR(str[0]));
    }

    inline static int PRECEDENCE(char &ch)
    {
        switch (ch)
        {
        case '^':
            return 3;
        case '/':
        case '*':
        case '%':
            return 2;
        case '+':
        case '-':
            return 1;
        case '!':
            return 0;
        }
        return 0;
    }
    inline static int PRECEDENCE(std::string &str)
    {
        if (str == "(" || str == ")")
        {
            return 9;
        }
        else if (str == "!")
        {
            return 8;
        }
        else if (str == "^")
        {
            return 7;
        }
        else if (str == "*" || str == "/" || str == "%")
        {
            return 6;
        }
        else if (str == "+" || str == "-")
        {
            return 5;
        }
        else if (str == "==" || str == "!=")
        {
            return 4;
        }
        else if (str == ">" || str == ">=" || str == "<" || str == "<=")
        {
            return 3;
        }
        else if (str == "&&")
        {
            return 2;
        }
        else if (str == "||")
        {
            return 1;
        }
        return 0;
    }

    /*
     * This function is used to check if the passes string is a valid variable name or not.

     The conditions for a valid variable name are as follows:
     * 1. First letter of the variable can only be an alphabet or an underscore.
     * 2. variable name can only contain alphabetic characters, numbers and underscores.
     * 3. length of the variable cannot exceed limit of 32 characters.
    */
    inline static bool CHECK_VALID_IDENTIFIER_NAME(std::string &str)
    {
        try
        {
            if (IS_KEYWORD(str))
            {
                DISPLAY_EXCEPTION("creating a variable named as '" + str + "'.", InvalidVariableNameException);
            }
            if (!(str[0] == '_' || isalpha(str[0]) > 0 || str.length() <= 32))
            {
                throw "creating a variable named as '" + str + "'.";
            }
            for (const auto &it : str)
            {
                if (!(it == '_' || is_alphabet(it) || is_number(it)))
                {
                    throw "creating a variable named as '" + str + "'.";
                }
            }
            return true;
        }
        catch (const std::string &str)
        {
            DISPLAY_EXCEPTION(str, InvalidVariableNameException);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("verifying the identifier.", SystemOutofMemoryException);
        }
        return false;
    }

    /*
     * This function will extract the possible type of variable from the given token after tokenizing process.
     */
    inline static unsigned short int IDENTIFY_TYPE_FROM_STRING(std::string &str)
    {
        if (str.length() == 1 && str[0] == '[')
        {
            return TYPE_LIST;
        }
        else if (str.length() > 1 && str[0] == '"')
        {
            return TYPE_STRING;
        }
        else if (str.length() == 3 && str[0] == '\'')
        {
            return TYPE_CHAR;
        }
        else if (str == "true" || str == "false")
        {
            return TYPE_BOOL;
        }
        else if (str.length() > 0 && (is_number(str[0]) || str[0] == '.' || (str[0] == '-' && str.length() > 1 && (is_number(str[1]) || str[1] == '.'))))
        {
            auto it = str.begin();
            if (*it == '-')
            {
                ++it;
            }
            for (; it < str.end(); ++it)
            {
                if (*it == '.')
                {
                    return TYPE_DOUBLE;
                }
            }
            return TYPE_INT;
        }
        else if (Support::IS_OPERATOR(str))
        {
            return TYPE_OPERATOR;
        }
        return IDENTIFIER;
    }

    // this function will return true if the passed std::string is a possible endings of a line
    // it returns true if str is "\n" or "}"
    inline static bool IS_VALID_END(std::string &str)
    {
        return (str == "\n" || str == "}");
    }
    inline static bool IS_VALID_END(char &ch)
    {
        return (ch == '\n' || ch == '}');
    }

    inline static unsigned short int GET_TYPE_NUMBER(std::string &str)
    {
        if (str == "Int")
        {
            return TYPE_INT;
        }
        else if (str == "Double")
        {
            return TYPE_DOUBLE;
        }
        else if (str == "Char")
        {
            return TYPE_CHAR;
        }
        else if (str == "String")
        {
            return TYPE_STRING;
        }
        else if (str == "Bool")
        {
            return TYPE_BOOL;
        }
        else if (str == "List")
        {
            return TYPE_LIST;
        }
        return IDENTIFIER;
    }

    // this function returns the lowercase of the character type value
    inline static char TO_LOWER(char &val)
    {
        int ch = (int)val;
        if (ch >= 65 && ch <= 90)
        {
            return ch + 32;
        }
        return ch;
    }

    // this function returns the lowercase of the string
    inline static std::string TO_LOWER(std::string str)
    {
        std::string fin = "";
        for (auto i : str)
        {
            fin += TO_LOWER(i);
        }
        return fin;
    }

    inline static bool IS_UNSIGNED_INTEGER(std::string &str)
    {
        for (const auto &i : str)
        {
            if (!Support::is_number(i))
            {
                return false;
            }
        }
        return true;
    }
}

#endif