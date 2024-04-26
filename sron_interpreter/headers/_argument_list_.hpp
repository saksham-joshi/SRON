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
    Argument_List(Any *value) : array(nullptr), size(0)
    {
        try
        {
            array = reinterpret_cast<Any **>(calloc(size, sizeof(Any *)));
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

    inline Any *operator[](unsigned short int index)
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

    inline Any *GET(unsigned short int index)
    {
        return this->operator[](index);
    }

    inline Int* GET_INT(unsigned short int index){
        Int* val = this->GET(0)->GET_INT();
        if(val == nullptr){
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected an 'Int' value.", ArgumentException, false);
        }
        return val;
    }

    inline Double* GET_DOUBLE(unsigned short int index){
        Double* val = this->GET(0)->GET_DOUBLE();
        if(val == nullptr){
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'Double' value.", ArgumentException, false);
        }
        return val;
    }

    inline Char* GET_CHAR(unsigned short int index){
        Char* val = this->GET(0)->GET_CHAR();
        if(val == nullptr){
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'Char' value.", ArgumentException, false);
        }
        return val;
    }

    inline String* GET_STRING(unsigned short int index){
        String* val = this->GET(0)->GET_STRING();
        if(val == nullptr){
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'String' value.", ArgumentException, false);
        }
        return val;
    }

    inline List* GET_LIST(unsigned short int index){
        List* val = this->GET(0)->GET_LIST();
        if(val == nullptr){
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'List' value.", ArgumentException, false);
        }
        return val;
    }

    inline Bool* GET_BOOL(unsigned short int index){
        Bool* val = this->GET(0)->GET_BOOL();
        if(val == nullptr){
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'Bool' value.", ArgumentException, false);
        }
        return val;
    }

    inline void PUT(Any *arg)
    {
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