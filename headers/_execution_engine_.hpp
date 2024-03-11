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
#include "_argument_list_.hpp"
#include "_variable_manager_.hpp"

#include <stack>

#ifndef EXECUTOR_H
#define EXECUTOR_H

inline namespace ExecutionEngine
{
    // this function will start execution of the code from the file in
    // Logs::mainfile
    inline static void EXECUTE();

    // this class is capable of executing codes
    class Function;

    // this stack will contains the function according to the order of how they are called.
    std::stack<Function *> FunctionStack;

    inline static void EXECUTE()
    {
        SronFunction _main_("MAIN");

        _main_.codefile = std::ifstream("MAIN.srb");

        if (_main_.codefile.fail())
        {
            DISPLAY_EXCEPTION("searching for MAIN.srb file.", MainFunctionNotFoundException, false);
        }

        Logs::filename = "MAIN.srb";

        _main_.EXECUTE(nullptr);
    }

    class SronFunction
    {

    private:
        std::ifstream codefile;
        VariableManager Vmanager;
        std::string codeline;
        std::string function_name;

        // this function will call the other functions
        inline Any *CALL_FUNCTION()
        {
            ExecutionEngine::SronFunction obj(codeline);
            auto output = obj.EXECUTE(PREPARE_ARGUMENTS());
            Logs::filename = this->function_name;
            return output;
        }

        // this function evalutes the mathematical block when Flag_EvalStart appears
        inline Any *EVALUATE()
        {
            this->GETLINE();

            // used to store the values from the mathematical block
            // whenever an operator arrives, the two variables from the 
            // top of the stack is popped and evaluated!
            std::stack<Any*> stk;
            while(this->codeline != Flag_EvalEnd){

            }
        }

        inline Char *EXTRACT_CHAR()
        {
        }

        inline Int *EXTRACT_INT()
        {
        }
        inline Double *EXTRACT_DOUBLE()
        {
        }

        inline List *EXTRACT_LIST()
        {
        }

        inline String *EXTRACT_STRING()
        {
            this->GETLINE();
            String *str = String::MAKE();
            while (this->codeline != Flag_StringScopeEnd)
            {
                str->APPENDS(codeline);
                str->APPENDS("\n");
            }
            str->POP_BACK();
            return str;
        }

        // this function extracts the line of the file one by one
        inline void GETLINE()
        {
            if(!std::getline(this->codefile, this->codeline)){
                
            }
        }

        // this method will prepare the arguments for function to be called by user
        inline Argument_List *PREPARE_ARGUMENTS()
        {
            return nullptr;
        }

        // this method will map the flags to the functions
        // this method will work like a central point for all the function.
        inline Any* FLAG_TO_FUNCTION_MAPPER()
        {
            if (this->codeline == Flag_FunctionArgsScopeStart)
            {
                
            }
            else if (this->codeline == Flag_FunctionCall)
            {
                this->GETLINE();
                return this->CALL_FUNCTION();
            }
            else if (this->codeline == Flag_StringScopeStart)
            {
                return this->EXTRACT_STRING();
            }
            else if (this->codeline == Flag_EvalStart)
            {
                return this->EVALUATE();
            }
            else if (this->codeline == Flag_Identifier_Variable)
            {
                this->GETLINE();
                this->Vmanager.GET(this->codeline);
            }
            else if(this->codeline == Flag_ListStart){

            }
        }

    public:
        SronFunction(std::string fnc_name)
        {
            try
            {
                this->function_name = fnc_name;
                this->codefile = std::ifstream(fnc_name + ".srb");
                if (this->codefile.fail())
                {
                    DISPLAY_EXCEPTION("calling the function named as '" + fnc_name + "'.", FunctionNotFoundException, false);
                }
            }
            catch (const std::exception &)
            {
                DISPLAY_EXCEPTION("executing the function '" + fnc_name + "'.", FunctionNotFoundException, false);
            }
        }

        ~SronFunction() {}

        // this function will start the execution of the code
        inline Any *EXECUTE(Argument_List *args)
        {
            Logs::filename = function_name + ".srb";
        }

        friend void ExecutionEngine::EXECUTE();
    };
}

#endif