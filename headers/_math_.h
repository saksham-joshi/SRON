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
class Math
{
public :
    //====================|  implementing absolute value
    inline static double ABSOLUTE(const double i)
    {
        return abs(i);
    }
    inline static int ABSOLUTE(const long long int i)
    {
        return abs(i);
    }

    //====================|  implementing max value
    inline static double MAX(const double i, const double j)
    {
        return (i > j) ? i : j;
    }
    inline static int MAX(const long long int i, const long long int j)
    {
        return (i > j) ? i : j;
    }

    //====================|  implementing min value
    inline static double MIN(const double i, const double j)
    {
        return (i > j) ? j : i;
    }
    inline static long long int MIN(const long long int i, const long long int j)
    {
        return (i > j) ? j : i;
    }

    //====================|  implementing Square Root function
    inline static double SQRT(const double i)
    {
        return sqrt(i);
    }
    inline static double SQRT(const long long int i)
    {
        return sqrt((double)i);
    }

    //====================|  implementing Cube Root function
    inline static double CBRT(const double i)
    {
        return cbrt(i);
    }
    inline static double CBRT(const long long int i)
    {
        return cbrt((double)i);
    }

    //====================|  implementing log base 10 function
    inline static double LOG10(const double i)
    {
        return log10(i);
    }
    inline static double LOG10(const long long int i)
    {
        return log10((double)i);
    }

    //====================| implmenting log function
    inline static double LOG(const double i)
    {
        return log(i);
    }
    inline static double LOG(const long long int i)
    {
        return log((double)i);
    }

    //====================| implementing log base 2 function
    inline static double LOG2(const double i)
    {
        return log2(i);
    }
    inline static double LOG2(const long long int i)
    {
        return log2((double)i);
    }

    /*
    ===========| implementing trigonometic functions below
        1. Sin
        2. Cos
        3. tan
    */

    //=====| SIN |=====//
    inline static double SIN(const double d)
    {
        return sin(d);
    }
    inline static double SIN(const long long int d)
    {
        return sin((double)d);
    }

    //=====| COS |=====//
    inline static double COS(const double d)
    {
        return cos(d);
    }
    inline static double COS(const long long int d)
    {
        return cos((double)d);
    }

    //=====| TAN |=====//
    inline static double TAN(const double d)
    {
        return tan(d);
    }
    inline static double TAN(const long long int d)
    {
        return tan((double)d);
    }

    /*
    Now, implementation of floor, ceil and round
        1. floor = returns the largest integer that is smaller than or equal to the value passed as the argument (i.e.: rounds down the nearest integer).
        2. ceil = returns the smallest integer that is greater than or equal to the value passed as the argument (i.e.: rounds up the nearest integer).
        3. round = returns the decimal or integer value rounded to x number of decimal places.
    */
    inline static long long int CEIL(double d)
    {
        return ((long long int)ceil(d));
    }
    inline static long long int FLOOR(double d)
    {
        return ((long long int)floor(d));
    }

    ~Math(){ }
};
// implementing eval
// class eval{
// private :
//     string str="";

//     void replacer_checker(){
//         string fin="";
//         for(int i = 0 ; i< str.length() ; i++){
//             try{

//             }
//             catch(exception e){ }

//         }
//         str = fin;
//     }

// public :
//     eval(const string str){
//         this->str = str;
//         replacer_checker();
//     }
// };