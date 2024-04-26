#ifndef LOGS_H
#define LOGS_H

#include <fstream>
#include <iostream>
#include <ctime>

inline namespace Logs
{

    static unsigned short int line_number = 1;

    static std::string filename = "terminal";

    const static clock_t execution_start_time = clock();

    static std::ifstream *mainfile;

    // this function contains the path to the file.
    static std::string directory_path;

    // this function just saves the path to the file in Logs::path
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