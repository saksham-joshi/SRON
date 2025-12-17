/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 *
 * @author: SAKSHAM JOSHI
 *
 */

/*
    This file contains the implementation of Execution Engine which will execute the Instruction Vectors
    containing attributes and instructions.

    It will perform the following operations :
        1. Calling the functions
        2. Solving the mathematical expressions.
        3. Allocating variables.
        4. Executes Conditional statements.
        5. Executes looping statements.


    In overall, it will perform the most vital operations and it will act like a brain of SRON programming
    language.

*/

#pragma once

#include "headers/_user_fnc_.hpp"
#include "headers/_function_.hpp"

#ifndef EXECUTOR_H
#define EXECUTOR_H

namespace ExecutionEngine
{
    // called whem Flag_UserDefinedFunctionCall or Flag_InBuiltFunctionCall is found
    inline static void ASSIGN_ARGUMENTS(SronFncPtr);

    // called when Flag_Assign is found. Assign the variable with a value
    inline static AnyBindPtr  ASSIGN_VALUE(SronFncPtr);

    inline static AnyBindPtr CALL_IN_BUILT_FUNCTION(SronFncPtr);

    inline static AnyBindPtr CALL_USER_DEFINED_FUNCTION(SronFncPtr);

    // called when Flag_ConsoleStart is found. Prints the variables without generating the Argument_List
    inline static void CONSOLE_VALUES(SronFncPtr);
    
    inline static AnyBindPtr EXTRACT_INT(SronFncPtr);
    inline static AnyBindPtr EXTRACT_DOUBLE(SronFncPtr);
    inline static AnyBindPtr EXTRACT_CHAR(SronFncPtr);
    inline static AnyBindPtr EXTRACT_STRING(SronFncPtr);
    inline static AnyBindPtr EXTRACT_LIST(SronFncPtr);

    inline static void EXECUTE_FUNCTION(SronFncPtr);

    inline static void EXTRACT_ARGUMENTS(SronFncPtr, ArgListPtr);

    // called when Flag_Identifier_Variable is found. Extracts the value from the VariableManager
    inline static AnyBindPtr EXTRACT_IDENTIFIER(SronFncPtr);

    // called when Flag_EvalStart is found. Solves the postfix expression ...
    inline static AnyBindPtr EVALUATE(SronFncPtr);

    inline static void EXECUTE_CONDITIONAL_STATEMENT(SronFncPtr);
    inline static void EXECUTE_FOR_STATEMENT(SronFncPtr);
    inline static void EXECUTE_WHILE_STATEMENT(SronFncPtr);
    inline static void EXECUTE_FOREACH_STATEMENT(SronFncPtr);
    
    // maps the flags to functions of this namespace ...!!
    inline static AnyBindPtr FLAG_TO_FUNCTION_MAP(const flag_t, SronFncPtr);

    // starts the Execution Engine ...
    inline static void MAIN(AnyBindPtr);

    // moves the seek of the file to the end of conditional statement by adding up closing indices
    inline static void MOVE_SEEK_TO_END_OF_CONDITIONAL_STATEMENT(SronFncPtr);

    inline static AnyBindPtr REFINE_TO_INT(SronFncPtr);
    inline static AnyBindPtr REFINE_TO_DOUBLE(SronFncPtr);
    inline static AnyBindPtr REFINE_TO_CHAR(SronFncPtr);
    inline static AnyBindPtr REFINE_TO_BOOL(SronFncPtr);
    inline static AnyBindPtr REFINE_TO_STRING(SronFncPtr);
    inline static AnyBindPtr REFINE_TO_LIST(SronFncPtr);

    inline static void RETURN_VALUE(SronFncPtr);

    inline static void ROTATE_VARIABLES(SronFncPtr);

    inline static AnyBindPtr  ADD_AND_ASSIGN(SronFncPtr);
    inline static AnyBindPtr  MIN_AND_ASSIGN(SronFncPtr);
    inline static AnyBindPtr  MULT_AND_ASSIGN(SronFncPtr);
    inline static AnyBindPtr  DIV_AND_ASSIGN(SronFncPtr);
    inline static AnyBindPtr  MOD_AND_ASSIGN(SronFncPtr);
    inline static AnyBindPtr  POW_AND_ASSIGN(SronFncPtr);
}

#endif