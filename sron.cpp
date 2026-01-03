// #define SRON_DEVELOPMENT_PHASE
// #define SRON_DEBUG_MODE

#ifndef SRON_H
#define SRON_H

#include "sron_interpreter/_execution_engine_.hpp"

int main(int argc, char **argv)
{
    try
    {
        #ifdef _WIN64 
            SetConsoleOutputCP(CP_UTF8);
            SetConsoleCP(CP_UTF8);
        #endif

        SronLogs::registerSignals();

        GarbageCollector::init();
        
        // create a List to provide command line arguments to the user
        ListPtr arglist = new List(0u);

        for (int i = 1; i < argc; ++i)
        {
            arglist->pushWithoutCopy(new LiteralString(argv[i]), SronTypeNum::TYPE_LITERAL_STR);
        }

        /*
            Calling ExecutionEngine::MAIN will execute the bytecode file with insane speed.

            Now, the ExecutionEngine is not open-sourced, so to contribute, you can test
            and optimize the inbuilt functions, datatypes and other compoenets of SRON's
            interpreter.
        */
        // ExecutionEngine::MAIN(GarbageCollector::registerMemory(arglist , SronTypeNum::TYPE_LIST));

        checkSignalStatus;
    }
    catch(const SronException::NullPointerException &excep)
    {
        SronException::displayException(excep.what(), SronException::NullAccessingException, "memory");
        
        SronLogs::EXIT_CODE__ = static_cast<int>(SronExitCodes::INVALID_MEMORY_ACCESS);
    }
    catch (const ThrowException &excep)
    {
        SronException::displayException(excep.what(), excep.excode__, excep.filename__.c_str());

        SronLogs::EXIT_CODE__ =  static_cast<int>(excep.exitcode__);
    }
    catch(const ExecutionEngine::Logs::CallStackOverflow& __excep)
    {
        SronException::displayException(__excep._message, __excep._exception, "Call-Stack");

        SronLogs::EXIT_CODE__ =  static_cast<int>(__excep._exitcode);
    }
    catch(const SronLogs::SignalHandler& __excep)
    {
        std::cerr << "\nSignal [" << static_cast<int>(SronLogs::SIGNAL__) << "]" << SronLogs::ERROR_MESSAGE__;
    }
    catch (const std::bad_alloc &)
    {
        errno = ENOMEM;
        std::perror ( "\n+================================+"
                      "\n|     System Out of Memory       |"
                      "\n+================================+"
                );

        SronLogs::EXIT_CODE__ =  static_cast<int>(SronExitCodes::SYSTEM_OUT_OF_MEMORY);
    }
    catch(const SronException::ExceptionThrowByUser& __excep)
    {
        __excep.print();

        SronLogs::EXIT_CODE__ =  static_cast<int>(SronExitCodes::EXCEPTION_THROWN_BY_USER);
    }
    catch(const SronException::UserWantsExit& __excep)
    {
        SronLogs::EXIT_CODE__ = __excep._exit_code;
    }
    catch (const std::exception &excep)
    {
        std::printf("\n | Error: %s\n" , excep.what() );

        SronException::displayException("executing the bytecode. An Unexpected Error showed up. Mail the error/exception to '" SRON_GITHUB_REPO "' along with source code and above mentioned error", SronException::DefaultException, "terminal");
        
        SronLogs::EXIT_CODE__ =  static_cast<int>(SronExitCodes::CPP_STD_EXCEP);
    }

    #ifdef SRON_DEVELOPMENT_PHASE
        GarbageCollector::totalDestruction();
        std::printf("\n <|--- Total destruction done ---|> \n");
        std::printf( "\n   _________________________________________\n   | Time taken by SRON : %llu ms. |\n" , SronSupport::getExecTime(SronSupport::getCurTime(), SronSupport::CODE_START_TIME));
    #endif

    printf(SronExtra::TERMINAL_RESET_STRING);

    return SronLogs::EXIT_CODE__;
}

#endif