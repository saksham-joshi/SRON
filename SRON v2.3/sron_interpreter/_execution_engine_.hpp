
#pragma once

#include "_if_elif_else_.hpp"

// this function loads the Main.srb file and starts the execution of the code.
// keep in mind that the Main.srb file doesn't get cached in 
// BytecodeManager::__UserDefinedFncMap__
inline static void ExecutionEngine::MAIN(AnyBindPtr __arglist)
{
    ArgumentList args(__arglist);

    BytecodeManager::BytecodeBinder mainfile( SRON_MAIN_FILE , SRON_MAIN_FILE );

    SronFunction __main__( mainfile , &args);

    ExecutionEngine::EXECUTE_FUNCTION(&__main__ , SRON_MAIN_FILE );
    
}

inline void ExecutionEngine::EXECUTE_FUNCTION(SronFncPtr __top, const char*const __filename)
{
}

inline static AnyBindPtr ExecutionEngine::CALL_IN_BUILT_FUNCTION(SronFncPtr __top)
{

}

inline static AnyBindPtr ExecutionEngine::CALL_USER_DEFINED_FUNCTION(SronFncPtr __top)
{

}

inline static AnyBindPtr ExecutionEngine::FLAG_TO_FUNCTION_MAP(const BytecodeFlags __flag, SronFncPtr __top)
{

}
