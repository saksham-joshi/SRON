#include<iostream>
#include<vector>
#include<variant>
#include "_exception_.h"

#ifndef ARGUMENT_LIST_H
#define ARGUMENT_LIST_H

class ArgumentList{

    std::vector<std::variant<long long int, double, char, bool, std::string, std::vector<long long int>, std::vector<double>, std::vector<char>, std::vector<bool>, std::vector<std::string>>> vec;

    public :

    /*
     * This function returns the argument and it also throws exceptions whenever
     * a wrong value is returned.
    */
    inline long long int GET_INT(int index){ 
        try{
            if(index >= vec.size()){
                throw " " ;
            }
            else if(std::holds_alternative<long long int>(vec[index]) ){
                return std::get<long long int>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Int.",23);
            }
        }
        catch(const char *){
            DISPLAY_EXCEPTION("extracting the passes argument of type Int.",23);
        }
        return 0;
    }
    inline double GET_DOUBLE(int index){
        try{
            if(index >= vec.size()){
                throw " ";
            }
            else if(std::holds_alternative<double>(vec[index]) ){
                return std::get<double>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Double.",23);
            }
        }
        catch(const char *){
            DISPLAY_EXCEPTION("extracting the passes argument of type Double.",23);
        }
        return 0;
    }
    inline char GET_CHAR(int index){
        try{
            if(index >= vec.size()){
                throw " ";
            }
            else if(std::holds_alternative<char>(vec[index]) ){
                return std::get<char>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Char.",23);
            }
        }
        catch(const char *){
            
        }
        return ' ' ;
    }
    inline bool GET_BOOL(int index){
        try{
            if(index >= vec.size()){
                throw " ";
            }
            else if(std::holds_alternative<bool>(vec[index]) ){
                return std::get<bool>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Bool.",23);
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("extracting the passes argument of type Bool.",23);
        }
        return false;
    }
    inline std::string GET_STRING(int index){
        try{
            if(index >= vec.size()){
                throw " ";
            }
            else if(std::holds_alternative<std::string>(vec[index]) ){
                return std::get<std::string>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type String.",23);
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("extracting the passes argument of type String.",23);
        }
        return " ";
    }

    inline std::vector<long long int> GET_INT_VECTOR(int index){
        try{
            if(index >= vec.size()){
                throw " ";
            }
            else if(std::holds_alternative<std::vector<long long int>>(vec[index]) ){
                return std::get<std::vector<long long int>>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Int[].",23);
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("extracting the passes argument of type Int[].",23);
        }
    }
    inline std::vector<double> GET_DOUBLE_VECTOR(int index){
        try{
            if(index >= vec.size()){
                throw " ";
            }
            else if(std::holds_alternative<std::vector<double>>(vec[index]) ){
                return std::get<std::vector<double>>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Double[].",23);
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("extracting the passes argument of type Double[].",23);
        }
    }
    inline std::vector<char> GET_CHAR_VECTOR(int index){
        try{
            if(index >= vec.size()){
                throw " ";
            }
            else if(std::holds_alternative<std::vector<char>>(vec[index]) ){
                return std::get<std::vector<char>>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Char[].",23);
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("extracting the passes argument of type Char[].",23);
        }
    }
    inline std::vector<bool> GET_BOOL_VECTOR(int index){
        try{
            if(index >= vec.size()){
                throw " ";
            }
            else if(std::holds_alternative<std::vector<bool>>(vec[index]) ){
                return std::get<std::vector<bool>>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Bool[].",23);
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("extracting the passes argument of type Bool[].",23);
        }
    }
    inline std::vector<std::string> GET_STRING_VECTOR(int index){
        try{
            if(index >= vec.size()){
                throw " ";
            }
            else if(std::holds_alternative<std::vector<std::string>>(vec[index]) ){
                return std::get<std::vector<std::string>>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type String[].",23);
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("extracting the passes argument of type String[].",23);
        }
    }

    /*
     * This function is used to input the values to the argument list.
     * 
    */
    inline void PUT(long long int val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("passing the Int type argument to the function.",3);
        }
    }
    inline void PUT(double val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("passing the Double type argument to the function.",3);
        }
    }
    inline void PUT(char val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("passing the Char type argument to the function.",3);
        }
    }
    inline void PUT(bool val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("passing the Bool type argument to the function.",3);
        }
    }
    inline void PUT(std::string val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("passing the String type argument to the function.",3);
        }
    }
    inline void PUT(std::vector<long long int> val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("passing the Int[] type argument to the function.",3);
        }
    }
    inline void PUT(std::vector<double> val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("passing the Double[] type argument to the function.",3);
        }
    }
    inline void PUT(std::vector<char> val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("passing the Char[] type argument to the function.",3);
        }
    }
    inline void PUT(std::vector<bool> val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("passing the Bool[] type argument to the function.",3);
        }
    }
    inline void PUT(std::vector<std::string> val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("passing the String[] type argument to the function.",3);
        }
    }
};

#endif