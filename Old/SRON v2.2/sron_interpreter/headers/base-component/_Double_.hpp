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
    Double::PRECISION_PRINT( this->value);
}

inline void Double::F_PRINT() const
{
    this->PRINT();
}

inline void Double::PREMOVE(){ }

inline void Double::FILL_OBUFFER(SronOBuffer& __buffer) const
{
    __buffer << this->value;
}

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

inline SronTypeNum Double::TYPE_NUMBER() const
{
    return SronTypeNum::TYPE_DOUBLE;
}

inline SronInt_t Double::GET_INT_ABS()
{
    return this->value;
}

inline SronDouble_t Double::GET_DOUBLE_ABS()
{
    return this->value;
}

inline SronBool_t Double::GET_BOOL_ABS()
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

    GarbageCollector::REGISTER_MEMORY(ptr , SronTypeNum::TYPE_INT);

    return ptr;
}

inline BoolPtr Double::GET_BOOL() const
{
    return reinterpret_cast<BoolPtr>( this->value  ? Bool::__SronTrue->ptr() : Bool::__SronFalse->ptr());
}


inline AnyPtr Double::__ADD__(Any & __val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Double(this->value + **intCast( &__val ));

        case TYPE_DOUBLE: return new Double(this->value + **doubleCast( &__val ));

        case TYPE_STRING : return new String(std::to_string(this->value).append( **stringCast( &__val) ));

        default : MATH_EVALUATION_EXCEPTION("+", "Double", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Double::__SUB__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Double(this->value - **intCast( &__val));

        case TYPE_DOUBLE: return new Double(this->value - **doubleCast( &__val));

        default : MATH_EVALUATION_EXCEPTION("-", "Double", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Double::__MULT__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Double(this->value * (**intCast( &__val )));

        case TYPE_DOUBLE: return new Double(this->value * (**doubleCast( &__val )));

        default : MATH_EVALUATION_EXCEPTION("*", "Double", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Double::__DIV__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Double(SAFE_DIVIDE(this->value, **intCast( &__val )));

        case TYPE_DOUBLE: return new Double(SAFE_DIVIDE(this->value, **doubleCast( &__val )));

        default : MATH_EVALUATION_EXCEPTION("/", "Double", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Double::__MOD__(Any &__val , SronTypeNum __type) const
{

    switch ( __type )
    {
        case TYPE_INT: return new Double(SAFE_MOD(this->value, **intCast( &__val )));

        case TYPE_DOUBLE: return new Double(SAFE_MOD(this->value, **doubleCast( &__val )));

        default : MATH_EVALUATION_EXCEPTION("%", "Double", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Double::__POW__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Double(std::pow(this->value, **intCast( &__val)));

        case TYPE_DOUBLE: return new Double(std::pow(this->value, **doubleCast( &__val)));

        default : MATH_EVALUATION_EXCEPTION("^", "Double", __val.TYPE());
    }

    return nullptr;
}

inline SronBool_t Double::__IS_EQUAL__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value == **intCast( &__val ));

        case TYPE_DOUBLE: return this->value == **doubleCast( &__val );

        default : { }
    }

    return false;
}

inline SronBool_t Double::__NOT_EQUAL__(Any & __val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return this->value != **intCast( &__val );

        case TYPE_DOUBLE: return this->value != **doubleCast(&__val);

        default : { }
    }

    return true;
}

inline SronBool_t Double::__LESS_THAN__(Any & __val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value < **intCast( &__val ));

        case TYPE_DOUBLE: return (this->value < **doubleCast( &__val ));

        default : { }
    }

    return this->TYPE_NUMBER() < __type;
}

inline SronBool_t Double::__LESS_THAN_EQUAL__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value <= **intCast( &__val ));

        case TYPE_DOUBLE: return (this->value <= **intCast( &__val ));

        default : { }
    }

    return this->TYPE_NUMBER() <= __type;
}

inline SronBool_t Double::__MORE_THAN__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value > **intCast( &__val));

        case TYPE_DOUBLE: return (this->value > **doubleCast( &__val ));

        default : { }
    }

    return this->TYPE_NUMBER() > __type;
}

inline SronBool_t Double::__MORE_THAN_EQUAL__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value >= **intCast( &__val));

        case TYPE_DOUBLE: return (this->value >= **doubleCast( &__val ));

        default : { }
    }

    return this->TYPE_NUMBER() >= __type;
}

inline AnyPtr Double::__NEGATE__() const
{
    return new Double(-this->value);
}

inline SronBool_t Double::__NOT__() const
{
    return !this->value;
}

inline void Double::__ADD_AND_ASSIGN__(Any& __val , SronTypeNum __type)
{
    switch(__type)
    {
        case TYPE_INT : this->value += (**intCast( &__val)); break;

        case TYPE_DOUBLE : this->value += (**doubleCast( &__val)); break;

        default : MATH_EVALUATION_EXCEPTION("+=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__MIN_AND_ASSIGN__(Any& __val, SronTypeNum __type)
{
    switch(__type)
    {
        case TYPE_INT : this->value -= (**intCast( &__val)); break;

        case TYPE_DOUBLE : this->value -= (**doubleCast( &__val)); break;

        default : MATH_EVALUATION_EXCEPTION("-=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__MULT_AND_ASSIGN__(Any& __val, SronTypeNum __type)
{
    switch(__type)
    {
        case TYPE_INT : this->value *= (**intCast( &__val)); break;

        case TYPE_DOUBLE : this->value *= (**doubleCast( &__val)); break;

        default : MATH_EVALUATION_EXCEPTION("*=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__DIV_AND_ASSIGN__(Any& __val , SronTypeNum __type)
{
    switch(__type)
    {
        case TYPE_INT : this->value /= (**intCast( &__val)); break;

        case TYPE_DOUBLE : this->value /= (**doubleCast( &__val)); break;

        default : MATH_EVALUATION_EXCEPTION("/=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__MOD_AND_ASSIGN__(Any& __val , SronTypeNum __type){

    switch(__type)
    {
        case TYPE_INT : this->value = std::fmod( this->value, (**intCast( &__val)) ); break;

        case TYPE_DOUBLE : this->value = std::fmod(this->value, (**doubleCast( &__val)) ); break;

        default : MATH_EVALUATION_EXCEPTION("/=", this->TYPE(), __val.TYPE());
    }
}

inline void Double::__POW_AND_ASSIGN__(Any& __val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value = std::pow( this->value, (**intCast( &__val)) ); break;

        case TYPE_DOUBLE : this->value = std::pow( this->value, (**doubleCast( &__val)) ); break;

        default : MATH_EVALUATION_EXCEPTION("^=", this->TYPE(), __val.TYPE());
    }
}

inline SronDouble_t &Double::operator*()
{
    return this->value;
}

inline Double::~Double() noexcept{}

#endif