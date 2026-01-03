#pragma once

#include "inbuilts/_file_fnc_.hpp"

#ifndef EXECUTOR_H
#define EXECUTOR_H

namespace ExecutionEngine
{

    // called whem Flag_UserDefinedFunctionCall or Flag_InBuiltFunctionCall is found
    [[gnu::hot]] inline static void       ASSIGN_ARGUMENTS(SronFncPtr);

    // called when Flag_Assign is found. Assign the variable with a value
    [[gnu::hot]] inline static AnyBindPtr ASSIGN_VALUE(SronFncPtr);

    [[gnu::hot]] inline static AnyBindPtr CALL_IN_BUILT_FUNCTION(SronFncPtr);

    [[gnu::hot]] inline static AnyBindPtr CALL_USER_DEFINED_FUNCTION(SronFncPtr);

    // called when Flag_ConsoleStart is found. Prints the variables without generating the Argument_List
    [[gnu::hot]] inline static void       CONSOLE_VALUES(SronFncPtr);

    template <typename Tp>
    [[gnu::always_inline]] [[gnu::hot]] inline static AnyBindPtr DECLARE_VARIABLE( SronFncPtr , SronTypeNum );
    [[gnu::hot]] [[gnu::always_inline]] inline static AnyBindPtr DECLARE_LSTR(SronFncPtr);

    [[gnu::hot]] inline static AnyBindPtr EXTRACT_STRING(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr EXTRACT_LIST(SronFncPtr);

    [[gnu::hot]] inline static void       EXECUTE_FUNCTION( SronFncPtr, const char*const );

    [[gnu::hot]] inline static void       EXTRACT_ARGUMENTS(SronFncPtr, ArgListRef);

    // called when Flag_EvalStart is found. Solves the postfix expression ...
    [[gnu::hot]] inline static AnyBindPtr EVALUATE(SronFncPtr);

    [[gnu::hot]] inline static void       EXECUTE_CONDITIONAL_STATEMENT(SronFncPtr);
    [[gnu::hot]] inline static void       EXECUTE_FOR_STATEMENT(SronFncPtr);
    [[gnu::hot]] inline static void       EXECUTE_WHILE_STATEMENT(SronFncPtr);
    [[gnu::hot]] inline static void       EXECUTE_FOREACH_STATEMENT(SronFncPtr);

    [[gnu::hot]] inline static void       EXECUTE_WINDOWS_BLOCK(SronFncPtr);
    [[gnu::hot]] inline static void       EXECUTE_LINUX_BLOCK  (SronFncPtr);
    
    // maps the flags to functions of this namespace ...!!
    [[gnu::hot]] inline static AnyBindPtr FLAG_TO_FUNCTION_MAP(const BytecodeFlags, SronFncPtr);

    [[gnu::hot]] inline static void       INSERT_INTO_BUFFER( SronFncPtr );

    // starts the Execution Engine ...
    inline static void MAIN(AnyBindPtr);

    // moves the seek of the file to the end of conditional statement by adding up closing indices
    [[gnu::hot]] inline static void       MOVE_SEEK_TO_END_OF_CONDITIONAL_STATEMENT(SronFncPtr);
    
    [[gnu::hot]] inline static AnyBindPtr REFINE_TO_INT(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr REFINE_TO_DOUBLE(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr REFINE_TO_CHAR(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr REFINE_TO_BOOL(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr REFINE_TO_STRING(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr REFINE_TO_LIST(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr REFINE_TO_FREADER(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr REFINE_TO_FWRITER(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr REFINE_TO_LSTR(SronFncPtr);

    [[gnu::hot]] inline static void        RETURN_VALUE(SronFncPtr);

    [[gnu::hot]] inline static void        ROTATE_VARIABLES(SronFncPtr);

    [[gnu::hot]] inline static AnyBindPtr  ADD_AND_ASSIGN(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr  MIN_AND_ASSIGN(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr  MULT_AND_ASSIGN(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr  DIV_AND_ASSIGN(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr  MOD_AND_ASSIGN(SronFncPtr);
    [[gnu::hot]] inline static AnyBindPtr  POW_AND_ASSIGN(SronFncPtr);

    namespace Logs
    {
        unsigned short CALL_STACK_SIZE = 0;

        constexpr const unsigned short MAX_CALL_STACK_SIZE = 2000;

        struct CallStackOverflow
        {
            const char*const _message = "calling a function which overflowed the Call stack. The Max Limit of Call Stack is '2000'";
            const char*const _exception = SronException::CallStackOverflowException;
            SronExitCodes _exitcode = SronExitCodes::STACK_OVERFLOW;

            CallStackOverflow( ) { }
        };

        [[gnu::hot]] [[gnu::always_inline]] inline static void incrementCallStack(void)
        {
            if ( Logs::CALL_STACK_SIZE >= Logs::MAX_CALL_STACK_SIZE) [[unlikely]] throw CallStackOverflow();

            ++Logs::CALL_STACK_SIZE;
        }

        [[gnu::hot]] [[gnu::always_inline]] inline static void decrementCallStack(void) noexcept
        {
            --Logs::CALL_STACK_SIZE;
        }
    }
}

#endif