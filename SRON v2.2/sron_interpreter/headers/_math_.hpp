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

    [[gnu::leaf]] constexpr inline static SronDouble_t ABS(SronDouble_t val) noexcept
    {
        return (val < 0) ? -val : val;
    }

    [[gnu::leaf]] constexpr inline static SronInt_t ABS(SronInt_t val) noexcept
    {
        return (val < 0) ? -val : val;
    }

    //================================================================

    [[gnu::leaf]] constexpr inline static SronDouble_t MAX(SronDouble_t val1, SronDouble_t val2) noexcept
    {
        return (val1 > val2) ? val1 : val2;
    }

    [[gnu::leaf]] constexpr inline static SronInt_t MAX(SronInt_t val1, SronInt_t val2) noexcept
    {
        return (val1 > val2) ? val1 : val2;
    }

    [[gnu::leaf]] constexpr inline static SronChar_t MAX(SronChar_t val1, SronChar_t val2) noexcept
    {
        return (val1 > val2) ? val1 : val2;
    }

    //================================================================

    constexpr inline static SronDouble_t SQRT(SronDouble_t val) noexcept
    {
        return std::sqrt(val) ;
    }

    constexpr inline static SronDouble_t SQRT(SronInt_t val) noexcept
    {
        return std::sqrt(val);
    }

    //================================================================

    constexpr inline static SronDouble_t CBRT(SronDouble_t val) noexcept
    {
        return std::cbrt(val) ;
    }

    constexpr inline static SronDouble_t CBRT(SronInt_t val) noexcept
    {
        return std::cbrt(val);
    }

    //================================================================

    constexpr inline static SronDouble_t LOG(SronDouble_t val) noexcept
    {
        return std::log(val) ;
    }

    constexpr inline static SronDouble_t LOG(SronInt_t val) noexcept
    {
        return std::log(val);
    }

    //================================================================

    constexpr inline static SronDouble_t LOG2(SronDouble_t val) noexcept
    {
        return std::log2(val) ;
    }

    constexpr inline static SronDouble_t LOG2(SronInt_t val) noexcept
    {
        return std::log2(val);
    }

    //================================================================

    constexpr inline static SronDouble_t LOG10(SronDouble_t val) noexcept
    {
        return std::log10(val) ;
    }

    constexpr inline static SronDouble_t LOG10(SronInt_t val) noexcept
    {
        return std::log10(val);
    }

    //================================================================

    constexpr inline static SronDouble_t SIN(SronDouble_t val) noexcept
    {
        return std::sin(val) ;
    }

    constexpr inline static SronDouble_t SIN(SronInt_t val) noexcept
    {
        return std::sin(val);
    }

    //================================================================

    constexpr inline static SronDouble_t COS(SronDouble_t val) noexcept
    {
        return std::cos(val) ;
    }

    constexpr inline static SronDouble_t COS(SronInt_t val) noexcept
    {
        return std::cos(val);
    }

    //================================================================

    constexpr inline static SronDouble_t TAN(SronDouble_t val) noexcept
    {
        return std::tan(val) ;
    }

    constexpr inline static SronDouble_t TAN(SronInt_t val) noexcept
    {
        return std::tan(val);
    }

    //================================================================

    constexpr inline static SronInt_t CEIL(SronDouble_t val) noexcept
    {
        return std::ceil(val) ;
    }

    constexpr inline static SronInt_t CEIL(SronInt_t val) noexcept
    {
        return std::ceil(val);
    }

    //================================================================

    constexpr inline static SronInt_t FLOOR(SronDouble_t val) noexcept
    {
        return std::floor(val) ;
    }

    constexpr inline static SronInt_t FLOOR(SronInt_t val) noexcept
    {
        return std::floor(val);
    }

    //================================================================

}

#endif