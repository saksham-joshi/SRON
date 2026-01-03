
#pragma once

#ifndef _SRON_CHAR_H_
#define _SRON_CHAR_H

#include "_bytecode_components_.hpp"

namespace SronChar{

    // ============================================================================== TO CHECK IF THE GIVEN CHAR IS ALPHABET OR NOT
    
    [[gnu::leaf]] constexpr inline static bool isAlphabet(const SronChar_t __ch) noexcept 
    {
        return ((__ch >= 'A' && __ch <= 'Z') || ( __ch >= 'a' && __ch <= 'z'));
    }

     // ============================================================================== TO CHECK IF THE GIVEN CHAR IS VOWEL OR NOT
    
    [[gnu::leaf]] constexpr inline static bool isVowel(const SronChar_t __ch) noexcept
    {
        if(__ch == 'a' || __ch == 'e' || __ch == 'i' || __ch == 'o' || __ch == 'u' || 
           __ch == 'A' || __ch == 'E' || __ch == 'I' || __ch == 'O' || __ch == 'U') return true; 
            
        return false;
    }

    constexpr inline static bool isConsonant(const SronChar_t __ch)
    {
        if( SronChar::isAlphabet(__ch) && !SronChar::isVowel(__ch)) return true;
        
        return false;
    }

    [[gnu::leaf]] constexpr inline static bool isDigit(const SronChar_t __ch) noexcept
    {
        if(__ch >= '0' && __ch <= '9') return true;
           
        return false;
    }

    [[gnu::leaf]] constexpr inline static bool isLowerCase(const SronChar_t __ch) noexcept
    {
        return (__ch >= 'a' && __ch <= 'z');
    }

    [[gnu::leaf]] constexpr inline static bool isUpperCase(const SronChar_t __ch) noexcept 
    {
        return (__ch >= 'A' && __ch <= 'Z' );
    }

    constexpr inline static SronChar_t toLowercase(const SronChar_t __ch) noexcept
    {
        return ( SronChar::isUpperCase( __ch ) ? __ch + 32 : __ch );
    }

    constexpr inline static SronChar_t toUppercase(const SronChar_t __ch) noexcept
    {
        return ( SronChar::isLowerCase( __ch ) ? __ch - 32 : __ch );
    }

    [[gnu::leaf]] constexpr inline static int toAscii(const SronChar_t __ch) noexcept
    {
        return (int)__ch;
    }

    [[gnu::leaf]] constexpr inline static SronChar_t fromAscii(const int __ch) noexcept
    {
        return (SronChar_t)__ch;
    }

    [[gnu::leaf]] constexpr inline static bool isAlphaNum(const SronChar_t __ch) noexcept
    {
        return (__ch >= 'A' && __ch <= 'Z') || (__ch >= '0' && __ch <= '9') || (__ch >= 'a' && __ch <= 'z');
    }
}

#endif