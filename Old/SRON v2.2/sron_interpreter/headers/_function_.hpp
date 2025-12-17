
#pragma once

#ifndef _SRON_FNC_H_
#define _SRON_FNC_H_

#include "_bytecode_reader_.hpp"

struct SronFunction
{
    SronBytecodeReader _codefile;

    // contains the variables
    VariableManager _Vmanager;

    // ArgumentList containing the values passed to the function
    ArgListPtr _arglist;

    AnyBindPtr _return_value;

    inline SronFunction( BytecodeManager::BytecodeBinder& __file , ArgListPtr __args ) : 
    _codefile(__file.getStart(), __file.getEnd()) , _arglist(__args) , _return_value(Void::void_object)
    {
        this->_Vmanager.allocate( this->_codefile.readVariable());
    }

    inline SronFunction( const char*const __function_name, unsigned short int __len_of_function_name, const char*const __function_name_exclude_dir_path , ArgListPtr __args, AnyBindPtr __returnValue = Void::void_object) 
    : _codefile(__function_name , __len_of_function_name , __function_name_exclude_dir_path), _arglist(__args) , _return_value(__returnValue)
    { 
        this->_Vmanager.allocate( this->_codefile.readVariable());
    }


    inline SronFunction( SronFunction&& __fnc ) noexcept : _codefile(std::move(__fnc._codefile)) , 
    _Vmanager(std::move(__fnc._Vmanager)) , _arglist(__fnc._arglist) , _return_value(__fnc._return_value) 
               {      }

    inline SronFunction( SronFunction &) = delete;

    inline SronFunction operator=( SronFunction&) = delete;

    ~SronFunction() { }
};

typedef SronFunction* SronFncPtr;
typedef SronFunction& SronFncRef;

#endif