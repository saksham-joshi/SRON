
#pragma once

#ifndef LOGS_H
#define LOGS_H

#include <fstream>
#include <iostream>
#include <ctime>
#include <windows.h>

inline namespace Logs
{

    static unsigned short int line_number = 1;

    static std::string filename = "terminal";

    static std::ifstream *mainfile;

    // this function contains the path to the file.
    static std::string directory_path;

    static std::string executable_path;

    // extracts the path to a file ...
    inline static std::string GET_FILE_PATH(std::string filepath){
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

        Logs::directory_path = GET_FILE_PATH(Logs::filename);
    }

    inline static void SET_EXECUTABLE_PATH()
    {
        char path[MAX_PATH];
        DWORD length = GetModuleFileName(NULL, path, MAX_PATH);

        if (length == 0)
        {
            std::cerr << "\n =| Failed to get the executable's path |=\n";
            exit(1);
        }

        Logs::executable_path = Logs::GET_FILE_PATH(path);
    }

}
#endif