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

}

#endif