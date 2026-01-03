
#pragma once

#ifndef _DATATYPE_OVERLOAD_
#define _DATATYPE_OVERLOAD_

#include "_any_bind_.hpp"

inline static AnyBindPtr operator==(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__isEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__isEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__isEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__isEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__isEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__isEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LITERAL_STR : output = lstrCast(__val1.ptr() )->__isEqual__(*__val2, __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__isEqual__( *__val2 , __val2.type()); break;

        default : output = (__val1->__isEqual__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator&&(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__and__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__and__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__and__( *__val2 , __val2.type()); break;

        default : output = (__val1->__and__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator||(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__or__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__or__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__or__( *__val2 , __val2.type()); break;

        default : output = (__val1->__or__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator!=(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__notEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__notEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__notEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__notEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__notEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__notEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LITERAL_STR : output = lstrCast(__val1.ptr() )->__notEqual__(*__val2, __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__notEqual__( *__val2 , __val2.type()); break;

        default : output = (__val1->__notEqual__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator!(AnyBind &__value)
{
    SronBool_t output;

    switch ( __value.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __value.ptr() )->__not__(); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __value.ptr() )->__not__(); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __value.ptr() )->__not__(); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __value.ptr() )->__not__(); break;

        default : output = __value->__not__();
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator-(AnyBind &__value)
{
    AnyPtr output = nullptr;

    switch ( __value.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __value.ptr() )->__negate__(); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __value.ptr() )->__negate__(); break;

        default : output = __value->__negate__();
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator<(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__lessThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__lessThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__lessThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__lessThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__lessThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__lessThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LITERAL_STR : output = lstrCast(__val1.ptr() )->__lessThan__(*__val2, __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__lessThan__( *__val2 , __val2.type()); break;

        default : output = (__val1->__lessThan__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator<=(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__lessEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__lessEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__lessEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__lessEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__lessEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__lessEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LITERAL_STR : output = lstrCast(__val1.ptr() )->__lessEqual__(*__val2, __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__lessEqual__( *__val2 , __val2.type()); break;

        default : output = (__val1->__lessEqual__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator>(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__moreThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__moreThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__moreThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__moreThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__moreThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__moreThan__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LITERAL_STR : output = lstrCast(__val1.ptr() )->__moreThan__(*__val2, __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__moreThan__( *__val2 , __val2.type()); break;

        default : output = (__val1->__moreThan__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator>=(AnyBind &__val1 , AnyBind &__val2)
{
    SronBool_t output = false;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_VOID:    output = voidCast( __val1.ptr() )->__moreEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__moreEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__moreEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__moreEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_BOOL:    output = boolCast( __val1.ptr() )->__moreEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__moreEqual__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LITERAL_STR : output = lstrCast(__val1.ptr() )->__moreEqual__(*__val2, __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__moreEqual__( *__val2 , __val2.type()); break;

        default : output = (__val1->__moreEqual__(*__val2 , __val2.type()));
    }

    return output ? Bool::__SronTrue : Bool::__SronFalse;
}

inline static AnyBindPtr operator+(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__add__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__add__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__add__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  output = stringCast( __val1.ptr() )->__add__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST:    output = listCast( __val1.ptr() )->__add__( *__val2 , __val2.type()); break;

        default : output = (__val1->__add__(*__val2 , __val2.type()));
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator-(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__sub__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__sub__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__sub__( *__val2 , __val2.type()); break;

        default : output = (__val1->__sub__(*__val2 , __val2.type()));
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator*(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__mult__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__mult__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__mult__( *__val2 , __val2.type()); break;

        default : output = (__val1->__mult__(*__val2 , __val2.type()));
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator/(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__div__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__div__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__div__( *__val2 , __val2.type()); break;

        default : output = (__val1->__div__(*__val2 , __val2.type()));
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator%(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__mod__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__mod__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__mod__( *__val2 , __val2.type()); break;

        default : output = (__val1->__mod__(*__val2 , __val2.type()));
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator^(AnyBind &__val1 , AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__pow__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  output = doubleCast( __val1.ptr() )->__pow__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    output = charCast( __val1.ptr() )->__pow__( *__val2 , __val2.type()); break;

        default : output = (__val1->__pow__(*__val2 , __val2.type()));
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator~(AnyBind &__value)
{
    AnyPtr output = nullptr;

    switch ( __value.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __value.ptr() )->__bitNot__(); break;

        default : output = (__value->__bitNot__());
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator&(AnyBind &__val1, AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__bitAnd__( *__val2 , __val2.type()); break;

        default : output = __val2->__bitAnd__( *__val2 , __val2.type());
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator|(AnyBind &__val1, AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__bitOr__( *__val2 , __val2.type()); break;

        default : output = __val2->__bitOr__( *__val2 , __val2.type());
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator<<(AnyBind &__val1, AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__leftShift__( *__val2 , __val2.type()); break;

        default : output = __val2->__leftShift__( *__val2 , __val2.type());
    }

    return GarbageCollector::registerMemory( output );
}

inline static AnyBindPtr operator>>(AnyBind &__val1, AnyBind &__val2)
{
    AnyPtr output = nullptr;

    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     output = intCast( __val1.ptr() )->__rightShift__( *__val2 , __val2.type()); break;

        default : output = __val2->__rightShift__( *__val2 , __val2.type());
    }

    return GarbageCollector::registerMemory( output );
}

inline static void operator+=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__addAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__addAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__addAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_STRING:  stringCast( __val1.ptr() )->__addAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_LIST :   listCast( __val1.ptr() )->__addAssign__( *__val2 , __val2.type()); break;

        default : __val1->__addAssign__( *__val2 , __val2.type() );
    }
}
inline static void operator-=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__subAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__subAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__subAssign__( *__val2 , __val2.type()); break;

        default : __val1->__subAssign__( *__val2 , __val2.type() );
    }
}
inline static void operator*=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__multAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__multAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__multAssign__( *__val2 , __val2.type()); break;

        default : __val1->__multAssign__( *__val2 , __val2.type() );
    }
}
inline static void operator/=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__divAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__divAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__divAssign__( *__val2 , __val2.type()); break;

        default : __val1->__divAssign__( *__val2 , __val2.type() );
    }
}
inline static void operator%=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__modAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__modAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__modAssign__( *__val2 , __val2.type()); break;

        default : __val1->__modAssign__( *__val2 , __val2.type() );
    }
}
inline static void operator^=(AnyBind &__val1, AnyBind &__val2)
{
    switch ( __val1.type() )
    {
        case SronTypeNum::TYPE_INT:     intCast( __val1.ptr() )->__powAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_DOUBLE:  doubleCast( __val1.ptr() )->__powAssign__( *__val2 , __val2.type()); break;

        case SronTypeNum::TYPE_CHAR:    charCast( __val1.ptr() )->__powAssign__( *__val2 , __val2.type()); break;

        default : __val1->__powAssign__( *__val2 , __val2.type() );
    }
}

#endif