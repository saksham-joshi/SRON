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
    try
    {
        std::ifstream code_file(argv[1]);
        
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout<<std::fixed<<std::setprecision(8);

        if (code_file.fail())
        {
            if (argc == 1)
            {
                DISPLAY_EXCEPTION("getting the file name.", FileNameNotSpecifiedException);
            }
            DISPLAY_EXCEPTION("getting the file from the specified path.", FileNotFoundException);
        }

        Logs::filename = argv[1];

        Logs::mainfile = &code_file;

        EXECUTION_ENGINE::EXECUTE();

        Logs::mainfile->close();

    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("interpreting the written code.", SystemOutofMemoryException);
    }
    return 0;
}

#endif