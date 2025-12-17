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

inline Double::Double() {}
inline Double::Double(double val) : value(val) {}

inline Double::Double(std::string &val) : value(Converter::TO_DOUBLE(val)) {}

inline Double Double::operator=(double val)
{
    return Double(val);
}

inline Double::operator double() const
{
    return this->value;
}

inline AnyPtr Double::COPY() const
{
    return new Double(this->value);
}

inline void Double::PRINT() const
{
    std::cout << this->value;
}

inline void Double::F_PRINT() const
{
    this->PRINT();
}

inline void Double::PREMOVE(){ }

inline long long int Double::SIZE_OF() const
{
    return sizeof(this->value);
}

inline std::string Double::TO_STRING() const
{
    return std::to_string(this->value);
}

inline bool Double::IS_COLLECTIVE() const
{
    return false;
}


inline const char *Double::TYPE() const
{
    return "Double";
}

inline void Double::TYPE(std::string &str) const
{
    str.append("Double");
}

inline const unsigned short int Double::TYPE_NUMBER() const
{
    return TYPE_DOUBLE;
}

inline long long int Double::GET_INT_ABS(){
    return this->value;
}

inline double Double::GET_DOUBLE_ABS(){
    return this->value;
}

inline bool Double::GET_BOOL_ABS()
{
    return this->value;
}

inline DoublePtr Double::GET_DOUBLE() const
{
    return const_cast<Double *>(this);
}

inline IntPtr Double::GET_INT() const
{
    IntPtr ptr = new Int(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr);

    return ptr;
}

inline BoolPtr Double::GET_BOOL() const
{

    return (this->value > 0 ) ? Bool::__SronTrue->ptr_->GET_BOOL() : Bool::__SronFalse->ptr_->GET_BOOL();
}

inline void Double::SET(double &value)
{
    this->value = value;
}

inline AnyPtr Double::__ADD__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Double(this->value + (val.GET_INT_ABS()));

    case TYPE_DOUBLE:
        return new Double(this->value + (val.GET_DOUBLE_ABS()));

    case TYPE_STRING :
        return new String(std::to_string(this->value).append(**val.GET_STRING()));
    }

    MATH_EVALUATION_EXCEPTION("+", "Double", val.TYPE());

    return nullptr;
}

inline AnyPtr Double::__SUB__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Double(this->value - (val.GET_INT_ABS()));

    case TYPE_DOUBLE:
        return new Double(this->value - (val.GET_DOUBLE_ABS()));
    }

    MATH_EVALUATION_EXCEPTION("-", "Double", val.TYPE());

    return nullptr;
}

inline AnyPtr Double::__MULT__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Double(this->value * (val.GET_INT_ABS()));

    case TYPE_DOUBLE:
        return new Double(this->value * (val.GET_DOUBLE_ABS()));
    }

    MATH_EVALUATION_EXCEPTION("*", "Double", val.TYPE());

    return nullptr;
}

inline AnyPtr Double::__DIV__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Double(SAFE_DIVIDE(this->value, (val.GET_INT_ABS())));

    case TYPE_DOUBLE:
        return new Double(SAFE_DIVIDE(this->value,(val.GET_DOUBLE_ABS())));
    }

    MATH_EVALUATION_EXCEPTION("/", "Double", val.TYPE());

    return nullptr;
}

inline AnyPtr Double::__MOD__(Any &val) const
{

    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Double(SAFE_MOD(this->value, (val.GET_INT_ABS())));

    case TYPE_DOUBLE:
        return new Double(SAFE_MOD(this->value, (val.GET_DOUBLE_ABS())));
    }

    MATH_EVALUATION_EXCEPTION("%", "Double", val.TYPE());

    return nullptr;
}

inline AnyPtr Double::__POW__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Double(std::pow(this->value, val.GET_INT_ABS()));

    case TYPE_DOUBLE:
        return new Double(std::pow(this->value, val.GET_DOUBLE_ABS()));
    }

    MATH_EVALUATION_EXCEPTION("^", "Double", val.TYPE());

    return nullptr;
}

inline bool Double::__IS_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value == val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value == val.GET_DOUBLE_ABS());
    }

    return false;
}

inline bool Double::__NOT_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value != val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value != val.GET_DOUBLE_ABS());
    }

    return true;
}

inline bool Double::__LESS_THAN__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value < val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value < val.GET_DOUBLE_ABS());
    }

    return this->TYPE_NUMBER() < val.TYPE_NUMBER();
}

inline bool Double::__LESS_THAN_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value <= val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value <= val.GET_DOUBLE_ABS());
    }

    return this->TYPE_NUMBER() <= val.TYPE_NUMBER();
}

inline bool Double::__MORE_THAN__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value > val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value > val.GET_DOUBLE_ABS());
    }

    return this->TYPE_NUMBER() > val.TYPE_NUMBER();
}

inline bool Double::__MORE_THAN_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value >= val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value >= val.GET_DOUBLE_ABS());
    }

    return this->TYPE_NUMBER() >= val.TYPE_NUMBER();
}

inline AnyPtr Double::__NEGATE__() const
{
    return new Double(-this->value);
}

inline void Double::__ADD_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value += (__val.GET_INT_ABS()); break;

        case TYPE_DOUBLE : this->value += (__val.GET_DOUBLE_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("+=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__MIN_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value -= (__val.GET_INT_ABS()); break;

        case TYPE_DOUBLE : this->value -= (__val.GET_DOUBLE_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("-=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__MULT_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value *= (__val.GET_INT_ABS()); break;

        case TYPE_DOUBLE : this->value *= (__val.GET_DOUBLE_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("*=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__DIV_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value /= (__val.GET_INT_ABS()); break;

        case TYPE_DOUBLE : this->value /= (__val.GET_DOUBLE_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("/=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__MOD_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value = std::fmod( this->value, (__val.GET_INT_ABS())); break;

        case TYPE_DOUBLE : this->value = std::fmod(this->value, (__val.GET_DOUBLE_ABS())); break;

        default : MATH_EVALUATION_EXCEPTION("/=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__POW_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value = std::pow( this->value, (__val.GET_INT_ABS())); break;

        case TYPE_DOUBLE : this->value = std::pow(this->value, (__val.GET_DOUBLE_ABS())); break;

        default : MATH_EVALUATION_EXCEPTION("^=", this->TYPE(), __val.TYPE());
    }
}

inline double &Double::operator*()
{
    return this->value;
}

inline Double::~Double() noexcept{}

#endif