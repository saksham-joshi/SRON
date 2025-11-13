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

inline AnyPtr Void::copy() const
{
    return new Void();
}

inline void Void::print() const
{
    std::printf("%s", VOID_STRING_PRINT_FORMAT );
}

inline void Void::formatPrint() const
{
    this->print();
}

inline long long int Void::sizeOf() const
{
    return 0;
}
inline std::string Void::toString() const
{
    return VOID_STRING_PRINT_FORMAT;
}

inline bool Void::isCollective() const
{
    return false;
}

inline void Void::preMove(){ }

inline void Void::fillObuffer(SronOBuffer& __buffer) const
{
    __buffer.append(VOID_STRING_PRINT_FORMAT , sizeof( VOID_STRING_PRINT_FORMAT) - 1);
}

inline const char *Void::type() const
{
    return "Void";
}
inline void Void::type(std::string &str) const
{
    str.append("Void");
}

inline SronTypeNum Void::typeNum() const
{
    return SronTypeNum::TYPE_VOID;
}

inline VoidPtr Void::getVoid() const
{
    return const_cast<Void *>(this);
}

inline SronBool_t Void::__isEqual__(Any &, SronTypeNum __type) const
{
    return ( __type == this->typeNum());
}

inline SronBool_t Void::__notEqual__(Any &, SronTypeNum __type) const
{
    return this->typeNum() != __type;
}

inline SronBool_t Void::__lessThan__(Any & , SronTypeNum __type) const
{

    return this->typeNum() < __type;
}

inline SronBool_t Void::__lessEqual__(Any & , SronTypeNum __type) const
{

    return this->typeNum() <= __type;
}

inline SronBool_t Void::__moreThan__(Any &, SronTypeNum __type) const
{
    return this->typeNum() > __type;
}

inline SronBool_t Void::__moreEqual__(Any &, SronTypeNum __type) const
{
    return this->typeNum() >= __type;
}

inline Void::~Void() noexcept {}

#endif