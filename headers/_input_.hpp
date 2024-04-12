/*
 * This file contains the implementation of user input functions.
 * It contains the methods to handle input for these datatypes :
 *              1. String.
 *              2. Double.
 *              3. Int.
 *              4. Char.
 */

#include "_argument_list_.hpp"

#ifndef INPUT_H
#define INPUT_H
inline namespace SronInput
{ 
    // ================================ FOR STRING USER INPUTS
    inline static std::string INPUT_STRING()
    {
        try
        {
            std::string x;
            std::getline(std::cin, x);
            return x;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking string user input.", SystemOutofMemoryException);
        }
        return " ";
    }

    inline static std::string INPUT_STRING(std::string msg)
    {
        std::cout << msg;
        return INPUT_STRING();
    }

    // ========================================================================== FOR DOUBLE USER INPUTS
    inline static double INPUT_DOUBLE()
    {
        double d = 0;
        try
        {
            std::cin >> d;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking Double type input value from user via console.", InputTypeException);
        }
        return d;
    }
    inline static double INPUT_DOUBLE(std::string msg)
    {
        printf("%s", msg.c_str());
        return INPUT_DOUBLE();
    }

    // =============================== FOR INT USER INPUTS
    inline static long long int INPUT_INT()
    {
        long long int val = 0;
        try
        {
            if (!scanf("%lld", &val))
            {
                throw std::exception();
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking Int type input value from user via console.", InputTypeException);
        }
        return val;
    }
    inline static long long int INPUT_INT(std::string msg)
    {
        printf("%s", msg.c_str());
        return INPUT_INT();
    }

    // ================================== FOR CHAR USER INPUTS
    inline static char INPUT_CHAR()
    {
        char ch = ' ';
        try
        {
            if (!scanf("%c", &ch))
            {
                throw std::exception();
            }
            return ch;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking Char type input value from user via console.", InputTypeException);
        }
        return ch;
    }
    inline static char INPUT_CHAR(std::string msg)
    {
        printf("%s", msg.c_str());
        return INPUT_CHAR();
    }
}

#endif