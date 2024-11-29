

#pragma once

#ifndef _BYTECODE_WRTR_H
#define _BYTECODE_WRTR_H

#include "lib/_postfix_.hpp"

namespace ByteCodeWriter
{

    /* stores the direct address (&) of name of the function stored in
     * SronTokenString within SronToken. It is not dynamically allocated
     * but needs to be assigned to nullptr after the work is done. */
    SronTokenString *fnc_name = nullptr;

    flag_t __returnTypeFlag__ = Flag_Any;

    TokenVector::iterator iterator;
    TokenVector::const_iterator tokenVectorEnd;

    FILE *__ByteCodeFile__ = nullptr;

    // stores the ending flags of, ),  for, while, if, elif and else ...
    std::list<SeekTracker> seek_tracker;

    inline static void ATTRIBUTE_ARGS_WRITER();
    inline static void ATTRIBUTE_MAPPER();
    inline static void ATTRIBUTE_CONSOLE_WRITER();
    inline static void ATTRIBUTE_RETURN_WRITER();
    inline static void ATTRIBUTE_ROTATE_WRITER();

    inline static void ATTRIBUTE_FOR_WRITER();

    inline static void ATTRIBUTE_WHILE_WRITER();

    inline static void ATTRIBUTE_FOREACH_WRITER();

    inline static void ATTRIBUTE_IF_ELIF_ELSE_WRITER();

    inline static void DATATYPE_WRITER();

    inline static void FUNCTION_CALL_WRITER();

    inline static void GENERATE(TokenVector &);

    inline static void HANDLE_SCOPES();

    inline static void IDENTIFIER_WRITER();

    inline static void LIST_WRITER();

    inline static void MATH_BLOCK_WRITER();

    inline static void RESET() noexcept;

    inline static void SAVE_CONST_CHAR_TO_FILE(const char*,unsigned short int);
    inline static void SAVE_FLAG_TO_FILE(flag_t);
    inline static void SAVE_INT64_TO_FILE(long long int);
    inline static void SAVE_DOUBLE_TO_FILE(double);
    inline static void SAVE_CHAR_TO_FILE(char);
    inline static void SAVE_LONG_TO_FILE(long);
    inline static size_t SAVE_UNSIGNED_INT64_TO_FILE(SronTokenString &);
    inline static size_t SAVE_UNSIGNED_INT64_TO_FILE(size_t);
    inline static void SAVE_U_INT16_TO_FILE(unsigned short int);
    inline static void SAVE_STRING_TO_FILE(SronTokenString &);

    inline static void TYPE_MAPPER();

    inline static void WRITE_CLOSING_INDEX();

}

#endif