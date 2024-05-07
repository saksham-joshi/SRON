/*
 * This file contains the implementation of user input functions.
 * It contains the methods to handle input for these datatypes :
 *              1. String.
 *              2. Double.
 *              3. Int.
 *              4. Char.
 */
#pragma once

#include "_argument_list_.hpp"

#ifndef INPUT_H
#define INPUT_H

inline namespace SronInput
{
    // ================================ FOR STRING USER INPUTS
    inline static String *INPUT_STRING()
    {
        try
        {
            std::string value(" ");

            if (std::getline(std::cin, value).fail())
            {
                throw std::exception();
            }

            return new String(value);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking 'String' input from terminal.", InputTypeException, false);
        }
        return nullptr;
    }

    // ========================================================================== FOR DOUBLE USER INPUTS
    inline static Double *INPUT_DOUBLE()
    {
        try
        {
            double value = 0;

            std::cin >> value;

            if (std::cin.fail())
            {
                throw std::exception();
            }

            return new Double(value);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking 'Double' input from terminal.", InputTypeException, false);
        }
        return nullptr;
    }

    // =============================== FOR INT USER INPUTS
    inline static Int *INPUT_INT()
    {
        try
        {
            long long int value = 0;

            std::cin >> value;

            if (std::cin.fail())
            {
                throw std::exception();
            }

            return new Int(value);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking 'Int' input from terminal.", InputTypeException, false);
        }

        return nullptr;
    }

    // ================================== FOR CHAR USER INPUTS
    inline static Char *INPUT_CHAR()
    {
        try
        {
            char value = ' ';

            std::cin >> value;

            if (std::cin.fail())
            {
                throw std::exception();
            }

            return new Char(value);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking 'Char' input from terminal.", InputTypeException, false);
        }
        return nullptr;
    }

}

#endif