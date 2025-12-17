
/*
The converter Class provides conversion from one datatype to another
It includes functions :
    1. string to double
    2. bool to double
    3. long long int to double
    4. double to double

    5. long long int to string
    6. double to string
    7. char to string
    8. bool to string
    9. string to string

    10. string to long long int
    11. double to long long int
    12. char to long long int
    13. bool to long long int

    14. string to bool
    15. long long int to bool
    16. double to bool
*/

#pragma once

#ifndef CONVERTER_H
#define CONVERTER_H


#include "_throw_exception_.hpp"


namespace Converter
{

    inline static std::string TOUPPERCASE(std::string &str)
    {
        for (size_t i = 0; i < str.length(); ++i)
        {
            str[i] = toupper(str[i]);
        }
        return str;
    }
    inline static int get_number_from_char(int ch)
    {
        try
        {
            if (ch >= 48 && ch <= 57)
            {
                return ch - 48;
            }
            throw std::exception();
        }
        catch (const std::exception &)
        {
            throw ThrowException("conversion of datatypes", TypeConversionError);
        }
        return 0;
    }

    /*
        |==========  TO_DOUBLE ==========|
        Conversion to double type ....
        1. string         ->    double
        2. double         ->    double
        3. bool           ->    double
        4. long long int  ->    double
    */

    inline static double TO_DOUBLE(std::string &str)
    {
        try
        {
            double result = 0;

            // creating the number till an invalid character or decimal point '.' doesn't arrive.
            size_t i = (str[0] == '-') ? 1 : 0;

            while (i < str.length() && str[i] != '.')
            {
                result = (result * 10) + get_number_from_char(str[i++]);
            }

            // now creating the after decimal point part
            ++i;
            double j = 10;
            while (i < str.length())
            {
                result += get_number_from_char(str[i++]) / j;
                j *= 10;
            }
            return (str[0] == '-' ? (-result) : result);
        }
        catch (const std::exception &)
        {
            throw ThrowException("converting '"+ str +"' to Double", TypeConversionError);
        }
        return 0;
    }
    inline static double TO_DOUBLE(long long int i)
    {
        try
        {
            return (double)i;
        }
        catch (const std::exception &)
        {
            throw ThrowException("converting '"+std::to_string(i)+"' to Double", TypeConversionError);
        }
        return 0;
    }
    inline static double TO_DOUBLE(double d)
    {
        return d;
    }
    inline static double TO_DOUBLE(bool b)
    {
        return (b) ? 1 : 0;
    }

    /*
        |==========  TO_STRING ==========|
        Conversion to string type ....
        1. long long int  ->    string
        2. double         ->    string
        3. bool           ->    string
        4. char           ->    string
        5. string         ->    string
    */

    inline static std::string TO_STRING(long long int i)
    {
        return std::to_string(i);
    }
    inline static std::string TO_STRING(double d)
    {
        return std::to_string(d);
    }
    inline static std::string TO_STRING(std::string &i)
    {
        return i;
    }
    inline static std::string TO_STRING(bool b)
    {
        return (b) ? "true" : "false";
    }
    inline static std::string TO_STRING(char ch)
    {
        return (std::string) "" + ch;
    }

    /*
        |==========  TO_INT ==========|
        Conversion to long long int type ....
        1. string         ->    long long int
        2. double         ->    long long int
        3. bool           ->    long long int
        4. char           ->    long long int
        5. string         ->    long long int
    */

    inline static long long int TO_INT(const std::string &str)
    {
        try
        {
            long long int val = 0;
            auto it = (str.front() == '-') ? str.begin() + 1 : str.begin();

            for (; it < str.end(); ++it)
            {
                int ascii = (int)*it;
                if (ascii >= 48 && ascii <= 57)
                {
                    val = (val * 10) + (ascii - 48);
                    continue;
                }
                throw std::exception();
            }
            return (str.front() == '-') ? -val : val;
        }
        catch (const std::exception &)
        {
            throw ThrowException("converting '" + str + "' to Int", TypeConversionError);
        }
        return 0;
    }
    inline static long long int TO_INT(double d)
    {
        return (long long int)d;
    }
    inline static long long int TO_INT(char c)
    {
        try
        {
            int ascii = (int)c;
            if (ascii >= 48 && ascii <= 57)
            {
                return (long long int)((int)c) - 48;
            }
            throw std::exception();
        }
        catch (const std::exception &)
        {
            throw ThrowException("converting '"+std::to_string(c)+"' to Int", TypeConversionError);
        }
        return 0;
    }
    inline static long long int TO_INT(bool b)
    {
        return (b) ? 1 : 0;
    }
    inline static long long int TO_INT(long long int x)
    {
        return x;
    }

    /*
        |==========  TO_BOOL ==========|
        Conversion to bool type ....
        1. string         ->    bool
        2. double    ->    bool
        3. bool           ->    bool
        4. long long int  ->    bool
    */

    inline static bool TO_BOOL(std::string &str)
    {
        try
        {
            if (str == "true")
            {
                return true;
            }
            else if (str == "false")
            {
                return false;
            }
            throw std::exception();
        }
        catch (const std::exception &)
        {
            throw ThrowException("converting '" + str + "' to Bool", TypeConversionError);
        }
        return false;
    }
    inline static bool TO_BOOL(long long int i)
    {
        return (i > 0);
    }
    inline static bool TO_BOOL(double d)
    {
        return (d > 0);
    }
    inline static bool TO_BOOL(bool b)
    {
        return b;
    }

}

#endif