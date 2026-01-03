#ifndef _LOGS_H_
#define _LOGS_H_

#include "__import__.hpp"

namespace SronLogs{

    static int EXIT_CODE__ = static_cast<int>(SronExitCodes::EXECUTION_SUCCESS);
    
    static bool OKAY__ = true;
    
    static const char* ERROR_MESSAGE__ = "";

    static int SIGNAL__ = 0;

    typedef struct {
        // It is empty because I am using it
        // just to throw exception
    } SignalHandler;

    inline static void prepareLogs( const int __signal) noexcept
    {
        switch(__signal)
        {
            #ifdef _WIN64
                case SIGBREAK : 
                            SronLogs::EXIT_CODE__ = static_cast<int>(SronExitCodes::SIG_BREAK);
                            SronLogs::ERROR_MESSAGE__ = SRON_SIGBREAK_MESSAGE;
                            break;

                case SIGTERM :
                            SronLogs::EXIT_CODE__ = static_cast<int>(SronExitCodes::SIG_TERMINATE);
                            SronLogs::ERROR_MESSAGE__ = SRON_SIGTERM_MESSAGE;
                            break;
            #elifdef __linux__
                case SIGKILL :  
                            SronLogs::EXIT_CODE__ = static_cast<int>(SronExitCodes::SIG_KILL);
                            SronLogs::ERROR_MESSAGE__  = SRON_SIGKILL_MESSAGE;
                            break;
            #endif
            
            case SIGINT :  
                            SronLogs::EXIT_CODE__ = static_cast<int>(SronExitCodes::SIG_INT);
                            SronLogs::ERROR_MESSAGE__ = SRON_SIGINT_MESSAGE;
                            break;
            
            case SIGABRT :  
                            SronLogs::EXIT_CODE__ = static_cast<int>(SronExitCodes::SIG_ABORT);
                            SronLogs::ERROR_MESSAGE__ = SRON_SIGABRT_MESSAGE;
                            break;

            
            default : 
                            SronLogs::EXIT_CODE__ = static_cast<int>(SronExitCodes::SIG_UNKNOWN);
                            SronLogs::ERROR_MESSAGE__ = SRON_SIGUNKNOWN_MESSAGE;
                            break;
        }
    }
    
    void handleSignal(int __signal)
    {
        if(__signal == SIGSEGV)
        {
            std::cerr << SRON_SIGSEGV_MESSAGE;
            std::exit(static_cast<int>(SronExitCodes::SIG_SEG_FAULT));
        }
        else
        {
            SronLogs::prepareLogs(__signal);
            SronLogs::OKAY__ = false;
        }
    }
    
    static void registerSignals()
    {
        std::signal(SIGINT, SronLogs::handleSignal);
        std::signal(SIGABRT, SronLogs::handleSignal);
        std::signal(SIGSEGV, SronLogs::handleSignal);
        
        #ifdef _WIN64
            std::signal(SIGTERM, SronLogs::handleSignal);
            std::signal(SIGBREAK, SronLogs::handleSignal);
        #elifdef __linux__
            std::signal(SIGKILL, SronLogs::handleSignal);
        #else
            #error "Handle signals here for this operating system"
        #endif
    }

}

#define checkSignalStatus if(! SronLogs::OKAY__) throw SronLogs::SignalHandler()

#endif