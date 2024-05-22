/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 * @author- SAKSHAM JOSHI
 * @Linkedin- @sakshamjoshi27
 * @Twitter- @sakshamjoshi27
 * @email- social.sakshamjoshi@gmail.com
 */

#include "sron_interpreter/_execution_engine_.hpp"
#include <ctime>

#ifndef SRON_H
#define SRON_H

int main(int argc, char **argv)
{
    try
    {
        // create a Listist to provide command line arguments to the user
        List arglist;

        for (int i = 1; i < argc; ++i)
        {
            arglist.PUSH(new String(argv[i]));
        }

        /*
        If command line arguments are passed, then turning off the syncing may rise sudden termination
        of the code, therefore checking if the arguments are passed or not is vital...!!
        */
        if (argc == 1)
        {
            std::ios::sync_with_stdio(false);
            std::cout.tie(nullptr);
        }

        // starting the execution of the code
        ExecutionEngine::MAIN(arglist);

        std::cout << "\n   __________________________________________\n   | Time taken by SRON : " << std::fixed << double(clock()) / double(CLOCKS_PER_SEC) << " seconds. |";
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("interpreting the written code.", SystemOutofMemoryException, false);
    }
    return 0;
}

#endif