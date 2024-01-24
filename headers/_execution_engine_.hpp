#include "headers/lexical_analyst.hpp"

#ifndef EXECUTOR_H
#define EXECUTOR_H

namespace EXECUTION_ENGINE{
    std::vector<Function> function_vector;

    Function& FIND_FUNCTION(std::string fnc_name){
        for(auto& fnc : EXECUTION_ENGINE::function_vector){
            if(fnc.fnc_name == fnc_name){
                return fnc;
            }
        }
        if(fnc_name == "MAIN" || fnc_name == "main" || fnc_name == "Main"){
            DISPLAY_EXCEPTION("finding the main function.",MainFunctionNotFoundException);
        }
        DISPLAY_EXCEPTION(("finding the '"+ fnc_name +"' function.").c_str(),FunctionNotFoundException);
        exit(1);
    }

    void EXECUTE(std::vector<Function>& vec){
        EXECUTION_ENGINE::function_vector = vec;

        auto& main_fnc = FIND_FUNCTION("main");

        for(const auto& codemap : main_fnc.codemap){
            std::string attribute = codemap.first;
            if(attribute == "variables"){

            }
            else if(attribute == "if"){

            }
            else if(attribute == "for"){

            }
            else if(attribute == "while"){

            }
    
        }
    }
}

#endif