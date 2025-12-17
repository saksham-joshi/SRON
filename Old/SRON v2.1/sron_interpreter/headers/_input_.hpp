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

namespace SronInput
{
    // ================================ FOR STRING USER INPUTS
    inline static StringPtr INPUT_STRING()
    {
        std::cin.sync();

        StringPtr ptr = new String();

        if (std::getline(std::cin, **ptr).fail())
        {
            throw ThrowException("taking 'String' input from terminal", InputTypeException);
        }

        return ptr;
    }

    // ========================================================================== FOR DOUBLE USER INPUTS
    inline static DoublePtr INPUT_DOUBLE()
    {
        std::cin.sync();

        DoublePtr ptr = new Double();

        std::cin >> **ptr;

        if (std::cin.fail())
        {
            throw ThrowException("taking 'Double' input from terminal", InputTypeException);
        }

        return ptr;
    }

    // =============================== FOR INT USER INPUTS
    inline static IntPtr INPUT_INT()
    {

        std::cin.sync();

        IntPtr ptr = new Int();

        std::cin >> **ptr;

        if (std::cin.fail())
        {
            throw ThrowException("taking 'Int' input from terminal", InputTypeException);
        }

        return ptr;
    }

    // ================================== FOR CHAR USER INPUTS
    inline static CharPtr INPUT_CHAR()
    {

        std::cin.sync();

        CharPtr ptr = new Char();

        std::cin >> **ptr;

        if (std::cin.fail())
        {
            throw ThrowException("taking 'Char' input from terminal", InputTypeException);
        }

        return ptr;
    }
}

#endif