/*
 * Copyright (c) 2025 SAKSHAM JOSHI
 * All rights reserved.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 * @author- SAKSHAM JOSHI
 * @Linkedin- @sakshamjoshi27
 * @Twitter- @sakshamjoshi27
 * @email- social.sakshamjoshi@gmail.com
 */

#include "sron_interpreter/_execution_engine_.hpp"


int main(int argc, char **argv)
{
    try
    {

        GarbageCollector::INITIALIZE();
        
        std::ios_base::sync_with_stdio(false);
        std::cout.tie(0);

        std::cout<< std::boolalpha << std::fixed << std::setprecision(5);

        // create a List to provide command line arguments to the user
        ListPtr arglist = new List(0Ul);

        for (int i = 1; i < argc; ++i)
        {
            arglist->PUSH_WITHOUT_COPY(new String(argv[i]));
        }

        // starting the execution of the code
        ExecutionEngine::MAIN(GarbageCollector::REGISTER_MEMORY(arglist));

        std::cout << "\n   _________________________________________\n   | Time taken by SRON : " << std::fixed << double(clock()) / double(CLOCKS_PER_SEC) << " seconds. |";
       
    }
    catch(const NullPointerException &excep)
    {
        DISPLAY_EXCEPTION(excep.what(),NullAccessingException);
        return 1;
    }
    catch (const ThrowException &excep)
    {
        DISPLAY_EXCEPTION(excep.message__.GET(), excep.excode__);
        return 1;
    }
    catch (const std::bad_alloc &)
    {
        std::cerr << "\n+================================+\n"
                       "|     System Out of Memory       |\n"
                       "+================================+\n";

                       return 1;
    }
    catch(const ExceptionThrowByUser& __excep)
    {
        __excep.DISPLAY_EXCEPTION();
    }
    catch (const std::exception &excep)
    {
        std::cerr << "\n | Error: " << excep.what() << '\n';

        DISPLAY_EXCEPTION("compiling the source code. An Unexpected Error showed up. Mail the error to 'sron.language@gmail.com' along with source code and above mentioned error", NoException);
        return 1;
    }

    #ifdef SRON_DEVELOPMENT_PHASE
        // DESTROYING ALL GATHERED MEMORY .....
        GarbageCollector::TOTAL_DESTRUCTION();
        std::cout << "\n <|--- Total destruction done ---|> \n";
    #endif

    return 0;
}
