#pragma once

#ifndef _LEX_H
#define _LEX_H

#include "_lex_found_.hpp"


// tokenizes the code ===================================================
inline static void LexicalAnalyzer::tokenizer()
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
            LexicalAnalyzer::jumpIteratorToChar('\n');

            continue;
        }
        else if (*iterator == '}')
        {
            LexicalAnalyzer::foundScopeClose();
        }
        else if (*iterator == '(' || *iterator == '[' || *iterator == '{' || *iterator == ')' || *iterator == ']')
        {
            LexicalAnalyzer::foundScopeOperator();
        }
        else if (*iterator == '\n')
        {

            SemanticAnalyzer::THROW_ERROR_IF_INSIDE_MATH_BLOCK(SronTokenType::TYPE_NEWLINE, LexicalAnalyzer::inside_math_expression);

            // if a newline is just after another newline then, the count of newline will be incremented
            // This may result in less memory usage and simple semantic analysis!!
            if (LexicalAnalyzer::getLastTokenAddress()->_type == SronTokenType::TYPE_NEWLINE)
            {
                continue;
            }

            LexicalAnalyzer::foundNewline();
        }
        else if (*iterator == '=')
        {
            LexicalAnalyzer::foundAssign();

            LexicalAnalyzer::resetTokenObject();

            continue;
        }
        else if (*iterator == ':')
        {
            SemanticAnalyzer::THROW_ERROR_IF_NOT_ATTRIBUTE(LexicalAnalyzer::tokenVector.back());

            LexicalAnalyzer::updateTokenObject(SronTokenType::TYPE_COLON, ":", BytecodeFlags::Flag_bydefault);
        }
        else if (*iterator == '$')
        {

            LexicalAnalyzer::foundDollar();
        }
        else if (*iterator == '-')
        {

            LexicalAnalyzer::foundMinus();
        }

        else if (*iterator == '\'')
        {

            LexicalAnalyzer::foundSingleQuote();
        }
        else if (*iterator == '\"')
        {

            LexicalAnalyzer::foundDoubleQuote();
        }
        else if (Support::IS_ALPHABET(*iterator) || *iterator == '_')
        {

            LexicalAnalyzer::foundAlphabetOrUnderscore();
        }
        else if (Support::IS_NUMBER(*iterator) || *iterator == '.')
        {

            LexicalAnalyzer::foundNumber();

            continue;
        }
        else if (Support::IS_OPERATOR(*iterator))
        {

            LexicalAnalyzer::foundOperator();
        }
        else
        {
            LexicalAnalyzer::temp_string += *iterator;

            throw ThrowException("tokenizing the code and found an invalid token '" + LexicalAnalyzer::temp_string + "'", SronError::InvalidTokenError, LexicalAnalyzer::getSourceCodeIndex());
        }

        LexicalAnalyzer::tokenVector.push_back(tokenObject);
        LexicalAnalyzer::tokenVector.back()._file_index = LexicalAnalyzer::getSourceCodeIndex();

        // if the scope stack is empty it means that the function scope is completed
        // now the analysis is performed in it. If no error is found then the bytecode is generated.
        if (scope_stack.empty())
        {
            LexicalAnalyzer::fncTokenizationDone();
        }

        LexicalAnalyzer::resetTokenObject();

        LexicalAnalyzer::temp_string.clear();
    }

    if (!scope_stack.empty())
    {
        throw ThrowException("tokenizing the code", SronError::InvalidScopeError, LexicalAnalyzer::getSourceCodeIndex());
    }
}

#endif