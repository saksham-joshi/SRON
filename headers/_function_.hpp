#include<vector>
#include<string>
#include "Argument_List.hpp"
#include "Variable_Manager.hpp"

#ifndef _FUNCTION_H
#define _FUNCTION_H

struct _function_
{
    std::string function_name;
    std::vector<std::string> lexcode;
    VariableManager vm ;

    _function_(std::string& function_name,std::vector<std::string>& lexcode){
        this->function_name = function_name;
        this->lexcode = lexcode;
        VariableManager vm(function_name) ;
        this->vm = vm;
    }
};
#endif