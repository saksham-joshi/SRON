
/*
 * This class will work as a storage of variables and values.
 * It can store values of type long long int, long double, char, string and bool, List renamed as Int, Double, Char, String and Bool respectively in SRON.
 * It uses the map of string and Any*. string will store the variable name and Any* will store the reference to the values.
 */

#pragma once

#ifndef VariableManager_H
#define VariableManager_H

#include "_datatypes_.hpp"

class VariableManager
{
private:
    std::unordered_map<std::string, Any *> vmap;

public:
    inline void INSERT(std::string &type, std::string &variable_name);
    
    inline void INSERT(std::string variable_name, Any *value);

    inline void FREE(std::string &variable_name); 
    

    inline Any *GET(std::string variable_name);

    inline void CLEAR();

    ~VariableManager()
    {
        this->CLEAR();
    }
};

#endif