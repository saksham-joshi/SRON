/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 */

/*
    This file contains the implementation of Execution Engine which will execute the Instruction Vectors
    containing attributes and instructions.

    It will perform the following operations :
        1. Calling the functions
        2. Solving the expressions.
        3. Allocating variables.
        4. Executes Conditional statements.
        5. Executes looping statements.

    In overall, it will perform the most vital operations and it will act like a brain of SRON programming
    language.
*/

#include "lexical_analyst.hpp"
#include "_user_fnc_.hpp"
#include "_support_.hpp"
#include "_converter_.hpp"

#ifndef EXECUTOR_H
#define EXECUTOR_H

namespace EXECUTION_ENGINE
{

    // This will contain the Function vector containing the name of the function and the Instruction vector.
    std::vector<Function> function_vector;

    // This will contain the Function Map used by the user to call the functions.
    FunctionMap inbuilt_fnc_map = GET_FUNCTION_MAP();

    // This pointer will contain the reference to the current vector which is being executed.
    std::vector<std::string> *current_vector;

    std::vector<std::string>::iterator iterator;

    std::stack<Function> FunctionStack;

    
    inline static List *CREATE_LIST();
    inline static String *CREATE_STRING();
    inline static Char *CREATE_CHAR();
    inline static Any *CREATE_VARIABLE();
    inline static Any *CALL_FUNCTION();
    inline static Double* EVALUATER();
    inline static Any *EXTRACT_VALUE_FROM_IDENTIFIER();
    inline static Function &FIND_USER_DEFINED_FUNCTION(std::string);
    inline static void ATTRIBUTE_VARIABLE();

    // This will prepare a argument list used to call the function.
    inline static Argument_List* PREPARE_ARGUMENTS()
    {
        ++iterator;
        auto arg_list = new Argument_List();
        while (iterator < current_vector->end() && *iterator != ")")
        {
            if (*iterator != ",")
            {
                arg_list->PUT(CREATE_VARIABLE());
            }
            ++iterator;
        }
        return arg_list;
    }

    // This function will create a String value from a user-defined String value.
    inline static String *CREATE_STRING()
    {
        return (*iterator == "\"\"") ? String::MAKE() : String::MAKE(iterator->substr(1, iterator->size() - 2));
    }

    // This function will create a Char value from a user-defined Char value.
    inline static Char *CREATE_CHAR()
    {
        return (*iterator == "''") ? Char::MAKE() : Char::MAKE(iterator->at(1));
    }

    // This function will create the list from the user-defined List.
    inline static List *CREATE_LIST()
    {
        ++iterator;
        auto lst = List::MAKE();

        while (iterator < current_vector->end() && *iterator != "]")
        {

            if (*iterator == "[")
            {
                ++iterator;
                lst->PUSH(CREATE_LIST());
            }
            lst->PUSH(CREATE_VARIABLE());
            ++iterator;
        }
        return lst;
    }

    // This function is used to create variables from the given user-defined value by identifing its type.
    inline static Any *CREATE_VARIABLE()
    {
        switch (Support::IDENTIFY_TYPE_FROM_STRING(*iterator))
        {
        case TYPE_INT:
            return Int::MAKE(Converter::TO_INT(*iterator));
        case TYPE_DOUBLE:
            return Double::MAKE(Converter::TO_DOUBLE(*iterator));
        case TYPE_CHAR:
            return EXECUTION_ENGINE::CREATE_CHAR();
        case TYPE_BOOL:
            return Bool::MAKE(*iterator);
        case TYPE_STRING:
            return CREATE_STRING();
        case TYPE_LIST:
            return CREATE_LIST();
        case IDENTIFIER:
            return EXTRACT_VALUE_FROM_IDENTIFIER();
        default:
            DISPLAY_EXCEPTION("creating variables and allocating memory.", InvalidValueException);
        }
        return new Void();
    }

    // This function will extract the value from the variable name or function name
    inline static Any *EXTRACT_VALUE_FROM_IDENTIFIER()
    {
        if (*(iterator + 1) == "(")
        {
            return CALL_FUNCTION();
        }
        return FunctionStack.top().Vmanager.GET(*iterator);
    }

    // This function will search the user defined functions Instruction pair
    // by taking the function's name as the argument.
    inline static Function &FIND_USER_DEFINED_FUNCTION(std::string fnc_name)
    {
        for (auto &fnc : EXECUTION_ENGINE::function_vector)
        {
            if (fnc.fnc_name == fnc_name)
            {
                return fnc;
            }
        }
        if (fnc_name == "MAIN" || fnc_name == "main" || fnc_name == "Main")
        {
            DISPLAY_EXCEPTION("finding the main function.", MainFunctionNotFoundException);
        }
        DISPLAY_EXCEPTION("finding the '" + fnc_name + "' function.", FunctionNotFoundException);
        exit(1);
    }

    // This will call the functions both user defined and in-built functions.
    inline static Any* CALL_FUNCTION()
    {
        // finding user_defined function
        try
        {
            for (auto &fnc : EXECUTION_ENGINE::function_vector)
            {
                if (fnc.fnc_name == *iterator)
                {
                    FunctionStack.push(fnc);
                    EXECUTE();
                    FunctionStack.pop();
                    return;
                }
            }
            auto fnc = inbuilt_fnc_map.find(*iterator);
            if(fnc == nullptr){
                DISPLAY_EXCEPTION("calling the function '"+*iterator+"'.",FunctionNotFoundException);
            }
            return fnc->second(PREPARE_ARGUMENTS()) ;

        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("calling the function.",SystemOutofMemoryException);
        }

        return Void::MAKE();
    }

    // Execution of the SRON Code starts from here.
    inline static void EXECUTE()
    {

        for (const auto &pair : FunctionStack.top().codemap)
        {
        }
    }

    inline static void ATTRIBUTE_VARIABLE()
    {
        while (iterator < current_vector->end())
        {
            if (*iterator == ",")
            {
                ++iterator;
                continue;
            }
            if (*iterator == "Any" && iterator < (current_vector->end() - 3))
            {
                ++iterator;
                if (Support::CHECK_VALID_VARIABLE_NAME(*iterator))
                { // Any val = "SRON"
                    ++iterator;
                    if (*iterator == "=")
                    {
                        ++iterator;
                        FunctionStack.top().Vmanager.INSERT(*(iterator - 2), CREATE_VARIABLE());
                        ++iterator;
                        continue;
                    }
                    else
                    {
                        DISPLAY_EXCEPTION("creating variables.", InvalidVariableSyntaxException);
                    }
                }
            }
            else if (iterator < current_vector->end() - 3)
            {
                ++iterator;
                if (*(iterator + 1) == "=")
                { // Int val = 10;
                    iterator += 2;
                    FunctionStack.top().Vmanager.INSERT(*(iterator - 2), CREATE_VARIABLE());
                    ++iterator;
                    continue;
                }
                else if (iterator < current_vector->end() - 1 || *(iterator + 1) == ",")
                { // Int val
                    FunctionStack.top().Vmanager.INSERT(*(iterator - 1), *iterator);
                    ++iterator;
                    continue;
                }
                DISPLAY_EXCEPTION("creating variables.", InvalidVariableSyntaxException);
            }
            ++iterator;
        }
    }

    inline static Double* EVALUATER(){
        ++iterator;

        // arglist is lightweight than vector
        Argument_List *arglist = new Argument_List();
        while(iterator < current_vector->end() && *iterator != "~"){
            auto temp = Support::IDENTIFY_TYPE_FROM_STRING(*iterator) ;
            if(IS_MATH_OPERATOR(*iterator)){
                arglist->PUT(Char::MAKE((*iterator)[0] ));
            }
            else if(temp== TYPE_DOUBLE || temp == TYPE_INT){
                arglist->PUT(Double::MAKE(Converter::TO_DOUBLE(*iterator)));
            }
            else{
                DISPLAY_EXCEPTION("evaluating mathematical expression.",MathEvaluationException);
            }
            ++iterator;
        }

        //return Evaluater::Evaluate(arglist);
    }

}

#endif