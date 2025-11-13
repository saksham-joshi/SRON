
#pragma once

#ifndef _BOOL_H
#define _BOOL_H

#include "_Char_.hpp"

/*
  |====================== BOOL ===============================|
 'Bool' datatype uses bool to store values.
  > bool take 1 bytes.
  > Syntax in SRON : "Bool x = true" or "Bool x"
*/

inline Bool::Bool() noexcept {}
inline Bool::Bool(SronBool_t __val) noexcept : value(__val) {}

inline SronBool_t Bool::operator*() noexcept
{
    return this->value;
}

inline AnyPtr Bool::copy() const
{
    return new Bool(this->value);
}

inline void Bool::print() const
{
    std::printf("%s", GET_SRON_BOOL_STRING( this->value ));
}

inline void Bool::formatPrint() const
{
    this->print();
}

inline void Bool::preMove(){ }

inline void Bool::fillObuffer(SronOBuffer& __buffer) const
{
    if ( this->value ) __buffer.append( TRUE_STRING_PRINT_FORMAT  , sizeof( TRUE_STRING_PRINT_FORMAT)  - 1);
    
    else               __buffer.append( FALSE_STRING_PRINT_FORMAT , sizeof( FALSE_STRING_PRINT_FORMAT) - 1);
}

inline long long int Bool::sizeOf() const
{
    return sizeof(this->value);
}

inline std::string Bool::toString() const
{
    return GET_SRON_BOOL_STRING( this->value );
}

inline bool Bool::isCollective() const
{
    return false;
}

inline const char *Bool::type() const
{
    return "Bool";
}

inline void Bool::type(std::string &str) const
{
    str.append("Bool");
}
inline SronTypeNum Bool::typeNum() const
{
    return SronTypeNum::TYPE_BOOL;
}


inline SronBool_t Bool::getBaseBool()
{
    return this->value;
}
inline SronInt_t Bool::getBaseInt()
{
    return this->value;
}
inline SronDouble_t Bool::getBaseDouble()
{
    return this->value;
}

inline BoolPtr Bool::getBool() const
{
    return const_cast<BoolPtr>(this);
}

inline SronBool_t Bool::GET() const noexcept
{
    return this->value;
}


inline IntPtr Bool::getInt() const
{
    IntPtr ptr = new Int(this->value);

    GarbageCollector::registerMemory(ptr , SronTypeNum::TYPE_INT);
    return ptr;
}

inline SronBool_t Bool::__isEqual__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_BOOL: return this->value == **boolCast( &__val );

        case SronTypeNum::TYPE_INT: return this->value == **intCast( &__val );

        default : return false;
    }
 
    return false;
}

inline SronBool_t Bool::__notEqual__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {

        case SronTypeNum::TYPE_BOOL: return this->value != **boolCast( &__val );

        case SronTypeNum::TYPE_INT: return this->value != **intCast( &__val );

        default : return true;
    }

    return true;
}

inline SronBool_t Bool::__and__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_BOOL: return this->value && **boolCast( &__val );

        case SronTypeNum::TYPE_INT: return this->value && **intCast( &__val );

        default : mathEvaluationException("&&", "Bool", __val.type());
    }

    return false;
}

inline SronBool_t Bool::__or__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_BOOL: return this->value || **boolCast( &__val );

        case SronTypeNum::TYPE_INT: return this->value || **intCast( &__val );

        default : mathEvaluationException("||", "Bool", __val.type());
    }

    return false;
}

inline SronBool_t Bool::__not__() const
{
    return !this->value;
}

inline SronBool_t Bool::__lessThan__(Any &, SronTypeNum __type) const
{
    return this->typeNum() < __type;
}

inline SronBool_t Bool::__lessEqual__(Any &, SronTypeNum __type) const
{
    return this->typeNum() <= __type;
}

inline SronBool_t Bool::__moreThan__(Any &, SronTypeNum __type) const
{
    return this->typeNum() > __type;
}

inline SronBool_t Bool::__moreEqual__(Any &, SronTypeNum __type) const
{
    return this->typeNum() >= __type;
}

inline Bool::~Bool() noexcept {}

#endif