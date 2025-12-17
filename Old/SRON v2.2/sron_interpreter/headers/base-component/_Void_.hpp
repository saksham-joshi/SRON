#pragma once

#ifndef _VOID_H
#define _VOID_H

#include "GC/_sron_extra_.hpp"

/*
  |====================== VOID ===============================|
 'Void' datatype will be used to implement NULL or None values.
  > Syntax in SRON : "Void x"
*/

inline Void::Void() noexcept {}

inline AnyPtr Void::COPY() const
{
    return new Void();
}

inline void Void::PRINT() const
{
    printf_s("%s", VOID_STRING_PRINT_FORMAT );
}

inline void Void::F_PRINT() const
{
    this->PRINT();
}

inline long long int Void::SIZE_OF() const
{
    return 0;
}
inline std::string Void::TO_STRING() const
{
    return VOID_STRING_PRINT_FORMAT;
}

inline bool Void::IS_COLLECTIVE() const
{
    return false;
}

inline void Void::PREMOVE(){ }

inline void Void::FILL_OBUFFER(SronOBuffer& __buffer) const
{
    __buffer.append(VOID_STRING_PRINT_FORMAT , sizeof( VOID_STRING_PRINT_FORMAT) - 1);
}

inline const char *Void::TYPE() const
{
    return "Void";
}
inline void Void::TYPE(std::string &str) const
{
    str.append("Void");
}

inline SronTypeNum Void::TYPE_NUMBER() const
{
    return SronTypeNum::TYPE_VOID;
}

inline VoidPtr Void::GET_VOID() const
{
    return const_cast<Void *>(this);
}

inline SronBool_t Void::__IS_EQUAL__(Any &, SronTypeNum __type) const
{
    return ( __type == this->TYPE_NUMBER());
}

inline SronBool_t Void::__NOT_EQUAL__(Any &, SronTypeNum __type) const
{
    return this->TYPE_NUMBER() != __type;
}

inline SronBool_t Void::__LESS_THAN__(Any & , SronTypeNum __type) const
{

    return this->TYPE_NUMBER() < __type;
}

inline SronBool_t Void::__LESS_THAN_EQUAL__(Any & , SronTypeNum __type) const
{

    return this->TYPE_NUMBER() <= __type;
}

inline SronBool_t Void::__MORE_THAN__(Any &, SronTypeNum __type) const
{
    return this->TYPE_NUMBER() > __type;
}

inline SronBool_t Void::__MORE_THAN_EQUAL__(Any &, SronTypeNum __type) const
{
    return this->TYPE_NUMBER() >= __type;
}

inline Void::~Void() noexcept {}

#endif