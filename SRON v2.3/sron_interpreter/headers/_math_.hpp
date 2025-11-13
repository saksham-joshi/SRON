#include <cmath>
/*
In this file, the following Mathematical functions are declared :
    1. Abs
    2. Max
    3. Min
    4. Square root
    5. Cube root
    6. Log10
    7. Log
    8. Log2
    9. Sin
    10. Cos
    11. tan
    12. ceil
    13. floor
*/

#ifndef MATH_H
#define MATH_H

namespace SronMath{

    [[gnu::leaf]] constexpr inline static SronDouble_t abs(SronDouble_t val) noexcept
    {
        return (val < 0) ? -val : val;
    }

    [[gnu::leaf]] constexpr inline static SronInt_t abs(SronInt_t val) noexcept
    {
        return (val < 0) ? -val : val;
    }

    //================================================================

    [[gnu::leaf]] constexpr inline static SronDouble_t maxValue(SronDouble_t val1, SronDouble_t val2) noexcept
    {
        return (val1 > val2) ? val1 : val2;
    }

    [[gnu::leaf]] constexpr inline static SronInt_t maxValue(SronInt_t val1, SronInt_t val2) noexcept
    {
        return (val1 > val2) ? val1 : val2;
    }

    [[gnu::leaf]] constexpr inline static SronChar_t maxValue(SronChar_t val1, SronChar_t val2) noexcept
    {
        return (val1 > val2) ? val1 : val2;
    }

    //================================================================

    constexpr inline static SronDouble_t sqrt(SronDouble_t val) noexcept
    {
        return std::sqrt(val) ;
    }

    constexpr inline static SronDouble_t sqrt(SronInt_t val) noexcept
    {
        return std::sqrt(val);
    }

    //================================================================

    constexpr inline static SronDouble_t cbrt(SronDouble_t val) noexcept
    {
        return std::cbrt(val) ;
    }

    constexpr inline static SronDouble_t cbrt(SronInt_t val) noexcept
    {
        return std::cbrt(val);
    }

    //================================================================

    constexpr inline static SronDouble_t log(SronDouble_t val) noexcept
    {
        return std::log(val) ;
    }

    constexpr inline static SronDouble_t log(SronInt_t val) noexcept
    {
        return std::log(val);
    }

    //================================================================

    constexpr inline static SronDouble_t log2(SronDouble_t val) noexcept
    {
        return std::log2(val) ;
    }

    constexpr inline static SronDouble_t log2(SronInt_t val) noexcept
    {
        return std::log2(val);
    }

    //================================================================

    constexpr inline static SronDouble_t log10(SronDouble_t val) noexcept
    {
        return std::log10(val) ;
    }

    constexpr inline static SronDouble_t log10(SronInt_t val) noexcept
    {
        return std::log10(val);
    }

    //================================================================

    constexpr inline static SronDouble_t sin(SronDouble_t val) noexcept
    {
        return std::sin(val) ;
    }

    constexpr inline static SronDouble_t sin(SronInt_t val) noexcept
    {
        return std::sin(val);
    }

    //================================================================

    constexpr inline static SronDouble_t cos(SronDouble_t val) noexcept
    {
        return std::cos(val) ;
    }

    constexpr inline static SronDouble_t cos(SronInt_t val) noexcept
    {
        return std::cos(val);
    }

    //================================================================

    constexpr inline static SronDouble_t tan(SronDouble_t val) noexcept
    {
        return std::tan(val) ;
    }

    constexpr inline static SronDouble_t tan(SronInt_t val) noexcept
    {
        return std::tan(val);
    }

    //================================================================

    constexpr inline static SronInt_t ceil(SronDouble_t val) noexcept
    {
        return std::ceil(val) ;
    }

    constexpr inline static SronInt_t ceil(SronInt_t val) noexcept
    {
        return std::ceil(val);
    }

    //================================================================

    constexpr inline static SronInt_t floor(SronDouble_t val) noexcept
    {
        return std::floor(val) ;
    }

    constexpr inline static SronInt_t floor(SronInt_t val) noexcept
    {
        return std::floor(val);
    }

    //================================================================

}

#endif