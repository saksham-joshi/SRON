#pragma once

#ifndef ARGLIST_H
#define ARGLIST_H

#include "base-component/_String_.hpp"

class ArgumentList
{
private:
    std::vector<AnyBindPtr> array;

public:
    inline ArgumentList() {}
    
    inline ArgumentList(AnyBindPtr value)
    {
        array.push_back(value);
    }

    inline AnyBindPtr GET(const unsigned short int index)
    {
        if (array.size() <= index)
        {
            throw ThrowException("extracting the passed arguments", ArgumentException);
        }
        return (array[index]) ;
    }

    inline IntPtr GET_INT(const unsigned short int index)
    {
        return this->GET(index)->ptr_->GET_INT();
    }

    inline DoublePtr GET_DOUBLE(const unsigned short int index)
    {
        return this->GET(index)->ptr_->GET_DOUBLE();
    }

    inline CharPtr GET_CHAR(const unsigned short int index)
    {
        return this->GET(index)->ptr_->GET_CHAR();
    }

    inline StringPtr GET_STRING(const unsigned short int index)
    {
        return this->GET(index)->ptr_->GET_STRING();
    }

    inline ColPtr GET_COLLECTIVE(const unsigned short int index)
    {
        return this->GET(index)->ptr_->GET_COLLECTIVE();
    }

    inline ListPtr GET_LIST(const unsigned short int index)
    {
        return this->GET(index)->ptr_->GET_LIST();
    }

    inline BoolPtr GET_BOOL(const unsigned short int index)
    {
        return this->GET(index)->ptr_->GET_BOOL();
    }

    inline void PUT(AnyBindPtr arg)
    {
        array.push_back(arg);
    }

    inline void CLEAR() noexcept
    {
        array.clear();
    }

    #ifdef SRON_DEBUG_MODE
        inline void PRINT() const{

            std::cout << "\n Arglist : [";
            for(const auto& i : this->array){
                i->ptr_->F_PRINT();
                std::cout << "  ";
            }
            std::cout << "]\n";
        }
    #endif

    inline const unsigned short int LEN() const
    {
        return array.size();
    }
};

typedef ArgumentList* ArgListPtr;

#endif