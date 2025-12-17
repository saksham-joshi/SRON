#pragma once

#ifndef _INT_H
#define _INT_H

#include "_Double_.hpp"

/*
  |====================== INT ===============================|
 'Int' datatype implements integer type with long long modifier.
 > SronInt_t takes 8 bytes.
 > Syntax in SRON : "Int x = 10" or "Int x"
*/

inline Int::Int(const SronInt_t __value) noexcept : value(__value) {}

inline Int::Int(const std::string &val) : value(Converter::TO_INT(val)) {}

inline Int Int::operator=(SronInt_t &val)
{
    return Int(val);
}

inline SronInt_t &Int::operator*()
{
    return this->value;
}

inline Int::operator SronInt_t() const
{
    return this->value;
}

inline AnyPtr Int::COPY() const
{
    return new Int(this->value);
}

inline void Int::PRINT() const
{
    printf_s("%lld", this->value);
}

inline void Int::F_PRINT() const
{
    this->PRINT();
}

inline void Int::PREMOVE(){ }

inline void Int::FILL_OBUFFER(SronOBuffer& __buffer) const
{
    __buffer << this->value;
}

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

inline SronTypeNum Int::TYPE_NUMBER() const
{
    return SronTypeNum::TYPE_INT;
}

inline std::string Int::TO_STRING() const
{
    return std::to_string(this->value);
}

inline bool Int::IS_COLLECTIVE() const
{
    return false;
}


inline SronInt_t Int::GET_INT_ABS()
{
    return this->value;
}

inline SronDouble_t Int::GET_DOUBLE_ABS(){
    return this->value;
}

inline SronChar_t Int::GET_CHAR_ABS()
{
    return this->value;
}

inline SronBool_t Int::GET_BOOL_ABS()
{
    return this->value;
}

inline IntPtr Int::GET_INT() const
{
    return const_cast<IntPtr>(this);
}

inline DoublePtr Int::GET_DOUBLE() const
{
    DoublePtr ptr = new Double(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr , SronTypeNum::TYPE_DOUBLE);

    return ptr;
}

inline CharPtr Int::GET_CHAR() const
{
    CharPtr ptr = new Char(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr , SronTypeNum::TYPE_CHAR);

    return ptr;
}

inline BoolPtr Int::GET_BOOL() const
{
    return reinterpret_cast<BoolPtr>( this->value  ? Bool::__SronTrue->ptr() : Bool::__SronFalse->ptr());
}

inline AnyPtr Int::__ADD__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT:
            return new Int(this->value + **intCast( &__val ));

        case TYPE_DOUBLE:
            return new Double(this->value + **doubleCast( &__val));

        case TYPE_CHAR:
            return new Int(this->value + **charCast( &__val ));

        case TYPE_STRING:
            return new String(this->TO_STRING().append(**stringCast( &__val)));

        default : MATH_EVALUATION_EXCEPTION("+", "Int", __val.TYPE());
    } 

    return nullptr;
}

inline AnyPtr Int::__SUB__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT:
            return new Int(this->value - **intCast( &__val ));

        case TYPE_DOUBLE:
            return new Double(this->value - **doubleCast( &__val));

        case TYPE_CHAR:
            return new Int(this->value - **charCast( &__val ));

        default : MATH_EVALUATION_EXCEPTION("-", "Int", __val.TYPE());
    }

    

    return nullptr;
}

inline AnyPtr Int::__MULT__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT:
            return new Int(this->value * (**intCast( &__val )));

        case TYPE_DOUBLE:
            return new Double(this->value * (**doubleCast( &__val)));

        case TYPE_CHAR:
            return new Int(this->value * (**charCast( &__val )));

        default : MATH_EVALUATION_EXCEPTION("*", "Int", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Int::__DIV__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT:
            return new Int(SAFE_DIVIDE(this->value, **intCast( &__val )));

        case TYPE_DOUBLE:
            return new Double(SAFE_DIVIDE(this->value, **doubleCast( &__val)));

        case TYPE_CHAR:
            return new Int(SAFE_DIVIDE(this->value,(SronInt_t)**charCast( &__val )));

        default : MATH_EVALUATION_EXCEPTION("/", "Int", __val.TYPE());
    }

    

    return nullptr;
}

inline AnyPtr Int::__MOD__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT:
            return new Int(SAFE_MOD(this->value , **intCast( &__val )));

        case TYPE_DOUBLE:
            return new Double(SAFE_MOD(this->value, **doubleCast( &__val)));

        case TYPE_CHAR:
            return new Int(SAFE_MOD(this->value,(SronInt_t) **charCast( &__val )));

        default : MATH_EVALUATION_EXCEPTION("%", "Int", __val.TYPE());
    }

    

    return nullptr;
}

inline AnyPtr Int::__POW__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT:
            return new Int(std::pow((SronDouble_t)this->value, (SronDouble_t)**intCast( &__val )));

        case TYPE_DOUBLE:
            return new Double(std::pow((SronDouble_t)this->value, **doubleCast( &__val)));

        case TYPE_CHAR:
            return new Int(std::pow((SronDouble_t)this->value, (SronDouble_t)**charCast( &__val )));

        default : MATH_EVALUATION_EXCEPTION("^", "Int", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Int::__XOR__(Any &__val , SronTypeNum __type) const
{
    switch(__type){

        case TYPE_INT : return new Int( this->value ^ **intCast( &__val) );

        case TYPE_DOUBLE : return new Int( this->value ^ (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return new Int(this->value ^ (SronInt_t)**charCast( &__val ) );

        default : MATH_EVALUATION_EXCEPTION("xor", this->TYPE(), __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Int::__BITWISE_AND__(Any &__val , SronTypeNum __type) const
{
    switch(__type){

        case TYPE_INT : return new Int( this->value & **intCast( &__val ));

        case TYPE_DOUBLE : return new Int( this->value & (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return new Int(this->value & **charCast( &__val ));

        default : MATH_EVALUATION_EXCEPTION("bitwise-and", this->TYPE(), __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Int::__BITWISE_OR__(Any &__val , SronTypeNum __type) const 
{
    switch(__type){

        case TYPE_INT : return new Int( this->value | **intCast( &__val) );

        case TYPE_DOUBLE : return new Int( this->value | (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return new Int(this->value | (SronInt_t)**charCast( &__val ) );

        default : MATH_EVALUATION_EXCEPTION("bitwise-or", this->TYPE(), __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Int::__BITWISE_NOT__() const
{
    return new Int(~(this->value));
}

inline AnyPtr Int::__LEFT_SHIFT__(Any &__val , SronTypeNum __type) const
{

    switch(__type){

        case TYPE_INT : return new Int( this->value << **intCast( &__val) );

        case TYPE_DOUBLE : return new Int( this->value << (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return new Int(this->value << (SronInt_t)**charCast( &__val ) );

        default : MATH_EVALUATION_EXCEPTION("lsft", this->TYPE(), __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Int::__RIGHT_SHIFT__(Any &__val , SronTypeNum __type) const
{
    switch(__type)
    {
        case TYPE_INT : return new Int( this->value >> **intCast( &__val) );

        case TYPE_DOUBLE : return new Int( this->value >> (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return new Int(this->value >> (SronInt_t)**charCast( &__val ) );

        default : MATH_EVALUATION_EXCEPTION("rsft", this->TYPE(), __val.TYPE());
    }
    
    return nullptr;
}

inline SronBool_t Int::__IS_EQUAL__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT : return this->value == **intCast( &__val);

        case TYPE_DOUBLE : return ( this->value == (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return (this->value == (SronInt_t)**charCast( &__val ) );

        default : { }
    }

    return false;
}

inline SronBool_t Int::__NOT_EQUAL__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT : return this->value != **intCast( &__val);

        case TYPE_DOUBLE : return ( this->value != (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return (this->value != (SronInt_t)**charCast( &__val ) );

        default : { }
    }

    return true;
}

inline SronBool_t Int::__AND__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT : return this->value && **intCast( &__val);

        case TYPE_BOOL : return ( this->value && (SronInt_t)**boolCast( &__val ));

        case TYPE_CHAR : return (this->value && (SronInt_t)**charCast( &__val ) );

        default : MATH_EVALUATION_EXCEPTION("&&", "Int", __val.TYPE());
    }

    return false;
}

inline SronBool_t Int::__OR__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT : return this->value || **intCast( &__val);

        case TYPE_BOOL : return ( this->value || (SronInt_t)**boolCast( &__val ));

        case TYPE_CHAR : return (this->value || (SronInt_t)**charCast( &__val ) );

        default : MATH_EVALUATION_EXCEPTION("||", "Int", __val.TYPE());
    }

    return false;
}

inline SronBool_t Int::__NOT__() const
{
    return (!(this->value > 0));
}

inline SronBool_t Int::__LESS_THAN__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT : return this->value < **intCast( &__val) ;

        case TYPE_DOUBLE : return ( this->value < (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return (this->value < (SronInt_t)**charCast( &__val ) );

        default : MATH_EVALUATION_EXCEPTION("<", "Int", __val.TYPE());
    }

    return false;
}

inline SronBool_t Int::__LESS_THAN_EQUAL__(Any &__val , SronTypeNum __type) const
{

    switch (__type)
    {
        case TYPE_INT : return this->value <= **intCast( &__val) ;

        case TYPE_DOUBLE : return ( this->value <= (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return (this->value <= (SronInt_t)**charCast( &__val ));

        default : MATH_EVALUATION_EXCEPTION("<=", "Int", __val.TYPE());
    }

    return false;
}

inline SronBool_t Int::__MORE_THAN__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT : return this->value > **intCast( &__val);

        case TYPE_DOUBLE : return ( this->value > (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return (this->value > (SronInt_t)**charCast( &__val ) );

        default : MATH_EVALUATION_EXCEPTION(">", "Int", __val.TYPE());
    }

    return false;
}

inline SronBool_t Int::__MORE_THAN_EQUAL__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_INT : return this->value >= **intCast( &__val);

        case TYPE_DOUBLE : return ( this->value >= (SronInt_t)**doubleCast( &__val ));

        case TYPE_CHAR : return (this->value >= (SronInt_t)**charCast( &__val ) );

        default : MATH_EVALUATION_EXCEPTION(">=", "Int", __val.TYPE());
    }

    return false;
}

inline AnyPtr Int::__NEGATE__() const
{
    return new Int(-this->value);
}

inline void Int::__ADD_AND_ASSIGN__(Any &__val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value+= (**intCast( &__val )); break;

        case TYPE_DOUBLE : this->value+= (**doubleCast( &__val)); break;

        case TYPE_CHAR : this->value+= ((SronInt_t)**charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("+=", this->TYPE(), __val.TYPE());
    }
}

inline void Int::__MIN_AND_ASSIGN__(Any &__val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value-= (**intCast( &__val )); break;

        case TYPE_DOUBLE : this->value-= (**doubleCast( &__val)); break;

        case TYPE_CHAR : this->value-= ((SronInt_t) **charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("-=", this->TYPE() , __val.TYPE());
    }
}

inline void Int::__MULT_AND_ASSIGN__(Any &__val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value*= (**intCast( &__val )); break;

        case TYPE_DOUBLE : this->value*= (**doubleCast( &__val)); break;

        case TYPE_CHAR : this->value*= ((SronInt_t) **charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("*=", this->TYPE() , __val.TYPE());
    }
}

inline void Int::__DIV_AND_ASSIGN__(Any &__val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value/= (**intCast( &__val )); break;

        case TYPE_DOUBLE : this->value/= (**doubleCast( &__val)); break;

        case TYPE_CHAR : this->value/= ((SronInt_t) **charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("/=", this->TYPE() , __val.TYPE());
    }
}

inline void Int::__MOD_AND_ASSIGN__(Any &__val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value %= (**intCast( &__val )); break;

        case TYPE_DOUBLE : this->value%= ((SronInt_t)**doubleCast( &__val)); break;

        case TYPE_CHAR : this->value%= ((SronInt_t) **charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("%=", this->TYPE() , __val.TYPE());
    }
}

inline void Int::__POW_AND_ASSIGN__(Any &__val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value = std::pow(this->value, (**intCast( &__val ))); break;

        case TYPE_DOUBLE : this->value= std::pow(this->value, (**doubleCast( &__val))); break;

        case TYPE_CHAR : this->value = std::pow(this->value, ((SronInt_t) **charCast( &__val ))); break;

        default : MATH_EVALUATION_EXCEPTION("^=", this->TYPE() , __val.TYPE());
    }
}

inline Int::~Int() noexcept{}

#endif