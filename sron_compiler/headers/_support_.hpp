
#pragma once

#ifndef SUPPORT_H
#define SUPPORT_H

#include "_flags_.hpp"
#include "_error_.hpp"

inline namespace Support
{
    inline static bool CHECK_VALID_IDENTIFIER_NAME(std::string &);

    inline static void DISPLAY_VERSION() noexcept;

    inline static const char *GET_ENDING_FLAG_OF_CONDITIONAL_STATEMENT(std::string &s) noexcept;

    inline static bool IS_CURLY_BRACES(char &) noexcept;
    inline static bool IS_CURLY_BRACES(std::string &) noexcept;

    inline static bool IS_IDENTIFIER(const std::string &) noexcept;

    inline static bool IS_INNER_SCOPE_ATTRIBUTE(std::string &) noexcept;
    inline static bool IS_INBUILT_ATTRIBUTE(std::string &) noexcept;
    inline static bool IS_ATTRIBUTE(std::string &) noexcept;
    inline static bool IS_VALID_ATTRIBUTE_WITH_ROUND_BRACKETS(std::string &) noexcept;

    inline static bool IS_DATATYPE(std::string &) noexcept;
    inline static bool IS_KEYWORD(std::string &) noexcept;
    inline static bool IS_LOGICAL_OPERATOR(std::string &) noexcept;

    inline static bool IS_SQUARE_BRACKET(char &ch) noexcept;

    inline static char TO_LOWER(char &) noexcept;
    inline static std::string TO_LOWER(std::string) noexcept;

    inline static bool IS_UNSIGNED_INTEGER(std::string &) noexcept;
    inline static bool IS_RESERVED_FILENAME(std::string &) noexcept;

    inline static bool IS_FLAG(std::string &) noexcept;
    inline static bool IS_LOOP_OPENING_FLAG(std::string &str) noexcept;
    inline static bool IS_LOOP_ENDING_FLAG(std::string &str) noexcept;

    inline static bool IS_VALID_ATTRIBUTE_FOR_CONDITION_ATTRIBUTE(std::string &) noexcept;
    inline static bool IS_VALID_FUNCTION_NAME(std::string &) noexcept;

    inline static bool IS_VALID_TYPE_AFTER_OPERATOR(const unsigned short int type) noexcept;
    inline static bool IS_VALID_TYPE_BEFORE_OPERATOR(const unsigned short int type) noexcept;

    inline static int PRECEDENCE(std::string &str) noexcept;

    inline static const char *TYPE_FLAG_TO_STRING(unsigned short int) noexcept;

    inline static void DISPLAY_VERSION() noexcept
    {
        std::cout << "\n"
                     "+----------------------------+\n"
                     "|      SRON version 1.3      |\n"
                     "|  @Author : Saksham Joshi   |\n"
                     "+----------------------------+\n\n";
    }

    // this function will check if the passed value type is valid to be put after assign (=) operator
    inline static bool IS_VALID_TYPE_AFTER_ASSIGN(unsigned short int _type_) noexcept
    {
        return ((_type_ == TYPE_INT) || (_type_ == TYPE_DOUBLE) || (_type_ == TYPE_CHAR) || (_type_ == TYPE_STRING) || (_type_ == TYPE_BOOL) || (_type_ == TYPE_LIST_OPEN) || (_type_ == TYPE_FUNCTION_CALL) || (_type_ == TYPE_IDENTIFIER) || (_type_ == TYPE_MATH_BLOCK));
    }

    // returns true if the passed attribute is 'args' , 'condition' or 'range'.
    inline static bool IS_VALID_ATTRIBUTE_WITH_ROUND_BRACKETS(std::string &attribute) noexcept
    {
        return (attribute == AttributeArgs || attribute == AttributeCondition || attribute == AttributeRange);
    }

    inline static const char *TYPE_FLAG_TO_STRING(unsigned short int _type_) noexcept
    {

        switch (_type_)
        {

        case TYPE_VOID:
            return "Void";
        case TYPE_INT:
            return "Int";
        case TYPE_DOUBLE:
            return "Double";
        case TYPE_STRING:
            return "String";
        case TYPE_CHAR:
            return "Char";
        case TYPE_BOOL:
            return "Bool";
        case TYPE_LIST:
        case TYPE_LIST_OPEN:
        case TYPE_LIST_CLOSE:
            return "List";
        case TYPE_IDENTIFIER:
            return "Identifier";
        case TYPE_OPERATOR:
            return "Operator";
        case TYPE_ATTRIBUTE:
            return "Attribute";
        case TYPE_KEYWORD:
            return "Keyword";
        case TYPE_COLON:
            return "Colon";
        case TYPE_MATH_BLOCK:
            return "MathBlock";
        case TYPE_OPENING_BRACKETS:
            return "OpeningBrackets";
        case TYPE_CLOSING_BRACKETS:
            return "ClosingBrackets";
        case TYPE_FUNCTION_SCOPE_START:
            return "FunctionScopeStart";
        case TYPE_FUNCTION_SCOPE_CLOSE:
            return "FunctionScopeClose";
        case TYPE_FUNCTION_CALL:
            return "FunctionCall";
        case TYPE_NEWLINE:
            return "Newline(\\n) ";
        case TYPE_ASSIGN:
            return "Assign";
        case TYPE_DATATYPE:
            return "DataType";
        case TYPE_COMMA:
            return "Comma";
        }

        return " Cannot identify type flag";
    }

    inline static bool is_number(int ch) noexcept
    {
        return (ch >= 48 && ch <= 57);
    }

    inline static bool IS_NUMBER(std::string &str) noexcept
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
    inline static bool IS_DECIMAL_NUMBER(const std::string &str) noexcept
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

    inline static bool is_alphabet(int ch) noexcept
    {
        return ((ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90));
    }
    inline static bool is_alpha_number(int ch) noexcept
    {
        return (is_number(ch) || is_alphabet(ch));
    }

    inline static bool IS_INNER_SCOPE_ATTRIBUTE(std::string &str) noexcept
    {
        return (str == AttributeIf || str == AttributeElif || str == AttributeElse || str == AttributeFor || str == AttributeWhile);
    }

    inline static bool IS_INBUILT_ATTRIBUTE(std::string &str) noexcept
    {
        return (IS_INNER_SCOPE_ATTRIBUTE(str) || str == AttributeName || str == AttributeArgs || str == AttributeComment || str == AttributeCondition || str == AttributeRange || str == AttributeReturn || str == AttributeVariables);
    }

    inline static bool IS_ATTRIBUTE(std::string &word) noexcept
    {
        if (IS_INBUILT_ATTRIBUTE(word))
        {
            return true;
        }
        return IS_NUMBER(word);
    }

    inline static bool IS_DATATYPE(std::string &word) noexcept
    {
        return (word == "Any" || word == "Int" || word == "List" || word == "String" || word == "Double" || word == "Char" || word == "Bool");
    }

    inline static bool IS_KEYWORD(std::string &word) noexcept
    {
        return (IS_INBUILT_ATTRIBUTE(word) || IS_DATATYPE(word) || word == "MAIN" || word == "break" || word == "continue" || word == "true" || word == "false" || word == "PI");
    }

    inline static bool IS_CURLY_BRACES(char &ch) noexcept
    {
        return (ch == '{' || ch == '}');
    }
    inline static bool IS_CURLY_BRACES(std::string &str) noexcept
    {
        return (str == "{" || str == "}");
    }

    inline static bool IS_IDENTIFIER(const std::string &str) noexcept
    {
        return str.length() > 0 && (str[0] == '_' || is_alphabet(str[0]));
    }

    inline static bool IS_SQUARE_BRACKET(char &ch) noexcept
    {
        return (ch == '[' || ch == ']');
    }

    inline static bool IS_SCOPE_OPERATOR(char &ch) noexcept
    {
        return (IS_CURLY_BRACES(ch) || IS_SQUARE_BRACKET(ch) || ch == '(' || ch == ')');
    }
    inline static bool IS_MATH_OPERATOR(const char &ch) noexcept
    {
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^');
    }
    inline static bool IS_MATH_OPERATOR(const std::string &str) noexcept
    {
        return (str.length() == 1) ? IS_MATH_OPERATOR(str[0]) : false;
    }

    inline static bool IS_LOGICAL_OPERATOR(std::string &str) noexcept
    {
        return (str == "&&" || str == "||" || str == "!");
    }
    inline static bool IS_COMPARISON_OPERATOR(std::string &str) noexcept
    {
        return (str == "==" || str == "!=" || str == "<" || str == ">" || str == "<=" || str == ">=");
    }
    inline static bool IS_OPERATOR(char &ch) noexcept
    {
        return (IS_MATH_OPERATOR(ch) || ch == '=' || ch == '!');
    }
    inline static bool IS_OPERATOR(std::string &str) noexcept
    {
        return (IS_MATH_OPERATOR(str) || IS_LOGICAL_OPERATOR(str) || IS_COMPARISON_OPERATOR(str) || IS_OPERATOR(str[0]));
    }

    inline static bool IS_VALID_FUNCTION_NAME(std::string &fnc_name) noexcept
    {
        return fnc_name.length() < 32 && Support::IS_IDENTIFIER(fnc_name) && (!Support::IS_RESERVED_FILENAME(fnc_name));
    }

    inline static int PRECEDENCE(char &ch) noexcept
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
    inline static int PRECEDENCE(std::string &str) noexcept
    {
        if (str == "!")
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

    // this function returns the lowercase of the character type value
    inline static char TO_LOWER(char &val) noexcept
    {
        int ch = (int)val;
        if (ch >= 65 && ch <= 90)
        {
            return ch + 32;
        }
        return ch;
    }

    // this function returns the lowercase of the string
    inline static std::string TO_LOWER(std::string str) noexcept
    {
        std::string fin = "";
        for (auto i : str)
        {
            fin += TO_LOWER(i);
        }
        return fin;
    }

    inline static bool IS_UNSIGNED_INTEGER(std::string &str) noexcept
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

    /*
    This function returns if the std::string is a reserved file and folder name in
    windows or not. This function will be used by Semantic Analyzer to determine
    a valid file name must be there so that any OS Exception while saving the
    bytecode will not generate.
    */
    inline static bool IS_RESERVED_FILENAME(std::string &str) noexcept
    {
        str = Support::TO_LOWER(str);
        return (
            str == "con" || str == "prn" || str == "aux" || str == "nul" || str == "com0" || str == "com1" || str == "com2" || str == "com3" || str == "com4" || str == "com5" || str == "com6" || str == "com7" || str == "com8" || str == "com9" || str == "lpt0" || str == "lpt1" || str == "lpt2" || str == "lpt3" || str == "lpt4" || str == "lpt5" || str == "lpt6" || str == "lpt7" || str == "lpt8" || str == "lpt9");
    }

    // this function will return if the passed is a flag or not!
    inline static bool IS_FLAG(std::string &str) noexcept
    {

        /*
        Suppose a case when user creates a char value '`' then the
        interpreter may consider it as flag that's why this condition
        is mentioned here that if the passed std::string is tilt(`),
        then it can't be a flag.
        */
        if (str.length() == 0 || str == "`" || str[0] != '`')
        {
            return false;
        }
        return true;
    }

    inline static bool IS_LOOP_OPENING_FLAG(std::string &str) noexcept
    {
        return (str == Flag_ForScopeStart || str == Flag_WhileScopeStart);
    }
    inline static bool IS_LOOP_ENDING_FLAG(std::string &str) noexcept
    {
        return (str == Flag_ForScopeEnd || str == Flag_WhileScopeEnd);
    }

    inline static const char *GET_LOOP_ENDING_FLAG(const std::string &flag) noexcept
    {
        return (flag == Flag_WhileScopeStart) ? Flag_WhileScopeEnd : Flag_ForScopeEnd;
    }

    inline static const char *GET_ENDING_FLAG_OF_CONDITIONAL_STATEMENT(std::string &str) noexcept
    {
        if (str == Flag_IfScopeStart)
        {
            return Flag_IfScopeEnd;
        }
        else if (str == Flag_ElifScopeStart)
        {
            return Flag_ElifScopeEnd;
        }
        return Flag_ElseScopeEnd;
    }

    inline static bool IS_VALID_ATTRIBUTE_FOR_CONDITION_ATTRIBUTE(std::string &str) noexcept
    {
        return (str == AttributeIf || str == AttributeWhile || str == AttributeElif);
    }

    inline static bool IS_VALID_TYPE_AFTER_OPERATOR(const unsigned short int _type_) noexcept
    {
        return ((_type_ == TYPE_INT) || (_type_ == TYPE_DOUBLE) || (_type_ == TYPE_CHAR) || (_type_ == TYPE_STRING) || (_type_ == TYPE_BOOL) || (_type_ == TYPE_LIST_OPEN) || (_type_ == TYPE_FUNCTION_CALL) || (_type_ == TYPE_IDENTIFIER) || (_type_ == TYPE_CLOSING_BRACKETS));
    }
    inline static bool IS_VALID_TYPE_BEFORE_OPERATOR(const unsigned short int _type_) noexcept
    {
        return ((_type_ == TYPE_INT) || (_type_ == TYPE_DOUBLE) || (_type_ == TYPE_CHAR) || (_type_ == TYPE_STRING) || (_type_ == TYPE_BOOL) || (_type_ == TYPE_LIST_CLOSE) || (_type_ == TYPE_IDENTIFIER) || (_type_ == TYPE_CLOSING_BRACKETS) || (_type_ == TYPE_OPENING_BRACKETS));
    }
}
#endif