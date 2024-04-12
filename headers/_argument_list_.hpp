#ifndef ARGLIST_H
#define ARGLIST_H

#include "_datatypes_.hpp"

class Argument_List
{

private:
    Any **array;
    unsigned short int size;

public:
    Argument_List() : array(nullptr), size(0)
    {
        try
        {
            array = reinterpret_cast<Any **>(calloc(1, sizeof(Any *)));
            if (!array)
            {
                DISPLAY_EXCEPTION("allocating a memory to call a function.", SystemOutofMemoryException);
            }
        }
        catch (const std::bad_alloc &)
        {
            DISPLAY_EXCEPTION("allocating memory to create argument list.", SystemOutofMemoryException);
        }
    }
    Argument_List(Any *value) : array(nullptr), size(1)
    {
        try
        {
            array = reinterpret_cast<Any **>(calloc(1, sizeof(Any *)));
            if (!array)
            {
                DISPLAY_EXCEPTION("allocating a memory to call a function.", SystemOutofMemoryException);
            }
            this->PUT(value);
        }
        catch (const std::bad_alloc &)
        {
            DISPLAY_EXCEPTION("allocating memory to create argument list.", SystemOutofMemoryException);
        }
    }

    ~Argument_List()
    {
        free(array);
        this->size = 0;
    }

    Any *operator[](unsigned short int index)
    {
        if (index < size)
        {
            return array[index];
        }
        else
        {
            DISPLAY_EXCEPTION("extracting the passed arguments.", IndexNotWithinRange);
            return nullptr;
        }
    }

    Any *GET(unsigned short int index)
    {
        return this->operator[](index);
    }

    inline void PUT(Any *arg)
    {
        // std::cout<<"value inserted = "<<arg->TO_STRING()<<"\n";
        try
        {
            ++size;
            array = reinterpret_cast<Any **>(realloc(array, size * sizeof(Any *)));
            array[size - 1] = arg;
        }
        catch (const std::bad_alloc &)
        {
            DISPLAY_EXCEPTION("allocating memory to create argument list.", SystemOutofMemoryException);
        }
    }

    inline void PRINT()
    {
        std::cout << "\n{";
        for (unsigned short int i = 0; i < this->size; ++i)
        {
            std::cout << "\n   >";
            this->array[i]->PRINT();
        }
        std::cout << "\n}";
    }

    inline void CLEAR()
    {
        array = NULL;
        size = 0;
    }

    inline unsigned short int LEN()
    {
        return size;
    }
};

#endif