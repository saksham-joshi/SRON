//#include <iostream>
#include <string>
#include "Support.hpp"
// #include <stack>
// #include "./_string_.hpp"
// #include "./_hashtable_.hpp"
// #include "./_utility_.hpp"
// #include "./Argument_List.hpp"
// #include "./lexical_analyst.hpp"
// #include "./Variable_Manager.hpp"

#ifndef _EXECUTOR_H
#define _EXECUTOR_H




class Executor
{
    

private:
    friend int main(int argc, char **argv);

public:
    Executor()
    {
        
    }
    void VARIABLES(std::vector<std::string> vec)
    {
        try
        {
            for (std::vector<std::string>::iterator it = vec.begin() + 3; it != vec.end(); ++it)
            {
                if (*it == "Int")
                {
                    if(it < vec.end()-2){
                        
                    }
                    

                }
                else if(*it == "Double"){

                }
                else if(*it == "String"){

                }
                else if(*it == "Char"){

                }
                else if(*it == "Bool"){
                    
                }
            }
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            DISPLAY_EXCEPTION("storing the variable from \'variables\' attribute.", 19);
        }
    }
};

#endif