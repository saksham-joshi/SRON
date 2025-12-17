#pragma once

#ifndef _CHAR_H
#define _CHAR_H

#include "_Int_.hpp"
/*
  |====================== CHAR ===============================|
 'Char' datatype uses char to store values.
  > char take 1 byte.
  > Syntax in SRON : Char x = 'S'
*/

inline Char::Char() {}

inline Char::Char(const char &val) : value(val) {}

inline Char Char::operator=(char &val)
{
    return Char(val);
}

inline char &Char::operator*()
{
    return this->value;
}

inline Char::operator char() const
{
    return this->value;
}

inline AnyPtr Char::COPY() const
{
    return new Char(this->value);
}

inline void Char::PRINT() const
{
    std::cout << this->value;
}

inline void Char::F_PRINT() const
{
    std::cout << '\'' << this->value << '\'';
}

inline void Char::PREMOVE(){ }

inline long long int Char::SIZE_OF() const
{
    return sizeof(this->value);
}
inline std::string Char::TO_STRING() const
{
    return (std::string) "" + this->value;
}
inline bool Char::IS_COLLECTIVE() const
{
    return false;
}


inline const char *Char::TYPE() const
{
    return "Char";
}
inline void Char::TYPE(std::string &str) const
{
    str.append("Char");
}
inline const unsigned short int Char::TYPE_NUMBER() const
{
    return TYPE_CHAR;
}

inline char Char::GET_CHAR_ABS()
{
    return this->value;
}

inline long long int Char::GET_INT_ABS()
{
    return this->value;
}

inline CharPtr Char::GET_CHAR() const
{
    return const_cast<CharPtr>(this);
}

inline IntPtr Char::GET_INT() const
{
    IntPtr ptr = new Int(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr);

    return ptr;
}

inline StringPtr Char::GET_STRING() const
{
    StringPtr ptr = new String(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr);

    return ptr;
}

inline void Char::SET(char &value)
{
    this->value = value;
}

inline CharPtr Char::TO_LOWERCASE()
{
    return new Char(std::tolower(this->value));
}
inline CharPtr Char::TO_UPPERCASE()
{
    return new Char(std::toupper(this->value));
}

inline AnyPtr Char::__ADD__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Char(this->value + val.GET_INT_ABS());

    case TYPE_CHAR:
        return new Char(this->value + val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION("+", "Char", val.TYPE());

    return nullptr;
}

inline AnyPtr Char::__SUB__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Char(this->value - val.GET_INT_ABS());

    case TYPE_CHAR:
        return new Char(this->value - val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION("-", "Char", val.TYPE());

    return nullptr;
}

inline AnyPtr Char::__MULT__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Char(this->value * (val.GET_INT_ABS()));

    case TYPE_CHAR:
        return new Char(this->value * (val.GET_CHAR_ABS()));
    }

    MATH_EVALUATION_EXCEPTION("*", "Char", val.TYPE());

    return nullptr;
}

inline AnyPtr Char::__DIV__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Char(SAFE_DIVIDE((long long int) this->value, (val.GET_INT_ABS())));

    case TYPE_CHAR:
        return new Char(SAFE_DIVIDE((long long int) this->value, (long long int) (val.GET_CHAR_ABS())));
    }

    MATH_EVALUATION_EXCEPTION("/", "Char", val.TYPE());

    return nullptr;
}

inline AnyPtr Char::__MOD__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Char(SAFE_MOD((long long int) this->value , (val.GET_INT_ABS())));

    case TYPE_CHAR:
        return new Char(SAFE_MOD((long long int) this->value , (long long int) (val.GET_CHAR_ABS())));
    }

    MATH_EVALUATION_EXCEPTION("%", "Char", val.TYPE());

    return nullptr;
}

inline AnyPtr Char::__POW__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Char(std::pow(this->value, val.GET_INT_ABS()));

    case TYPE_CHAR:
        return new Char(std::pow(this->value, val.GET_CHAR_ABS()));
    }

    MATH_EVALUATION_EXCEPTION("^", "Char", val.TYPE());

    return nullptr;
}

inline bool Char::__IS_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value == val.GET_INT_ABS());

    case TYPE_CHAR:
        return (this->value == val.GET_CHAR_ABS());
    }

    return false;
}

inline bool Char::__NOT_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value != val.GET_INT_ABS());

    case TYPE_CHAR:
        return (this->value != val.GET_CHAR_ABS());
    }

    return true;
}

inline bool Char::__AND__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value && val.GET_INT_ABS());

    case TYPE_CHAR:
        return (this->value && val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION("&&", "Char", val.TYPE());

    return false;
}

inline bool Char::__OR__(Any &val) const
{

    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value || val.GET_INT_ABS());

    case TYPE_CHAR:
        return (this->value || val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION("||", "Char", val.TYPE());

    return false;
}

inline bool Char::__NOT__() const
{
    return false;
}

inline bool Char::__LESS_THAN__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value < val.GET_INT_ABS());

    case TYPE_CHAR:
        return (this->value < val.GET_CHAR_ABS());
    }

    return this->TYPE_NUMBER() < val.TYPE_NUMBER();
}

inline bool Char::__LESS_THAN_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value <= val.GET_INT_ABS());

    case TYPE_CHAR:
        return (this->value <= val.GET_CHAR_ABS());
    }

    return this->TYPE_NUMBER() <= val.TYPE_NUMBER();
}

inline bool Char::__MORE_THAN__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value > val.GET_INT_ABS());

    case TYPE_CHAR:
        return (this->value > val.GET_CHAR_ABS());
    }

    return this->TYPE_NUMBER() > val.TYPE_NUMBER();
}

inline bool Char::__MORE_THAN_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value >= (val.GET_INT_ABS()));

    case TYPE_CHAR:
        return (this->value >= (val.GET_CHAR_ABS()));
    }

   return this->TYPE_NUMBER() >= val.TYPE_NUMBER();
}

inline void Char::__ADD_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value+=(__val.GET_INT_ABS()); break;

        case TYPE_CHAR : this->value+=(__val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("+=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__MIN_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value -=(__val.GET_INT_ABS()); break;

        case TYPE_CHAR : this->value -=(__val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("-=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__MULT_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value*=(__val.GET_INT_ABS()); break;

        case TYPE_CHAR : this->value*=(__val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("*=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__DIV_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value/=(__val.GET_INT_ABS()); break;

        case TYPE_CHAR : this->value/=(__val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("/=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__MOD_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value %= (__val.GET_INT_ABS()); break;

        case TYPE_CHAR : this->value %= (__val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("%=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__POW_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value = std::pow( this->value, (__val.GET_INT_ABS())); break;

        case TYPE_CHAR : this->value = std::pow( this->value, (__val.GET_CHAR_ABS())); break;

        default : MATH_EVALUATION_EXCEPTION("+=", this->TYPE() , __val.TYPE()); break;
    }
}

inline Char::~Char() noexcept
{ }

#endif