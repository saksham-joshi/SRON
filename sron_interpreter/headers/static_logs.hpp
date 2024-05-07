#pragma once

#ifndef LOGS_H
#define LOGS_H

#include <fstream>
#include <iostream>

inline namespace Logs
{

    // contains the SRON's current version...
    const static double version = 1.0;

    // contains the line number of the current flow of program...
    static unsigned short int line_number = 1;

    // contains the current filename otherwise it will show terminal...
    static std::string filename = "terminal";

    inline static unsigned short int GET_LINE_NUMBER();

    inline static void INCREMENT_LINE_NUMBER();

    static std::ifstream *mainfile;

    // this function contains the path to the file.
    static std::string directory_path;

    // this function just saves the path to the file in Logs::path
    inline static void SET_DIRECTORY_PATH();

    inline static unsigned short int GET_LINE_NUMBER()
    {
        return Logs::line_number;
    }

    inline static void INCREMENT_LINE_NUMBER()
    {
        ++Logs::line_number;
    }

    inline void SET_DIRECTORY_PATH()
    {
        int i = Logs::filename.length() - 1;

        while (i > 0 && !(Logs::filename[i] == '/' || Logs::filename[i] == '\\'))
        {
            --i;
        }
        if (i > 0)
        {
            ++i;
        }
        Logs::directory_path = Logs::filename.substr(0, i);
    }
}
#endif