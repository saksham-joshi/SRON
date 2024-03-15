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
    
    //This stack contains the pointer to the struct SronFunction.
    std::stack<SronFunction *> _FunctionStack_;

    // this function is called whenn Flag_Assign is found!
    inline static Any *ASSIGN_VALUE();

    // this function is called when Flag_FunctionArgsStart is found!
    inline static Any *ASSIGN_ARGUMENTS();

    // this function creates a variable 
    inline static Any *CREATE_VARIABLE();

    inline static Any *CALL_FUNCTION();

    // this function is used to call function by user
    //inline static Any *CALL_FUNCTION(std::string function_name, Argument_List *args);

    // executes the user-defined function..
    inline static Any *EXECUTE_FUNCTION(std::string &function_name, Argument_List *args);

    // this function extracts the arguments required to execute the functions
    inline static Argument_List* EXTRACT_ARGUMENTS();

    // this function is called when Flag_String_Value is found!
    inline static Any* EXTRACT_STRING();

    // this function is called when Flag_Char_Value is found!
    inline static Any* EXTRACT_CHAR();

    // this function is called when Flag_Double_Value is found!
    inline static Any* EXTRACT_DOUBLE();

    // this function is called when Flag_Int_Value is found!
    inline static Any* EXTRACT_INT();

    // this function is called when Flag_ListStart is found!
    inline static Any* EXTRACT_LIST();

    //this function is called when Flag_Bool_Value is found!
    inline static Any* EXTRACT_BOOL();

    // this function is called when Flag_Identifier_Variable is found!
    inline static Any* EXTRACT_IDENTIFIER();

    // this function is called when Flag_EvalStart is found!
    inline static Any* EVALUATE();
    
    // this function is called when any flag is found!
    inline static Any* FLAG_TO_FUNCTION_MAP();

    // this function handles the scopes
    inline static Any* HANDLE_OPENING_SCOPES();

    inline static Any* HANDLE_CLOSING_SCOPES();

    // // substitute for ++_FunctionStack_.top()->_iterator
    // inline static std::vector<std::string>& INCREMENT_TOP_ITERATOR(){
    //     auto& it = ++_FunctionStack_.top()->_iterator;
    //     return it;
    // }

    using ExecutionEngineFuncMap = std::unordered_map<std::string, std::function<Any*()>>;

    static ExecutionEngineFuncMap _funcmap_{
            {Flag_Int_Value, ExecutionEngine::EXTRACT_INT },
            {Flag_Double_Value, ExecutionEngine::EXTRACT_DOUBLE},
            {Flag_Char_Value, ExecutionEngine::EXTRACT_CHAR},
            {Flag_StringScopeStart, ExecutionEngine::EXTRACT_STRING},
            {Flag_Bool_Value, ExecutionEngine::EXTRACT_BOOL},
            {Flag_Identifier_Variable, ExecutionEngine::EXTRACT_IDENTIFIER},
            {Flag_EvalStart, ExecutionEngine::EVALUATE},
            {Flag_Variable, ExecutionEngine::CREATE_VARIABLE},
            {Flag_Assign, ExecutionEngine::ASSIGN_VALUE},
            {Flag_FunctionArgsScopeStart, ExecutionEngine::ASSIGN_ARGUMENTS},
            {Flag_ScopeStart, ExecutionEngine::HANDLE_OPENING_SCOPES},
            {Flag_ScopeEnd, ExecutionEngine::HANDLE_CLOSING_SCOPES},
            {Flag_FunctionCall, ExecutionEngine::CALL_FUNCTION}
        };

    // this function loads the MAIN.srb file and starts the execution of the code.
    inline static void MAIN(List *arglist)
    {
        try
        {
            SronFunction _main_("MAIN", new Argument_List(arglist));

            Logs::filename = "MAIN.srb";

            ExecutionEngine::_FunctionStack_.push(&_main_);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing the 'MAIN' function.", SystemOutofMemoryException);
        }
    }

    inline static Any *ASSIGN_ARGUMENTS(){
        unsigned int index = 0;

        auto *it = &(++_FunctionStack_.top()->_iterator);
        while(*it < _FunctionStack_.top()->_codevector.end() && **it != Flag_FunctionArgsScopeEnd){
            if(**it == Flag_Variable){
                ++(*it);
                _FunctionStack_.top()->_Vmanager.INSERT(**it, _FunctionStack_.top()->_arglist->GET(index));
                ++index;
            }
        }

        return nullptr;
    }

    inline static Any *ASSIGN_VALUE(){
        auto *it = &(++_FunctionStack_.top()->_iterator);
        Any *temp;
        if(Support::IS_FLAG(**it)){
            temp = ExecutionEngine::FLAG_TO_FUNCTION_MAP();
            _FunctionStack_.top()->_Vmanager.INSERT(**(it-2), temp);
        }
        return temp;
    }

    inline static Any *CREATE_VARIABLE(){
        auto *it = &(++_FunctionStack_.top()->_iterator);
        _FunctionStack_.top()->_Vmanager.INSERT(**(it-2), **it);
        return nullptr;
    }

    // this function will check if the function is in-built then it
    // it is executed otherwise it will call the EXECUTE_FUNCTION() functioN.
    inline static Any *CALL_FUNCTION()
    {
        std::string fnc_name = *(++_FunctionStack_.top()->_iterator);
        
        // checking if the function is in-built
        auto fnc = Sron::GET_SRON_FUNCTION(fnc_name);
        if (fnc != nullptr)
        {
            return fnc(ExecutionEngine::EXTRACT_ARGUMENTS());
        }
        return EXECUTE_FUNCTION(fnc_name, ExecutionEngine::EXTRACT_ARGUMENTS());
    }

    inline static Argument_List* EXTRACT_ARGUMENTS(){
        Argument_List *args = new Argument_List();

        auto *it = &(++_FunctionStack_.top()->_iterator);
        while(*it < _FunctionStack_.top()->_codevector.end() && **it != Flag_Args_End){
            args->PUT(ExecutionEngine::FLAG_TO_FUNCTION_MAP());
            ++(*it);
        }
        return args;
    }

    // if the function is user-defined then this function is called.
    inline static Any *EXECUTE_FUNCTION(std::string &function_name, Argument_List *args)
    {
        SronFunction fnc(function_name, args);

        ExecutionEngine::_FunctionStack_.push(&fnc);

        Logs::filename = function_name+".srb";

        // code here
        
        for(; fnc._iterator < fnc._codevector.end() ; ++fnc._iterator){
            ExecutionEngine::FLAG_TO_FUNCTION_MAP();
        }

        fnc.~SronFunction();

        ExecutionEngine::_FunctionStack_.pop();

        Logs::filename = function_name+".srb";

        return new Void();
    }

    inline static Any* EXTRACT_INT(){
        auto *it = &(++_FunctionStack_.top()->_iterator);
        return new Int(Converter::TO_INT(**it));
    }

    inline static Any* EXTRACT_DOUBLE(){
        auto *it = &(++_FunctionStack_.top()->_iterator);
        return new Double(Converter::TO_DOUBLE(**it));
    }

    inline static Any* EXTRACT_CHAR(){
        auto *it = &(++_FunctionStack_.top()->_iterator);
        
        if(**it == "\n"){
            return new Char('\n');
        }
        else if(**it == "\t"){
            return new Char('\t');
        }
        return new Char((**it)[0]);
    }

    inline static Any* EXTRACT_BOOL(){
        auto *it = &(++_FunctionStack_.top()->_iterator);

        return new Bool((**it == "true")?true:false);
    }

    inline static Any* EXTRACT_STRING(){
        auto *it = &(++_FunctionStack_.top()->_iterator);
        String *str = new String();

        while(*it < _FunctionStack_.top()->_codevector.end() && **it != Flag_StringScopeEnd){
            str->APPENDS(**it+'\n');
        }
        str->POP_BACK();
        return str;
    }

    inline static Any* EXTRACT_IDENTIFIER(){
        return _FunctionStack_.top()->_Vmanager.GET(*(++_FunctionStack_.top()->_iterator));
    }

    inline static Any* EXTRACT_LIST(){
        List *lst;
        // code here
        return lst;
    }

    inline static Any* EVALUATE(){

       return nullptr; 
    }

    inline static Any* FLAG_TO_FUNCTION_MAP(){
        auto it = ExecutionEngine::_funcmap_.find(*(_FunctionStack_.top()->_iterator));
        if(it == _funcmap_.end()){
            DISPLAY_EXCEPTION("executing the SRON's bytecode.",InvalidByteCodeException);
        }
        return (*it).second();
    }

    inline static Any* HANDLE_OPENING_SCOPES(){
        _FunctionStack_.top()->_scopestack.push(*(_FunctionStack_.top()->_iterator));
        return nullptr;
    }
    inline static Any* HANDLE_CLOSING_SCOPES(){
        _FunctionStack_.top()->_scopestack.pop();
        return nullptr;
    }


}

#endif