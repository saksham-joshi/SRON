#ifndef _MATH_BLOCK_ANALYZER_H
#define _MATH_BLOCK_ANALYZER_H

#include "_semantic_analyzer_.hpp"

inline void SemanticAnalyzer::MathBlockAnalyzer::pushOperator()
{
    using SemanticAnalyzer::iterator;

    auto op = iterator->_flag;
    auto precedence = this->getPrecedence(op);

    while(this->_mathStack.size() > 0 && this->_mathStack.back() != BytecodeFlags::Flag_Args_Start && precedence < this->getPrecedence(this->_mathStack.back()))
    {
        this->popOperator();
    }

    this->_mathStack.push_back(op);
}

inline void SemanticAnalyzer::MathBlockAnalyzer::popOperator()
{
    if(this->_mathStack.size() != 0 && this->_valueCount > 0)
    {
        auto op = this->_mathStack.back();

        this->_mathStack.pop_back();

        if(!SronToken::isUnaryOperator(op)) --this->_valueCount;
    }
    else
    {
        throw ThrowException("analyzing the mathematical block. The expression is invalid", SronError::MathBlockSyntaxError, SemanticAnalyzer::iterator->_file_index);
    }
}

constexpr inline unsigned short SemanticAnalyzer::MathBlockAnalyzer::getPrecedence(const BytecodeFlags __op)
{
    return PostFixGenerator::PRECEDENCE(__op);
}

inline void SemanticAnalyzer::MathBlockAnalyzer::startAnalysis()
{
    using SemanticAnalyzer::iterator;

    ++iterator;

    for(; iterator < SemanticAnalyzer::tokenVectorEnd && iterator->_flag != BytecodeFlags::Flag_EvalEnd; ++iterator)
    {
        if(iterator->isValueType())
        {
            ++this->_valueCount;
            SemanticAnalyzer::VALUE_TYPE_CHECK();
        }
        else if(iterator->_flag == BytecodeFlags::Flag_Args_Start)  // '('
        {
            this->_mathStack.push_back(iterator->_flag);
        }
        else if(iterator->_flag == BytecodeFlags::Flag_Args_End)    // ')'
        {
            while(this->_mathStack.size() > 0 && this->_mathStack.back() != BytecodeFlags::Flag_Args_Start)
            {
                this->popOperator();
            }

            if(this->_mathStack.size() != 0) this->_mathStack.pop_back();  // removing the '('
        }
        else if(iterator->isOperator())
        {
            this->pushOperator();
        }
        else
        {
            throw ThrowException("analyzing the code. Expected a value type or operator but found token '"+ iterator->_token +"' in the Math block", SronError::MathBlockSyntaxError, iterator->_file_index);
        }
    }

    // final pops
    while(!this->_mathStack.empty())
    {
        this->popOperator();
    }

    if(this->_valueCount != 1) throw ThrowException("analyzing the code. Found invalid mathematical expression", SronError::MathBlockSyntaxError, iterator->_file_index);
}

#endif