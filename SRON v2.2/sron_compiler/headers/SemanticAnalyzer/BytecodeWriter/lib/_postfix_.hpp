#pragma once

#ifndef _PSTFX_H
#define _PSTFX_H

#include "_stack_set_.hpp"

class PostFixGenerator
{

    TokenVector::iterator vecit;
    TokenVector::const_iterator tokenVectorEnd;

    // used as a stack for postfix expression storage
    std::vector<SronToken> stk;

    inline void ADD_SCOPE_CONTENT_TO_EXP(const unsigned short int, const unsigned short int);

    inline bool CHECK_IF_TOP_TWO_ELEMENTS_IN_STACK_ARE_CONSTANTS();

    inline void INNER_POSTFIX();

    constexpr inline static unsigned short int PRECEDENCE(const Flag_t __flag);

public:
    // used to store the final postfix expression
    TokenVector expression;

    inline PostFixGenerator(TokenVector::iterator __vecit, TokenVector::const_iterator &__tokenVectorEnd)
        : vecit(__vecit), tokenVectorEnd(__tokenVectorEnd) {}

    // whenever a '[' or argument of function call '(' comes inside the mathematical block

    inline TokenVector::iterator POSTFIX();
};
/*
 Implementation start from here ================>
*/

inline void PostFixGenerator::ADD_SCOPE_CONTENT_TO_EXP(const unsigned short int __opener, const unsigned short int __closer)
{
    unsigned short int bracket_count = 1;

    expression.push_back(std::move(*this->vecit));
    ++(this->vecit);

    while (this->vecit < this->tokenVectorEnd && (bracket_count != 0))
    {

        bracket_count += (this->vecit->_type == __opener) ? 1 : 0 ;
        bracket_count -= (this->vecit->_type == __closer) ? 1 : 0 ;

        expression.push_back(std::move(*this->vecit));

        ++(this->vecit);
    }

    --(this->vecit);
}

inline bool PostFixGenerator::CHECK_IF_TOP_TWO_ELEMENTS_IN_STACK_ARE_CONSTANTS()
{

    auto is_constant_value = [](unsigned short int _type_)
    {
        return (_type_ == TYPE_INT || _type_ == TYPE_DOUBLE || _type_ == TYPE_CHAR || _type_ == TYPE_STRING || _type_ == TYPE_VOID || _type_ == TYPE_BOOL);
    };

    if (stk.size() < 2)
    {
        return false;
    }

    if (is_constant_value(stk.back()._type) && is_constant_value((stk.end() - 1)->_type))
    {
        return true;
    }

    return false;
}

/*
 * This function is called when Flag_EvalStart is found.
 * It justs add the token to the expression as it is.
 * Because when the Flag_EvalStart is found in ByteCodeWriter
 * then an instance of PostFixGenerator is created and POSTFIX()
 * method is called which creates the postfix expression. After
 * the expression is created, the ByteCodeWriter maps all the 
 * flag to the function and generates the bytecode. So, If there
 * is a Flag_EvalStart inside the Flag_EvalStart's scope, then it
 * again creates the PostFixGenerator instance and starts the whole
 * process again as explained before.
*/
inline void PostFixGenerator::INNER_POSTFIX()
{
    this->expression.push_back(std::move(*vecit));

    unsigned short int inner_scope_count = 1;

    ++vecit;

    while(this->vecit < this->tokenVectorEnd && (inner_scope_count != 0)){

        this->expression.push_back(std::move(*vecit));

        inner_scope_count += ((vecit->_flag == Flag_EvalStart) ? 1 : 0);
        inner_scope_count -= ((vecit->_flag == Flag_EvalEnd) ? 1 : 0);

        ++vecit;
    }

    // decrementing the vecit to move at the position of }~
    --vecit;

    this->expression.push_back(std::move(*vecit));
    
}

constexpr inline unsigned short int PostFixGenerator::PRECEDENCE(const Flag_t __flag)
{
    switch (__flag)
    {
        case Flag_Not:
        case Flag_BitwiseNot:
        case Flag_Negate: return 10;

        case Flag_Pow: return 9;

        case Flag_Mult:
        case Flag_Div:
        case Flag_Mod: return 8;

        case Flag_Add:
        case Flag_Minus: return 7;

        case Flag_Lshift:
        case Flag_Rshift : return 6;

        case Flag_MoreThan:
        case Flag_MoreThanEqual:
        case Flag_LessThan:
        case Flag_LessThanEqual: return 5;

        case Flag_Compare:
        case Flag_StrictCompare:
        case Flag_NotEqual: return 4;

        case Flag_Xor:
        case Flag_BitwiseAnd:
        case Flag_BitwiseOr : return 3;

        case Flag_And: return 2;

        case Flag_Or: return 1;
    }

    throw ThrowException("optimizing mathematic block. No precedence for operator for '" + std::to_string(__flag) + "' found");
}

// this function is called by the functions of ByteCodeWriter to generate the postfix
inline TokenVector::iterator PostFixGenerator::POSTFIX()
{
    // current position of vecit is at '~{'
    ++this->vecit;

    while (this->vecit < tokenVectorEnd && vecit->_flag != Flag_EvalEnd)
    {
        #ifdef SRON_DEBUG_MODE
            printf_s("\n----------->>>>>>>> Token='%s'    Flag='%s'", this->vecit->_token.c_str() , Support::FLAG_TO_STRING(this->vecit->_flag));
        #endif

        const auto temp = vecit->_type;

        // checking if the token is a number or a variable
        if (temp == TYPE_DOUBLE || temp == TYPE_INT || temp == TYPE_CHAR || temp == TYPE_BOOL || temp == TYPE_STRING || temp == TYPE_IDENTIFIER)
        {
            expression.push_back(std::move(*vecit));
        }
        else if (temp == TYPE_LIST_OPEN)
        {
            PostFixGenerator::ADD_SCOPE_CONTENT_TO_EXP(TYPE_LIST_OPEN, TYPE_LIST_CLOSE);

        }
        else if (temp == TYPE_FUNCTION_CALL)
        {
            // inserting the function name and incrementing the vecit because
            // ADD_SCOPE_CONTNENT_TO_EXP will start from (
            this->expression.push_back(*vecit);
            ++vecit;
            this->ADD_SCOPE_CONTENT_TO_EXP(TYPE_OPENING_BRACKETS, TYPE_CLOSING_BRACKETS);
        }
        else if (temp == TYPE_OPENING_BRACKETS)
        {
            stk.push_back(std::move(*vecit));
        }
        else if (temp == TYPE_CLOSING_BRACKETS)
        {
            while (!stk.empty() && stk.back()._type != TYPE_OPENING_BRACKETS)
            {
                expression.push_back(std::move(stk.back()));
                stk.pop_back();
            }

            // if the stack is made empty, then there will be nothing but if there is a round bracket
            // then removing that round bracket.
            if (!stk.empty())
            {
                stk.pop_back();
            }
        }
        else if (vecit->_type == TYPE_MATH_BLOCK)
        {
            this->INNER_POSTFIX();
        }
        else if (vecit->_type == TYPE_OPERATOR)
        {
            while ((!stk.empty()) && (stk.back()._type != TYPE_OPENING_BRACKETS) && (PostFixGenerator::PRECEDENCE(vecit->_flag) <= PostFixGenerator::PRECEDENCE(stk.back()._flag)))
            {

                expression.push_back(std::move(stk.back()));
                stk.pop_back();
            }

            if ((!stk.empty()) && stk.back()._type == TYPE_OPENING_BRACKETS){
                stk.pop_back();  }

            stk.push_back(std::move(*vecit));
        }
        else
        {
            throw ThrowException("parsing and optimizing a mathematical expression. Found this token '" + std::string(vecit->_token.c_str()) + "' of type '" + std::string(Support::TYPE_TO_STRING(vecit->_type)) + "'", SronError::MathBlockSyntaxError);
        }

        ++vecit;
    }

    // transferring all the element in the stack to the vector
    while (!this->stk.empty())
    {
        expression.push_back(std::move(stk.back()));
        stk.pop_back();
    }

    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s("\n Postfix : ~{");

        for (const auto &i : this->expression)
        {
            printf_s( "%s ", i._token.c_str());
        }

        printf_s(" }~\n");
    #endif

    return vecit;
}


#endif