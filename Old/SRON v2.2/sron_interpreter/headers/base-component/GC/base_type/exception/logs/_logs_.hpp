#pragma once

#ifndef LOGS_H
#define LOGS_H

#include "__import__.hpp"


namespace Logs
{
    constexpr static const char*const terminal = "terminal";

    inline std::string GET_EXECUTABLE_PATH()
    {
        std::string temp;
        // extracting the address of exectuable 'sron.exe'..
        #ifdef _WIN64
            char path[MAX_PATH];
            DWORD length = GetModuleFileName(NULL, path, MAX_PATH);

            if (length == 0)
            {
                std::cerr<<"\n =| Failed to get the executable's path |=\n";
                exit(1);
            }

            // assigning the filename with the address of executable...
            temp = path;
        #elif __linux__
            #error "Can't compile this codebase for linux os"
        #elif __APPLE__ || TARGET_OS_MAC
            #error "Can't compile this codebase for apple system"
        #else
            #error "Can't detect O.S"
        #endif

        int i = temp.length() - 1;

        while (i > 0 && !(temp[i] == '/' || temp[i] == '\\' || temp[i] == ':'))
        {
            --i;
        }
        if (i > 0)
        {
            ++i;
        }

        return temp.substr(0, i);
    }
}
#endif