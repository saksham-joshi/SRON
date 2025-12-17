

#pragma once

#ifndef _CNST_CHR_MAP_SPRT_H_
#define _CNST_CHR_MAP_SPRT_H_

#include "_sron_hasher_.hpp"

namespace ConstCharMapSupport
{

    struct HashFunction
    {

        inline size_t operator()(const char *__s) const noexcept
        {
            return SronHasher(__s).GET();
        }
    };

    struct KeyEqual
    {
        inline bool operator()(const char * __lhs, const char * __rhs) const noexcept
        {
            while( *__lhs && *__rhs && *__lhs == *__rhs)
            {
                ++__lhs;
                ++__rhs;
            }

            return *__lhs == *__rhs;
        }
    };
}
#endif