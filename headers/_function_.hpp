#include<unordered_map>
#include "_user_fnc_.hpp"
#include<functional>

#ifndef _FUNCTION_H
#define _FUNCTION_H

typedef std::pair<std::string, std::vector<std::string>> InstructionPair;
typedef std::vector<InstructionPair> InstructionVector;

struct Function
{
    std::string fnc_name;
    InstructionVector codemap;
    
    Function(std::string fname,InstructionVector code) : codemap(code) ,fnc_name(fname) { }
};

using FunctionMap = std::unordered_map<std::string, std::function<Any*(Argument_List&)>>;
using namespace Sron;

inline static FunctionMap& GET_FNC_MAP(){
    static FunctionMap fmap{
        {"PRINTLN",PRINTLN},
        {"PRINT",PRINT},
        {"LEN",LEN},
        {"SIZE_OF",SIZE_OF},
        {"AT",AT}
    };
    return fmap;
}


#endif