#pragma once

#ifndef _VOID_H
#define _VOID_H

#include "GC/_datatypes_overload_.hpp"

/*
  |====================== VOID ===============================|
 'Void' datatype will be used to implement NULL or None values.
  > Syntax in SRON : "Void x"
*/

inline Void::Void() {}

inline AnyPtr Void::COPY() const
{
    return new Void();
}

inline void Void::PRINT() const
{
    std::cout << __void_printable_string__;
}

inline void Void::F_PRINT() const
{
    this->PRINT();
}

inline long long int Void::SIZE_OF() const
{
    return 0;
}
inline std::string Void::TO_STRING() const
{
    return __void_printable_string__;
}

inline bool Void::IS_COLLECTIVE() const
{
    return false;
}

inline void Void::PREMOVE(){ }


inline const char *Void::TYPE() const
{
    return "Void";
}
inline void Void::TYPE(std::string &str) const
{
    str.append("Void");
}

inline const unsigned short int Void::TYPE_NUMBER() const
{
    return TYPE_VOID;
}

inline VoidPtr Void::GET_VOID() const
{
    return const_cast<Void *>(this);
}

// operative methods ....
inline AnyPtr Void::__ADD__(Any &val) const
{
    if (val.TYPE_NUMBER() == TYPE_STRING)
    {
        return new String(this->TO_STRING() + (**val.GET_STRING()));
    }

    MATH_EVALUATION_EXCEPTION("+", "Void", val.TYPE());

    return nullptr;
}

inline bool Void::__IS_EQUAL__(Any &val) const
{
    return (val.TYPE_NUMBER() == this->TYPE_NUMBER());
}

inline bool Void::__NOT_EQUAL__(Any &val) const
{
    return this->TYPE_NUMBER() != val.TYPE_NUMBER();
}

inline bool Void::__LESS_THAN__(Any &val) const
{

    return this->TYPE_NUMBER() < val.TYPE_NUMBER();
}

inline bool Void::__LESS_THAN_EQUAL__(Any &val) const
{

    return this->TYPE_NUMBER() <= val.TYPE_NUMBER();
}
inline bool Void::__MORE_THAN__(Any &val) const
{

    return this->TYPE_NUMBER() > val.TYPE_NUMBER();
}
inline bool Void::__MORE_THAN_EQUAL__(Any &val) const
{

    return this->TYPE_NUMBER() >= val.TYPE_NUMBER();
}

// this object will not be registered on GarbageCollector!
//AnyBindPtr Void::void_object;

inline Void::~Void() noexcept {}

#endif