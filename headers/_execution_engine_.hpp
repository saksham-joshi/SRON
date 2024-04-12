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

#include "_user_fnc_.hpp"
#include "_support_.hpp"
#include "_converter_.hpp"
#include "_function_.hpp"

#ifndef EXECUTOR_H
#define EXECUTOR_H

inline namespace ExecutionEngine
{

    // This stack contains the pointer to the struct SronFunction.
    std::stack<SronFunction *> _FunctionStack_;

    // this function is called whenn Flag_Assign is found!
    inline static Any *ASSIGN_VALUE();

    // this function is called when Flag_FunctionArgsStart is found!
    inline static Any *ASSIGN_ARGUMENTS();

    // this function handles the code when break keyword arrives
    inline static Any *BREAK_KEYWORD();

    // this function handles the code when continue keyword arrives
    inline static Any *CONTINUE_KEYWORD();

    // this function creates a variable
    inline static Any *CREATE_VARIABLE();

    inline static Any *CALL_FUNCTION();

    // executes the user-defined function..
    inline static Any *EXECUTE_FUNCTION(std::string &function_name, Argument_List *args);

    // this function extracts the arguments required to execute the functions
    inline static Argument_List *EXTRACT_ARGUMENTS();

    // this function is called when Flag_String_Value is found!
    inline static Any *EXTRACT_STRING();

    // this function is called when Flag_Char_Value is found!
    inline static Any *EXTRACT_CHAR();

    // this function is called when Flag_Double_Value is found!
    inline static Any *EXTRACT_DOUBLE();

    // this function is called when Flag_Int_Value is found!
    inline static Any *EXTRACT_INT();

    // this function is called when Flag_ListStart is found!
    inline static Any *EXTRACT_LIST();

    // this function is called when Flag_Bool_Value is found!
    inline static Any *EXTRACT_BOOL();

    // this function is called when Flag_Identifier_Variable is found!
    inline static Any *EXTRACT_IDENTIFIER();

    // this function is called when Flag_EvalStart is found!
    inline static Any *EVALUATE();

    // this function handles the if-elif-else statement
    inline static Any *EXECUTE_CONDITIONAL_STATEMENT();

    // this function handles the for statement
    inline static Any *EXECUTE_FOR_STATEMENT();

    // this function handles the while statement
    inline static Any *EXECUTE_WHILE_STATEMENT();

    // this function is called when any flag is found!
    inline static Any *FLAG_TO_FUNCTION_MAP();

    // this function handles the scopes
    inline static Any *HANDLE_OPENING_SCOPES();

    inline static Any *HANDLE_CLOSING_SCOPES();

    inline static Any *NOTHING_PERFORMING_FUNCTION();

    using ExecutionEngineFuncMap = std::unordered_map<std::string, std::function<Any *()>>;

    static ExecutionEngineFuncMap _funcmap_{
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
        {Flag_Break, ExecutionEngine::BREAK_KEYWORD},
        {Flag_Continue, ExecutionEngine::CONTINUE_KEYWORD},
        {Flag_IfScopeStart, ExecutionEngine::EXECUTE_CONDITIONAL_STATEMENT},
        {Flag_ForScopeStart, ExecutionEngine::EXECUTE_FOR_STATEMENT},
        {Flag_WhileScopeStart, ExecutionEngine::EXECUTE_WHILE_STATEMENT}};

    // this function loads the MAIN.srb file and starts the execution of the code.
    inline static void MAIN(List *arglist)
    {
        try
        {
            SronFunction _main_("MAIN", new Argument_List(arglist));

            Logs::filename = "MAIN.srb";

            ExecutionEngine::_FunctionStack_.push(&_main_);

            for (; _main_._iterator < _main_._codevector.end(); ++_main_._iterator)
            {
                if (*_main_._iterator == Flag_Return)
                {
                    ++_main_._iterator;
                    ExecutionEngine::FLAG_TO_FUNCTION_MAP();
                    break;
                }

                ExecutionEngine::FLAG_TO_FUNCTION_MAP();
            }

            ExecutionEngine::_FunctionStack_.pop();

            _main_.~SronFunction();
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing the 'MAIN' function.", SystemOutofMemoryException);
        }
    }

    inline static Any *ASSIGN_ARGUMENTS()
    {
        unsigned short int index = 0;

        auto *it = &(++_FunctionStack_.top()->_iterator);
        while (*it < _FunctionStack_.top()->_codevector.end() && **it != Flag_FunctionArgsScopeEnd)
        {
            if (**it == Flag_Variable)
            {
                ++(*it);
                _FunctionStack_.top()->_Vmanager.INSERT(**it, _FunctionStack_.top()->_arglist->GET(index));
                ++index;
            }
            ++*it;
        }

        return nullptr;
    }

    inline static Any *ASSIGN_VALUE()
    {
        std::string variable_name = *(_FunctionStack_.top()->_iterator - 1);

        ++_FunctionStack_.top()->_iterator;

        auto value = ExecutionEngine::FLAG_TO_FUNCTION_MAP();

        _FunctionStack_.top()->_Vmanager.INSERT(variable_name, value);

        return value;
    }

    inline static Any *BREAK_KEYWORD()
    {
        auto it = &(++ExecutionEngine::_FunctionStack_.top()->_iterator);
        while (*it < ExecutionEngine::_FunctionStack_.top()->_codevector.end() && !Support::IS_LOOP_ENDING_FLAG(**it))
        {
            ++(*it);
        }
        return nullptr;
    }

    inline static Any *CONTINUE_KEYWORD()
    {
        _FunctionStack_.top()->_iterator = _FunctionStack_.top()->_scopestack.top();

        return nullptr;
    }

    inline static Any *CREATE_VARIABLE()
    {

        auto it = &(++_FunctionStack_.top()->_iterator);

        _FunctionStack_.top()->_Vmanager.INSERT(*(*it - 2), **it);

        return nullptr;
    }

    // this function will check if the function is in-built then it
    // it is executed otherwise it will call the EXECUTE_FUNCTION() functioN.
    inline static Any *CALL_FUNCTION()
    {
        // std::cout << "\n>Start call_function()<\n";
        std::string fnc_name = *(++_FunctionStack_.top()->_iterator);

        // by incrementing the _iterator it will move to Flag_Args_Start
        // and now the arguments can be extracted
        ++_FunctionStack_.top()->_iterator;

        // checking if the function is in-built
        auto fnc = Sron::GET_SRON_FUNCTION(fnc_name);

        if (fnc != nullptr)
        {
            // std::cout << "\n>end call_function()<\n";
            return fnc(ExecutionEngine::EXTRACT_ARGUMENTS());
        } 
        
        return EXECUTE_FUNCTION(fnc_name, ExecutionEngine::EXTRACT_ARGUMENTS());
    }

    inline static Argument_List *EXTRACT_ARGUMENTS()
    {
        try
        {
            Argument_List *args = new Argument_List();

            auto it = &(++_FunctionStack_.top()->_iterator);

            while (*it < _FunctionStack_.top()->_codevector.end() && **it != Flag_Args_End)
            {
                args->PUT(ExecutionEngine::FLAG_TO_FUNCTION_MAP());
                ++(*it);
            }

            return args;
        }
        catch(const std::bad_alloc&){
            DISPLAY_EXCEPTION("creating arguments to call function.", SystemOutofMemoryException, false);
        }
        catch (const std::exception &)
        {
            
        }
        return nullptr;
    }

    // if the function is user-defined then this function is called.
    inline static Any *EXECUTE_FUNCTION(std::string &function_name, Argument_List *args)
    {
        // std::cout << "\n>Start execute_function()<\n";
        try
        {
            SronFunction fnc(function_name, args);

            ExecutionEngine::_FunctionStack_.push(&fnc);

            Logs::filename = function_name + ".srb";

            Any *val = new Void();

            // code here ...
            for (; fnc._iterator < fnc._codevector.end(); ++fnc._iterator)
            {
                if (*fnc._iterator == Flag_Return)
                {
                    ++fnc._iterator;
                    val = ExecutionEngine::FLAG_TO_FUNCTION_MAP()->COPY();
                    break;
                }
                ExecutionEngine::FLAG_TO_FUNCTION_MAP();
            }

            ExecutionEngine::_FunctionStack_.pop();

            std::cout<<"\nreturned value = "<< val->TO_STRING()<<"<\n";

            return val;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing the function '" + function_name + "'.", SystemOutofMemoryException, false);
        }
        return nullptr;
    }

    inline static Any *EXTRACT_INT()
    {
        auto it = &(++_FunctionStack_.top()->_iterator);
        return new Int(Converter::TO_INT(**it));
    }

    inline static Any *EXTRACT_DOUBLE()
    {
        auto it = &(++_FunctionStack_.top()->_iterator);
        return new Double(Converter::TO_DOUBLE(**it));
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
        auto *it = &(++_FunctionStack_.top()->_iterator);

        return new Bool((**it == "true") ? true : false);
    }

    inline static Any *EXTRACT_STRING()
    {
        auto it = &(++_FunctionStack_.top()->_iterator);
        String *str = new String();

        while (*it < _FunctionStack_.top()->_codevector.end() && **it != Flag_StringScopeEnd)
        {
            str->APPENDS(**it + '\n');
            ++(*it);
        }
        str->POP_BACK();
        return str;
    }

    inline static Any *EXTRACT_IDENTIFIER()
    {
        return _FunctionStack_.top()->_Vmanager.GET(*(++_FunctionStack_.top()->_iterator));
    }

    inline static Any *EXTRACT_LIST()
    {
        try
        {
            List *lst = new List();
            auto it = &(++_FunctionStack_.top()->_iterator);
            while (*it < _FunctionStack_.top()->_codevector.end() && ((**it) != Flag_ListEnd))
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

    inline static Any *EXECUTE_CONDITIONAL_STATEMENT()
    {
        return nullptr;
    }

    inline static Any *EXECUTE_FOR_STATEMENT()
    {
        return nullptr;
    }

    inline static Any *EXECUTE_WHILE_STATEMENT()
    {
        return nullptr;
    }

    inline static Any *EVALUATE()
    {
        // std::cout << "\n>Start EVALUATE()<\n";
        try
        {
            std::vector<std::string>::iterator *it = &(++_FunctionStack_.top()->_iterator);

            std::stack<Any *> stk;

            while (*it < _FunctionStack_.top()->_codevector.end() && (**it) != Flag_EvalEnd)
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
                        DISPLAY_EXCEPTION("solving the mathematical expression.", MathEvaluationException);
                    }
                }
                ++(*it);
            }
            return stk.top();
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("solving the mathematical expression.", SystemOutofMemoryException);
        }
        return nullptr;
    }

    inline static Any *FLAG_TO_FUNCTION_MAP()
    {

        auto it = ExecutionEngine::_funcmap_.find(*(_FunctionStack_.top()->_iterator));

        if (it == ExecutionEngine::_funcmap_.end())
        {
            DISPLAY_EXCEPTION("executing the SRON's bytecode.", InvalidByteCodeException);
        }
        // std::cout<<"\n"+*(_FunctionStack_.top()->_iterator)<<"<\n";
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

    inline static Any *NOTHING_PERFORMING_FUNCTION()
    {
        return nullptr;
    }

}

#endif