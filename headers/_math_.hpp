#include <cmath>
#include<vector>
#include "_argument_list_.hpp"
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
    //===========================================================================|  implementing absolute value
    inline static double ABSOLUTE(const double i)
    {
        return abs(i);
    }
    inline static long long int ABSOLUTE(const long long int i)
    {
        return abs(i);
    }

    inline static long double NEGATE(const long double i){
        return -i;
    }
    inline static long long int NEGATE(const long long int i)
    {
        return -i;
    }

    //===========================================================================|  implementing MAX value
    
    template<typename t> inline static t MAX(const std::vector<t>& vec){
        try{
            if(vec.size() != 0){
                t max = vec[0];
                for(typename std::vector<t>::const_iterator it = vec.begin()+1 ; it != vec.end() ; ++it){
                    max = (max < *it)? *it : max;
                }
                return max;
            }
            throw ThrowException();
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("finding the maximum value from a vector. If you haven't passed similar types of arguments, this exception could be one of the reasons.",7);
        }
        return vec[0];
    }

    inline static Collection MAX(ArgumentList& args){
        std::string type = args.GET_TYPE(0);

        if(type == "Int[]"){
            return MAX(args.GET_INT_VECTOR(0));
        }
        else if(type == "Double[]"){
            return MAX(args.GET_DOUBLE_VECTOR(0));
        }
        else if(type =="String[]"){
            return MAX(args.GET_STRING_VECTOR(0));
        }

        DISPLAY_EXCEPTION("finding the maximum value from passed argument.",23);
        return 0;
    }

    // //===========================================================================|  implementing MIN value
    template<typename t> inline static t MIN(const std::vector<t>& vec){
        try{
            if(vec.size() != 0){
                t min = vec[0];
                for(typename std::vector<t>::const_iterator it = vec.begin()+1 ; it != vec.end() ; ++it){
                    min = (min<*it)?min:*it;
                }
                return min;
            }
            throw ThrowException() ;
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("finding the minimum value from a vector. If you haven't passed similar types of arguments, this exception could be one of the reasons.",7);
        }
        return vec[0]; 
    }
    inline static Collection MIN(ArgumentList& args){
        std::string type = args.GET_TYPE(0); 
        if(type == "Int[]" ){
            return MIN(args.GET_INT_VECTOR(0));
        }
        else if(type == "Double[]"){
            return MIN(args.GET_DOUBLE_VECTOR(0));
        }
        else if(type == "String[]"){
            return MIN(args.GET_STRING_VECTOR(0));
        }
        DISPLAY_EXCEPTION("finding the minimum value from passed argument.",23);
        return 0;
    }

    //===========================================================================|  implementing Square Root function
    inline static Collection SQRT(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return sqrt((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return sqrt(args.GET_DOUBLE(0));
        }
        DISPLAY_EXCEPTION("calculating the Square root of passed argument.",23);
        return 0;
    }
    inline static double SQRT(const double i)
    {
        return sqrt(i);
    }
    inline static double SQRT(const long long int i)
    {
        return sqrt((double)i);
    }

    //===========================================================================|  implementing Cube Root function
    inline static Collection CBRT(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return cbrt((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return cbrt(args.GET_DOUBLE(0));                                                                                                                                                                                                                                                    
        }
        DISPLAY_EXCEPTION("calculating the Cube root of passed argument.",23);
    }
    inline static double CBRT(const double i)
    {
        return cbrt(i);
    }
    inline static double CBRT(const long long int i)
    {
        return cbrt((double)i);
    }

    //===========================================================================|  implementing log base 10 function
    inline static Collection LOG10(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return log10((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return log10(args.GET_DOUBLE(0));
        }
        DISPLAY_EXCEPTION("calculating the Log10 of the passes argument.",23);
        return 0;
    }
    inline static double LOG10(const double i)
    {
        return log10(i);
    }
    inline static double LOG10(const long long int i)
    {
        return log10((double)i);
    }

    //===========================================================================| implmenting log function
    inline static Collection LOG(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return log((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return log(args.GET_DOUBLE(0));
        }
        DISPLAY_EXCEPTION("calculating the Log of the passes argument.",23);
        return 0;
    }
    inline static double LOG(const double i)
    {
        return log(i);
    }
    inline static double LOG(const long long int i)
    {
        return log((double)i);
    }

    //===========================================================================| implementing log base 2 function
    inline static Collection LOG2(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return log2((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return log2(args.GET_DOUBLE(0));
        }
        DISPLAY_EXCEPTION("calculating the Log2 of the passes argument.",23);
        return 0;
    }
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

    //===========================================================================|| SIN |=====//
    inline static Collection SIN(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return sin((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return sin(args.GET_DOUBLE(0));
        }
        DISPLAY_EXCEPTION("calculating the sin of the passes argument.",23);
        return 0;
    }
    inline static double SIN(const double d)
    {
        return sin(d);
    }
    inline static double SIN(const long long int d)
    {
        return sin((double)d);
    }

    //===========================================================================|| COS |=====//
    inline static Collection COS(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return cos((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return cos(args.GET_DOUBLE(0));
        }
        DISPLAY_EXCEPTION("calculating the cos of the passes argument.",23);
        return 0;
    }
    inline static double COS(const double d)
    {
        return cos(d);
    }
    inline static double COS(const long long int d)
    {
        return cos((double)d);
    }

    //===========================================================================|| TAN |=====//
    inline static Collection TAN(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return tan((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return tan(args.GET_DOUBLE(0));
        }
        DISPLAY_EXCEPTION("calculating the tan of the passes argument.",23);
        return 0;
    }
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
    inline static Collection CEIL(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return (long long int)ceil((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return ceil(args.GET_DOUBLE(0));
        }
        DISPLAY_EXCEPTION("calculating the ceil of the passes argument.",23);
        return 0;
    }
    inline static long long int CEIL(double d)
    {
        return ((long long int)ceil(d));
    }

    inline static Collection FLOOR(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return (long long int)floor((double)args.GET_INT(0));
        }
        else if(type == "Double"){
            return floor(args.GET_DOUBLE(0));
        }
        DISPLAY_EXCEPTION("calculating the floor of the passes argument.",23);
        return 0;
    }
    inline static long long int FLOOR(double d)
    {
        return ((long long int)floor(d));
    }

    ~Math(){ }
};