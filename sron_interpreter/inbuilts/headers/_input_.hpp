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
    
    #define SRON_INPUT_BUFFER_CLEAR std::cin.ignore( LLONG_MAX , '\n')

    static_assert(sizeof(std::streamsize) >= sizeof(LLONG_MAX), "Replace the MAX value passed to 'SRON_INPUT_BUFFER_CLEAR' to avoid runtime numeric overflow and undefined behaviour");

    
    // ================================ FOR STRING USER INPUTS
   [[gnu::malloc]] [[nodiscard]] inline static StringPtr inputString()
    {
        std::cin.sync();

        StringPtr ptr = new String();

        if (std::getline(std::cin, ptr->getBaseString()).fail())
        {
            checkSignalStatus;

            throw ThrowException("taking 'String' input from terminal", SronException::InputTypeException);
        }

        return ptr;
    }

    // ========================================================================== FOR DOUBLE USER INPUTS
    [[gnu::malloc]] [[nodiscard]] inline static DoublePtr inputDouble()
    {
        std::cin.sync();

        SronDouble_t val;

        std::cin >> val;

        if (std::cin.fail())
        {
            checkSignalStatus;

            throw ThrowException("taking 'Double' input from terminal", SronException::InputTypeException);
        }

        SRON_INPUT_BUFFER_CLEAR;

        return new Double(val);
    }

    // =============================== FOR INT USER INPUTS
    [[gnu::malloc]] [[nodiscard]] inline static IntPtr inputInt()
    {

        std::cin.sync();

        SronInt_t val;

        std::cin >> val;

        if (std::cin.fail())
        {
            checkSignalStatus;

            throw ThrowException("taking 'Int' input from terminal", SronException::InputTypeException);
        }

        SRON_INPUT_BUFFER_CLEAR;

        return new Int(val);
    }

    // ================================== FOR CHAR USER INPUTS
    [[gnu::malloc]] [[nodiscard]] inline static CharPtr inputChar()
    {
        std::cin.sync();

        SronChar_t ch;

        std::cin >> ch;

        if (std::cin.fail())
        {
            checkSignalStatus;
            
            throw ThrowException("taking 'Char' input from terminal", SronException::InputTypeException);
        }

        SRON_INPUT_BUFFER_CLEAR;

        return new Char(ch);
    }
}

#endif