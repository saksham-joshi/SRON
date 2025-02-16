#pragma once

#include "_loops_.hpp"

inline static void ExecutionEngine::EXECUTE_CONDITIONAL_STATEMENT(SronFncPtr __top)
{
    // storing the index, if the condition turns out to be false
    auto set_position = __top->_codefile.READ_LONG();

    if(!(ExecutionEngine::FLAG_TO_FUNCTION_MAP(__top->_codefile.READ_FLAG(), __top)->ptr_->GET_BOOL_ABS()))
    {
        __top->_codefile.SET_SEEK_AT(set_position);
    }
}

inline static void ExecutionEngine::MOVE_SEEK_TO_END_OF_CONDITIONAL_STATEMENT(SronFncPtr __top)
{

    flag_t flag = __top->_codefile.READ_FLAG();

    while(flag == Flag_ElifScopeStart || flag == Flag_ElseScopeStart)
    {

        __top->_codefile.SET_SEEK_AT(__top->_codefile.READ_LONG());

        flag = __top->_codefile.READ_FLAG();
    }

    __top->_codefile.DECREMENT_SEEK_BY(sizeof(flag_t)) ;

}