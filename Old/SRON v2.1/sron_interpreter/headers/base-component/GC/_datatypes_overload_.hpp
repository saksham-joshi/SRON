
#pragma once

#ifndef _DATATYPE_OVERLOAD_
#define _DATATYPE_OVERLOAD_

#include "_any_bind_.hpp"

inline static AnyBindPtr operator==(Any &__val1 , Any &__val2)
{

    return (__val1.__IS_EQUAL__(__val2)) ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator&&(Any &__val1 , Any &__val2)
{
    return (__val1.__AND__(__val2)) ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator||(Any &__val1 , Any &__val2)
{
    return (__val1.__OR__(__val2)) ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator!=(Any &__val1 , Any &__val2)
{
    return (__val1.__NOT_EQUAL__(__val2)) ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator!(Any &val)
{
    return (val.__NOT__()) ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator-(Any &val)
{
    return GarbageCollector::REGISTER_MEMORY(val.__NEGATE__());
}

inline static AnyBindPtr operator<(Any &__val1 , Any &__val2)
{
    return (__val1.__LESS_THAN__(__val2)) ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator<=(Any &__val1 , Any &__val2)
{
    return (__val1.__LESS_THAN_EQUAL__(__val2)) ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator>(Any &__val1 , Any &__val2)
{
    return (__val1.__MORE_THAN__(__val2)) ? Bool::__SronTrue : Bool::__SronFalse;
}
inline static AnyBindPtr operator>=(Any &__val1 , Any &__val2)
{
    return (__val1.__MORE_THAN_EQUAL__(__val2)) ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator+(Any &__val1 , Any &__val2)
{

    return GarbageCollector::REGISTER_MEMORY(__val1.__ADD__(__val2));
}

inline static AnyBindPtr operator-(Any &__val1 , Any &__val2)
{
    return GarbageCollector::REGISTER_MEMORY(__val1.__SUB__(__val2));
}
inline static AnyBindPtr operator*(Any &__val1 , Any &__val2)
{
    return GarbageCollector::REGISTER_MEMORY(__val1.__MULT__(__val2));
}

inline static AnyBindPtr operator/(Any &__val1 , Any &__val2)
{
    return GarbageCollector::REGISTER_MEMORY(__val1.__DIV__(__val2));
}

inline static AnyBindPtr operator%(Any &__val1 , Any &__val2)
{
    return GarbageCollector::REGISTER_MEMORY(__val1.__MOD__(__val2));
}

inline static AnyBindPtr operator^(Any &__val1 , Any &__val2)
{
    return GarbageCollector::REGISTER_MEMORY(__val1.__POW__(__val2));
}

inline static AnyBindPtr operator~(Any &__val)
{
    return GarbageCollector::REGISTER_MEMORY(__val.__BITWISE_NOT__());
}

inline static AnyBindPtr operator&(Any &__val1, Any &__val2)
{
    return GarbageCollector::REGISTER_MEMORY(__val1.__BITWISE_AND__(__val2));
}

inline static AnyBindPtr operator|(Any &__val1, Any &__val2)
{
    return GarbageCollector::REGISTER_MEMORY(__val1.__BITWISE_OR__(__val2));
}

inline static AnyBindPtr operator<<(Any &__val1, Any &__val2)
{
    return GarbageCollector::REGISTER_MEMORY(__val1.__LEFT_SHIFT__(__val2));
}

inline static AnyBindPtr operator>>(Any &__val1, Any &__val2)
{
    return GarbageCollector::REGISTER_MEMORY(__val1.__RIGHT_SHIFT__(__val2));
}

inline static void operator+=(Any &__val1, Any &__val2)
{
    __val1.__ADD_AND_ASSIGN__(__val2);
}
inline static void operator-=(Any &__val1, Any &__val2)
{
    __val1.__MIN_AND_ASSIGN__(__val2);
}
inline static void operator*=(Any &__val1, Any &__val2)
{
    __val1.__MULT_AND_ASSIGN__(__val2);
}
inline static void operator/=(Any &__val1, Any &__val2)
{
    __val1.__DIV_AND_ASSIGN__(__val2);
}
inline static void operator%=(Any &__val1, Any &__val2)
{
    __val1.__MOD_AND_ASSIGN__(__val2);
}
inline static void operator^=(Any &__val1, Any &__val2)
{
    __val1.__POW_AND_ASSIGN__(__val2);
}

#endif