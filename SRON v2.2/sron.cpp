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

// #define SRON_DEVELOPMENT_PHASE
// #define SRON_DEBUG_MODE

#ifndef SRON_H
#define SRON_H

#include "sron_interpreter/_execution_engine_.hpp"

int main(int argc, char **argv)
{
    try
    {

        GarbageCollector::INITIALIZE();
        
        // create a List to provide command line arguments to the user
        ListPtr arglist = new List(0Ul);

        for (int i = 1; i < argc; ++i)
        {
            arglist->PUSH_WITHOUT_COPY(new String(argv[i]), SronTypeNum::TYPE_STRING);
        }

        // starting the execution of the code
        ExecutionEngine::MAIN(GarbageCollector::REGISTER_MEMORY(arglist , SronTypeNum::TYPE_LIST));
    }
    catch(const SronException::NullPointerException &excep)
    {
        SronException::DISPLAY_EXCEPTION(excep.what(), SronException::NullAccessingException, "memory");
        
        return SronExitCodes::SRON_INVALID_MEMORY_ACCESS;
    }
    catch (const ThrowException &excep)
    {
        SronException::DISPLAY_EXCEPTION(excep.what(), excep.excode__, excep.filename__);

        return SronExitCodes::SRON_BASIC_EXCEPTION;
    }
    catch (const std::bad_alloc &)
    {
        printf_s ( "\n+================================+"
                   "\n|     System Out of Memory       |"
                   "\n+================================+"
                );

        return SronExitCodes::SRON_SYSTEM_OUT_OF_MEMORY;
    }
    catch(const ExceptionThrowByUser& __excep)
    {
        __excep.DISPLAY_EXCEPTION();

        return SronExitCodes::SRON_EXCEPTION_THROWN_BY_USER;
    }
    catch (const std::exception &excep)
    {
        printf_s("\n | Error: %s\n" , excep.what() );

        SronException::DISPLAY_EXCEPTION("executing the bytecode. An Unexpected Error showed up. Mail the error/exception to 'sron.language@gmail.com' along with source code and above mentioned error", SronException::DefaultException, Logs::terminal);
        
        return SronExitCodes::SRON_CPP_STD_EXCEP;
    }

    #ifdef SRON_DEVELOPMENT_PHASE
        GarbageCollector::TOTAL_DESTRUCTION();
        printf_s("\n <|--- Total destruction done ---|> \n");
        printf_s( "\n   _________________________________________\n   | Time taken by SRON : %.5lf seconds. |" , double(clock()) / double(CLOCKS_PER_SEC));
    #endif

    return SronExitCodes::SRON_EXECUTION_SUCCESS;
}

#endif