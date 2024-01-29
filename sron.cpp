/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 * 
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
*/

#include "headers/_execution_engine_.hpp"


#ifndef SRON_H
#define SRON_H

int main(int argc, char **argv)
{
    std::string str;
    try
    {
        std::ifstream code_file(argv[1]);

        if (code_file.fail())
        {
            if (argc == 1)
            {
                DISPLAY_EXCEPTION("getting the file name.", FileNameNotSpecifiedException);
            }
            DISPLAY_EXCEPTION("getting the file from the specified path.", FileNotFoundException);
        }

        Logs::filename = argv[1];

        std::string file_content((std::istreambuf_iterator<char>(code_file)), (std::istreambuf_iterator<char>()));
        
        LEXICAL_ANALYSER::LEX(file_content);

        Logs::line_number = 0;

        EXECUTION_ENGINE::function_vector = LEXICAL_ANALYSER::FunctionVector;

        auto& main_fnc = EXECUTION_ENGINE::FIND_USER_DEFINED_FUNCTION("MAIN");
        EXECUTION_ENGINE::FunctionStack.push(main_fnc);
        EXECUTION_ENGINE::EXECUTE();

        
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("interpreting the written code.", SystemOutofMemoryException);
    }
    return 0;
}

#endif