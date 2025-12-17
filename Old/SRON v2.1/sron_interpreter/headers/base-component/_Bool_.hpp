
#pragma once

#ifndef _BOOL_H
#define _BOOL_H

#include "_Char_.hpp"

/*
  |====================== BOOL ===============================|
 'Bool' datatype uses bool to store values.
  > bool take 1 bytes.
  > Syntax in SRON : "Bool x = true" or "Bool x"
*/

inline Bool::Bool() {}
inline Bool::Bool(bool __val) : value(__val) {}

inline bool Bool::operator*()
{
    return this->value;
}

inline AnyPtr Bool::COPY() const
{
    return new Bool(this->value);
}

inline void Bool::PRINT() const
{
    std::cout << this->value;
}

inline void Bool::F_PRINT() const
{
    this->PRINT();
}

inline void Bool::PREMOVE(){ }

inline long long int Bool::SIZE_OF() const
{
    return sizeof(this->value);
}

inline std::string Bool::TO_STRING() const
{
    return (this->value) ? "true" : "false";
}

inline bool Bool::IS_COLLECTIVE() const
{
    return false;
}

inline const char *Bool::TYPE() const
{
    return "Bool";
}

inline void Bool::TYPE(std::string &str) const
{
    str.append("Bool");
}
inline const unsigned short int Bool::TYPE_NUMBER() const
{
    return TYPE_BOOL;
}


inline bool Bool::GET_BOOL_ABS()
{
    return this->value;
}
inline long long int Bool::GET_INT_ABS()
{
    return this->value;
}
inline double Bool::GET_DOUBLE_ABS(){
    return this->value;
}

inline BoolPtr Bool::GET_BOOL() const
{
    return const_cast<BoolPtr>(this);
}

inline bool Bool::GET() const noexcept
{
    return this->value;
}


inline IntPtr Bool::GET_INT() const
{
    IntPtr ptr = new Int(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr);

    return ptr;
}

inline bool Bool::__IS_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_BOOL:
        return this->value == **val.GET_BOOL();

    case TYPE_INT:
        return this->value == **val.GET_INT();
    }
 
    return false;
}

inline bool Bool::__NOT_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_BOOL:
        return this->value != **val.GET_BOOL();

    case TYPE_INT:
        return this->value != **val.GET_INT();
    }

    return true;
}

inline bool Bool::__AND__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_BOOL:
        return this->value && **val.GET_BOOL();

    case TYPE_INT:
        return this->value && **val.GET_INT();
    }

    MATH_EVALUATION_EXCEPTION("&&", "Bool", val.TYPE());

    return false;
}

inline bool Bool::__OR__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_BOOL:
        return this->value || **val.GET_BOOL();

    case TYPE_INT:
        return this->value || **val.GET_INT();
    }

    MATH_EVALUATION_EXCEPTION("||", "Bool", val.TYPE());

    return false;
}

inline bool Bool::__NOT__() const
{
    return !this->value;
}

inline bool Bool::__LESS_THAN__(Any &val) const
{

    return this->TYPE_NUMBER() < val.TYPE_NUMBER();
}

inline bool Bool::__LESS_THAN_EQUAL__(Any &val) const
{

    return this->TYPE_NUMBER() <= val.TYPE_NUMBER();
}
inline bool Bool::__MORE_THAN__(Any &val) const
{

    return this->TYPE_NUMBER() > val.TYPE_NUMBER();
}
inline bool Bool::__MORE_THAN_EQUAL__(Any &val) const
{

    return this->TYPE_NUMBER() >= val.TYPE_NUMBER();
}

inline Bool::~Bool() noexcept {}

#endif