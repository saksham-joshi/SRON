#include <cmath>
#include<string>
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

    inline static double ABS(double val){
        return (val < 0) ? -val : val;
    }

    inline static long long int ABS(long long int val){
        return (val < 0) ? -val : val;
    }

    //================================================================

    inline static double MAX(double val1, double val2){
        return (val1 > val2) ? val1 : val2;
    }

    inline static long long int MAX(long long int val1, long long int val2){
        return (val1 > val2) ? val1 : val2;
    }

    inline static char MAX(char val1, char val2){
        return (val1 > val2) ? val1 : val2;
    }

    inline static std::string& MAX(std::string val1, std::string val2){
        return (val1 > val2) ? val1 : val2;
    }

    //================================================================

    inline static double MIN(double val1, double val2){
        return (val1 < val2) ? val1 : val2;
    }

    inline static long long int MIN(long long int val1, long long int val2){
        return (val1 < val2) ? val1 : val2;
    }

    inline static char MIN(char val1, char val2){
        return (val1 < val2) ? val1 : val2;
    }

    inline static std::string& MIN(std::string val1, std::string val2){
        return (val1 < val2) ? val1 : val2;
    }

    //================================================================

    inline static double SQRT(double val){
        return std::sqrt(val) ;
    }

    inline static double SQRT(long long int val){
        return std::sqrt(val);
    }

    //================================================================

    inline static double CBRT(double val){
        return std::cbrt(val) ;
    }

    inline static double CBRT(long long int val){
        return std::cbrt(val);
    }

    //================================================================

    inline static double LOG(double val){
        return std::log(val) ;
    }

    inline static double LOG(long long int val){
        return std::log(val);
    }

    //================================================================

    inline static double LOG2(double val){
        return std::log2(val) ;
    }

    inline static double LOG2(long long int val){
        return std::log2(val);
    }

    //================================================================

    inline static double LOG10(double val){
        return std::log10(val) ;
    }

    inline static double LOG10(long long int val){
        return std::log10(val);
    }

    //================================================================

    inline static double SIN(double val){
        return std::sin(val) ;
    }

    inline static double SIN(long long int val){
        return std::sin(val);
    }

    //================================================================

    inline static double COS(double val){
        return std::cos(val) ;
    }

    inline static double COS(long long int val){
        return std::cos(val);
    }

    //================================================================

    inline static double TAN(double val){
        return std::tan(val) ;
    }

    inline static double TAN(long long int val){
        return std::tan(val);
    }

    //================================================================

    inline static long long int CEIL(double val){
        return std::ceil(val) ;
    }

    inline static long long int CEIL(long long int val){
        return std::ceil(val);
    }

    //================================================================

    inline static long long int FLOOR(double val){
        return std::floor(val) ;
    }

    inline static long long int FLOOR(long long int val){
        return std::floor(val);
    }

    //================================================================

}

#endif