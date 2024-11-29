
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
        // This code is not open sourced for security reasons
    }

    inline void INSERT_WITH_CONVERTIBLE(const unsigned short int __expected_type , size_t __variable_id , AnyBind& __value){
        // This code is not open sourced for security reasons
    }

public:


    inline void INSERT(const flag_t type, const size_t variable_name)
    {
        // This code is not open sourced for security reasons
    }
    inline AnyBindPtr INSERT(AnyBindPtr value, const size_t __variable_id)
    {
        // This code is not open sourced for security reasons
    }

    inline void INSERT(const flag_t __flag, const size_t __variable_id, AnyBindPtr __value)
    {
        // This code is not open sourced for security reasons
    }

    inline void FREE(const size_t __variable_id)
    {
        // This code is not open sourced for security reasons
    }

    inline auto GET_ITERATOR(const size_t __variable_id)
    {

        // This code is not open sourced for security reasons
    }

    inline AnyBindPtr GET(const size_t __variable_id)
    {
        // This code is not open sourced for security reasons
    }

    inline void CLEAR()
    {
        vmap.Clear();
    }

    inline ~VariableManager() noexcept {}
};

#endif