#include "headers/lexical_analyst.hpp"

#ifndef SRON_H
#define SRON_H

int main(int argc, char **argv)
{
    std::string str;
    try
    {
        std::ifstream code_file(argv[1]);

        if (code_file.fail())
        {
            if (argc == 1)
            {
                DISPLAY_EXCEPTION("getting the file name.", FileNameNotSpecifiedException);
            }
            DISPLAY_EXCEPTION("getting the file from the specified path.", FileNotFoundException);
        }

        Logs::filename = argv[1];

        std::string file_content((std::istreambuf_iterator<char>(code_file)), (std::istreambuf_iterator<char>()));
        
        LEXICAL_ANALYSER::LEX(file_content);

        for (const auto j : LEXICAL_ANALYSER::FunctionVector)
        {
            for (const auto i : j.codemap)
            {
                std::cout << "\nAttribute -> " << i.first << "\n\t Vector -> ";
                print_vector(i.second);
            }
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("interpreting the written code.", SystemOutofMemoryException);
    }
    return 0;
}

#endif