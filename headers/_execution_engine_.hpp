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

#include<stack>

#ifndef EXECUTOR_H
#define EXECUTOR_H

namespace EXECUTION_ENGINE
{

    // This will contain the Function vector containing the name of the function and the Instruction vector.
    std::vector<std::string > function_vector;

    // This will contain the Function Map used by the user to call the functions.
    FunctionMap inbuilt_fnc_map = GET_FUNCTION_MAP();

    // This pointer will contain the reference to the current vector which is being executed.
    std::vector<std::string> *current_vector;

    std::vector<std::string>::iterator iterator;

    std::stack<std::string> FlagMap;

    std::string code;

    inline static Any* CREATE_ARGUMENTS();
    inline static List *CREATE_LIST();
    inline static String *CREATE_STRING();
    inline static Char *CREATE_CHAR();
    inline static Any *CREATE_VARIABLE();
    inline static Any *CALL_FUNCTION();
    inline static Double* EVALUATER();
    inline static void EXECUTE();
    inline static Any *EXTRACT_VALUE_FROM_IDENTIFIER();

    inline static void EXECUTE(){

        while(std::getline( *Logs::mainfile, code )){
            if(code[0] == '`' ){
                if(code == Flag_Args_Start ){
                    CREATE_ARGUMENTS();
                }
                else if(code == Flag_String){
                    CREATE_STRING();
                }
                else if(code == Flag_List){
                    CREATE_LIST();
                }
            }
        }
    }

}

#endif