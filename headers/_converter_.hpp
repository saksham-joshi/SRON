#include<string>
#include<iostream>
#include "_utility_.hpp"
#include "_rectifier_.hpp"
#include "Argument_List.hpp"

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

#ifndef CONVERTER_H
#define CONVERTER_H

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
                throw ThrowException();
            }
        }
        catch (const std::exception)
        {
            DISPLAY_EXCEPTION("conversion of datatypes.",13);
        }
        return -1;
    }

public :

    //=======================================================================| ToDOUBLE |=========//
    inline static double TODOUBLE(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return TODOUBLE(args.GET_INT(0));
        }
        else if(type == "String"){
            return TODOUBLE(args.GET_STRING(0));
        }
        else if(type == "Double"){
            return args.GET_DOUBLE(0);
        }
        DISPLAY_EXCEPTION("conversion of passed argument type to Double.",23);
        return 0;
    }
    inline static double TODOUBLE(std::string i){
        try{
            /* checking if it can be converted to double because stod function doesn't throw exception 
             * if the character after the first character is not a number. */
            for(auto it = i.begin(); it != i.end(); ++it){
                if(*it == '.' || ( (int)*it >=48 && (int)*it <= 57 )){
                    continue;
                }
                DISPLAY_EXCEPTION("conversion of String type to Double.",13);
            }
            return std::stod(i);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("conversion of String type to Double.",13);
        }
        return 0;
    }
    inline static double TODOUBLE(long long int i){
        try{
            return (double)i;
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("conversion of Int type to Double.",17);
        }
        return 0;
    }
    inline static double TODOUBLE(double d){
        return d;
    }

    //=====================================================================| TOSTRING |=========//
    inline static std::string TOSTRING(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "Int"){
            return TOSTRING(args.GET_INT(0));
        }
        else if(type == "Double"){
            return TOSTRING(args.GET_DOUBLE(0));
        }
        else if(type == "String"){
            return args.GET_STRING(0);
        }
        else if(type == "Bool"){
            return TOSTRING(args.GET_BOOL(0));
        }
        else if(type == "Char"){
            return TOSTRING(args.GET_CHAR(0));
        }
        DISPLAY_EXCEPTION("conversion of other types to String.",23);
        return " ";
    }
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
    
    //========================================================================| ToINT |=========//
    inline static long long int TOINT(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "String"){
            return TOINT(args.GET_STRING(0));
        }
        else if(type == "Double"){
            return TOINT(args.GET_DOUBLE(0));
        }
        else if(type == "Char"){
            return TOINT(args.GET_CHAR(0));
        }
        else if(type == "Bool"){
            return TOINT(args.GET_BOOL(0));
        }
        else if(type == "Int"){
            return args.GET_INT(0);
        }
        DISPLAY_EXCEPTION("conversion of other types to Int.",23);
        return 0;
    }
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
        catch(const std::exception&){
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
            throw ThrowException();
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

    //=========================================================================| ToBOOL |=========//
    inline static bool TOBOOL(ArgumentList& args){
        std::string type = args.GET_TYPE(0);
        if(type == "String"){
            return TOBOOL(args.GET_STRING(0));
        }
        else if(type == "Int"){
            return TOBOOL(args.GET_INT(0));
        }
        else if(type == "Double"){
            return TOBOOL(args.GET_DOUBLE(0));
        }
        else if(type == "Bool"){
            return args.GET_BOOL(0);
        }
        DISPLAY_EXCEPTION("conversion of other types to Bool.",23);
        return false;
    }
    inline static bool TOBOOL(std::string str){
        try{
            if(str == "true"){ 
                return true;
            }
            else if(str == "false"){
                return false;
            }
            throw ThrowException();
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("conversion of String type to Bool.",17);
        }
        return false;
    }
    inline static bool TOBOOL(long long int i){
        return (i>0);
    }
    inline static bool TOBOOL(double d){
        return (d>0);
    }
    inline static bool TOBOOL(bool b){
        return b;
    }
    ~Converter(){ }
};

#endif