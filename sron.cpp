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

#include "headers/_execution_engine_.hpp"

#ifndef SRON_H
#define SRON_H

int main()
{
    try
    {
        
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(NULL);
        std::cout<<std::fixed<<std::setprecision(8);

        ExecutionEngine::EXECUTE();

        Logs::mainfile->close();

    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("interpreting the written code.", SystemOutofMemoryException,false);
    }
    return 0;
}

#endif