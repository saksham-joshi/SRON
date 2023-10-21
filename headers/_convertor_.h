#include<string>
#include<iostream>
#include "_utility_.h"
#include "_exception_.h"

using namespace std;

struct TypeConversionError : public std::exception{
    const char* what() const throw(){
        return "Exception Caught :\n > Error while Converting datatypes ";
    }
};

/*
The Convertor Class provides conversion from one datatype to another
It includes functions :
    1. string to double
    2. bool to double
    3. int to double
    4. double to double
    
    5. int to string
    6. double to string
    7. char to string
    8. bool to string
    9. string to string

    10. string to int
    11. double to int
    12. char to int
    13. bool to int

    14. string to bool
    15. int to bool
    16. double to bool
*/

class Convertor{

private:
    inline static std::string TOUPPERCASE(std::string str){
        for(int i=0;i<str.length();++i){
            str[i] = toupper(str[i]);
        }
        return str;
    }
    inline static double get_number_from_char(char ch){
        try{
            int ascii = (int)ch;
            if(ascii>=48 && ascii <= 57){
                return ascii-48;
            }
            else{
                throw TypeConversionError();
                exit(1);
            }
        }
        catch (std::exception e)
        {
            DISPLAY_EXCEPTION("conversion of datatypes.",13);
        }
        return -1;
    }

public :

    //=========| ToDOUBLE |=========//
    inline static double TODOUBLE(std::string i){
        try{
            double d = std::stod(i);
            return d;
        }
        catch(std::exception e){
            // printf("\nException Caught :\n > While Conversion of string type to double.\n\t> Reason : You input Invalid Characters.\n\t> Solution : Store only numbers(positive & negative) and decimal point in your string.");
            // exit(1);
            DISPLAY_EXCEPTION("conversion of String type to Double.",13);
        }
        return 0;
    }
    inline static double TODOUBLE(long long int i){
        try{
            double d = (double)i;
            return d;
        }
        catch(std::exception e){
            printf("\nException Caught :\n > While Conversion of Int type TO Double.\n\t> Reason : You input Invalid Characters.\n\t> Solution : Store only numbers(positive & negative) and decimal point in your string.");
            exit(1);
        }
        return 0;
    }
    inline static double TODOUBLE(double d){
        return d;
    }

    //=========| TOSTRING |=========//
    inline static std::string TOSTRING(long long int i){
        return to_string(i);
    }
    inline static std::string TOSTRING(double d){
        return to_string(d);
    }
    inline static std::string ToSTRING(string i){
        return i;
    }
    inline static std::string TOSTRING(bool b){
        return (b)?"true":"false";
    }
    inline static std::string TOSTRING(char ch){
        return (std::string)""+ch;
    }
    
    //=========| ToINT |=========//
    inline static long long int TOINT(std::string str){
        try{
            long long int i = std::stoll(str);
            return i;
        }
        catch(std::exception e){
            printf("\nException Caught :\n > While Conversion of String type to Int.\n\t> Reason : You input Invalid Characters.\n\t> Solution : Store only numbers(positive & negative) in your string.");
            exit(1);
        }
        return 0;
    }
    inline static long long int TOINT(double d){
        return (long long int)d;
    }
    inline static long long int TOINT(char c){
        try{
            int ascii = (int)c;
            if(ascii>=48 && ascii<=57){
                return (long long int)((int)c)-48;
            }
            throw TypeConversionError();
        }
        catch(std::exception e){
            printf("\nException Caught :\n > While Conversion of Char type to Int.\n\t> Reason : You input Invalid Characters.\n\t> Solution : Store only single-digit in your string.");
            exit(1);
        }
        return 0;
    }
    inline static long long int TOINT(bool b){
        return (b)?1:0;
    }
    inline static long long int TOINT(long long int x){
        return x;
    }

    //=========| ToBOOL |=========//
    inline static bool TOBOOL(std::string str){
        try{
            str = TOUPPERCASE(str);
            if(str == "TRUE") return true;
            else if(str == "FALSE") return false;
            throw TypeConversionError();
        }
        catch(std::exception e){
            printf("\nException Caught :\n > While Conversion of String type to Bool.\n\t> Reason : You input Invalid Characters.\n\t> Solution : Store True and False in any case(upper/lower/camel etc.) in your string.");
            exit(1);
        }
    }
    inline static bool TOBOOL(long long int i){
        return (i>0)?true:false;
    }
    inline static bool ToBOOL(double d){
        return (d>0?true:false);
    }
    inline static bool TOBOOL(bool b){
        return b;
    }
    ~Convertor(){ }
};