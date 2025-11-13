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

inline AnyPtr Char::copy() const
{
    return new Char(this->value);
}

inline void Char::print() const
{
    std::printf("%c", this->value);
}

inline void Char::formatPrint() const
{
    std::printf("'%c'", this->value);
}

inline void Char::preMove(){ }

inline void Char::fillObuffer(SronOBuffer& __buffer) const
{
    __buffer << this->value;
}

inline long long int Char::sizeOf() const
{
    return sizeof(this->value);
}
inline std::string Char::toString() const
{
    return (std::string) "" + this->value;
}
inline bool Char::isCollective() const
{
    return false;
}


inline const char *Char::type() const
{
    return "Char";
}
inline void Char::type(std::string &str) const
{
    str.append("Char");
}
inline SronTypeNum Char::typeNum() const
{
    return SronTypeNum::TYPE_CHAR;
}

inline SronChar_t Char::getBaseChar()
{
    return this->value;
}

inline SronInt_t Char::getBaseInt()
{
    return this->value;
}

inline CharPtr Char::getChar() const
{
    return const_cast<CharPtr>(this);
}

inline IntPtr Char::getInt() const
{
    IntPtr ptr = new Int(this->value);

    GarbageCollector::registerMemory(ptr , SronTypeNum::TYPE_INT);

    return ptr;
}

inline StringPtr Char::getString() const
{
    StringPtr ptr = new String(this->value);

    GarbageCollector::registerMemory(ptr , SronTypeNum::TYPE_STRING);

    return ptr;
}

inline CharPtr Char::toLowercase()
{
    return new Char(std::tolower(this->value));
}
inline CharPtr Char::toUppercase()
{
    return new Char(std::toupper(this->value));
}

inline AnyPtr Char::__add__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Char(this->value + **intCast( &__val ));

        case SronTypeNum::TYPE_CHAR: return new Char(this->value + **charCast( &__val ));

        default : mathEvaluationException("+", "Char", __val.type());
    }

    return nullptr;
}

inline AnyPtr Char::__sub__(Any &__val , SronTypeNum __type) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Char(this->value - **intCast( &__val ));

        case SronTypeNum::TYPE_CHAR: return new Char(this->value - **charCast( &__val ));

        default : mathEvaluationException("-", "Char", __val.type());
    }

    return nullptr;
}

inline AnyPtr Char::__mult__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Char(this->value * (**intCast( &__val )));

        case SronTypeNum::TYPE_CHAR: return new Char(this->value * (**charCast( &__val )));

        default : mathEvaluationException("*", "Char", __val.type());
    }

    return nullptr;
}

inline AnyPtr Char::__div__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Char(safeDivide((SronInt_t) this->value, (**intCast( &__val ))));

        case SronTypeNum::TYPE_CHAR: return new Char(safeDivide((SronInt_t) this->value, (SronInt_t) (**charCast( &__val ))));

        default : mathEvaluationException("/", "Char", __val.type());
    }

    return nullptr;
}

inline AnyPtr Char::__mod__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Char(SAFE_MOD((SronInt_t) this->value , (**intCast( &__val ))));

        case SronTypeNum::TYPE_CHAR: return new Char(SAFE_MOD((SronInt_t) this->value , (SronInt_t) (**charCast( &__val ))));

        default : mathEvaluationException("%", "Char", __val.type());
    } 

    return nullptr;
}

inline AnyPtr Char::__pow__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return new Char(std::pow(this->value, **intCast( &__val )));

        case SronTypeNum::TYPE_CHAR: return new Char(std::pow(this->value, **charCast( &__val )));

        default : mathEvaluationException("^", "Char", __val.type());
    }

    return nullptr;
}

inline SronBool_t Char::__isEqual__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value == **intCast( &__val ));

        case SronTypeNum::TYPE_CHAR: return (this->value == **charCast( &__val ));

        default : { }
    }

    return false;
}

inline SronBool_t Char::__notEqual__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value != **intCast( &__val ));

        case SronTypeNum::TYPE_CHAR: return (this->value != **charCast( &__val ));
        
        default : { }
    }

    return true;
}

inline SronBool_t Char::__and__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value && **intCast( &__val ));

        case SronTypeNum::TYPE_CHAR: return (this->value && **charCast( &__val ));

        default : mathEvaluationException("&&", "Char", __val.type());
    }

    return false;
}

inline SronBool_t Char::__or__(Any &__val , SronTypeNum __type ) const
{

    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value || **intCast( &__val ));

        case SronTypeNum::TYPE_CHAR: return (this->value || **charCast( &__val ));

        default : mathEvaluationException("||", "Char", __val.type());
    }

    return false;
}

inline SronBool_t Char::__not__() const
{
    return false;
}

inline SronBool_t Char::__lessThan__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value < **intCast( &__val ));

        case SronTypeNum::TYPE_CHAR: return (this->value < **charCast( &__val ));

        default : { }
    }

    return this->typeNum() < __type;
}

inline SronBool_t Char::__lessEqual__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value <= **intCast( &__val ));

        case SronTypeNum::TYPE_CHAR: return (this->value <= **charCast( &__val ));

        default : { }
    }

    return this->typeNum() <= __type;
}

inline SronBool_t Char::__moreThan__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {
        case SronTypeNum::TYPE_INT: return (this->value > **intCast( &__val ));

        case SronTypeNum::TYPE_CHAR: return (this->value > **charCast( &__val ));

        default : { }
    }

    return this->typeNum() > __type;
}

inline SronBool_t Char::__moreEqual__(Any &__val , SronTypeNum __type ) const
{
    switch ( __type )
    {

        case SronTypeNum::TYPE_INT: return (this->value >= (**intCast( &__val )));

        case SronTypeNum::TYPE_CHAR: return (this->value >= (**charCast( &__val )));

        default : { }
    }

   return this->typeNum() >= __type;
}

inline void Char::__addAssign__(Any& __val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value+=(**intCast( &__val )); break;

        case SronTypeNum::TYPE_CHAR : this->value+=(**charCast( &__val )); break;

        default : mathEvaluationException("+=", this->type() , __val.type()); break;
    }
}

inline void Char::__subAssign__(Any& __val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value -=(**intCast( &__val )); break;

        case SronTypeNum::TYPE_CHAR : this->value -=(**charCast( &__val )); break;

        default : mathEvaluationException("-=", this->type() , __val.type()); break;
    }
}

inline void Char::__multAssign__(Any& __val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value*=(**intCast( &__val )); break;

        case SronTypeNum::TYPE_CHAR : this->value*=(**charCast( &__val )); break;

        default : mathEvaluationException("*=", this->type() , __val.type()); break;
    }
}

inline void Char::__divAssign__(Any& __val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value/=(**intCast( &__val )); break;

        case SronTypeNum::TYPE_CHAR : this->value/=(**charCast( &__val )); break;

        default : mathEvaluationException("/=", this->type() , __val.type()); break;
    }
}

inline void Char::__modAssign__(Any& __val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value %= (**intCast( &__val )); break;

        case SronTypeNum::TYPE_CHAR : this->value %= (**charCast( &__val )); break;

        default : mathEvaluationException("%=", this->type() , __val.type()); break;
    }
}

inline void Char::__powAssign__(Any& __val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value = std::pow( this->value, (**intCast( &__val ))); break;

        case SronTypeNum::TYPE_CHAR : this->value = std::pow( this->value, (**charCast( &__val ))); break;

        default : mathEvaluationException("+=", this->type() , __val.type()); break;
    }
}

inline Char::~Char() noexcept
{ }

#endif