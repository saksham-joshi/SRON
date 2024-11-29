
#pragma once

// #pragma GCC poison printf
// #pragma GCC poison scanf

#ifndef LOGS_H
#define LOGS_H

#include "__import__.hpp"

inline namespace Logs
{   
    // this flag is used to indicate whether user passed the '-op' compiler flag or not!
    bool ___optimization = false;

    // This value is divided by the no of character in the source code file
    // and is used to reserve the size for LexicalAnalyzer::tokenVector 
    // This value cannot be set to zero. The lesser this value is, the more 
    // memory will be resereved 
    constexpr const size_t __ReserveOfTokenVector__ = 4;

    #if ((__ReserveOfTokenVector__ < 1) && (__ReserveOfTokenVector > 10))
        #error "Logs::__ReserveOfTokenVector__ cannot be less than 1 and more than 10"
    #endif

   

    constexpr const double __SronVersion__ = 2.1;

    static std::string filename = "terminal";

    const static std::string version_string =   "\n"
                                                "+----------------------------+\n"
                                                "|      SRON version 2.1      |\n"
                                                "|   @Author: Saksham Joshi   |\n"
                                                "+----------------------------+\n\n";

    static std::ifstream mainfile;
    
    static std::string directory_path;
    static std::string executable_path;

    // extracts the path to a file ...
    inline static std::string GET_FILE_PATH(const std::string& filepath){
        int i = filepath.length() - 1;

        while (i > 0 && !(filepath[i] == '/' || filepath[i] == '\\' || filepath[i] == ':'))
        {
            --i;
        }
        if (i > 0)
        {
            ++i;
        }

        return filepath.substr(0,i);
    }

    // this function just saves the path to the file in Logs::path
    inline static void SET_DIRECTORY_PATH()
    {

        Logs::directory_path = Logs::GET_FILE_PATH(Logs::filename);
    }

    inline static void SET_EXECUTABLE_PATH()
    {
        #ifdef _WIN64
            char path[MAX_PATH];

            DWORD length = GetModuleFileName(NULL, path, MAX_PATH);

            if (length == 0)
            {
                std::cerr << "\n =| Failed to get the executable's path |=\n";
                exit(1);
            }

            Logs::executable_path = Logs::GET_FILE_PATH(path);
        #elif __linux__
            #error "Can't compile it for linux os"
        #elif __APPLE__ || TARGET_OS_MAC
            #error "Can't compile it for apple system"
        #endif
    }

}
#endif