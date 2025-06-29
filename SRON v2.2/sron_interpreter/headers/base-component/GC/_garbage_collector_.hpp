
#pragma once

#ifndef _GC_H_
#define _GC_H_

#include "_sron_obuffer_.hpp"

inline GarbageCollector::MemoryChain::MemoryChain(const GarbageCollector::GcSize_t __layer_index ) noexcept : 

  _head(nullptr), _tail(nullptr), _layer_index(__layer_index) 
{ 

}

inline GarbageCollector::MemoryChain::MemoryChain(GarbageCollector::MemoryChain &&__other) noexcept : 

  _head(__other._head), _tail(__other._tail), _layer_index(__other._layer_index)
{
    __other._head = __other._tail = nullptr;
}

inline AnyBindPtr GarbageCollector::MemoryChain::push(AnyPtr __ptr)
{
    return this->push( __ptr , __ptr->TYPE_NUMBER() );
}

inline AnyBindPtr GarbageCollector::MemoryChain::push( AnyPtr __ptr , SronTypeNum __type )
{
    return this->push(AnyBind(__ptr, __type, this->_layer_index));
}

inline AnyBindPtr GarbageCollector::MemoryChain::push(AnyBind &&__binder)
{
    if (this->_tail) [[likely]]
    {
        this->_tail->_next = new MemoryChain::Node<AnyBind>( std::move(__binder) );

        this->_tail = this->_tail->_next;
    }
    else
    {
        this->_head = this->_tail = new MemoryChain::Node<AnyBind>( std::move(__binder) );
    }

    return &(this->_tail->_value);   
}

inline AnyBindPtr GarbageCollector::MemoryChain::back()
{
    if (this->_tail) [[likely]] return &(this->_tail->_value);

    throw ThrowException("extracting the layer values. The current function layer is empty and has no registered memory [Interpreter-Issue]");
}

inline GarbageCollector::MemoryChain::~MemoryChain() noexcept
{
    if ( this->_head )
    {    
        auto current = this->_head;
        
        while( current )
        {
            auto next = current->_next;

            delete current;

            current = next;
        }

        this->_head = this->_tail = nullptr;
    }
}

// ==================================================================== //

inline static void GarbageCollector::INITIALIZE()
{
    GarbageCollector::ADD_LAYER();

    Void::void_object = GarbageCollector::REGISTER_MEMORY(new Void() , SronTypeNum::TYPE_VOID);
    Bool::__SronTrue = GarbageCollector::REGISTER_MEMORY(new Bool(true) , SronTypeNum::TYPE_BOOL);
    Bool::__SronFalse = GarbageCollector::REGISTER_MEMORY(new Bool(false) , SronTypeNum::TYPE_BOOL);
}

inline static void GarbageCollector::ADD_LAYER()
{
    ++GarbageCollector::__gcStackTopLoc;

    GarbageCollector::__garbageStack.push_back(GarbageCollector::MemoryChain(GarbageCollector::__gcStackTopLoc));

    __top = &GarbageCollector::__garbageStack.back();
}

inline static void GarbageCollector::DESTROY_LAYER()
{
    using GarbageCollector::__garbageStack;
    using GarbageCollector::__top;

    if (__garbageStack.empty()) [[unlikely]]
    {
        throw ThrowException("destroying Garbage Collector's layer. Cannot destory layer if the stack is empty [Interpreter-Issue]");
    }

    __garbageStack.pop_back();

    __top = __garbageStack.empty() ? nullptr : &__garbageStack.back();

    --GarbageCollector::__gcStackTopLoc;
}

inline static AnyBindPtr GarbageCollector::REGISTER_AT( GarbageCollector::GcSize_t __layer , AnyPtr __value , SronTypeNum __type )
{
    return GarbageCollector::__garbageStack[ __layer ].push( __value , __type );
}

inline static void GarbageCollector::TOTAL_DESTRUCTION() noexcept
{
    GarbageCollector::__garbageStack.clear();

    GarbageCollector::__top = nullptr;

    GarbageCollector::__gcStackTopLoc = ULONG_MAX;
}

inline static AnyBindPtr GarbageCollector::MOVE(AnyBindPtr __binder)
{
    if (__binder->layer() == 0) return __binder;

    __binder->ptr()->PREMOVE();

    AnyBindPtr val = GarbageCollector::REGISTER_AT( GarbageCollector::__gcStackTopLoc - 1 , __binder->ptr() , __binder->type() );

    __binder->set(nullptr , SronTypeNum::INVALID_TYPE);

    return val;
}

inline static AnyBindPtr GarbageCollector::REGISTER_MEMORY(AnyPtr __ptr)
{
    return GarbageCollector::__top->push(__ptr);
}

inline static AnyBindPtr GarbageCollector::REGISTER_MEMORY(AnyPtr __ptr , SronTypeNum __type )
{
    return GarbageCollector::__top->push( __ptr , __type);
}

#endif