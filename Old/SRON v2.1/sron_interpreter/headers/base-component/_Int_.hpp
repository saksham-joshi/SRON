#pragma once

#ifndef _INT_H
#define _INT_H

#include "_Double_.hpp"

/*
  |====================== INT ===============================|
 'Int' datatype implements integer type with long long modifier.
 > long long int takes 8 bytes.
 > Syntax in SRON : "Int x = 10" or "Int x"
*/

inline Int::Int() {}
inline Int::Int(const long long int val) : value(val) {}
inline Int::Int(const std::string &val) : value(Converter::TO_INT(val)) {}

inline Int Int::operator=(long long int &val)
{
    return Int(val);
}

inline long long int &Int::operator*()
{
    return this->value;
}

inline Int::operator long long int() const
{
    return this->value;
}

inline AnyPtr Int::COPY() const
{
    return new Int(this->value);
}

inline void Int::PRINT() const
{
    std::cout << this->value;
}

inline void Int::F_PRINT() const
{
    this->PRINT();
}

inline void Int::PREMOVE(){ }

inline long long int Int::SIZE_OF() const
{
    return sizeof(this->value);
}

inline const char *Int::TYPE() const
{
    return "Int";
}

inline void Int::TYPE(std::string &str) const
{
    str.append("Int");
}

inline const unsigned short int Int::TYPE_NUMBER() const
{
    return TYPE_INT;
}

inline std::string Int::TO_STRING() const
{
    return std::to_string(this->value);
}

inline bool Int::IS_COLLECTIVE() const
{
    return false;
}


inline long long int Int::GET_INT_ABS()
{
    return this->value;
}

inline double Int::GET_DOUBLE_ABS(){
    return this->value;
}

inline char Int::GET_CHAR_ABS(){
    return this->value;
}

inline bool Int::GET_BOOL_ABS(){
    return this->value;
}

inline IntPtr Int::GET_INT() const
{
    return const_cast<IntPtr>(this);
}

inline DoublePtr Int::GET_DOUBLE() const
{
    DoublePtr ptr = new Double(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr);

    return ptr;
}

inline CharPtr Int::GET_CHAR() const
{
    CharPtr ptr = new Char(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr);

    return ptr;
}

inline BoolPtr Int::GET_BOOL() const
{
    return (this->value > 0 ) ? Bool::__SronTrue->ptr_->GET_BOOL() : Bool::__SronFalse->ptr_->GET_BOOL();
}

// inline void Int::SET(long long int &value)
// {
//     this->value = value;
// }

inline AnyPtr Int::__ADD__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Int(this->value + val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return new Double(this->value + val.GET_DOUBLE_ABS());

    case TYPE_CHAR:
        return new Int(this->value + val.GET_CHAR_ABS());

    case TYPE_STRING:
        return new String(this->TO_STRING().append(**val.GET_STRING()));
    }

    MATH_EVALUATION_EXCEPTION("+", "Int", val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__SUB__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Int(this->value - val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return new Double(this->value - val.GET_DOUBLE_ABS());

    case TYPE_CHAR:
        return new Int(this->value - val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION("-", "Int", val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__MULT__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Int(this->value * (val.GET_INT_ABS()));

    case TYPE_DOUBLE:
        return new Double(this->value * (val.GET_DOUBLE_ABS()));

    case TYPE_CHAR:
        return new Int(this->value * (val.GET_CHAR_ABS()));
    }

    MATH_EVALUATION_EXCEPTION("*", "Int", val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__DIV__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Int(SAFE_DIVIDE(this->value, val.GET_INT_ABS()));

    case TYPE_DOUBLE:
        return new Double(SAFE_DIVIDE(this->value, val.GET_DOUBLE_ABS()));

    case TYPE_CHAR:
        return new Int(SAFE_DIVIDE(this->value,(long long int)val.GET_CHAR_ABS()));
    }

    MATH_EVALUATION_EXCEPTION("/", "Int", val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__MOD__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Int(SAFE_MOD(this->value , val.GET_INT_ABS()));

    case TYPE_DOUBLE:
        return new Double(SAFE_MOD(this->value, val.GET_DOUBLE_ABS()));

    case TYPE_CHAR:
        return new Int(SAFE_MOD(this->value,(long long int) val.GET_CHAR_ABS()));
    }

    MATH_EVALUATION_EXCEPTION("%", "Int", val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__POW__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return new Int(std::pow((double)this->value, (double)val.GET_INT_ABS()));

    case TYPE_DOUBLE:
        return new Double(std::pow((double)this->value, val.GET_DOUBLE_ABS()));

    case TYPE_CHAR:
        return new Int(std::pow((double)this->value, (double)(int)val.GET_CHAR_ABS()));
    }

    MATH_EVALUATION_EXCEPTION("^", "Int", val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__XOR__(Any &__val) const
{
    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : 

        case TYPE_DOUBLE :

        case TYPE_CHAR : return new Int(this->value ^ __val.GET_INT_ABS());
    }
    
    MATH_EVALUATION_EXCEPTION("xor", this->TYPE(), __val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__BITWISE_AND__(Any &__val) const
{
    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : 

        case TYPE_DOUBLE :

        case TYPE_CHAR : return new Int(this->value & __val.GET_INT_ABS());
    }
    
    MATH_EVALUATION_EXCEPTION("bitwise-and", this->TYPE(), __val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__BITWISE_OR__(Any &__val) const 
{
    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : 

        case TYPE_DOUBLE :

        case TYPE_CHAR : return new Int(this->value | __val.GET_INT_ABS());
    }
    
    MATH_EVALUATION_EXCEPTION("bitwise-or", this->TYPE(), __val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__BITWISE_NOT__() const
{
    return new Int(~(this->value));
}

inline AnyPtr Int::__LEFT_SHIFT__(Any &__val) const
{
    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : 

        case TYPE_DOUBLE :

        case TYPE_CHAR : return new Int(this->value << __val.GET_INT_ABS());
    }
    
    MATH_EVALUATION_EXCEPTION("lsft", this->TYPE(), __val.TYPE());

    return nullptr;
}

inline AnyPtr Int::__RIGHT_SHIFT__(Any &__val) const
{
    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : 

        case TYPE_DOUBLE :

        case TYPE_CHAR : return new Int(this->value >> __val.GET_INT_ABS());
    }
    
    MATH_EVALUATION_EXCEPTION("rsft", this->TYPE(), __val.TYPE());

    return nullptr;
}

inline bool Int::__IS_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value == val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value == val.GET_DOUBLE_ABS());

    case TYPE_CHAR:
        return (this->value == val.GET_CHAR_ABS());
    }

    return (false);
}

inline bool Int::__NOT_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value != val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value != val.GET_DOUBLE_ABS());

    case TYPE_CHAR:
        return (this->value != val.GET_CHAR_ABS());
    }

    return (true);
}

inline bool Int::__AND__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value && val.GET_INT_ABS());

    case TYPE_BOOL:
        return (this->value && **val.GET_BOOL());

    case TYPE_CHAR:
        return (this->value && (int)val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION("&&", "Int", val.TYPE());

    return false;
}

inline bool Int::__OR__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value || val.GET_INT_ABS());

    case TYPE_BOOL:
        return (this->value || **val.GET_BOOL());

    case TYPE_CHAR:
        return (this->value || (int)val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION("||", "Int", val.TYPE());

    return false;
}

inline bool Int::__NOT__() const
{
    return (!(this->value > 0));
}

inline bool Int::__LESS_THAN__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value < val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value < val.GET_DOUBLE_ABS());
    case TYPE_CHAR:
        return (this->value < (int)val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION("<", "Int", val.TYPE());

    return false;
}

inline bool Int::__LESS_THAN_EQUAL__(Any &val) const
{

    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value <= val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value <= val.GET_DOUBLE_ABS());

    case TYPE_CHAR:
        return (this->value <= (int)val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION("<=", "Int", val.TYPE());

    return false;
}

inline bool Int::__MORE_THAN__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value > val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value > val.GET_DOUBLE_ABS());
    case TYPE_CHAR:
        return (this->value > (int)val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION(">", "Int", val.TYPE());

    return false;
}

inline bool Int::__MORE_THAN_EQUAL__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

    case TYPE_INT:
        return (this->value >= val.GET_INT_ABS());

    case TYPE_DOUBLE:
        return (this->value >= val.GET_DOUBLE_ABS());
    case TYPE_CHAR:
        return (this->value >= (int)val.GET_CHAR_ABS());
    }

    MATH_EVALUATION_EXCEPTION(">=", "Int", val.TYPE());

    return false;
}

inline AnyPtr Int::__NEGATE__() const
{
    return new Int(-this->value);
}

inline void Int::__ADD_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value+= (__val.GET_INT_ABS()); break;

        case TYPE_DOUBLE : this->value+= (__val.GET_DOUBLE_ABS()); break;

        case TYPE_CHAR : this->value+= ((int)__val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("+=", this->TYPE(), __val.TYPE());
    }
}

inline void Int::__MIN_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value-= (__val.GET_INT_ABS()); break;

        case TYPE_DOUBLE : this->value-= (__val.GET_DOUBLE_ABS()); break;

        case TYPE_CHAR : this->value-= ((int) __val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("-=", this->TYPE() , __val.TYPE());
    }
}

inline void Int::__MULT_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value*= (__val.GET_INT_ABS()); break;

        case TYPE_DOUBLE : this->value*= (__val.GET_DOUBLE_ABS()); break;

        case TYPE_CHAR : this->value*= ((int) __val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("*=", this->TYPE() , __val.TYPE());
    }
}

inline void Int::__DIV_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value/= (__val.GET_INT_ABS()); break;

        case TYPE_DOUBLE : this->value/= (__val.GET_DOUBLE_ABS()); break;

        case TYPE_CHAR : this->value/= ((int) __val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("/=", this->TYPE() , __val.TYPE());
    }
}

inline void Int::__MOD_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value %= (__val.GET_INT_ABS()); break;

        case TYPE_DOUBLE : this->value%= ((int)__val.GET_DOUBLE_ABS()); break;

        case TYPE_CHAR : this->value%= ((int) __val.GET_CHAR_ABS()); break;

        default : MATH_EVALUATION_EXCEPTION("%=", this->TYPE() , __val.TYPE());
    }
}

inline void Int::__POW_AND_ASSIGN__(Any& __val){

    switch(__val.TYPE_NUMBER()){

        case TYPE_INT : this->value = std::pow(this->value, (__val.GET_INT_ABS())); break;

        case TYPE_DOUBLE : this->value= std::pow(this->value, (__val.GET_DOUBLE_ABS())); break;

        case TYPE_CHAR : this->value = std::pow(this->value, ((int) __val.GET_CHAR_ABS())); break;

        default : MATH_EVALUATION_EXCEPTION("^=", this->TYPE() , __val.TYPE());
    }
}

inline Int::~Int() noexcept{}

#endif