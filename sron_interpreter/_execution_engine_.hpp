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

    inline static Any *INCREMENT_ITERATOR();

    inline static Any *NOTHING_PERFORMING_FUNCTION();

    inline static Any *RETURN_VALUE();

    //================ Functions which are not mapped by the ExecutionEngine::_funcmap_ .....

    inline static bool SOLVE_CONDITION();

    inline static std::string &GET_RANGE_VARIABLES(Any **, Any **, Any **);

    inline static void MOVE_ITERATOR_BEYOND_CONDITIONAL_STATEMENT();

    /* This function takes two Flags as parameter and move the iterator to out of the scope.*/
    inline static void EXIT_ITERATOR_FROM_SCOPE(const char *, const char *);

    // this bool variable is used to check if a loop exiting because of break keyword.
    static bool _BREAK_ = false;

    // using ExecutionEngineFuncMap = ;

    static std::unordered_map<std::string, std::function<Any *()>> _funcmap_{
        {Flag_Int_Value, ExecutionEngine::EXTRACT_INT},
        {Flag_Double_Value, ExecutionEngine::EXTRACT_DOUBLE},
        {Flag_Char_Value, ExecutionEngine::EXTRACT_CHAR},
        {Flag_StringScopeStart, ExecutionEngine::EXTRACT_STRING},
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
        {Flag_LineEnd, ExecutionEngine::NOTHING_PERFORMING_FUNCTION},

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

    // assign the arguments of a function to the variable_manager
    inline static Any *ASSIGN_ARGUMENTS()
    {

        unsigned short int index = 0;

        const auto &_top_ = _FunctionStack_.top();

        auto it = &(++_top_->_iterator);

        const auto &end = _top_->_end;

        while (*it < end && **it != Flag_FunctionArgsScopeEnd)
        {
            // if a Flag_Variable is found, then the next element is a variable name
            if (**it == Flag_Variable)
            {
                ++(*it);
                _top_->_Vmanager.INSERT(**it, _top_->_arglist.GET(index));
                ++index;
            }
            ++*it;
        }

        return nullptr;
    }

    inline static Any *ASSIGN_VALUE()
    {
        try
        {
            const auto &_top_ = _FunctionStack_.top();

            // extracting the variable name which is going to store the value.
            std::string &variable_name = *(_top_->_iterator - 1);

            ++_top_->_iterator;

            // extracting the value from the flag
            auto value = ExecutionEngine::FLAG_TO_FUNCTION_MAP();

            // inserting the value to the variable manager
            _top_->_Vmanager.INSERT(variable_name, value);

            // returning the value so that the scenario where code written like this can work : a = b = c.
            return value;
        }
        catch (const std::exception &)
        {
            ExecutionEngine::SET_LINE_NUMBER_TO_STATIC_LOG();
            DISPLAY_EXCEPTION("assigning value to a variable .", SystemOutofMemoryException);
        }
        return nullptr;
    }

    /* This function is used to exit the loop.
     * It moves the ExecutionEngine::_FunctionStack.top()->_iterator to
     * the first occurence of the loop ending flag.
     */
    inline static Any *BREAK_LOOP()
    {

        const auto &_top_ = ExecutionEngine::_FunctionStack_.top();

        auto it = &(++_top_->_iterator);

        const auto &end = _top_->_end;

        // iterating until a loop ending flag is not found
        while (*it < end && (!Support::IS_LOOP_ENDING_FLAG(**it)))
        {
            // if there is a case where there is nested loop then it will again call
            // this function in recursive manner.
            if (Support::IS_LOOP_OPENING_FLAG(**it))
            {
                _top_->_scopestack.push(*it);
                BREAK_LOOP();
            }
            ++(*it);
        }

        ExecutionEngine::_BREAK_ = true;

        //_top_->_scopestack.pop();

        return nullptr;
    }

    /* This function will move the iterator next to the most recent Loop opening flag.
     * In case of forloop, it will move the iterator to the Flag_RangeScopeEnd
     * In case of whileloop, it will move the iterator to the Flag_ConditionScopeStart
     */
    inline static Any *CONTINUE_LOOP()
    {
        _FunctionStack_.top()->_iterator++ = _FunctionStack_.top()->_scopestack.top();

        return nullptr;
    }

    // this function creates the variable and saves it to the variable_manager.
    inline static Any *CREATE_VARIABLE()
    {

        auto it = &(++_FunctionStack_.top()->_iterator);

        _FunctionStack_.top()->_Vmanager.INSERT(*(*it - 2), **it);

        return nullptr;
    }

    /* This function will check if the function is in-built then it
     is executed otherwise it will call the EXECUTE_FUNCTION() function.

      - Invoked by Flag_FunctionCall
      - Ending Flag = Flag_Args_End
     */

    inline static Any *CALL_FUNCTION()
    {
        std::string fnc_name = *(++_FunctionStack_.top()->_iterator);

        // by incrementing the _iterator it will move to Flag_Args_Start
        // and now the arguments can be extracted
        ++_FunctionStack_.top()->_iterator;

        // checking if the function is in-built
        auto fnc = Sron::GET_SRON_FUNCTION(fnc_name);

        if (fnc != nullptr)
        {
            return fnc(ExecutionEngine::EXTRACT_ARGUMENTS());
        }

        return EXECUTE_FUNCTION(fnc_name, ExecutionEngine::EXTRACT_ARGUMENTS());
    }

    /*
     * This function creates the Argument list required to call a function.

     * Invoked by Flag_Args_Start
     * Ending Flag = Flag_Args_End
    */
    inline static Argument_List *EXTRACT_ARGUMENTS()
    {
        try
        {
            Argument_List *args = new Argument_List();

            // moving the iterator to next flag
            auto it = &(++_FunctionStack_.top()->_iterator);

            // running the loop until the Flag_Args_End is not found
            for (; **it != Flag_Args_End; ++*it)
            {
                args->PUT(ExecutionEngine::FLAG_TO_FUNCTION_MAP());
            }

            return args;
        }
        catch (const std::bad_alloc &)
        {
            ExecutionEngine::SET_LINE_NUMBER_TO_STATIC_LOG();
            DISPLAY_EXCEPTION("creating arguments to call function.", SystemOutofMemoryException);
        }
        catch (const std::exception &)
        {
        }
        return nullptr;
    }

    /* This function executes when an Flag_ElseScopeStart statement is found
     * It moves the ExecutionEngine::_FunctionStack_.top()->_iterator to the
     * end of loop where Flag_ElseScopeEnd resides.
     */
    inline static Any *EXECUTE_ELSE_STATEMENT()
    {
        auto it = &(++ExecutionEngine::_FunctionStack_.top()->_iterator);

        // const auto &end = ExecutionEngine::_FunctionStack_.top()->_end;

        for (; **it != Flag_ElseScopeEnd; ++*it)
        {
            ExecutionEngine::FLAG_TO_FUNCTION_MAP();
        }

        return nullptr;
    }

    // if the function is user-defined then this function is called.
    inline static Any *EXECUTE_FUNCTION(std::string &function_name, Argument_List *args)
    {
        try
        {
            SronFunction fnc(function_name, args);

            ExecutionEngine::_FunctionStack_.push(&fnc);

            Logs::filename = function_name + ".srb";

            // code here ...
            for (; fnc._iterator < fnc._end; ++fnc._iterator)
            {
                ExecutionEngine::FLAG_TO_FUNCTION_MAP();
            }

            if (!ExecutionEngine::_FunctionStack_.empty())
            {
                ExecutionEngine::_FunctionStack_.pop();
            }

            return (fnc._return_value == nullptr) ? new Void() : fnc._return_value;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing the function '" + function_name + "'.", SystemOutofMemoryException, false);
        }
        return nullptr;
    }

    inline static Any *EXTRACT_INT()
    {
        return new Int(Converter::TO_INT(*(++_FunctionStack_.top()->_iterator)));
    }

    inline static Any *EXTRACT_DOUBLE()
    {
        return new Double(Converter::TO_DOUBLE(*(++_FunctionStack_.top()->_iterator)));
    }

    inline static Any *EXTRACT_CHAR()
    {
        auto char_value = *(++_FunctionStack_.top()->_iterator);

        if (char_value == "\\n")
        {
            return new Char('\n');
        }
        else if (char_value == "\\t")
        {
            return new Char('\t');
        }
        return new Char((char_value)[0]);
    }

    inline static Any *EXTRACT_BOOL()
    {

        return new Bool((*(++_FunctionStack_.top()->_iterator) == "true") ? true : false);
    }

    inline static Any *EXTRACT_STRING()
    {
        auto it = &(++_FunctionStack_.top()->_iterator);

        const auto &end = *it + Converter::TO_INT(**it);

        ++(*it);

        String *str = new String("");

        for (; *it < end; ++(*it))
        {
            str->APPENDS(**it + '\n');
        }
        str->POP_BACK();

        return str;
    }

    inline static Any *EXTRACT_IDENTIFIER()
    {
        return _FunctionStack_.top()->_Vmanager.GET(*(++_FunctionStack_.top()->_iterator));
    }

    // This function created the List and returns it.
    inline static Any *EXTRACT_LIST()
    {
        try
        {
            List *lst = new List();

            auto it = &(++_FunctionStack_.top()->_iterator);

            const auto &end = _FunctionStack_.top()->_end;

            while (*it < end && ((**it) != Flag_ListEnd))
            {
                lst->PUSH(ExecutionEngine::FLAG_TO_FUNCTION_MAP());
                ++(*it);
            }

            return lst;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("creating the list.", SystemOutofMemoryException);
        }
        return nullptr;
    }

    /* This method is executed when Flag_IfScopeStart or Flag_ElifScopeStart is found.
     * Ending flag = Flag_IfScopeEnd or Flag_ElifScopeEnd or Flag_ElseScopeEnd
     */
    inline static Any *EXECUTE_CONDITIONAL_STATEMENT()
    {

        /* This function is called when Flag_IfScopeStart or Flag_ElifScopeStart is found.
         * So different ending flag is required to execute the code inside the scope of
         * the conditional statement. That's why i saved the ending flag.
         */

        const auto &_top_ = ExecutionEngine::_FunctionStack_.top();

        const char *current_flag = (*_top_->_iterator).c_str();
        const char *end_flag = (*_top_->_iterator == Flag_IfScopeStart) ? Flag_IfScopeEnd : Flag_ElifScopeEnd;

        auto it = &(++_top_->_iterator);

        if (**it == Flag_ConditionScopeStart && !SOLVE_CONDITION())
        {
            /* If the condition is found to be false, then the iterator is moved to the end of the
             * conditional statement's scope.
             */
            ExecutionEngine::EXIT_ITERATOR_FROM_SCOPE(end_flag, current_flag);

            ++(*it);

            /*
             * Now, if the flag is Flag_ElifScopeStart, then the code this function is called.
             * if the flag is Flag_ElseScopeStart, then ExecutionEngine::EXECUTE_ELSE_STATEMENT()
             * is called.
             *
             * If both of the flag is not found, then the iterator is decremented so that the
             * loop which is running this function will increment the iterator. If not decremented
             * the flag will be missed which can cause troubles then.
             */
            if (**it == Flag_ElifScopeStart)
            {
                ExecutionEngine::EXECUTE_CONDITIONAL_STATEMENT();
                if (*(*it + 1) == Flag_ElseScopeStart)
                {
                    ExecutionEngine::EXECUTE_ELSE_STATEMENT();
                }
            }
            else if (**it == Flag_ElseScopeStart)
            {
                ExecutionEngine::EXECUTE_ELSE_STATEMENT();
            }
            else
            {
                // if the 'If' statement cannot executed successfully, then it is required to decrete
                // the iterator otherwise it will throw error.
                --(*it);
            }

            return nullptr;
        }

        /* If the condition inside the if-elif statement is true, then the below code will run....*/

        // moving the iterator next to the flag Flag_ConditionScopeEnd
        ++(*it);

        // if the condition is true, then code inside it will run.
        const auto &end = _top_->_end;

        while (*it < end && **it != end_flag)
        {
            ExecutionEngine::FLAG_TO_FUNCTION_MAP();
            ++(*it);
        }

        // moving the iterator next to the end_flag
        ++(*it);

        // exiting the conditional area because code within the scope of if-elif statement is executed successfully.
        ExecutionEngine::MOVE_ITERATOR_BEYOND_CONDITIONAL_STATEMENT();

        return nullptr;
    }

    // This function executes when Flag_ForScopeStart is found.
    inline static Any *EXECUTE_FOR_STATEMENT()
    {
        const auto &_top_ = ExecutionEngine::_FunctionStack_.top();

        auto it = &(_top_->_iterator);

        const auto &end = _top_->_end;

        Any *loop_start = &void_object;
        Any *loop_end = &void_object;
        Any *loop_step = &void_object;

        // extracting the variables of range of loop.
        std::string iteration_variable = ExecutionEngine::GET_RANGE_VARIABLES(&loop_start, &loop_end, &loop_step);

        /* the current flag is Flag_RangeScopeEnd, increment it again and save in the stack.*/
        ++(*it);
        _top_->_scopestack.push(*it);

        if (*loop_start < *loop_end)
        {
            for (; *it < end && ((*loop_start) < (*loop_end));)
            {

                while (*it < end && **it != Flag_ForScopeEnd)
                {
                    ExecutionEngine::FLAG_TO_FUNCTION_MAP();
                    ++(*it);
                }

                *it = _top_->_scopestack.top();

                (_top_->_Vmanager.INSERT(iteration_variable, (*_top_->_Vmanager.GET(iteration_variable) + *loop_step)));

                loop_start = _top_->_Vmanager.GET(iteration_variable);
            }
        }
        else
        {
            for (; *it < end && (*loop_start > *loop_end);)
            {

                while (*it < end && **it != Flag_ForScopeEnd)
                {
                    ExecutionEngine::FLAG_TO_FUNCTION_MAP();
                    ++(*it);
                }

                *it = _top_->_scopestack.top();

                (_top_->_Vmanager.INSERT(iteration_variable, (*_top_->_Vmanager.GET(iteration_variable) + *loop_step)));

                *loop_start = *_top_->_Vmanager.GET(iteration_variable);
            }
        }

        ExecutionEngine::EXIT_ITERATOR_FROM_SCOPE(Flag_ForScopeEnd, Flag_ForScopeStart);

        _top_->_scopestack.pop();

        return nullptr;
    }

    // This function executes when Flag_WhileScopeStart is found.
    inline static Any *EXECUTE_WHILE_STATEMENT()
    {
        try
        {

            const auto &_top_ = _FunctionStack_.top();

            auto it = &(++_top_->_iterator);

            // pushing the flag next to the Flag_WhileScopeStart
            _top_->_scopestack.push(*it);

            const auto &end = _top_->_end;

            while (*it < end)
            {

                /* Checking if the condition given in the while loop is true or not.
                 * If the condition is false, the iterator is moved to the end of the
                 * while loop where Flag_WhileScopeEnd resides.
                 */
                if (**it == Flag_ConditionScopeStart && !SOLVE_CONDITION())
                {
                    BREAK_LOOP();
                    ExecutionEngine::_BREAK_ = false;
                    break;
                }

                /* If the condition is true, then the iterator is incremented by 1, so
                 * that the iterator is moved next to the occurrence of Flag_ConditionScopeEnd
                 */
                ++(*it);

                while (*it < end && **it != Flag_WhileScopeEnd)
                {
                    ExecutionEngine::FLAG_TO_FUNCTION_MAP();
                    ++(*it);
                }

                // moving the iterator to the position where condition starts
                *it = _top_->_scopestack.top();
            }

            _top_->_scopestack.pop();

            return nullptr;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing the while statement. At : " + (*_FunctionStack_.top()->_iterator) + ".", InvalidByteCodeException, false);
        }
        return nullptr;
    }

    inline static Any *EVALUATE()
    {
        // std::cout << "\n>Start EVALUATE()<\n";
        try
        {
            std::vector<std::string>::iterator *it = &(++_FunctionStack_.top()->_iterator);

            const auto &end = _FunctionStack_.top()->_end;

            std::stack<Any *> stk;

            while (*it < end && (**it) != Flag_EvalEnd)
            {
                // if the element is a flag then there must be a value there next to it
                if (Support::IS_FLAG(**it))
                {
                    stk.push(ExecutionEngine::FLAG_TO_FUNCTION_MAP());
                }
                else if (**it == "!")
                {
                    Bool *val = new Bool(!(*stk.top()));
                    stk.pop();
                    stk.push(val);
                }
                else
                {
                    // if no flag is there then there must be a operator
                    Any *val2 = stk.top();
                    stk.pop();

                    Any *val1 = stk.top();
                    stk.pop();

                    std::string &op = **it;

                    if (op == "+")
                    {
                        stk.push((*val1) + (*val2));
                    }
                    else if (op == "-")
                    {
                        stk.push((*val1) - (*val2));
                    }
                    else if (op == "*")
                    {
                        stk.push((*val1) * (*val2));
                    }
                    else if (op == "/")
                    {
                        stk.push((*val1) / (*val2));
                    }
                    else if (op == "%")
                    {
                        stk.push((*val1) % (*val2));
                    }
                    else if (op == "^")
                    {
                        stk.push((*val1) ^ (*val2));
                    }
                    else if (op == "&&")
                    {
                        stk.push(new Bool(*val1 && *val2));
                    }
                    else if (op == "||")
                    {
                        stk.push(new Bool(*val1 || *val2));
                    }
                    else if (op == "==")
                    {
                        stk.push(new Bool(*val1 == *val2));
                    }
                    else if (op == "!=")
                    {
                        stk.push(new Bool(*val1 != *val2));
                    }
                    else if (op == ">")
                    {
                        stk.push(new Bool(*val1 > *val2));
                    }
                    else if (op == ">=")
                    {
                        stk.push(new Bool(*val1 >= *val2));
                    }
                    else if (op == "<")
                    {
                        stk.push(new Bool(*val1 < *val2));
                    }
                    else if (op == "<=")
                    {
                        stk.push(new Bool(*val1 <= *val2));
                    }
                    else
                    {
                        ExecutionEngine::SET_LINE_NUMBER_TO_STATIC_LOG();
                        DISPLAY_EXCEPTION("solving the mathematical expression.", MathEvaluationException, false);
                    }
                }
                ++(*it);
            }
            return stk.top();
        }
        catch (const std::exception &)
        {
            ExecutionEngine::SET_LINE_NUMBER_TO_STATIC_LOG();
            DISPLAY_EXCEPTION("solving the mathematical expression.", SystemOutofMemoryException, false);
        }
        return nullptr;
    }

    inline static Any *FLAG_TO_FUNCTION_MAP()
    {

        auto it = ExecutionEngine::_funcmap_.find(*(_FunctionStack_.top()->_iterator));

        if (it == ExecutionEngine::_funcmap_.end())
        {
            ExecutionEngine::SET_LINE_NUMBER_TO_STATIC_LOG();
            DISPLAY_EXCEPTION("executing the SRON's bytecode and mapping the flags to functions. Found : '" + *(_FunctionStack_.top()->_iterator) + "'.", InvalidByteCodeException);
        }

        return (*it).second();
    }

    inline static Any *HANDLE_OPENING_SCOPES()
    {
        // std::cout << "\n>Start Handle opening scopes()<\n";
        _FunctionStack_.top()->_scopestack.push(_FunctionStack_.top()->_iterator);
        // std::cout << "\n>end handle opening scopes()<\n";
        return nullptr;
    }
    inline static Any *HANDLE_CLOSING_SCOPES()
    {
        // std::cout << "\n>Start handle closing scopes()<\n";
        _FunctionStack_.top()->_scopestack.pop();
        // std::cout << "\n>end handle closing scopes()<\n";
        return nullptr;
    }

    inline static Any *INCREMENT_ITERATOR()
    {
        ++_FunctionStack_.top()->_iterator;
        return nullptr;
    }

    inline static Any *NOTHING_PERFORMING_FUNCTION()
    {
        return nullptr;
    }

    inline static Any *RETURN_VALUE()
    {
        const auto &_top_ = _FunctionStack_.top();

        ++_top_->_iterator;

        _top_->_return_value = ExecutionEngine::FLAG_TO_FUNCTION_MAP();

        _top_->_iterator = _top_->_end;

        return nullptr;
    }

    inline static bool SOLVE_CONDITION()
    {
        ++_FunctionStack_.top()->_iterator;
        Bool *val = ExecutionEngine::FLAG_TO_FUNCTION_MAP()->GET_BOOL();

        // checking if the value is not 'Bool' type. If it is not, then the condition written inside the
        // conditional block is wrong.
        if (val == nullptr)
        {
            DISPLAY_EXCEPTION("checking the condition. Expecting 'Bool' value.", InvalidConditionalStatement, false);
        }
        ExecutionEngine::INCREMENT_ITERATOR();
        // std::cout << "after solving condition, iterator = :" << *_FunctionStack_.top()->_iterator << '\n';
        return val->GET();
    }

    inline static void EXIT_ITERATOR_FROM_SCOPE(const char *target_flag, const char *flag_for_recursion)
    {
        auto it = &(++ExecutionEngine::_FunctionStack_.top()->_iterator);

        const auto &end = ExecutionEngine::_FunctionStack_.top()->_end;

        while (*it < end && **it != target_flag)
        {
            ++(*it);
            if (**it == flag_for_recursion)
            {
                ExecutionEngine::EXIT_ITERATOR_FROM_SCOPE(target_flag, flag_for_recursion);
                ++(*it);
            }
        }
    }

    // moves the iterator to the position of Flag_ElseScopeEnd or Flag_ElifScopeEnd
    inline static void MOVE_ITERATOR_BEYOND_CONDITIONAL_STATEMENT()
    {

        auto it = &(ExecutionEngine::_FunctionStack_.top()->_iterator);

        const auto &end = ExecutionEngine::_FunctionStack_.top()->_end;

        while (*it < end)
        {
            if (**it == Flag_ElifScopeStart)
            {
                ExecutionEngine::EXIT_ITERATOR_FROM_SCOPE(Flag_ElifScopeEnd, Flag_ElifScopeStart);
                ++(*it);
                continue;
            }
            else if (**it == Flag_ElseScopeStart)
            {
                ExecutionEngine::EXIT_ITERATOR_FROM_SCOPE(Flag_ElseScopeEnd, Flag_ElseScopeStart);
            }
            break;
        }
    }

    inline static std::string &GET_RANGE_VARIABLES(Any **loop_start, Any **loop_end, Any **loop_step)
    {
        auto it = &(++ExecutionEngine::_FunctionStack_.top()->_iterator);

        const auto &end = ExecutionEngine::_FunctionStack_.top()->_end;

        while (*it < end && **it != Flag_Assign)
        {
            ++(*it);
        }

        auto iteration_variable = (*it) - 1;

        // now the current flag is `=
        *loop_start = ExecutionEngine::FLAG_TO_FUNCTION_MAP();
        ++(*it);

        *loop_end = ExecutionEngine::FLAG_TO_FUNCTION_MAP();
        ++(*it);

        // if the start is larger than the end, then user is trying a reverse loop
        // so we will set the steps as -1;
        *loop_step = (**loop_start > **loop_end) ? new Int(-1) : new Int(1);

        if (**it != Flag_RangeScopeEnd)
        {
            *loop_step = ExecutionEngine::FLAG_TO_FUNCTION_MAP();
            ++(*it);
        }

        return *iteration_variable;
    }

}

#endif