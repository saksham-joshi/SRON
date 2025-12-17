

#pragma once

#ifndef _CNST_CHR_MAP_SPRT_H_
#define _CNST_CHR_MAP_SPRT_H_

#include<cstring>

namespace ConstCharMapSupport
{

    struct HashFunction
    {

        constexpr inline size_t operator()(const char *__s) const noexcept
        {
            std::size_t hash = 0;

            while (*__s)
            {
                hash = (hash * 31) + *__s++;
            }

            return hash;
        }
    };

    struct KeyEqual
    {
        constexpr inline bool operator()(const char *const &__lhs, const char *const &__rhs) const noexcept
        {
            return std::strcmp(__lhs, __rhs) == 0;
        }
    };
}
#endif