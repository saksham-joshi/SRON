#pragma once

#ifndef ARGLIST_H
#define ARGLIST_H

#include "_bytecode_manager_.hpp"
#include "_variable_manager_.hpp"

class ArgumentList
{
private:
    alignas(64) AnyBindPtr _array[ARGUMENT_LIST_MAX_LEN] = { 0 };
    ArgListLen_t _len = 0;

public:
    inline ArgumentList() {}
    
    inline ArgumentList(AnyBindPtr value)
    {
        _array[_len++] = value;
    }

    [[gnu::hot]] [[gnu::always_inline]] inline AnyBindPtr get(const ArgListLen_t index)
    {
        if ( index >= this->_len) [[unlikely]]
        {
            throw ThrowException("extracting the passed arguments", SronException::ArgumentException);
        }
        return this->_array[index] ;
    }

    [[gnu::hot]] [[gnu::always_inline]] inline IntPtr getInt(const ArgListLen_t index)
    {
        return this->get(index)->ptr()->getInt();
    }

    [[gnu::hot]] [[gnu::always_inline]] inline DoublePtr getDouble(const ArgListLen_t index)
    {
        return this->get(index)->ptr()->getDouble();
    }

    [[gnu::hot]] [[gnu::always_inline]] inline CharPtr getChar(const ArgListLen_t index)
    {
        return this->get(index)->ptr()->getChar();
    }

    [[gnu::hot]] [[gnu::always_inline]] inline StringPtr getString(const ArgListLen_t index)
    {
        return this->get(index)->ptr()->getString();
    }

    [[gnu::hot]] [[gnu::always_inline]] inline ColPtr getCollective(const ArgListLen_t index)
    {
        return this->get(index)->ptr()->getCollective();
    }

    [[gnu::hot]] [[gnu::always_inline]] inline ListPtr getList(const ArgListLen_t index)
    {
        return this->get(index)->ptr()->getList();
    }

    [[gnu::hot]] [[gnu::always_inline]] inline BoolPtr getBool(const ArgListLen_t index)
    {
        return this->get(index)->ptr()->getBool();
    }

    [[gnu::hot]] [[gnu::always_inline]] inline void put(AnyBindPtr arg)
    {
        this->_array[this->_len++] = arg;
    }

    #ifdef SRON_DEBUG_MODE
        inline void print() const{

            std::printf( "\n Arglist : [" );
            for(const auto& i : this->_array){
                i->ptr()->formatPrint();
                std::printf("  ");
            }
            std::printf( "]\n" );
        }
    #endif

    [[gnu::hot]] [[gnu::always_inline]] inline ArgListLen_t len() const
    {
        return this->_len;
    }
};

typedef ArgumentList* ArgListPtr;
typedef ArgumentList& ArgListRef;

#endif