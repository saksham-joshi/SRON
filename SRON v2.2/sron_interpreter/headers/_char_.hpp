

namespace SronChar{

    // ============================================================================== TO CHECK IF THE GIVEN CHAR IS ALPHABET OR NOT
    
    [[gnu::leaf]] constexpr inline static bool IS_ALPHABET(const SronChar_t __ch) noexcept 
    {
        return ((__ch >= 'A' && __ch <= 'Z') || ( __ch >= 'a' && __ch <= 'z'));
    }

     // ============================================================================== TO CHECK IF THE GIVEN CHAR IS VOWEL OR NOT
    
    [[gnu::leaf]] constexpr inline static bool IS_VOWEL(const SronChar_t __ch) noexcept
    {
        if(__ch == 'a' || __ch == 'e' || __ch == 'i' || __ch == 'o' || __ch == 'u' || 
           __ch == 'A' || __ch == 'E' || __ch == 'I' || __ch == 'O' || __ch == 'U') return true; 
            
        return false;
    }

    constexpr inline static bool IS_CONSONANT(const SronChar_t __ch)
    {
        if( SronChar::IS_ALPHABET(__ch) && !SronChar::IS_VOWEL(__ch)) return true;
        
        return false;
    }

    [[gnu::leaf]] constexpr inline static bool IS_NUMBER(const SronChar_t __ch) noexcept
    {
        if(__ch >= '0' && __ch <= '9') return true;
           
        return false;
    }

    [[gnu::leaf]] constexpr inline static bool IS_LOWERCASE(const SronChar_t __ch) noexcept
    {
        return (__ch >= 'a' && __ch <= 'z');
    }

    [[gnu::leaf]] constexpr inline static bool IS_UPPERCASE(const SronChar_t __ch) noexcept 
    {
        return (__ch >= 'A' && __ch <= 'Z' );
    }

    constexpr inline static SronChar_t TO_LOWERCASE(const SronChar_t __ch) noexcept
    {
        return ( SronChar::IS_UPPERCASE( __ch ) ? __ch + 32 : __ch );
    }

    constexpr inline static SronChar_t TO_UPPERCASE(const SronChar_t __ch) noexcept
    {
        return ( SronChar::IS_LOWERCASE( __ch ) ? __ch - 32 : __ch );
    }

    [[gnu::leaf]] constexpr inline static int TO_ASCII(const SronChar_t __ch) noexcept
    {
        return (int)__ch;
    }

    [[gnu::leaf]] constexpr inline static SronChar_t FROM_ASCII(const int __ch) noexcept
    {
        return (SronChar_t)__ch;
    }
}