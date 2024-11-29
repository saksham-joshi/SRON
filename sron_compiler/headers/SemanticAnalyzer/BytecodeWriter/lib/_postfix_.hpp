#pragma once

#ifndef _PSTFX_H
#define _PSTFX_H

#include "_seek_tracker_.hpp"

class PostFixGenerator
{

    TokenVector::iterator vecit;
    TokenVector::const_iterator tokenVectorEnd;

    // used as a stack for postfix expression storage
    std::vector<SronToken> stk;

    inline void ADD_SCOPE_CONTENT_TO_EXP(const unsigned short int, const unsigned short int);

    inline bool CHECK_IF_TOP_TWO_ELEMENTS_IN_STACK_ARE_CONSTANTS();

    inline void INNER_POSTFIX();

    constexpr inline static const unsigned short int PRECEDENCE(const flag_t __flag);

public:
    // used to store the final postfix expression
    TokenVector expression;

    inline PostFixGenerator(TokenVector::iterator __vecit, TokenVector::const_iterator &__tokenVectorEnd)
        : vecit(__vecit), tokenVectorEnd(__tokenVectorEnd) {}

    // whenever a '[' or argument of function call '(' comes inside the mathematical block

    inline TokenVector::iterator POSTFIX();
};

#endif