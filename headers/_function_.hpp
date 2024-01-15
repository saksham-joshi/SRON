#include<unordered_map>
#include "_user_fnc_.hpp"
#include<functional>

#ifndef _FUNCTION_H
#define _FUNCTION_H

struct Function
{
    std::unordered_map <std::string, std::vector<std::string> > codemap;

    Function(std::unordered_map <std::string, std::vector<std::string> > codemap){
        this->codemap = codemap;
    }
};



using FunctionMap = std::unordered_map<std::string, std::function<Any*(Argument_List&)>>;
using namespace Sron;

// std::unordered_map<string,std::function>FunctionMap;

inline static FunctionMap& GET_FNC_MAP(){
    static FunctionMap fmap{
        {"PRINTLN",PRINTLN},
        {"PRINT",PRINT},
        {"LEN",LEN}
    };
    return fmap;
}


#endif

// int main(){
//     auto& val = GET_FNC_MAP();
//     Argument_List args;
//     args.PUT(new Int(123456));
    
//     // val["PRINT"](args);
//     // args.CLEAR();
//     args.PUT(val["LEN"](args));
//     val["PRINTLN"](args);
// }