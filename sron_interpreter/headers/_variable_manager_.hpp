
/*
 * This class will work as a storage of variables and values.
 * It can store values of type long long int, long double, char, string and bool, List renamed as Int, Double, Char, String and Bool respectively in SRON.
 * It uses the map of string and Any*. string will store the variable name and Any* will store the reference to the values.
 */

#pragma once

#ifndef VariableManager_H
#define VariableManager_H

#include "base-component/_String_.hpp"

class VariableManager
{


private:
    Vmap_t vmap;

    inline void INSERT_WITH_STRICT_TYPE_CHECK(const unsigned short int __expected_type, size_t __variable_id, AnyBind& __value){
        
    }

    inline void INSERT_WITH_CONVERTIBLE(const unsigned short int __expected_type , size_t __variable_id , AnyBind& __value){
        
    }

public:


    inline void INSERT(const flag_t type, const size_t variable_name)
    {
        
    }
    inline AnyBindPtr INSERT(AnyBindPtr value, const size_t __variable_id)
    {
        
    }

    inline void INSERT(const flag_t __flag, const size_t __variable_id, AnyBindPtr __value)
    {
        
    }

    inline void FREE(const size_t __variable_id)
    {
        
    }

    inline auto GET_ITERATOR(const size_t __variable_id)
    {

        
    }

    inline AnyBindPtr GET(const size_t __variable_id)
    {
        
    }

    inline void CLEAR()
    {
        vmap.Clear();
    }

    inline ~VariableManager() noexcept {}
};

#endif