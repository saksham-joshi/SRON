

#pragma once

#ifndef _BYTECODE_WRTR_H
#define _BYTECODE_WRTR_H

#include "lib/_postfix_.hpp"

namespace ByteCodeWriter
{

    /* stores the direct address (&) of name of the function stored in
     * SronTokenString within SronToken. It is not dynamically allocated
     * but needs to be assigned to nullptr after the work is done. */
    SronToken::TokenElement_t*   fnc_name             = nullptr;

    FILE *                       __ByteCodeFile__     = nullptr;

    // contains either Flag_Any or Flag_IntExtractor, Flag_DoubleExtractor etc.
    BytecodeFlags                __returnTypeFlag__   = BytecodeFlags::Flag_Any;

    TokenVector::iterator        iterator;
    TokenVector::const_iterator  tokenVectorEnd;

    // stores the ending flags of, ),  for, while, if, elif and else ...
    std::list<SeekTracker>       seek_tracker;

    inline static void ATTRIBUTE_ARGS_WRITER            () ;
    inline static void ATTRIBUTE_MAPPER                 () ;
    inline static void ATTRIBUTE_CONSOLE_WRITER         () ;
    inline static void ATTRIBUTE_RETURN_WRITER          () ;
    inline static void ATTRIBUTE_ROTATE_WRITER          () ;
    inline static void ATTRIBUTE_FOR_WRITER             () ;
    inline static void ATTRIBUTE_WHILE_WRITER           () ;
    inline static void ATTRIBUTE_FOREACH_WRITER         () ;
    inline static void ATTRIBUTE_IF_ELIF_ELSE_WRITER    () ;
    
    inline static void DATATYPE_WRITER                  () ;
    inline static void FUNCTION_CALL_WRITER             () ;

    inline static void GENERATE                         (TokenVector &, BytecodeVariable_t) ;

    inline static void HANDLE_SCOPES                    () ;
    inline static void IDENTIFIER_WRITER                () ;
    inline static void KEYWORD_WRITER                   () ;
    inline static void LIST_WRITER                      () ;
    inline static void MATH_BLOCK_WRITER                () ;

    inline static void REMOVE_DEAD_CODE                 () ;
    inline static void RESET                            () noexcept;

    template <typename Tp> 
    inline static void SAVE_DATA               ( Tp );
    inline static void SAVE_CONST_CHAR         ( const char*,unsigned short int,bool __put_terminator = true );
    inline static void SAVE_FLAG               ( BytecodeFlags );
    inline static void SAVE_INT64              ( SronInt_t );
    inline static void SAVE_DOUBLE             ( SronDouble_t );
    inline static void SAVE_CHAR               ( SronChar_t );
    inline static void SAVE_VARIABLE           ( BytecodeVariable_t );
    inline static void SAVE_HASH               ( Hash_t );
    inline static void SAVE_STRING             ( const SronToken::TokenElement_t& );
    inline static void SAVE_SRON_STRING        ( const SronToken::TokenElement_t& );

    inline static void THROW_ERROR_IF_SEEK_TRACKER_IS_EMPTY  () ;

    inline static void TYPE_MAPPER                           () ;

    inline static void WRITE_CLOSING_INDEX                   () ;

}

#endif