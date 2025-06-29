
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

inline AnyPtr Bool::COPY() const
{
    return new Bool(this->value);
}

inline void Bool::PRINT() const
{
    printf_s("%s", GET_SRON_BOOL_STRING( this->value ));
}

inline void Bool::F_PRINT() const
{
    this->PRINT();
}

inline void Bool::PREMOVE(){ }

inline void Bool::FILL_OBUFFER(SronOBuffer& __buffer) const
{
    if ( this->value ) __buffer.append( TRUE_STRING_PRINT_FORMAT  , sizeof( TRUE_STRING_PRINT_FORMAT)  - 1);
    
    else               __buffer.append( FALSE_STRING_PRINT_FORMAT , sizeof( FALSE_STRING_PRINT_FORMAT) - 1);
}

inline long long int Bool::SIZE_OF() const
{
    return sizeof(this->value);
}

inline std::string Bool::TO_STRING() const
{
    return GET_SRON_BOOL_STRING( this->value );
}

inline bool Bool::IS_COLLECTIVE() const
{
    return false;
}

inline const char *Bool::TYPE() const
{
    return "Bool";
}

inline void Bool::TYPE(std::string &str) const
{
    str.append("Bool");
}
inline SronTypeNum Bool::TYPE_NUMBER() const
{
    return SronTypeNum::TYPE_BOOL;
}


inline SronBool_t Bool::GET_BOOL_ABS()
{
    return this->value;
}
inline SronInt_t Bool::GET_INT_ABS()
{
    return this->value;
}
inline SronDouble_t Bool::GET_DOUBLE_ABS()
{
    return this->value;
}

inline BoolPtr Bool::GET_BOOL() const
{
    return const_cast<BoolPtr>(this);
}

inline SronBool_t Bool::GET() const noexcept
{
    return this->value;
}


inline IntPtr Bool::GET_INT() const
{
    IntPtr ptr = new Int(this->value);

    GarbageCollector::REGISTER_MEMORY(ptr , SronTypeNum::TYPE_INT);
    return ptr;
}

inline SronBool_t Bool::__IS_EQUAL__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_BOOL: return this->value == **boolCast( &__val );

        case TYPE_INT: return this->value == **intCast( &__val );

        default : return false;
    }
 
    return false;
}

inline SronBool_t Bool::__NOT_EQUAL__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {

        case TYPE_BOOL: return this->value != **boolCast( &__val );

        case TYPE_INT: return this->value != **intCast( &__val );

        default : return true;
    }

    return true;
}

inline SronBool_t Bool::__AND__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_BOOL: return this->value && **boolCast( &__val );

        case TYPE_INT: return this->value && **intCast( &__val );

        default : MATH_EVALUATION_EXCEPTION("&&", "Bool", __val.TYPE());
    }

    return false;
}

inline SronBool_t Bool::__OR__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_BOOL: return this->value || **boolCast( &__val );

        case SronTypeNum::TYPE_INT: return this->value || **intCast( &__val );

        default : MATH_EVALUATION_EXCEPTION("||", "Bool", __val.TYPE());
    }

    return false;
}

inline SronBool_t Bool::__NOT__() const
{
    return !this->value;
}

inline SronBool_t Bool::__LESS_THAN__(Any &, SronTypeNum __type) const
{
    return this->TYPE_NUMBER() < __type;
}

inline SronBool_t Bool::__LESS_THAN_EQUAL__(Any &, SronTypeNum __type) const
{
    return this->TYPE_NUMBER() <= __type;
}

inline SronBool_t Bool::__MORE_THAN__(Any &, SronTypeNum __type) const
{
    return this->TYPE_NUMBER() > __type;
}

inline SronBool_t Bool::__MORE_THAN_EQUAL__(Any &, SronTypeNum __type) const
{
    return this->TYPE_NUMBER() >= __type;
}

inline Bool::~Bool() noexcept {}

#endif