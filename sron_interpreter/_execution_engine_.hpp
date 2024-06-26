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

    *| All the comments in this file uses some words which refers to different variables, explaination given below :
       1. iterator : ExecutionEngine::_FunctionStack_.top()._iterator;
       2. flags : it contains the #define Flags_... , defined in headers/_flags_.hpp

*/

#include "headers/_user_fnc_.hpp"
#include "headers/_support_.hpp"
#include "headers/_converter_.hpp"
#include "headers/_function_.hpp"

#ifndef EXECUTOR_H
#define EXECUTOR_H

inline namespace ExecutionEngine
{
    inline static Any *ASSIGN_VALUE(SronFunction &);

    inline static Any *ASSIGN_ARGUMENTS(SronFunction &);

    inline static Any *BREAK_LOOP(SronFunction &);

    inline static Any *CONTINUE_LOOP(SronFunction &);

    inline static Any *CREATE_VARIABLE(SronFunction &);

    inline static Any *CALL_FUNCTION(SronFunction &);

    inline static Any *EXECUTE_FUNCTION(SronFunction &);

    inline static Any *EXECUTE_FUNCTION(std::string &function_name, Argument_List &args);

    inline static void EXTRACT_ARGUMENTS(SronFunction &, Argument_List &args);

    inline static Any *EXTRACT_STRING(SronFunction &);

    inline static Any *EXTRACT_CHAR(SronFunction &);

    inline static Any *EXTRACT_DOUBLE(SronFunction &);

    inline static Any *EXTRACT_INT(SronFunction &);

    inline static Any *EXTRACT_LIST(SronFunction &);

    inline static Any *EXTRACT_BOOL(SronFunction &);

    inline static Any *EXTRACT_IDENTIFIER(SronFunction &);

    inline static Any *EVALUATE(SronFunction &);

    inline static Any *EXECUTE_CONDITIONAL_STATEMENT(SronFunction &);

    inline static Any *EXECUTE_ELSE_STATEMENT(SronFunction &);

    inline static Any *EXECUTE_FOR_STATEMENT(SronFunction &);

    inline static Any *EXECUTE_WHILE_STATEMENT(SronFunction &);

    inline static Any *FLAG_TO_FUNCTION_MAP(SronFunction &);

    inline static Any *FREE_FROM_VMANAGER(SronFunction &);

    inline static Any *GET_VOID(SronFunction &);

    inline static Any *NOTHING_PERFORMING_FUNCTION(SronFunction &);

    inline static Any *RETURN_VALUE(SronFunction &);

    //================ Functions which are not mapped by the ExecutionEngine::_funcmap_ .....

    inline static bool SOLVE_CONDITION(SronFunction &);

    inline static std::string &GET_RANGE_VARIABLES(SronFunction &, Any **, Any **, Any **);

    inline static void MOVE_ITERATOR_BEYOND_CONDITIONAL_STATEMENT(SronFunction &);


    // this bool variable is used to check if a loop exiting because of break keyword.
    static bool _BREAK_ = false;

    static const std::unordered_map<std::string, std::function<void(std::stack<Any *> &, Any &val1, Any &val2)>> _eval_map_{
        {"+", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(val1 + val2); }},
        {"-", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(val1 - val2); }},
        {"*", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(val1 * val2); }},
        {"/", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(val1 / val2); }},
        {"%", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(val1 % val2); }},
        {"^", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(val1 ^ val2); }},
        {"&&", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(new Bool(val1 && val2)); }},
        {"||", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(new Bool(val1 || val2)); }},
        {"==", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(new Bool(val1 == val2)); }},
        {"!=", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(new Bool(val1 != val2)); }},
        {">", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(new Bool(val1 > val2)); }},
        {">=", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(new Bool(val1 >= val2)); }},
        {"<", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(new Bool(val1 < val2)); }},
        {"<=", [](std::stack<Any *> &stk, Any &val1, Any &val2)
         { stk.push(new Bool(val1 <= val2)); }}};

    static const std::unordered_map<std::string, std::function<Any *(SronFunction &)>> _funcmap_{
        {Flag_Int_Value, ExecutionEngine::EXTRACT_INT},
        {Flag_Double_Value, ExecutionEngine::EXTRACT_DOUBLE},
        {Flag_Char_Value, ExecutionEngine::EXTRACT_CHAR},
        {Flag_String_Value, ExecutionEngine::EXTRACT_STRING},
        {Flag_Bool_Value, ExecutionEngine::EXTRACT_BOOL},
        {Flag_ListStart, ExecutionEngine::EXTRACT_LIST},

        {Flag_Identifier_Variable, ExecutionEngine::EXTRACT_IDENTIFIER},

        {Flag_EvalStart, ExecutionEngine::EVALUATE},
        {Flag_Variable, ExecutionEngine::CREATE_VARIABLE},
        {Flag_Assign, ExecutionEngine::ASSIGN_VALUE},
        {Flag_FunctionArgsScopeStart, ExecutionEngine::ASSIGN_ARGUMENTS},
        {Flag_FunctionCall, ExecutionEngine::CALL_FUNCTION},

        {Flag_Any, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_Void, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_Int, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_Double, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_Char, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_Bool, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_String, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_List, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},

        {Flag_Break, ExecutionEngine::BREAK_LOOP},
        {Flag_Continue, ExecutionEngine::CONTINUE_LOOP},
        {Flag_Return, ExecutionEngine::RETURN_VALUE},
        {Flag_Free, ExecutionEngine::FREE_FROM_VMANAGER},

        {Flag_IfScopeStart, ExecutionEngine::EXECUTE_CONDITIONAL_STATEMENT},
        {Flag_ElifScopeStart, ExecutionEngine::EXECUTE_CONDITIONAL_STATEMENT},
        {Flag_ElseScopeStart, ExecutionEngine::EXECUTE_ELSE_STATEMENT},

        {Flag_ForScopeStart, ExecutionEngine::EXECUTE_FOR_STATEMENT},
        {Flag_WhileScopeStart, ExecutionEngine::EXECUTE_WHILE_STATEMENT},

    };

    // this function loads the MAIN.srb file and starts the execution of the code.
    inline static void MAIN(List &arglist)
    {
        try
        {
            Argument_List args(&arglist);

            SronFunction _main_("MAIN", args);

            Logs::filename = "MAIN.srb" ;

            ExecutionEngine::EXECUTE_FUNCTION(_main_);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing the 'MAIN' function.", SystemOutofMemoryException, false);
        }
    }
}
#endif