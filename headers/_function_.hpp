#include "_variable_manager_.hpp"

#ifndef _FUNCTION_H
#define _FUNCTION_H

typedef std::pair<std::string, std::vector<std::string>> InstructionPair;
typedef std::vector<InstructionPair> InstructionVector;

struct Function
{
    std::string fnc_name;
    InstructionVector codemap;
    VariableManager Vmanager;
    
    Function(std::string fname,InstructionVector code,VariableManager vm) : codemap(code) ,fnc_name(fname), Vmanager(vm) { }
};


#endif