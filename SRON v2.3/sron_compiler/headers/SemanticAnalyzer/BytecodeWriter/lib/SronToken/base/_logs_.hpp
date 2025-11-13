
#pragma once

// #pragma GCC poison printf
// #pragma GCC poison scanf

#ifndef LOGS_H
#define LOGS_H

#include "__import__.hpp"

inline namespace Logs
{   
    // This value is divided by the no of character in the source code file
    // and is used to reserve the size for LexicalAnalyzer::tokenVector 
    // This value cannot be set to zero. The lesser this value is, the more 
    // memory will be resereved 
    constexpr const unsigned short __ReserveOfTokenVector__ = 4;

    static_assert((__ReserveOfTokenVector__ > 1) && (__ReserveOfTokenVector__ < 10), "Logs::__ReserveOfTokenVector__ cannot be less than 1 and more than 10" );

    /*
     - Contains the name of the file which needs to be compiled
     - The default name is "terminal" because if the user didn't 
       pass any filename as the command line arg, then the 
       DISPLAY_ERROR() function will print the "terminal" in 
       place of filename because error occurs at terminal.
    */
    static std::string_view filename = "terminal";

    // contains the file which will be compiled
    static std::ifstream *mainfile;
    
    // contains the path of file which needs to be compiled
    static std::string directory_path;

    // contains the length of the executable 
    static std::string executable_path;

    // extracts the path to a file ...
    inline static std::string GET_FILE_PATH(const std::string& __filepath)
    {
        auto it = __filepath.end() - 1;

        while ( it >= __filepath.begin() && !( *it == '/' || *it == '\\' || *it == ':') ) --it;
        
        if ( it >= __filepath.begin() ) ++it;

        return std::string( __filepath.begin() , it );
    }

    // this function just saves the path to the file in Logs::directory_path
    inline static void SET_DIRECTORY_PATH()
    {
        Logs::directory_path = std::filesystem::current_path().string();

        Logs::directory_path.push_back('/');
    }

}
#endif