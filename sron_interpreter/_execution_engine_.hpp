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
    /* This stack object contains the reference to the user_defined function being called by the user.
     * In-built functions defined in  _user_fnc_.hpp::Sron namespace are automatically handled by the
     * machine.
     */
    std::stack<SronFunction *> _FunctionStack_;

    inline static Any *ASSIGN_VALUE();

    inline static Any *ASSIGN_ARGUMENTS();

    inline static Any *BREAK_LOOP();

    inline static Any *CONTINUE_LOOP();

    inline static Any *CREATE_VARIABLE();

    inline static Any *CALL_FUNCTION();

    inline static Any *EXECUTE_FUNCTION(std::string &function_name, Argument_List *args);

    inline static Argument_List *EXTRACT_ARGUMENTS();

    inline static Any *EXTRACT_STRING();

    inline static Any *EXTRACT_CHAR();

    inline static Any *EXTRACT_DOUBLE();

    inline static Any *EXTRACT_INT();

    inline static Any *EXTRACT_LIST();

    inline static Any *EXTRACT_BOOL();

    inline static Any *EXTRACT_IDENTIFIER();

    inline static Any *EVALUATE();

    inline static Any *EXECUTE_CONDITIONAL_STATEMENT();

    inline static Any *EXECUTE_ELSE_STATEMENT();

    inline static Any *EXECUTE_FOR_STATEMENT();

    inline static Any *EXECUTE_WHILE_STATEMENT();

    inline static Any *FLAG_TO_FUNCTION_MAP();

    inline static Any *HANDLE_OPENING_SCOPES();

    inline static Any *HANDLE_CLOSING_SCOPES();

    //inline static Any *INCREMENT_ITERATOR();

    inline static Any *NOTHING_PERFORMING_FUNCTION();

    inline static Any *RETURN_VALUE();

    //================ Functions which are not mapped by the ExecutionEngine::_funcmap_ .....

    inline static bool SOLVE_CONDITION(std::vector<std::string>::iterator *it);

    inline static std::string &GET_RANGE_VARIABLES(Any **, Any **, Any **);

    inline static void MOVE_ITERATOR_BEYOND_CONDITIONAL_STATEMENT();

    /* This function takes two Flags as parameter and move the iterator to out of the scope.*/
    //inline static void EXIT_ITERATOR_FROM_SCOPE(const char *, const char *);

    // this bool variable is used to check if a loop exiting because of break keyword.
    static bool _BREAK_ = false;

    static const std::unordered_map<std::string, std::function<void(std::stack<Any*>&, Any* val1, Any* val2)>> _eval_map_{
        {"+",  [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push((*val1) + (*val2)); }},
        {"-",  [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push((*val1) - (*val2)); }},
        {"*",  [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push((*val1) * (*val2)); }},
        {"/",  [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push((*val1) / (*val2)); }},
        {"%",  [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push((*val1) % (*val2)); }},
        {"^",  [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push((*val1) ^ (*val2)); }},
        {"&&", [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push(new Bool(*val1 && *val2)); }},
        {"||", [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push(new Bool(*val1 || *val2)); }},
        {"==", [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push(new Bool(*val1 == *val2)); }},
        {"!=", [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push(new Bool(*val1 != *val2)); }},
        {">",  [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push(new Bool(*val1 > *val2)); }},
        {">=", [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push(new Bool(*val1 >= *val2)); }},
        {"<",  [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push(new Bool(*val1 < *val2)); }},
        {"<=", [](std::stack<Any*>& stk, Any* val1, Any* val2) { stk.push(new Bool(*val1 <= *val2)); }}
    };

    static const std::unordered_map<std::string, std::function<Any *()>> _funcmap_{
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
        {Flag_ScopeStart, ExecutionEngine::HANDLE_OPENING_SCOPES},
        {Flag_ScopeEnd, ExecutionEngine::HANDLE_CLOSING_SCOPES},
        {Flag_FunctionCall, ExecutionEngine::CALL_FUNCTION},

        {Flag_Any, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_Int, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_Double, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_Char, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_Bool, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_String, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},
        {Flag_List, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},

        {Flag_Break, ExecutionEngine::BREAK_LOOP},
        {Flag_Continue, ExecutionEngine::CONTINUE_LOOP},
        {Flag_Return, ExecutionEngine::RETURN_VALUE},

        {Flag_IfScopeStart, ExecutionEngine::EXECUTE_CONDITIONAL_STATEMENT},
        {Flag_ElifScopeStart, ExecutionEngine::EXECUTE_CONDITIONAL_STATEMENT},
        {Flag_ElseScopeStart, ExecutionEngine::EXECUTE_ELSE_STATEMENT},

        {Flag_ForScopeStart, ExecutionEngine::EXECUTE_FOR_STATEMENT},
        {Flag_WhileScopeStart, ExecutionEngine::EXECUTE_WHILE_STATEMENT},

    };

    // This function calculates the current line number of the code and set it to Logs::line_number.
    inline static void SET_LINE_NUMBER_TO_STATIC_LOG()
    {
        Logs::line_number += ExecutionEngine::_FunctionStack_.top()->_iterator - ExecutionEngine::_FunctionStack_.top()->_codevector.begin();
    }

    // this function loads the MAIN.srb file and starts the execution of the code.
    inline static void MAIN(List *arglist)
    {
        try
        {
            SronFunction _main_("MAIN", new Argument_List(arglist));

            Logs::filename = "MAIN.srb";

            ExecutionEngine::_FunctionStack_.push(&_main_);

            for (; _main_._iterator < _main_._end; ++_main_._iterator)
            {
                ExecutionEngine::FLAG_TO_FUNCTION_MAP();
            }

            if (!_main_._scopestack.empty())
            {
                ExecutionEngine::_FunctionStack_.pop();
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing the 'MAIN' function.", SystemOutofMemoryException, false);
        }
    }
}
#endif