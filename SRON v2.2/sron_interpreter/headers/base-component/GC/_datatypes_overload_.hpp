
#pragma once

#ifndef _DATATYPE_OVERLOAD_
#define _DATATYPE_OVERLOAD_

#include "_any_bind_.hpp"

inline static AnyBindPtr operator==(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__IS_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__IS_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__IS_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__IS_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__IS_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__IS_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__IS_EQUAL__( *__val2 , __val2.type()); break;

        default : output = (__val1->__IS_EQUAL__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator&&(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__AND__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__AND__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__AND__( *__val2 , __val2.type()); break;

        default : output = (__val1->__AND__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator||(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__OR__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__OR__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__OR__( *__val2 , __val2.type()); break;

        default : output = (__val1->__OR__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator!=(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__NOT_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__NOT_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__NOT_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__NOT_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__NOT_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__NOT_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__NOT_EQUAL__( *__val2 , __val2.type()); break;

        default : output = (__val1->__NOT_EQUAL__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator!(AnyBind &__value)
{
    SronBool_t output;

    switch ( __value.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __value.ptr() )->__NOT__(); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __value.ptr() )->__NOT__(); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __value.ptr() )->__NOT__(); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __value.ptr() )->__NOT__(); break;

        default : output = __value->__NOT__();
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator-(AnyBind &__value)
{
    AnyPtr output = nullptr;

    switch ( __value.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __value.ptr() )->__NEGATE__(); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __value.ptr() )->__NEGATE__(); break;

        default : output = __value->__NEGATE__();
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator<(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__LESS_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__LESS_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__LESS_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__LESS_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__LESS_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__LESS_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__LESS_THAN__( *__val2 , __val2.type()); break;

        default : output = (__val1->__LESS_THAN__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator<=(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__LESS_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__LESS_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__LESS_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__LESS_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__LESS_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__LESS_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__LESS_THAN_EQUAL__( *__val2 , __val2.type()); break;

        default : output = (__val1->__LESS_THAN_EQUAL__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator>(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__MORE_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__MORE_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__MORE_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__MORE_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__MORE_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__MORE_THAN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__MORE_THAN__( *__val2 , __val2.type()); break;

        default : output = (__val1->__MORE_THAN__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator>=(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output = false;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__MORE_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__MORE_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__MORE_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__MORE_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__MORE_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__MORE_THAN_EQUAL__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__MORE_THAN_EQUAL__( *__val2 , __val2.type()); break;

        default : output = (__val1->__MORE_THAN_EQUAL__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator+(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__ADD__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__ADD__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__ADD__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__ADD__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__ADD__( *__val2 , __val2.type()); break;

        default : output = (__val1->__ADD__(*__val2 , __val2.type()));
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator-(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__SUB__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__SUB__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__SUB__( *__val2 , __val2.type()); break;

        default : output = (__val1->__SUB__(*__val2 , __val2.type()));
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator*(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__MULT__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__MULT__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__MULT__( *__val2 , __val2.type()); break;

        default : output = (__val1->__MULT__(*__val2 , __val2.type()));
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator/(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__DIV__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__DIV__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__DIV__( *__val2 , __val2.type()); break;

        default : output = (__val1->__DIV__(*__val2 , __val2.type()));
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator%(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__MOD__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__MOD__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__MOD__( *__val2 , __val2.type()); break;

        default : output = (__val1->__MOD__(*__val2 , __val2.type()));
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator^(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__POW__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__POW__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__POW__( *__val2 , __val2.type()); break;

        default : output = (__val1->__POW__(*__val2 , __val2.type()));
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator~(AnyBind &__value)
{
    AnyPtr output = nullptr;

    switch ( __value.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __value.ptr() )->__BITWISE_NOT__(); break;

        default : output = (__value->__BITWISE_NOT__());
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator&(AnyBind &__val1, AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__BITWISE_AND__( *__val2 , __val2.type()); break;

        default : output = __val2->__BITWISE_AND__( *__val2 , __val2.type());
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator|(AnyBind &__val1, AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__BITWISE_OR__( *__val2 , __val2.type()); break;

        default : output = __val2->__BITWISE_OR__( *__val2 , __val2.type());
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator<<(AnyBind &__val1, AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__LEFT_SHIFT__( *__val2 , __val2.type()); break;

        default : output = __val2->__LEFT_SHIFT__( *__val2 , __val2.type());
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static AnyBindPtr operator>>(AnyBind &__val1, AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__RIGHT_SHIFT__( *__val2 , __val2.type()); break;

        default : output = __val2->__RIGHT_SHIFT__( *__val2 , __val2.type());
    }

    return GarbageCollector::REGISTER_MEMORY( output );
}

inline static void operator+=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__ADD_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__ADD_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__ADD_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  stringCast( __val1.ptr() )->__ADD_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST :   listCast( __val1.ptr() )->__ADD_AND_ASSIGN__( *__val2 , __val2.type()); break;

        default : __val1->__ADD_AND_ASSIGN__( *__val2 , __val2.type() );
    }
}
inline static void operator-=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__MIN_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__MIN_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__MIN_AND_ASSIGN__( *__val2 , __val2.type()); break;

        default : __val1->__MIN_AND_ASSIGN__( *__val2 , __val2.type() );
    }
}
inline static void operator*=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__MULT_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__MULT_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__MULT_AND_ASSIGN__( *__val2 , __val2.type()); break;

        default : __val1->__MULT_AND_ASSIGN__( *__val2 , __val2.type() );
    }
}
inline static void operator/=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__DIV_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__DIV_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__DIV_AND_ASSIGN__( *__val2 , __val2.type()); break;

        default : __val1->__DIV_AND_ASSIGN__( *__val2 , __val2.type() );
    }
}
inline static void operator%=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__MOD_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__MOD_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__MOD_AND_ASSIGN__( *__val2 , __val2.type()); break;

        default : __val1->__MOD_AND_ASSIGN__( *__val2 , __val2.type() );
    }
}
inline static void operator^=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__POW_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__POW_AND_ASSIGN__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__POW_AND_ASSIGN__( *__val2 , __val2.type()); break;

        default : __val1->__POW_AND_ASSIGN__( *__val2 , __val2.type() );
    }
}

#endif