
#pragma once

#include "_if_elif_else_.hpp"

// this function loads the MAIN.srb file and starts the execution of the code.
inline static void ExecutionEngine::MAIN(AnyBindPtr __arglist)
{

    ArgumentList args(__arglist);

    SronFunction __main__("MAIN.srb", &args);

    ExecutionEngine::EXECUTE_FUNCTION(&__main__);
    
}

inline void ExecutionEngine::EXECUTE_FUNCTION(SronFncPtr __top)
{

}

inline static AnyBindPtr ExecutionEngine::CALL_IN_BUILT_FUNCTION(SronFncPtr __top)
{

}

inline static AnyBindPtr ExecutionEngine::CALL_USER_DEFINED_FUNCTION(SronFncPtr __top)
{

}

inline static AnyBindPtr ExecutionEngine::FLAG_TO_FUNCTION_MAP(const flag_t __flag, SronFncPtr __top)
{
   
}