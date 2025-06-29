
/*
The converter Class provides conversion from one datatype to another
It includes functions :
    1. string to double
    2. SronBool_t to double
    3. SronInt_t to double
    4. double to double

    5. SronInt_t to string
    6. double to string
    7. char to string
    8. SronBool_t to string
    9. string to string

    10. string to SronInt_t
    11. double to SronInt_t
    12. char to SronInt_t
    13. SronBool_t to SronInt_t

    14. string to SronBool_t
    15. SronInt_t to SronBool_t
    16. double to SronBool_t
*/

#pragma once

#ifndef CONVERTER_H
#define CONVERTER_H


#include "_throw_exception_.hpp"


namespace Converter
{
    inline static int getNumberFromChar( char __ch)
    {
        
        if ( __ch >= '0' && __ch <= '9') return __ch - '0';
    
        throw " ";
    }

    /*
        |==========  TO_DOUBLE ==========|
        Conversion to SronDouble_t type ....
        1. string         ->    SronDouble_t
    */

    inline static SronDouble_t TO_DOUBLE(const std::string & __str)
    {
        if ( __str.length() == 0 ) return 0;

        try
        {
            SronDouble_t result = 0;

            // creating the number till an invalid character or decimal point '.' doesn't arrive.
            auto it = __str.begin() + ( __str[0] == '-' ? 1 : 0);


            while( it < __str.end() && *it != '.' ) 
            {
                result = (result * 10) + getNumberFromChar(*it);

                ++it;
            }

            // now moving iterator after decimal point
            ++it;

            SronDouble_t j = 10;

            while (it < __str.end() )
            {
                result += getNumberFromChar(*it) / j;

                j *= 10;

                ++it;
            }

            return ( __str[0] == '-' ? (-result) : result);
        }
        catch ( const char* )
        {
            throw ThrowException("converting '"+ __str +"' to Double", SronException::TypeConversionException);
        }
        return 0;
    }

    /*
        |==========  TO_STRING ==========|
        Conversion to string type ....
        1. SronInt_t            ->    string
        2. SronDouble_t         ->    string
        3. SronBool_t           ->    string
        4. SronChar_t           ->    string
        5. string               ->    string
    */

    inline static std::string TO_STRING( SronInt_t __value )
    {
        return std::to_string( __value );
    }
    inline static std::string TO_STRING( SronDouble_t __value )
    {
        return std::to_string( __value );
    }
    inline static std::string TO_STRING(std::string &__value)
    {
        return __value;
    }
    inline static std::string TO_STRING( SronBool_t __value)
    {
        return ( __value ) ? "true" : "false";
    }
    inline static std::string TO_STRING( SronChar_t __ch )
    {
        return (std::string) "" + __ch;
    }

    /*
        |==========  TO_INT ==========|
        Conversion to SronInt_t type ....
        1. string         ->    SronInt_t
    */

    inline static SronInt_t TO_INT(const std::string &__str)
    {
        if( __str.length() == 0 ) return 0;

        try
        {
            SronInt_t val = 0;

            auto it = __str.begin() + ( __str[0] == '-' ? 1 : 0);

            for (; it < __str.end(); ++it)
            {
                val = ( val * 10 ) + Converter::getNumberFromChar(*it);
            }

            return ( __str[0] == '-' ) ? -val : val;
        }
        catch (const char* )
        {
            throw ThrowException("converting '" + __str + "' to Int", SronException::TypeConversionException);
        }
        return 0;
    }

    /*
        |==========  TO_BOOL ==========|
        Conversion to SronBool_t type ....
        1. string         ->    SronBool_t
    */

    inline static SronBool_t TO_BOOL(std::string &str)
    {
        if (str == "true") return true;
            
        else if (str == "false") return false;
            
        throw ThrowException("converting '" + str + "' to Bool", SronException::TypeConversionException);
        
    }
}

#endif