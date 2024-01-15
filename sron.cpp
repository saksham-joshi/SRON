// #include "headers/_execution_engine_.hpp"
// #include "headers/lexical_analyst.hpp"
#include "headers/static_logs.hpp"
#include "headers/_exception_.hpp"
#include<iostream>

#include<string>
#include <fstream>

#ifndef SRON_H
#define SRON_H


std::string READ_WHOLE_FILE(std::ifstream& input){
    std::string content((std::istreambuf_iterator<char>(input)),(std::istreambuf_iterator<char>()));
    return content;
}

int main(int argc, char **argv)
{
    std::string str;
    try
    {
        std::ifstream code_file(argv[1]);
        
        if (code_file.fail())
        {
            if(argc == 1){
                DISPLAY_EXCEPTION("getting the file name.",16);
            }
            DISPLAY_EXCEPTION("getting the file from the specified path.", 1);
        }

        Logs::filename = argv[1] ;
        
        std::string lexcode = READ_WHOLE_FILE(code_file);
        std::cout<<lexcode;
    }
    catch (const std::exception&)
    {
        DISPLAY_EXCEPTION("interpreting the written code.",3);
    }
    return 0;
}

#endif