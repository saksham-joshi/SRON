#pragma once 

#ifndef _LEX_FND_H
#define _LEX_FND_H

#include "_lex_util_.hpp"

inline static void LexicalAnalyzer::foundAlphabetOrUnderscore()
{
    using LexicalAnalyzer::iterator;
    using LexicalAnalyzer::temp_string;
    using LexicalAnalyzer::tokenVector;

    auto if_valid_identifier_character = [](const char ch)
    {
        return ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch == '.' || ch == '_'));
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
    else if (LexicalAnalyzer::getLastTokenAddress()->_type == SronTokenType::TYPE_DATATYPE)
    {

        // it may be possible that the temp_string contains dot (.) or maybe its length
        // is larger than 32 so to reduce this issue.
        SemanticAnalyzer::THROW_ERROR_IF_INVALID_VARIABLE_NAME(__dot__, temp_string);

        // updating the LexicalAnalyzer::tokenObject
        LexicalAnalyzer::updateTokenObject(SronTokenType::TYPE_IDENTIFIER, temp_string.c_str(), BytecodeFlags::Flag_Identifier_Variable);
    }
    else
    {
        LexicalAnalyzer::updateTokenObject(SronTokenType::TYPE_IDENTIFIER, temp_string.c_str(), BytecodeFlags::Flag_Identifier_Variable);
    }

    --iterator;
}

// this function is called when '=' is found by LexicalAnalyzer::tokenizer() ...
inline static void LexicalAnalyzer::foundAssign()
{
    using LexicalAnalyzer::iterator;

    auto &__last_token = LexicalAnalyzer::tokenVector.back();

    // checking case of assignment operators except '='
    if (__last_token._type == SronTokenType::TYPE_OPERATOR && __last_token._token.length() == 1)
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
                __last_token._token += "=";

                __last_token = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(__last_token._token.c_str());
                break;
        }

        __last_token._file_index = LexicalAnalyzer::getSourceCodeIndex();
    }
    else
    {
        ++iterator;

        if(iterator >= LexicalAnalyzer::fileEnd) throw ThrowException("tokenizing the code. Expected some value after '" + temp_string +"'", LexicalAnalyzer::getSourceCodeIndex());

        // checking case of '==' (comparison)
        if(*iterator == '=')
        {
            ++iterator;

            if(iterator >= LexicalAnalyzer::fileEnd) throw ThrowException("tokenizing the code. Expected some value after '" + temp_string +"'", LexicalAnalyzer::getSourceCodeIndex());

            // checking case of '===' (strict comparison)
            if(*iterator == '=')
            {
                // if code has '==='
                LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP("===");
            }
            else 
            {
                // if code has '=='
                --iterator;
                LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP("==");
            }
        }
        else
        {
            --iterator;
            LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP("=");
        }

        LexicalAnalyzer::tokenObject._file_index = LexicalAnalyzer::getSourceCodeIndex();

        LexicalAnalyzer::tokenVector.push_back(LexicalAnalyzer::tokenObject);
        
    }
}

// when user is trying to add a String using double quote (") is found....
inline static void LexicalAnalyzer::foundDoubleQuote()
{
    ++iterator;

    while (iterator < fileEnd && (*iterator != '\"') && temp_string.length() < BYTECODE_STRING_MAX_LEN)
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

            case 'b':
                temp_string += '\b';
                break;

            case 'r':
                temp_string += '\r';
                break;

            case '"':

            case '\'':

            case '\\':
                temp_string += *iterator;
                break;

            default:
                throw ThrowException("tokenizing the code. Found an invalid escape sequence '" + (temp_string + *iterator) + "'. Only supported escape sequences are '\\n', '\\t' , '\\' , '\\\"' , '\\'' ", LexicalAnalyzer::getSourceCodeIndex());
            }
        }
        else temp_string += *iterator;

        ++iterator;
    }

    if (temp_string.length() >= BYTECODE_STRING_MAX_LEN)
        throw ThrowException("tokenizing the code. The length of the constant string is exceeding the limit", SronError::TooLargeStringError, LexicalAnalyzer::getSourceCodeIndex());

    LexicalAnalyzer::updateTokenObject(SronTokenType::TYPE_STRING, temp_string.c_str(), BytecodeFlags::Flag_String_Value);
}

inline static void LexicalAnalyzer::foundMinus()
{
    temp_string += *iterator;

    auto &__last_token = LexicalAnalyzer::tokenVector.back();

    switch (__last_token._type)
    {

    case SronTokenType::TYPE_VOID:

    case SronTokenType::TYPE_INT:

    case SronTokenType::TYPE_DOUBLE:

    case SronTokenType::TYPE_CHAR:

    case SronTokenType::TYPE_BOOL:

    case SronTokenType::TYPE_STRING:

    case SronTokenType::TYPE_LIST_CLOSE:

    case SronTokenType::TYPE_IDENTIFIER:

    case SronTokenType::TYPE_CLOSING_BRACKETS:
        LexicalAnalyzer::updateTokenObject(SronTokenType::TYPE_OPERATOR, "-", BytecodeFlags::Flag_Minus);
        break;

    default:
        LexicalAnalyzer::updateTokenObject(SronTokenType::TYPE_OPERATOR, "-", BytecodeFlags::Flag_Negate); // negate operator
    }
}

// Handle newline================================================================
inline static void LexicalAnalyzer::foundNewline()
{
    using LexicalAnalyzer::iterator;

    if (LexicalAnalyzer::inside_math_expression > 0)
    {
        throw ThrowException("tokenizing the code. Found newline inside a mathematical block which may lead to debugging problems", LexicalAnalyzer::getSourceCodeIndex());
    }

    temp_string += *iterator;

    LexicalAnalyzer::updateTokenObject(SronTokenType::TYPE_NEWLINE, "\n", BytecodeFlags::Flag_bydefault);
}

// handles numbers================================================================
inline static void LexicalAnalyzer::foundNumber()
{

    using LexicalAnalyzer::iterator;
    using LexicalAnalyzer::temp_string;

    // if the last token in the LexicalAnalyzer::tokenVector is a '!-' negate operator,
    // then user is trying to write the a negative number ... simple as heck !!!!!!
    temp_string += ((LexicalAnalyzer::tokenVector.back()._flag == BytecodeFlags::Flag_Negate) ? "-" : "");

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
            throw ThrowException("tokenizing the code. Found '" + (temp_string + *iterator) + "' which contains more than one decimal points", SronError::DefaultError, LexicalAnalyzer::getSourceCodeIndex());

        // LLONG_MAX has length of 19 and if the value contains '-', then the length becomes 20
        else if (temp_string.length() >= 21)
            throw ThrowException("tokenizing the code. Found '" + temp_string + "' is longer than enough", SronError::TooLargeNumberError, LexicalAnalyzer::getSourceCodeIndex());

        // if the character at iterator is not '.', then the original value at is_double_type_value will remain!
        is_double_type_value = (*iterator == '.') ? true : is_double_type_value;

        temp_string += *iterator;

        ++iterator;
    }

    // removing the initial zeros of 'Int' type and ending zeros of 'Double' type
    // by converting it back to its original form and then back to string form ...
    // temp_string = ((is_double_type_value) ? std::to_string(Converter::TO_DOUBLE(temp_string)) : std::to_string(Converter::TO_INT(temp_string)));

    // LexicalAnalyzer::updateTokenObject((is_double_type_value ? TYPE_DOUBLE : TYPE_INT), temp_string.c_str(), ((is_double_type_value) ? BytecodeFlags::Flag_Double_Value : BytecodeFlags::Flag_Int_Value));
    if (temp_string.front() == '-')
    {
        LexicalAnalyzer::tokenVector.pop_back();
    }

    // checking for division by zero
    if (LexicalAnalyzer::tokenVector.back()._flag == BytecodeFlags::Flag_Div || LexicalAnalyzer::tokenVector.back()._flag == BytecodeFlags::Flag_Mod)
    {
        SemanticAnalyzer::THROW_ERROR_IF_DIVISION_BY_ZERO_FOUND(temp_string, LexicalAnalyzer::getSourceCodeIndex());
    }

    LexicalAnalyzer::tokenVector.push_back(SronToken((is_double_type_value ? SronTokenType::TYPE_DOUBLE : SronTokenType::TYPE_INT), temp_string.c_str(), (is_double_type_value ? BytecodeFlags::Flag_Double_Value : BytecodeFlags::Flag_Int_Value)));
    LexicalAnalyzer::tokenVector.back()._file_index = LexicalAnalyzer::getSourceCodeIndex();

    LexicalAnalyzer::resetTokenObject();

    // moving back to the character where it delimited...
    --iterator;
}

// handles operators================================================================
inline static void LexicalAnalyzer::foundOperator()
{
    using LexicalAnalyzer::iterator;

    temp_string += *iterator;

    switch (*iterator)
    {
        case '&':
        case '|': {
            ++iterator;

            if(iterator >= LexicalAnalyzer::fileEnd) throw ThrowException("tokenizing the code. Expected a token after '" + temp_string + "' but source code ended", LexicalAnalyzer::getSourceCodeIndex());

            if (*iterator == temp_string.back()) temp_string.push_back(temp_string.back());
            
            else --iterator;

        } break;

        case '<':
        case '>': {
            ++iterator;
            
            if(iterator >= LexicalAnalyzer::fileEnd) throw ThrowException("tokenizing the code. Expected a token after '" + temp_string + "' but source code ended", LexicalAnalyzer::getSourceCodeIndex());

            if(*iterator == '=') temp_string.push_back('=');

            else --iterator;

        } break;
            
        case ',':
        case '!':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '^': 
        case '~': break;

        default: throw ThrowException("tokenizing the code. Found this non-defined operator '" + temp_string + "'", LexicalAnalyzer::getSourceCodeIndex());
    }

    LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);
}

/*
 * This function is used to handle scopes.
 * NOTE : the 'if' statement written within the case of ']' works like this :
 * the ascii of '[' is 91, ']' is 93, '{' is 123 and '}' is 125.
 * So, that statement converts the charcter to int and then subtract it by 2.
 * In case of '()', the ascii of '(' is 40 and ')' is 41.
 * Therefore, it is made in a different case.
 */
inline static void LexicalAnalyzer::foundScopeOperator()
{
    using namespace LexicalAnalyzer;

    try
    {
        temp_string += *iterator;

        switch (*iterator)
        {

        case '(':
            // this function will first check if the last token is a identifier or not,
            // if it is identifier then updates its flag and type to function call ...
            LexicalAnalyzer::makeLastTokenFunctionCall();
        case '{':
        case '[':
            LexicalAnalyzer::addToScopeStack(*iterator);
            //scope_stack.push(LexicalAnalyzer::ScopeTracker(iterator - LexicalAnalyzer::fileStart, *iterator));
            break;

        case ']':
        case ')':
        {
            if (!scope_stack.empty() && scope_stack.top()._ch == Support::GET_RESPECTIVE_OPENING_CHAR(*iterator))
            {
                // TODO: set up here <>
                auto& top = scope_stack.top();

                // preparing the tokenObject
                tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);

                tokenObject._pair_index = top._token_index;

                tokenVector[top._token_index]._pair_index = tokenVector.size();

                scope_stack.pop();

                return;
            }
            else
            {
                throw " ";
            }
            break;
        }
        default:
            throw " ";
        }

        LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);
    }
    catch (const char *)
    {
        throw ThrowException("generating bytecode and handling scopes. Found '" + temp_string + "'", SronError::InvalidScopeError, LexicalAnalyzer::getSourceCodeIndex());
    }
}

// handles single quotes================================================================
inline static void LexicalAnalyzer::foundSingleQuote()
{
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

        case 'b':
            temp_string += '\b';
            break;

        case 'r':
            temp_string += '\r';
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
            throw ThrowException("tokenizing the code. Found an invalid escape sequence '" + (temp_string + *iterator) + "'. Only supported escape sequences are '\\n', '\\t', '\\r', '\\b' , '\\' , '\\\"' , '\\'' ", LexicalAnalyzer::getSourceCodeIndex());
        }
    }
    // if user is trying to write an empty character like this x = ''
    else if (*iterator == '\'')
    {
        LexicalAnalyzer::updateTokenObject(SronTokenType::TYPE_CHAR, " ", BytecodeFlags::Flag_Char_Value);
    }
    else
    {
        temp_string += *iterator;
    }

    ++iterator;

    if (*iterator != '\'')
    {
        throw ThrowException("tokenizing the code. Single quotes (') can store a single character only. Found (" + temp_string + "). If you are trying to write Unicode Characters, then for your kind information- Unicode is not fully supported by SRON", LexicalAnalyzer::getSourceCodeIndex());
    }

    LexicalAnalyzer::updateTokenObject(SronTokenType::TYPE_CHAR, temp_string.c_str(), BytecodeFlags::Flag_Char_Value);
}

inline static void LexicalAnalyzer::foundDollar()
{

    using LexicalAnalyzer::iterator;
    using LexicalAnalyzer::temp_string;

    ++iterator;

    if (*iterator != '{')
    {
        throw ThrowException("tokenizing the code. Expected a '{' after '$' but found '" + (std::string() + *iterator) + "'", LexicalAnalyzer::getSourceCodeIndex());
    }

    // making the temp_string "${"
    temp_string += "${";

    LexicalAnalyzer::addToScopeStack('$');

    LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);

    LexicalAnalyzer::inside_math_expression++;
}

// called when '}' is found
inline static void LexicalAnalyzer::foundScopeClose()
{

    temp_string += *iterator;

    if (LexicalAnalyzer::scope_stack.empty())
    {
        throw ThrowException("tokenizing the code and handling scopes", SronError::InvalidScopeError, LexicalAnalyzer::getSourceCodeIndex());
    }

    LexicalAnalyzer::tokenObject = TokenMaps::EXTRACT_TOKEN_FROM_TOKEN_MAP(temp_string);

    if (LexicalAnalyzer::scope_stack.top()._ch == '{')
    {
        LexicalAnalyzer::tokenVector[LexicalAnalyzer::scope_stack.top()._token_index]._pair_index = LexicalAnalyzer::tokenVector.size();

        LexicalAnalyzer::tokenObject._pair_index = LexicalAnalyzer::scope_stack.top()._token_index;
    }
    // if someone is writing to write this ${ a + b }
    else if (LexicalAnalyzer::scope_stack.top()._ch == '$')
    {
        LexicalAnalyzer::tokenVector[LexicalAnalyzer::scope_stack.top()._token_index]._pair_index = LexicalAnalyzer::tokenVector.size();

        LexicalAnalyzer::tokenObject._pair_index = LexicalAnalyzer::scope_stack.top()._token_index;

        LexicalAnalyzer::tokenObject._flag = BytecodeFlags::Flag_EvalEnd;

        LexicalAnalyzer::tokenObject._type = SronTokenType::TYPE_MATH_BLOCK;

        LexicalAnalyzer::inside_math_expression--;
    }
    else
    {
        throw ThrowException("tokenizing the code and handling scope for '}'", SronError::InvalidScopeError, LexicalAnalyzer::getSourceCodeIndex());
    }

    LexicalAnalyzer::scope_stack.pop();
}
#endif 