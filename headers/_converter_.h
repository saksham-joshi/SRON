#include<string>
#include<iostream>
#include "_utility_.h"
#include "_exception_.h"

struct TypeConversionError : public std::exception{
    const char* what() const throw(){
        return "Exception Caught :\n > Error while Converting datatypes ";
    }
};

/*
The converter Class provides conversion from one datatype to another
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

class Converter{

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
        catch (const std::exception)
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
        catch(const std::exception){
            DISPLAY_EXCEPTION("conversion of String type to Double.",13);
        }
        return 0;
    }
    inline static double TODOUBLE(long long int i){
        try{
            double d = (double)i;
            return d;
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("conversion of Int type to Double.",17);
        }
        return 0;
    }
    inline static double TODOUBLE(double d){
        return d;
    }

    //=========| TOSTRING |=========//
    inline static std::string TOSTRING(long long int i){
        return std::to_string(i);
    }
    inline static std::string TOSTRING(double d){
        return std::to_string(d);
    }
    inline static std::string ToSTRING(std::string i){
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
            long long int val = 0;
            for(std::string::iterator it = str.begin(); it != str.end(); ++it){
                int ascii = (int)*it;
                if(ascii >=48 && ascii <=57){
                    val = (val*10)+(ascii-48 );
                    continue;
                }
                DISPLAY_EXCEPTION("conversion of String type to Int.",17);
            }
            return val;
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("conversion of String type to Int.",17);
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
        catch(const std::exception){
            DISPLAY_EXCEPTION("conversion of Char type to Int.",17);
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
            if(str == "TRUE"){ 
                return true;
            }
            else if(str == "FALSE"){
                return false;
            }
            throw TypeConversionError();
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("conversion of String type to Bool.",17);
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
    ~Converter(){ }
};