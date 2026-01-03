#pragma once

#ifndef _LEX_UTIL_H
#define _LEX_UTIL_H

#include "_lex_base_.hpp"

inline static void LexicalAnalyzer::fncTokenizationDone()
{
    #ifdef SRON_DEVELOPMENT_PHASE
        unsigned int index = 0;

        for (const auto &i : LexicalAnalyzer::tokenVector)
        {
            std::printf("\n %u = <[ Token=`%s`    Type=`%s`    Flag=`%s`    Pair=`%u` ]>", index, i._token.c_str(), Support::TYPE_TO_STRING(i._type), SronSupport::flagToString(i._flag), i._pair_index);
            ++index;
        }
    #endif

    // sending the tokenVector for analysis, if no errors will be found, the tokenVector will be sent further to generate bytecode
    SemanticAnalyzer::ANALYZE(LexicalAnalyzer::tokenVector);

    // clearing the LexicalAnalyzer::tokenVector
    LexicalAnalyzer::tokenVector.clear();

    // moving the iterator back to where code starts
    LexicalAnalyzer::moveIteratorWhereCodeStarts();

    // decrementing the iterator so the for loop in
    // LexicalAnalyzer::tokenizer increments it
    --LexicalAnalyzer::iterator;
}

inline static unsigned long LexicalAnalyzer::getSourceCodeIndex()
{
    return LexicalAnalyzer::iterator - LexicalAnalyzer::fileStart;
}

// returns the address of last token in tokenVector================================================================
inline static TokenVector::iterator LexicalAnalyzer::getLastTokenAddress()
{
    return (LexicalAnalyzer::tokenVector.end() - 1);
}

// moves the iterator over spaces==================================================================================
inline static void LexicalAnalyzer::jumpIteratorAboveSpaces() noexcept
{
    while (iterator < fileEnd && (*iterator == ' ' || *iterator == '\t'))
    {
        ++iterator;
    }
}

// moves the iterator to next first occurence of a particular character============================================
inline static int LexicalAnalyzer::jumpIteratorToChar(const char &ch) noexcept
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
inline static void LexicalAnalyzer::moveIteratorWhereCodeStarts()
{
    using LexicalAnalyzer::iterator;

    while (iterator < LexicalAnalyzer::fileEnd && (*iterator != '{'))
    {

        if (*iterator == '@')
            LexicalAnalyzer::jumpIteratorToChar('\n');
        else
            ++iterator;
    }
}

// resets the LexicalAnalyzer::tokenObject===============================================================

inline static void LexicalAnalyzer::resetTokenObject() noexcept
{

    using LexicalAnalyzer::tokenObject;

    tokenObject._flag = BytecodeFlags::Flag_bydefault;
    tokenObject._token = "";
    tokenObject._type = SronTokenType::TYPE_DEFAULT;
    tokenObject._cache_value = 0;
    tokenObject._file_index = 0;
    tokenObject._pair_index = 0;

    LexicalAnalyzer::temp_string.clear();
}

inline static void LexicalAnalyzer::updateTokenObject(const SronTokenType __type, const char *const __token, BytecodeFlags __flag) noexcept
{

    using LexicalAnalyzer::tokenObject;

    tokenObject._type = __type;
    tokenObject._flag = __flag;
    tokenObject._token = __token;
    tokenObject._file_index = LexicalAnalyzer::getSourceCodeIndex();

    // not overwriting other values becuase they are already set by the functions
}

inline static void LexicalAnalyzer::makeLastTokenFunctionCall()
{
    auto &__last_token = LexicalAnalyzer::tokenVector.back();

    if (__last_token._type == SronTokenType::TYPE_IDENTIFIER || __last_token._type == SronTokenType::TYPE_IDENTIFIER_WITH_DOT)
    {
        __last_token._type = SronTokenType::TYPE_FUNCTION_CALL;

        const auto it = SemanticAnalyzer::inbuiltFncSet.find(SronHasher(__last_token._token.c_str()).GET());

        if (it != SemanticAnalyzer::inbuiltFncSet.end())
        {
            __last_token._flag = BytecodeFlags::Flag_InBuiltFunctionCall;
            __last_token._cache_value = it->_index;
        }
        else
        {
            __last_token._flag = BytecodeFlags::Flag_UserDefinedFunctionCall;
        }
    }
}

#endif