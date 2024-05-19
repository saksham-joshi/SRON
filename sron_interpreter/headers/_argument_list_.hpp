#pragma once

#ifndef ARGLIST_H
#define ARGLIST_H

#include "_datatypes_.hpp"

class Argument_List
{
private:
    std::vector<Any *> array;

public:
    Argument_List() {}
    Argument_List(Any *value)
    {
        try
        {
            array.push_back(value);
        }
        catch (const std::bad_alloc &)
        {
            DISPLAY_EXCEPTION("allocating memory to create argument list.", SystemOutofMemoryException);
        }
    }

    inline Any *GET(unsigned short int index)
    {
        if (array.size() <= index)
        {
            DISPLAY_EXCEPTION("", NoException);
        }
        return array[index];
    }

    inline Int *GET_INT(unsigned short int index)
    {
        Int *val = this->GET(index)->GET_INT();
        if (val == nullptr)
        {
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected an 'Int' value.", ArgumentException, false);
        }
        return val;
    }

    inline Double *GET_DOUBLE(unsigned short int index)
    {
        Double *val = this->GET(index)->GET_DOUBLE();
        if (val == nullptr)
        {
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'Double' value.", ArgumentException, false);
        }
        return val;
    }

    inline Char *GET_CHAR(unsigned short int index)
    {
        Char *val = this->GET(index)->GET_CHAR();
        if (val == nullptr)
        {
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'Char' value.", ArgumentException, false);
        }
        return val;
    }

    inline String *GET_STRING(unsigned short int index)
    {
        String *val = this->GET(index)->GET_STRING();
        if (val == nullptr)
        {
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'String' value.", ArgumentException, false);
        }
        return val;
    }

    inline List *GET_LIST(unsigned short int index)
    {
        List *val = this->GET(index)->GET_LIST();
        if (val == nullptr)
        {
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'List' value.", ArgumentException, false);
        }
        return val;
    }

    inline Bool *GET_BOOL(unsigned short int index)
    {
        Bool *val = this->GET(index)->GET_BOOL();
        if (val == nullptr)
        {
            DISPLAY_EXCEPTION("extracting the passed arguments. Expected a 'Bool' value.", ArgumentException, false);
        }
        return val;
    }

    inline void PUT(Any *arg)
    {
        try
        {
            array.push_back(arg);
        }
        catch (const std::bad_alloc &)
        {
            DISPLAY_EXCEPTION("allocating memory to create argument list.", SystemOutofMemoryException);
        }
    }

    inline void CLEAR()
    {
        array.clear();
    }

    inline unsigned short int LEN()
    {
        return array.size();
    }
};

#endif