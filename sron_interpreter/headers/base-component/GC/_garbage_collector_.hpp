
#pragma once

#ifndef _GC_H_
#define _GC_H_

#include "base_type/_datatypes_.hpp"

namespace GarbageCollector
{

    GcStack __garbageStack;

    /* stores the __garbageStack.size() - 1. 
     * Initially set to ULONG_MAX, because
     * When the first layer is added, it is 
     * incremeneted and reaches to zero.
    */
    unsigned long __gcStackTopLoc = ULONG_MAX;

    GcLayer *__top;

    inline static void ADD_LAYER();
    inline static void DESTROY_LAYER();
    inline static void INITIALIZE();
    inline static AnyBindPtr MOVE(AnyBindPtr);
    inline static AnyBindPtr REGISTER_MEMORY(AnyPtr);
    inline static AnyBindPtr REGISTER_AT(AnyBindRef, GcSize_t);
    inline static void TOTAL_DESTRUCTION() noexcept;

}

#endif