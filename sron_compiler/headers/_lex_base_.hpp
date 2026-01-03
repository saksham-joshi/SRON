#pragma once

#ifndef _LEXER_BASE_H
#define _LEXER_BASE_H

#include "SemanticAnalyzer/_math_block_analyzer_.hpp"

namespace LexicalAnalyzer
{
    struct ScopeTracker
    {
        unsigned int _token_index;
        char _ch;
    };

    // contains the whole content of the source code
    std::string filecode;

    std::string temp_string;

    std::string::const_iterator fileStart;

    // the iterator on the content of the source code
    std::string::const_iterator iterator;

    // the end iterator on the content of the source code
    std::string::const_iterator fileEnd;

    TokenVector tokenVector;

    std::stack<LexicalAnalyzer::ScopeTracker> scope_stack;

    // temporary object of SronToken
    static SronToken tokenObject;

    short inside_math_expression = 0;

    inline static void addToScopeStack(char __ch)
    {
        LexicalAnalyzer::scope_stack.push(LexicalAnalyzer::ScopeTracker(LexicalAnalyzer::tokenVector.size(), __ch));
    }

    inline static void foundAlphabetOrUnderscore();
    inline static void foundAssign();
    inline static void foundDoubleQuote();
    inline static void foundMinus();
    inline static void foundNewline();
    inline static void foundNumber();
    inline static void foundOperator();
    inline static void foundSingleQuote();
    inline static void foundDollar();
    inline static void foundScopeClose();
    inline static void foundScopeOperator();

    inline static void fncTokenizationDone();

    inline static unsigned long getSourceCodeIndex();

    inline static TokenVector::iterator getLastTokenAddress();

    inline static void jumpIteratorAboveSpaces() noexcept;
    inline static int jumpIteratorToChar(const char &) noexcept;

    inline static void moveIteratorWhereCodeStarts();

    inline static void resetTokenObject() noexcept;

    inline static void tokenizer();

    inline static void makeLastTokenFunctionCall();

    inline static void updateTokenObject(const SronTokenType, const char *const, BytecodeFlags) noexcept;
}

#endif