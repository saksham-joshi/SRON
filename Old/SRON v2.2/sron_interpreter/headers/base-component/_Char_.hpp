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

inline Char::Char(const SronChar_t __value) noexcept : value(__value) {}

inline Char Char::operator=(SronChar_t &val)
{
    return Char(val);
}

inline SronChar_t &Char::operator*() noexcept
{
    return this->value;
}

inline Char::operator SronChar_t() const
{
    return this->value;
}

inline AnyPtr Char::COPY() const
{
    return new Char(this->value);
}

inline void Char::PRINT() const
{
    printf_s("%c", this->value);
}

inline void Char::F_PRINT() const
{
    printf_s("'%c'", this->value);
}

inline void Char::PREMOVE(){ }

inline void Char::FILL_OBUFFER(SronOBuffer& __buffer) const
{
    __buffer << this->value;
}

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
inline SronTypeNum Char::TYPE_NUMBER() const
{
    return SronTypeNum::TYPE_CHAR;
}

inline SronChar_t Char::GET_CHAR_ABS()
{
    return this->value;
}

inline SronInt_t Char::GET_INT_ABS()
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

    GarbageCollector::REGISTER_MEMORY(ptr , SronTypeNum::TYPE_INT);

    return ptr;
}

inline StringPtr Char::GET_STRING() const
{
    StringPtr ptr = new String(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr , SronTypeNum::TYPE_STRING);

    return ptr;
}

inline CharPtr Char::TO_LOWERCASE()
{
    return new Char(std::tolower(this->value));
}
inline CharPtr Char::TO_UPPERCASE()
{
    return new Char(std::toupper(this->value));
}

inline AnyPtr Char::__ADD__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Char(this->value + **intCast( &__val ));

        case TYPE_CHAR: return new Char(this->value + **charCast( &__val ));

        default : MATH_EVALUATION_EXCEPTION("+", "Char", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Char::__SUB__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Char(this->value - **intCast( &__val ));

        case TYPE_CHAR: return new Char(this->value - **charCast( &__val ));

        default : MATH_EVALUATION_EXCEPTION("-", "Char", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Char::__MULT__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Char(this->value * (**intCast( &__val )));

        case TYPE_CHAR: return new Char(this->value * (**charCast( &__val )));

        default : MATH_EVALUATION_EXCEPTION("*", "Char", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Char::__DIV__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Char(SAFE_DIVIDE((SronInt_t) this->value, (**intCast( &__val ))));

        case TYPE_CHAR: return new Char(SAFE_DIVIDE((SronInt_t) this->value, (SronInt_t) (**charCast( &__val ))));

        default : MATH_EVALUATION_EXCEPTION("/", "Char", __val.TYPE());
    }

    return nullptr;
}

inline AnyPtr Char::__MOD__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Char(SAFE_MOD((SronInt_t) this->value , (**intCast( &__val ))));

        case TYPE_CHAR: return new Char(SAFE_MOD((SronInt_t) this->value , (SronInt_t) (**charCast( &__val ))));

        default : MATH_EVALUATION_EXCEPTION("%", "Char", __val.TYPE());
    } 

    return nullptr;
}

inline AnyPtr Char::__POW__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return new Char(std::pow(this->value, **intCast( &__val )));

        case TYPE_CHAR: return new Char(std::pow(this->value, **charCast( &__val )));

        default : MATH_EVALUATION_EXCEPTION("^", "Char", __val.TYPE());
    }

    return nullptr;
}

inline SronBool_t Char::__IS_EQUAL__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value == **intCast( &__val ));

        case TYPE_CHAR: return (this->value == **charCast( &__val ));

        default : { }
    }

    return false;
}

inline SronBool_t Char::__NOT_EQUAL__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value != **intCast( &__val ));

        case TYPE_CHAR: return (this->value != **charCast( &__val ));
        
        default : { }
    }

    return true;
}

inline SronBool_t Char::__AND__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value && **intCast( &__val ));

        case TYPE_CHAR: return (this->value && **charCast( &__val ));

        default : MATH_EVALUATION_EXCEPTION("&&", "Char", __val.TYPE());
    }

    return false;
}

inline SronBool_t Char::__OR__(Any &__val , SronTypeNum __type ) const
{

    switch ( __type )
    {
        case TYPE_INT: return (this->value || **intCast( &__val ));

        case TYPE_CHAR: return (this->value || **charCast( &__val ));

        default : MATH_EVALUATION_EXCEPTION("||", "Char", __val.TYPE());
    }

    return false;
}

inline SronBool_t Char::__NOT__() const
{
    return false;
}

inline SronBool_t Char::__LESS_THAN__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value < **intCast( &__val ));

        case TYPE_CHAR: return (this->value < **charCast( &__val ));

        default : { }
    }

    return this->TYPE_NUMBER() < __type;
}

inline SronBool_t Char::__LESS_THAN_EQUAL__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value <= **intCast( &__val ));

        case TYPE_CHAR: return (this->value <= **charCast( &__val ));

        default : { }
    }

    return this->TYPE_NUMBER() <= __type;
}

inline SronBool_t Char::__MORE_THAN__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case TYPE_INT: return (this->value > **intCast( &__val ));

        case TYPE_CHAR: return (this->value > **charCast( &__val ));

        default : { }
    }

    return this->TYPE_NUMBER() > __type;
}

inline SronBool_t Char::__MORE_THAN_EQUAL__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {

        case TYPE_INT: return (this->value >= (**intCast( &__val )));

        case TYPE_CHAR: return (this->value >= (**charCast( &__val )));

        default : { }
    }

   return this->TYPE_NUMBER() >= __type;
}

inline void Char::__ADD_AND_ASSIGN__(Any& __val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value+=(**intCast( &__val )); break;

        case TYPE_CHAR : this->value+=(**charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("+=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__MIN_AND_ASSIGN__(Any& __val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value -=(**intCast( &__val )); break;

        case TYPE_CHAR : this->value -=(**charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("-=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__MULT_AND_ASSIGN__(Any& __val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value*=(**intCast( &__val )); break;

        case TYPE_CHAR : this->value*=(**charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("*=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__DIV_AND_ASSIGN__(Any& __val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value/=(**intCast( &__val )); break;

        case TYPE_CHAR : this->value/=(**charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("/=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__MOD_AND_ASSIGN__(Any& __val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value %= (**intCast( &__val )); break;

        case TYPE_CHAR : this->value %= (**charCast( &__val )); break;

        default : MATH_EVALUATION_EXCEPTION("%=", this->TYPE() , __val.TYPE()); break;
    }
}

inline void Char::__POW_AND_ASSIGN__(Any& __val , SronTypeNum __type){

    switch(__type){

        case TYPE_INT : this->value = std::pow( this->value, (**intCast( &__val ))); break;

        case TYPE_CHAR : this->value = std::pow( this->value, (**charCast( &__val ))); break;

        default : MATH_EVALUATION_EXCEPTION("+=", this->TYPE() , __val.TYPE()); break;
    }
}

inline Char::~Char() noexcept
{ }

#endif