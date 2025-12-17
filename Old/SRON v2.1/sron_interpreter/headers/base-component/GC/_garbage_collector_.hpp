
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

    // ==================================================================== //



    inline static void INITIALIZE()
    {
        
        GarbageCollector::ADD_LAYER();

        Void::void_object = GarbageCollector::REGISTER_MEMORY(new Void());
        Bool::__SronTrue = GarbageCollector::REGISTER_MEMORY(new Bool(true));
        Bool::__SronFalse = GarbageCollector::REGISTER_MEMORY(new Bool(false));

        Void::void_object->layer_ = Bool::__SronTrue->layer_ = Bool::__SronFalse->layer_ = GarbageCollector::__gcStackTopLoc;

    }

    inline static void ADD_LAYER()
    {
        GarbageCollector::__garbageStack.emplace_back();

        __top = &GarbageCollector::__garbageStack.back();

        ++GarbageCollector::__gcStackTopLoc;
    }

    inline static void DESTROY_LAYER()
    {
        using GarbageCollector::__garbageStack;
        using GarbageCollector::__top;

        if (__garbageStack.empty())
        {
            throw ThrowException("destroying Garbage Collector's layer. Cannot destory layer if the stack is empty");
        }

        __garbageStack.pop_back();

        __top = __garbageStack.empty()? nullptr : &__garbageStack.back();

        --GarbageCollector::__gcStackTopLoc;
        
    }


    inline static AnyBindPtr REGISTER_AT(AnyBindRef __binder, GcSize_t __layer)
    {
        AnyBindPtr temp = &(__garbageStack[__layer]).emplace_back(std::move(__binder));
        temp->layer_ = __layer;
        return temp;
    }


    inline static void TOTAL_DESTRUCTION() noexcept
    {

        GarbageCollector::__garbageStack.clear();

        GarbageCollector::__top = nullptr;

        GarbageCollector::__gcStackTopLoc = ULONG_MAX;

    }

    inline static AnyBindPtr MOVE(AnyBindPtr __binder){

        if(__binder->layer_ == 0) return __binder;

        __binder->ptr_->PREMOVE();

        return GarbageCollector::REGISTER_AT(*__binder, GarbageCollector::__gcStackTopLoc-1);

    }


    inline static AnyBindPtr REGISTER_MEMORY(AnyPtr __ptr)
    {

        return &GarbageCollector::__top->emplace_back(AnyBind(__ptr,GarbageCollector::__gcStackTopLoc));
    }
}

#endif