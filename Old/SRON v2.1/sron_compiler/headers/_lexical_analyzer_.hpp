#pragma once

#ifndef _LEX_H
#define _LEX_H

#include "SemanticAnalyzer/_semantic_analyzer_.hpp"

namespace LexicalAnalyzer
{

    // contains the whole content of the source code
    std::string filecode;

    std::string temp_string;

    std::string::const_iterator fileStart;

    // the iterator on the content of the source code
    std::string::const_iterator iterator;

    // the end iterator on the content of the source code
    std::string::const_iterator fileEnd;

    TokenVector tokenVector;

    std::stack<char> scope_stack;

    // temporary object of SronToken
    static SronToken tokenObject;

    bool inside_math_expression = false;

    inline static void FOUND_ALPHABET_OR_UNDERSCORE();
    inline static void FOUND_ASSIGN();
    inline static void FOUND_DOUBLE_QUOTE();
    inline static void FOUND_MINUS();
    inline static void FOUND_NEWLINE();
    inline static void FOUND_NUMBER();
    inline static void FOUND_OPERATOR();
    inline static void FOUND_SINGLE_QUOTE();
    inline static void FOUND_WAVE();
    inline static void FOUND_SCOPE_CLOSE();
    inline static void FOUND_SCOPE_OPERATOR();

    inline static void FUNCTION_TOKENIZATION_DONE();

    inline static unsigned long GET_SOURCE_CODE_INDEX();

    inline static TokenVector::iterator GET_LAST_TOKEN_ADDRESS();

    inline static void JUMP_ITERATOR_ABOVE_SPACES() noexcept;
    inline static int JUMP_ITERATOR_TO_CHARACTER(const char &) noexcept;

    inline static void MOVE_ITERATOR_TO_WHERE_CODE_STARTS();

    inline static void RESET_TOKEN_OBJECT() noexcept;

    inline static void TOKENIZER();

    inline static void UPDATE_LAST_TOKEN_IF_IDENTIFIER();

    inline static void UPDATE_TOKEN_OBJECT(const short unsigned int &type, const char *const &token, flag_t flag) noexcept
    {

        using LexicalAnalyzer::tokenObject;

        tokenObject._type = type;
        tokenObject._flag = flag;
        tokenObject._token = token;
        tokenObject._file_index = LexicalAnalyzer::GET_SOURCE_CODE_INDEX();
    }

    /*
        /===> Implementation of above defined function ...
    */

    inline static void FOUND_ALPHABET_OR_UNDERSCORE()
    {
        using LexicalAnalyzer::iterator;
        using LexicalAnalyzer::temp_string;
        using LexicalAnalyzer::tokenVector;

        auto if_valid_identifier_character = [](const short unsigned int ch)
        {
            return ((ch >= 48 && ch <= 57) || (ch >= 97 && ch <= 122) || (ch >= 65 && ch <= 90) || (ch == '.' || ch == '_'));
        };

        temp_string += *iterator++;

        // used to verify if there in dot inside the identifier
        bool __dot__ = false;

        while (iterator < LexicalAnalyzer::fileEnd && if_valid_identifier_character(*iterator))
        {
            __dot__ = (*iterator == '.');
            temp_string += *iterator;
            ++iterator;
        }

        // checking if it is a predefined token in the token_map
        const auto &it = TokenMaps::token_map.find(temp_string.c_str());

        if (it != TokenMaps::token_map.end())
        {
            LexicalAnalyzer::tokenObject = it->second;
        }
        // if the last token is a datatype so there must be a variable declaration, therefore it is needed
        // to add the variable name to the SemanticAnalyzer::variableList...
        else if (LexicalAnalyzer::GET_LAST_TOKEN_ADDRESS()->_type == TYPE_DATATYPE)
        {

            // it may be possible that the temp_string contains dot (.) or maybe its length
            // is larger than 32 so to reduce this issue.
            SemanticAnalyzer::THROW_ERROR_IF_INVALID_VARIABLE_NAME(__dot__, temp_string);

            // updating the LexicalAnalyzer::tokenObject
            LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_IDENTIFIER, temp_string.c_str(), Flag_Identifier_Variable);
        }
        else
        {
            LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_IDENTIFIER, temp_string.c_str(), Flag_Identifier_Variable);
        }
        // if the variable is already declared before...
        // else if (SemanticAnalyzer::IS_A_DECLARED_VARIABLE(temp_string))
        // {
        //     LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_IDENTIFIER, temp_string.c_str(), Flag_Identifier_Variable);
        // }

        // if the identifier is not a KEYWORD, EXISTING VARIABLE or a VARIABLE DECLARE then
        // either it is a Function Call or a function declaration or an invalid non-identified identifier...

        --iterator;
    }

    // this function is called when '=' is found by LexicalAnalyzer::TOKENIZER() ...
    inline static void FOUND_ASSIGN()
    {

        auto &__last_token = LexicalAnalyzer::tokenVector.back();

        if ((__last_token._type == TYPE_OPERATOR || __last_token._type == TYPE_ASSIGN) && __last_token._token.LEN() == 1)
        {

            switch (__last_token._token[0])
            {

            case '+':

            case '-':

            case '*':

            case '/':

            case '%':

            case '^':

            case '!':

            case '<':

            case '>':

            case '=':
                __last_token._token += "=";

                __last_token = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(__last_token._token.GET());
                break;
            }
        }
        else if (__last_token._type == TYPE_OPERATOR && __last_token._flag == Flag_Compare)
        {

            __last_token._token += "=";
            __last_token._flag = Flag_StrictCompare;
        }
        else
        {
            LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_ASSIGN, "=", Flag_Assign);

            LexicalAnalyzer::tokenVector.push_back(LexicalAnalyzer::tokenObject);
            LexicalAnalyzer::tokenVector.back()._file_index = LexicalAnalyzer::GET_SOURCE_CODE_INDEX();
        }
    }

    // when user is trying to add a String using double quote (") is found....
    inline static void FOUND_DOUBLE_QUOTE()
    {
        temp_string += *iterator;

        ++iterator;

        while (iterator < fileEnd && (*iterator != '\"'))
        {
            if (*iterator == '\\')
            {

                ++iterator;

                switch (*iterator)
                {

                case 'n':
                    temp_string += '\n';
                    break;

                case 't':
                    temp_string += '\t';
                    break;

                case '\"':
                    temp_string += '\"';
                    break;

                case '\'':

                case '\\':
                    temp_string += *iterator;
                    break;

                default:
                    //Logs::__SourceCodeIndex__ = LexicalAnalyzer::GET_SOURCE_CODE_INDEX();
                    throw ThrowException("tokenizing the code. Found an invalid escape sequence '" + (temp_string + *iterator) + "'. Only supported escape sequences are '\\n', '\\t' , '\\' , '\\\"' , '\\'' ", LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
                }

                ++iterator;

                continue;
            }

            //LexicalAnalyzer::tokenObject._newline_count += ((*iterator == '\n') ? 1 : 0);

            temp_string += *iterator;

            ++iterator;
        }

        // adding the last double quote to it...
        temp_string += *iterator;

        LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_STRING, temp_string.c_str(), Flag_String_Value);
    }

    inline static void FOUND_MINUS()
    {
        temp_string += *iterator;

        auto &__last_token = LexicalAnalyzer::tokenVector.back();

        switch (__last_token._type)
        {

        case TYPE_VOID:

        case TYPE_INT:

        case TYPE_DOUBLE:

        case TYPE_CHAR:

        case TYPE_BOOL:

        case TYPE_STRING:

        case TYPE_LIST_CLOSE:

        case TYPE_IDENTIFIER:

        case TYPE_CLOSING_BRACKETS:
            LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_OPERATOR, "-", Flag_Minus);
            break;

        default:
            LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_OPERATOR, "-", Flag_Negate); // negate operator
        }
    }

    // Handle newline================================================================
    inline static void FOUND_NEWLINE()
    {
        using LexicalAnalyzer::iterator;

        if (inside_math_expression)
        {
            throw ThrowException("tokenizing the code. Found newline inside a mathematical block which may lead to debugging problems", LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
        }

        temp_string += *iterator;

        LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_NEWLINE, "\n", Flag_bydefault);
    }

    // handles numbers================================================================
    inline static void FOUND_NUMBER()
    {

        using LexicalAnalyzer::iterator;
        using LexicalAnalyzer::temp_string;

        // if the last token in the LexicalAnalyzer::tokenVector is a '!-' negate operator,
        // then user is trying to write the a negative number ... simple as heck !!!!!!
        temp_string += ((LexicalAnalyzer::tokenVector.back()._flag == Flag_Negate) ? "-" : "");

        temp_string += *iterator;

        bool is_double_type_value = (*iterator == '.');

        ++iterator;

        auto valid_numeric_character = [](int ch)
        {
            return ((ch >= 48 && ch <= 57) || ch == '.' || ch == '_');
        };

        while (iterator < LexicalAnalyzer::fileEnd && valid_numeric_character(*iterator))
        {
            if (*iterator == '_')
            {
                ++iterator;
                continue;
            }
            else if (is_double_type_value && *iterator == '.')
            {
                throw ThrowException("tokenizing the code. Found '" + (temp_string + *iterator) + "' which contains more than one decimal points", NoException, LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
            }

            // if the character at iterator is not '.', then the original value at is_double_type_value will remain!
            is_double_type_value = (*iterator == '.') ? true : is_double_type_value;

            temp_string += *iterator;

            ++iterator;
        }

        // removing the initial zeros of 'Int' type and ending zeros of 'Double' type
        // by converting it back to its original form and then back to string form ...
        // temp_string = ((is_double_type_value) ? std::to_string(Converter::TO_DOUBLE(temp_string)) : std::to_string(Converter::TO_INT(temp_string)));

        // LexicalAnalyzer::UPDATE_TOKEN_OBJECT((is_double_type_value ? TYPE_DOUBLE : TYPE_INT), temp_string.c_str(), ((is_double_type_value) ? Flag_Double_Value : Flag_Int_Value));
        if (temp_string.front() == '-')
        {
            LexicalAnalyzer::tokenVector.pop_back();
        }

        // checking for division by zero
        if (LexicalAnalyzer::tokenVector.back()._flag == Flag_Div || LexicalAnalyzer::tokenVector.back()._flag == Flag_Mod)
        {
            SemanticAnalyzer::THROW_ERROR_IF_DIVISION_BY_ZERO_FOUND(temp_string);
        }

        LexicalAnalyzer::tokenVector.push_back(SronToken((is_double_type_value ? TYPE_DOUBLE : TYPE_INT), temp_string.c_str(), (is_double_type_value ? Flag_Double_Value : Flag_Int_Value)));
        LexicalAnalyzer::tokenVector.back()._file_index = LexicalAnalyzer::GET_SOURCE_CODE_INDEX();

        LexicalAnalyzer::RESET_TOKEN_OBJECT();

        // moving back to the character where it delimited...
        --iterator;

        LexicalAnalyzer::temp_string.clear();
    }

    // handles operators================================================================
    inline static void FOUND_OPERATOR()
    {
        temp_string += *iterator;

        switch (*iterator)
        {

        case '&':
        case '|':
        {
            if (*(iterator + 1) == *iterator)
            {

                ++iterator;
                temp_string += *iterator;
            }
            else
            {
                throw ThrowException("tokenizing the code. Found invalid operator '" + temp_string + "'. If you are trying to use '&&' or '||' operator, then make sure to remove spaces between them", LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
            }
        }

        case ',':

        case '!':

        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^':

        case '<':
        case '>':
            LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);
            break;

        default:
            throw ThrowException("tokenizing the code. Found this non-defined operator '" + temp_string + "'", LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
        }
    }

    /*
     * This function is used to handle scopes.
     * NOTE : the 'if' statement written within the case of ']' works like this :
     * the ascii of '[' is 91, ']' is 93, '{' is 123 and '}' is 125.
     * So, that statement converts the charcter to int and then subtract it by 2.
     * In case of '()', the ascii of '(' is 40 and ')' is 41.
     * Therefore, it is made in a different case.
     */
    inline static void FOUND_SCOPE_OPERATOR()
    {
        try
        {
            temp_string += *iterator;

            switch (*iterator)
            {

                case '(':
                    // this function will first check if the last token is a identifier or not,
                    // if it is identifier then updates its flag and type to function call ...
                    LexicalAnalyzer::UPDATE_LAST_TOKEN_IF_IDENTIFIER();
                case '{':
                case '[': scope_stack.push(*iterator); break;


                case ']':
                case ')':
                {
                    if (!scope_stack.empty() && scope_stack.top() == Support::GET_RESPECTIVE_OPENING_CHAR(*iterator) )
                    {
                        scope_stack.pop();
                    }
                    else
                    {
                        throw " ";
                    }
                    break;
                }
                default: throw " ";
                
            }

            LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);
        }
        catch (const char *)
        {
            throw ThrowException("generating bytecode and handling scopes. Found '" + temp_string + "'", InvalidScopeException, LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
        }
    }

    // handles single quotes================================================================
    inline static void FOUND_SINGLE_QUOTE()
    {
        temp_string += *iterator;

        ++iterator;

        if (*iterator == '\\')
        {
            switch (*(++iterator))
            {

            case 't':
                temp_string += "\t";
                break;

            case 'n':
                temp_string += "\n";
                break;

            case '\'':
                temp_string += '\'';
                break;

            case '\"':
                temp_string += '\"';
                break;

            case '\\':
                temp_string += "\\";
                break;

            default:
                throw ThrowException("tokenizing the code. Found an invalid escape sequence '" + (temp_string + *iterator) + "'. Only supported escape sequences are '\\n', '\\t' , '\\' , '\\\"' , '\\'' ", LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
            }
        }
        // if user is trying to write an empty character like this x = ''
        else if (*iterator == '\'')
        {
            LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_CHAR, " ", Flag_Char_Value);
        }
        else
        {

            temp_string += *iterator;
        }

        ++iterator;

        if (*iterator != '\'')
        {
            throw ThrowException("tokenizing the code. Single quotes (') can store a single character only. Found (" + temp_string + ")", LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
        }

        temp_string += '\'';

        LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_CHAR, temp_string.c_str(), Flag_Char_Value);
    }

    inline static void FOUND_WAVE()
    {

        using LexicalAnalyzer::iterator;
        using LexicalAnalyzer::temp_string;

        ++iterator;

        if (*iterator != '{')
        {
            throw ThrowException("tokenizing the code. Expected a '{' after '~' but found '" + (std::string() + *iterator) + "'", LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
        }

        // making the temp_string "~{"
        temp_string += "~{";

        LexicalAnalyzer::scope_stack.push('~');

        LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);
    }

    // called when '}' is found
    inline static void FOUND_SCOPE_CLOSE()
    {

        temp_string += *iterator;

        if(LexicalAnalyzer::scope_stack.empty()){
            throw ThrowException("tokenizing the code and handling scopes", InvalidScopeException , LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
        }

        if( LexicalAnalyzer::scope_stack.top() == '{')
        {
            LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);

            LexicalAnalyzer::scope_stack.pop();
            
        }
        else if(LexicalAnalyzer::scope_stack.top() == '~'){

            ++iterator;

            if(*iterator != '~'){
                throw ThrowException("tokenizing the code. Expected a '~' after "+temp_string+"'", LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
            }

            temp_string += *iterator;

            LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);

            LexicalAnalyzer::scope_stack.pop();
        }
        else{
            throw ThrowException("tokenizing the code and handling scope for '}'", InvalidScopeException , LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
        }

    }

    inline static void FUNCTION_TOKENIZATION_DONE()
    {

        #ifdef SRON_DEVELOPMENT_PHASE
            for (const auto &i : LexicalAnalyzer::tokenVector){
                std::cout << "<[ `" << i._token << "`   " << Support::TYPE_TO_STRING(i._type) << "    " << Support::FLAG_TO_STRING(i._flag) << " ]>\n";
            }
        #endif

        // sending the tokenVector for analysis, if no errors will be found, the tokenVector will be sent further to generate bytecode
        SemanticAnalyzer::ANALYZE(LexicalAnalyzer::tokenVector);

        // cleaning up the variable set
        SemanticAnalyzer::variableSet.clear();

        // clearing the LexicalAnalyzer::tokenVector
        LexicalAnalyzer::tokenVector.clear();

        // moving the iterator back to where code starts
        LexicalAnalyzer::MOVE_ITERATOR_TO_WHERE_CODE_STARTS();

        // decrementing the iterator so the for loop in
        // LexicalAnalyzer::TOKENIZER increments it
        --LexicalAnalyzer::iterator;
    }

    inline static unsigned long GET_SOURCE_CODE_INDEX()
    {
        return LexicalAnalyzer::iterator - LexicalAnalyzer::fileStart;
    }

    // returns the address of last token in tokenVector================================================================
    inline static TokenVector::iterator GET_LAST_TOKEN_ADDRESS()
    {
        return (LexicalAnalyzer::tokenVector.end() - 1);
    }

    // moves the iterator over spaces==================================================================================
    inline static void JUMP_ITERATOR_ABOVE_SPACES() noexcept
    {
        while (iterator < fileEnd && (*iterator == ' ' || *iterator == '\t'))
        {
            ++iterator;
        }
    }

    // moves the iterator to next first occurence of a particular character============================================
    inline static int JUMP_ITERATOR_TO_CHARACTER(const char &ch) noexcept
    {
        int count = 0;

        while (iterator < fileEnd && (*iterator != ch))
        {
            count += ((*iterator == '\n') ? 1 : 0);
            ++iterator;
        }

        count += (*iterator == '\n') ? 1 : 0;

        return count;
    }

    /*
     * This function moves the LexicalAnalyzer::iterator to the position of first
      occurrence of '{'. If their is a '@' behind the '{' then it will move forward
      and search for next '{'
     */
    inline static void MOVE_ITERATOR_TO_WHERE_CODE_STARTS()
    {
        using LexicalAnalyzer::iterator;

        while (iterator < LexicalAnalyzer::fileEnd && (*iterator != '{'))
        {

            if (*iterator == '@') LexicalAnalyzer::JUMP_ITERATOR_TO_CHARACTER('\n');
            else ++iterator;
        }
    }

    // resets the LexicalAnalyzer::tokenObject===============================================================

    inline static void RESET_TOKEN_OBJECT() noexcept
    {

        using LexicalAnalyzer::tokenObject;

        tokenObject._flag = Flag_bydefault;
        tokenObject._token = "";
        tokenObject._type = 0;

        LexicalAnalyzer::temp_string.clear();
    }

    // tokenizes the code ===================================================
    inline static void TOKENIZER()
    {
        using LexicalAnalyzer::fileEnd;
        using LexicalAnalyzer::iterator;

        for (; iterator < fileEnd; ++iterator)
        {

            if ((*iterator == ' ') || (*iterator == '\t'))
            {
                continue;
            }
            else if (*iterator == '@')
            {
                LexicalAnalyzer::JUMP_ITERATOR_TO_CHARACTER('\n');

                continue;
            }
            else if(*iterator == '}')
            {
                LexicalAnalyzer::FOUND_SCOPE_CLOSE();
            }
            else if (*iterator == '\n')
            {

                SemanticAnalyzer::THROW_ERROR_IF_INSIDE_MATH_BLOCK(TYPE_NEWLINE, LexicalAnalyzer::inside_math_expression);

                // if a newline is just after another newline then, the count of newline will be incremented
                // This may result in less memory usage and simple semantic analysis!!
                if (LexicalAnalyzer::GET_LAST_TOKEN_ADDRESS()->_type == TYPE_NEWLINE)
                {
                    ///LexicalAnalyzer::GET_LAST_TOKEN_ADDRESS()->_newline_count += 1;
                    continue;
                }

                LexicalAnalyzer::FOUND_NEWLINE();
            }
            else if (*iterator == '=')
            {
                LexicalAnalyzer::FOUND_ASSIGN();

                LexicalAnalyzer::RESET_TOKEN_OBJECT();

                continue;
            }
            else if (*iterator == ':')
            {
                SemanticAnalyzer::THROW_ERROR_IF_NOT_ATTRIBUTE(LexicalAnalyzer::tokenVector.back());

                LexicalAnalyzer::UPDATE_TOKEN_OBJECT(TYPE_COLON, ":", Flag_bydefault);
            }
            else if (*iterator == '~')
            {

                LexicalAnalyzer::FOUND_WAVE();
            }
            else if (*iterator == '-')
            {

                LexicalAnalyzer::FOUND_MINUS();
            }

            else if (*iterator == '\'')
            {

                LexicalAnalyzer::FOUND_SINGLE_QUOTE();
            }
            else if (*iterator == '\"')
            {

                LexicalAnalyzer::FOUND_DOUBLE_QUOTE();
            }
            else if (Support::IS_SCOPE_OPERATOR(*iterator))
            {

                LexicalAnalyzer::FOUND_SCOPE_OPERATOR();
            }
            else if (Support::IS_ALPHABET(*iterator) || *iterator == '_')
            {

                LexicalAnalyzer::FOUND_ALPHABET_OR_UNDERSCORE();
            }
            else if (Support::IS_NUMBER(*iterator) || *iterator == '.')
            {

                LexicalAnalyzer::FOUND_NUMBER();

                continue;
            }
            else if (Support::IS_OPERATOR(*iterator))
            {

                LexicalAnalyzer::FOUND_OPERATOR();
            }
            else
            {
                LexicalAnalyzer::temp_string += *iterator;

                throw ThrowException("tokenizing the code and found an invalid token '" + LexicalAnalyzer::temp_string + "'", InvalidTokenException, LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
            }

            LexicalAnalyzer::tokenVector.push_back(tokenObject);
            LexicalAnalyzer::tokenVector.back()._file_index = LexicalAnalyzer::GET_SOURCE_CODE_INDEX();

            // if the scope stack is empty it means that the function scope is completed
            // now the analysis is performed in it. If no error is found then the bytecode is generated.
            if (scope_stack.empty())
            {
                LexicalAnalyzer::FUNCTION_TOKENIZATION_DONE();
            }

            LexicalAnalyzer::RESET_TOKEN_OBJECT();

            LexicalAnalyzer::temp_string.clear();
        }

        if (!scope_stack.empty())
        {
            throw ThrowException("tokenizing the code", InvalidScopeException, LexicalAnalyzer::GET_SOURCE_CODE_INDEX());
        }
    }

    inline static void UPDATE_LAST_TOKEN_IF_IDENTIFIER()
    {

        auto &__last_token = LexicalAnalyzer::tokenVector.back();

        if (__last_token._type == TYPE_IDENTIFIER || __last_token._type == TYPE_IDENTIFIER_WITH_DOT)
        {
            __last_token._type = TYPE_FUNCTION_CALL;
            __last_token._flag = (SemanticAnalyzer::CHECK_IF_IN_BUILT_FUNCTION_EXISTS(__last_token._token)) ? Flag_InBuiltFunctionCall : Flag_UserDefinedFunctionCall;
        }
    }

}

#endif