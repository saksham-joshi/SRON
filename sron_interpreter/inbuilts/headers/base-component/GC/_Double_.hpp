#pragma once

#ifndef _DOUBLE_H
#define _DOUBLE_H

#include "_Void_.hpp"

/*
  |====================== DOUBLE ===============================|
 'Double' datatype use double to store values.
  > long double take 8 bytes.
  > Syntax in SRON : Double x = 1235.123124
*/

unsigned short Double::precision = 3;

inline Double::Double(const SronDouble_t __val) noexcept : value( __val ) { }

inline Double::Double(std::string &val) : value(Converter::toDouble(val)) {}

inline Double Double::operator=(double val)
{
    return Double(val);
}

inline Double::operator double() const
{
    return this->value;
}

inline AnyPtr Double::copy() const
{
    return new Double(this->value);
}

inline void Double::print() const
{
    Double::PRECISION_PRINT( this->value);
}

inline void Double::formatPrint() const
{
    this->print();
}

inline void Double::preMove(){ }

inline void Double::fillObuffer(SronOBuffer& __buffer) const
{
    __buffer << this->value;
}

inline long long int Double::sizeOf() const
{
    return sizeof(class Double);
}

inline std::string Double::toString() const
{
    return std::to_string(this->value);
}

inline bool Double::isCollective() const
{
    return false;
}


inline const char *Double::type() const
{
    return "Double";
}

inline void Double::type(std::string &str) const
{
    str.append("Double");
}

inline SronTypeNum Double::typeNum() const
{
    return SronTypeNum::TYPE_DOUBLE;
}

inline SronDouble_t Double::getBaseDouble() const noexcept
{
    return this->value;
}


inline AnyPtr Double::__add__(Any & __val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Double(this->value + intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE: return new Double(this->value + doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_STRING : return new String(std::to_string(this->value).append( stringCast(&__val)->getBaseString() ));

        default : mathEvaluationException("+", "Double", __val.type());
    }

    return nullptr;
}

inline AnyPtr Double::__sub__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Double(this->value - intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE: return new Double(this->value - doubleCast(&__val)->getBaseDouble());

        default : mathEvaluationException("-", "Double", __val.type());
    }

    return nullptr;
}

inline AnyPtr Double::__mult__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Double(this->value * (intCast(&__val)->getBaseInt()));

        case SronTypeNum::TYPE_DOUBLE: return new Double(this->value * (doubleCast(&__val)->getBaseDouble()));

        default : mathEvaluationException("*", "Double", __val.type());
    }

    return nullptr;
}

inline AnyPtr Double::__div__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Double(safeDivide(this->value, intCast(&__val)->getBaseInt()));

        case SronTypeNum::TYPE_DOUBLE: return new Double(safeDivide(this->value, doubleCast(&__val)->getBaseDouble()));

        default : mathEvaluationException("/", "Double", __val.type());
    }

    return nullptr;
}

inline AnyPtr Double::__mod__(Any &__val , SronTypeNum __type) const
{

    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Double(SAFE_MOD(this->value, intCast(&__val)->getBaseInt()));

        case SronTypeNum::TYPE_DOUBLE: return new Double(SAFE_MOD(this->value, doubleCast(&__val)->getBaseDouble()));

        default : mathEvaluationException("%", "Double", __val.type());
    }

    return nullptr;
}

inline AnyPtr Double::__pow__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Double(std::pow(this->value, intCast(&__val)->getBaseInt()));

        case SronTypeNum::TYPE_DOUBLE: return new Double(std::pow(this->value, doubleCast(&__val)->getBaseDouble()));

        default : mathEvaluationException("^", "Double", __val.type());
    }

    return nullptr;
}

inline SronBool_t Double::__isEqual__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value == intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE: return this->value == doubleCast(&__val)->getBaseDouble();

        default : { }
    }

    return false;
}

inline SronBool_t Double::__notEqual__(Any & __val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return this->value != intCast(&__val)->getBaseInt();

        case SronTypeNum::TYPE_DOUBLE: return this->value != doubleCast(&__val)->getBaseDouble();

        default : { }
    }

    return true;
}

inline SronBool_t Double::__lessThan__(Any & __val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value < intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE: return (this->value < doubleCast(&__val)->getBaseDouble());

        default : { }
    }

    return this->typeNum() < __type;
}

inline SronBool_t Double::__lessEqual__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value <= intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE: return (this->value <= intCast(&__val)->getBaseInt());

        default : { }
    }

    return this->typeNum() <= __type;
}

inline SronBool_t Double::__moreThan__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value > intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE: return (this->value > doubleCast(&__val)->getBaseDouble());

        default : { }
    }

    return this->typeNum() > __type;
}

inline SronBool_t Double::__moreEqual__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value >= intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE: return (this->value >= doubleCast(&__val)->getBaseDouble());

        default : { }
    }

    return this->typeNum() >= __type;
}

inline AnyPtr Double::__negate__() const
{
    return new Double(-this->value);
}

inline SronBool_t Double::__not__() const
{
    return !this->value;
}

inline void Double::__addAssign__(Any& __val , SronTypeNum __type)
{
    switch(__type)
    {
        case SronTypeNum::TYPE_INT : this->value += (intCast(&__val)->getBaseInt()); break;

        case SronTypeNum::TYPE_DOUBLE : this->value += (doubleCast(&__val)->getBaseDouble()); break;

        default : mathEvaluationException("+=", this->type(), __val.type());
    }
}

inline void Double::__subAssign__(Any& __val, SronTypeNum __type)
{
    switch(__type)
    {
        case SronTypeNum::TYPE_INT : this->value -= (intCast(&__val)->getBaseInt()); break;

        case SronTypeNum::TYPE_DOUBLE : this->value -= (doubleCast(&__val)->getBaseDouble()); break;

        default : mathEvaluationException("-=", this->type(), __val.type());
    }
}

inline void Double::__multAssign__(Any& __val, SronTypeNum __type)
{
    switch(__type)
    {
        case SronTypeNum::TYPE_INT : this->value *= (intCast(&__val)->getBaseInt()); break;

        case SronTypeNum::TYPE_DOUBLE : this->value *= (doubleCast(&__val)->getBaseDouble()); break;

        default : mathEvaluationException("*=", this->type(), __val.type());
    }
}

inline void Double::__divAssign__(Any& __val , SronTypeNum __type)
{
    switch(__type)
    {
        case SronTypeNum::TYPE_INT : this->value /= (intCast(&__val)->getBaseInt()); break;

        case SronTypeNum::TYPE_DOUBLE : this->value /= (doubleCast(&__val)->getBaseDouble()); break;

        default : mathEvaluationException("/=", this->type(), __val.type());
    }
}

inline void Double::__modAssign__(Any& __val , SronTypeNum __type){

    switch(__type)
    {
        case SronTypeNum::TYPE_INT : this->value = std::fmod( this->value, (intCast(&__val)->getBaseInt()) ); break;

        case SronTypeNum::TYPE_DOUBLE : this->value = std::fmod(this->value, (doubleCast(&__val)->getBaseDouble()) ); break;

        default : mathEvaluationException("/=", this->type(), __val.type());
    }
}

inline void Double::__powAssign__(Any& __val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value = std::pow( this->value, (intCast(&__val)->getBaseInt()) ); break;

        case SronTypeNum::TYPE_DOUBLE : this->value = std::pow( this->value, (doubleCast(&__val)->getBaseDouble()) ); break;

        default : mathEvaluationException("^=", this->type(), __val.type());
    }
}

inline Double::~Double() noexcept{}

#endif