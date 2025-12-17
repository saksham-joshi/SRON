
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

public:
    typedef std::unordered_map<size_t, AnyBindPtr> Vmap_t;

private:
    Vmap_t vmap;

    inline void INSERT_WITH_STRICT_TYPE_CHECK(const unsigned short int __expected_type, size_t __variable_id, AnyBind& __value){

            if(__value->TYPE_NUMBER() == __expected_type)
            {
                vmap[__variable_id] = &__value;
                return;
            }
            throw ThrowException("receving arguments value. Expected a argument of type '"+std::string() +"' but found type '"+std::string(__value->TYPE())+"'");
    }

    inline void INSERT_WITH_CONVERTIBLE(const unsigned short int __expected_type , size_t __variable_id , AnyBind& __value){

        // if the value is of type same as the expected_type then directly storing the value to the vmap
        if(__value->TYPE_NUMBER() == __expected_type){
            this->vmap[__variable_id] = &__value;
            return;
        }

        // program flow will come here when there the expected_type and the value is 
        // not same, then we will try converting the value to as per the expected_type

        switch(__expected_type){

            case TYPE_INT : __value->GET_INT(); break;

            case TYPE_DOUBLE : __value->GET_DOUBLE(); break;

            case TYPE_CHAR : __value->GET_CHAR(); break;

            case TYPE_BOOL : this->vmap[__variable_id] = ((__value->GET_BOOL_ABS())? Bool::__SronTrue : Bool::__SronFalse); return;

            case TYPE_STRING : __value->GET_STRING(); break;

            case TYPE_LIST : __value->GET_LIST(); break;

            default : throw ThrowException("assigning arguments to the function. Found invalid type '"+ std::to_string (__expected_type) +"'");
        }

        this->vmap[__variable_id] = &GarbageCollector::__top->back();
    }

public:


    inline void INSERT(const flag_t type, const size_t variable_name)
    {

        switch (type)
        {

            case Flag_Any : this->vmap[variable_name] = Void::void_object; break;

            case Flag_Int : this->vmap[variable_name] = GarbageCollector::REGISTER_MEMORY(new Int()); break;

            case Flag_Double : this->vmap[variable_name] = GarbageCollector::REGISTER_MEMORY(new Double()); break;

            case Flag_Char : this->vmap[variable_name] = GarbageCollector::REGISTER_MEMORY(new Char()); break;

            case Flag_Bool : this->vmap[variable_name] = GarbageCollector::REGISTER_MEMORY(new Bool()); break;

            case Flag_String : this->vmap[variable_name] = GarbageCollector::REGISTER_MEMORY(new String()); break;

            case Flag_List : this->vmap[variable_name] = GarbageCollector::REGISTER_MEMORY(new List()); break;

            default : throw ThrowException("declaring and allocating memory space for variables", InvalidTypeException);
        }
    }
    inline AnyBindPtr INSERT(AnyBindPtr value, const size_t __variable_id)
    {
        try
        {
            return this->vmap[__variable_id] = value;
        }
        catch (const std::exception &)
        {
            throw std::bad_alloc();
        }
    }

    inline void INSERT(const flag_t __flag, const size_t __variable_id, AnyBindPtr __value)
    {

        switch (__flag)
        {

            case Flag_Any : this->vmap[__variable_id] = __value; break;

            case Flag_Int : INSERT_WITH_CONVERTIBLE(TYPE_INT , __variable_id, *__value); break;

            case Flag_Double : INSERT_WITH_CONVERTIBLE(TYPE_DOUBLE , __variable_id, *__value); break;

            case Flag_Char : INSERT_WITH_CONVERTIBLE(TYPE_CHAR , __variable_id, *__value); break;

            case Flag_Bool : INSERT_WITH_CONVERTIBLE(TYPE_BOOL , __variable_id, *__value); break;

            case Flag_String : INSERT_WITH_CONVERTIBLE(TYPE_STRING , __variable_id, *__value); break;

            case Flag_List : INSERT_WITH_CONVERTIBLE(TYPE_LIST , __variable_id, *__value); break;

            case Flag_StrictInt : INSERT_WITH_STRICT_TYPE_CHECK(TYPE_INT, __variable_id , *__value ); break;

            case Flag_StrictDouble : INSERT_WITH_STRICT_TYPE_CHECK(TYPE_DOUBLE,  __variable_id , *__value ); break;

            case Flag_StrictChar : INSERT_WITH_STRICT_TYPE_CHECK(TYPE_CHAR,  __variable_id , *__value ); break;

            case Flag_StrictBool : INSERT_WITH_STRICT_TYPE_CHECK(TYPE_BOOL,  __variable_id , *__value ); break;

            case Flag_StrictString : INSERT_WITH_STRICT_TYPE_CHECK(TYPE_STRING,  __variable_id , *__value ); break;
            
            case Flag_StrictList : INSERT_WITH_STRICT_TYPE_CHECK(TYPE_LIST,  __variable_id , *__value ); break;

            default : throw ThrowException("assigning arguments to the function. Found flag '"+std::to_string(__flag) +"'", InvalidFlagException);
        
        }
    }

    inline void FREE(const size_t __variable_id)
    {
        Vmap_t::iterator it = vmap.find(__variable_id);

        if (it == vmap.end())
        {
            throw ThrowException("freeing up the memory space", VariableNotFoundException);
        }

        vmap.erase(it);
    }

    inline auto GET_ITERATOR(const size_t __variable_id)
    {

        auto it = this->vmap.find(__variable_id);

        if (it == this->vmap.end())
        {
            throw ThrowException("retreving the value of a variable at '" + std::to_string(__variable_id) + "'", VariableNotFoundException);
        }

        return it;
    }

    inline AnyBindPtr GET(const size_t __variable_id)
    {
        try
        {
            return vmap.at(__variable_id);
            
        }
        catch (const std::exception &)
        {
            throw ThrowException("retreving the value of a variable at '" + std::to_string(__variable_id) + "'", VariableNotFoundException);
        }
        return Void::void_object;
    }

    inline void CLEAR()
    {
        vmap.clear();
    }

    inline ~VariableManager() noexcept {}
};

#endif