
#pragma once

#ifndef _SRON_FNC_H_
#define _SRON_FNC_H_

#include "_bytecode_file_mng_.hpp"

struct SronFunction
{
    SronByteCodeFileManip _codefile;

    // this variable contains the variables
    VariableManager _Vmanager;

    // ArgumentList containing the values passed to the function
    ArgListPtr _arglist;

    AnyBindPtr _return_value;

    inline SronFunction( const char*const&__function_name, ArgListPtr __args, AnyBindPtr __returnValue = Void::void_object) 
    : _codefile(__function_name), _arglist(__args) , _return_value(__returnValue)
               {  Logs::__FileStack__.push_back(__function_name);  }

    inline SronFunction(std::string &__function_name, ArgListPtr __args, AnyBindPtr __returnValue = Void::void_object) 
    : _codefile(__function_name.c_str()) , _arglist(__args) , _return_value(__returnValue) 
               {  Logs::__FileStack__.push_back(__function_name);  }

    ~SronFunction() { }
};

typedef SronFunction* SronFncPtr;

#endif