/*
 * This HashTable implementation will be used to declare and store variables, in other words ,for variable and memory managment.
 * Also allow developers to free up memory at runtime which eventually increase the speed of the program at whole another level.
 */

#include<vector>
#include<map>
#include<iostream>
#include<algorithm>
#include "_exception_.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

using namespace std;

struct String_and_Int{
    string str;
    int index;
    String_and_Int(string str , int index){
        this->str = str;
        this->index = index;
    }
};


class HashTable{
    private :
    std::map<std::string,long long int> IntMap;
    std::map<std::string,double> DoubleMap;
    std::map<std::string,char> CharMap;
    std::map<std::string,std::string> StringMap;
    std::map<std::string,bool> BoolMap;
    std::map<std::string,std::vector<std::string>> VectorStringMap;
    std::map<std::string,std::vector<long long int>> VectorIntMap;
    std::map<std::string,std::vector<double>> VectorDoubleMap;
    std::map<std::string,std::vector<char>> VectorCharMap;
    std::map<std::string,std::vector<bool>> VectorBoolMap;
    
    //std::vector<std::string> variable_list;
    std::map<std::string , std::string> variable_map;

    void CHECK_IF_ELEMENT_EXIST(std::string str){
        if(variable_map.end() != variable_map.find(str)){
            DISPLAY_EXCEPTION( "creating a variable." , 9);
        }
    }

    string CHECK_IF_ELEMENT_EXIST_NOEXCEPTION(string str){
        auto i = variable_map.find(str);
        if(variable_map.end() == i ){
            return " ";
        }
        return i->second;
    }
    
    /*
    *                  Insert function Implementation
    * This function will be used to create variables of basic datatypes like Int, Double, Char, String, Bool and their Vectors.
    */
    void INSERT(std::string str , long long int val=0){
        CHECK_IF_ELEMENT_EXIST(str);
        IntMap[str] = val;
        variable_map[str] = "Int";
    }
    void INSERT(std::string str , double val=0){
        CHECK_IF_ELEMENT_EXIST(str);
        DoubleMap[str] = val;
        variable_map[str] = "Double";
    }
    void INSERT(std::string str , char val=' '){
        CHECK_IF_ELEMENT_EXIST(str);
        CharMap[str] = val;
        variable_map[str] = "Char";
    }
    void INSERT(std::string str , std::string val=""){
        CHECK_IF_ELEMENT_EXIST(str);
        StringMap[str] = val;
        variable_map[str] = "String";
    }
    void INSERT(std::string str , bool val=false){
        CHECK_IF_ELEMENT_EXIST(str);
        BoolMap[str] = val;
        variable_map[str] = "Bool";
    }
    void INSERT(std::string str , std::vector<std::string> vec){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorStringMap[str] = vec;
        variable_map[str] = "String[]";
    }
    void INSERT(std::string str , std::vector<long long int> vec){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorIntMap[str] = vec;
        variable_map[str] = "Int[]";
    }
    void INSERT(std::string str , std::vector<double> vec){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorDoubleMap[str] = vec;
        variable_map[str] = "Double[]";
    }
    void INSERT(std::string str , std::vector<char> vec){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorCharMap[str] = vec;
        variable_map[str] = "Char[]";
    }
    void INSERT(std::string str , std::vector<bool> vec){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorBoolMap[str] = vec;
        variable_map[str] = "Bool[]";
    }

    /*
    *                  Update function Implementation
    * This function will be implemented for = operator when developer wants to update or assign value of a particular variable
    */

    void UPDATE(std::string str , long long int val){
        CHECK_IF_ELEMENT_EXIST(str);
        IntMap[str] = val;
    }
    void UPDATE(std::string str , double val){
        CHECK_IF_ELEMENT_EXIST(str);
        DoubleMap[str] = val;
    }
    void UPDATE(std::string str , std::string val){
        CHECK_IF_ELEMENT_EXIST(str);
        StringMap[str] = val;
    }
    void UPDATE(std::string str , char val){
        CHECK_IF_ELEMENT_EXIST(str);
        CharMap[str] = val;
    }
    void UPDATE(std::string str , bool val){
        CHECK_IF_ELEMENT_EXIST(str);
        BoolMap[str] = val;
    }
    void UPDATE(std::string str , std::vector<long long int> val ){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorIntMap[str] = val;
    }
    void UPDATE(std::string str , std::vector<double> val ){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorDoubleMap[str] = val;
    }
    void UPDATE(std::string str , std::vector<std::string> val ){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorStringMap[str] = val;
    }
    void UPDATE(std::string str , std::vector<char> val ){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorCharMap[str] = val;
    }
    void UPDATE(std::string str , std::vector<bool> val ){
        CHECK_IF_ELEMENT_EXIST(str);
        VectorBoolMap[str] = val;
    }


    public :
    /*
     *                  Free function Implementation
     * This functionality will allow developers of clear up memory at runtime
     */
    void FREE(string str){
        auto i = variable_map.find(str);
        if( i != variable_map.end()){
            string variable_type = i->second;
            variable_map.erase(i);

            if(variable_type == "Int"){ IntMap.erase(str); }
            else if(variable_type == "Double"){ DoubleMap.erase(str); }
            else if(variable_type == "Char"){ CharMap.erase(str); }
            else if(variable_type == "String"){ StringMap.erase(str); }
            else if(variable_type == "Bool"){ BoolMap.erase(str); }
            else if(variable_type == "Int[]"){ VectorIntMap.erase(str); }
            else if(variable_type == "Double[]"){ VectorDoubleMap.erase(str); }
            else if(variable_type == "Char[]"){ VectorCharMap.erase(str); }
            else if(variable_type == "String[]"){ VectorStringMap.erase(str); }
            else if(variable_type == "Bool[]"){ VectorBoolMap.erase(str); }

            return;
        }
        DISPLAY_EXCEPTION("freeing up the variable.",10);
    }

    /*
    *              GET function implementation
    * this function allows you to get a value from the hashtable . basically it allows the developers to extract the value from a variable name
    */
    long long int GET_INT(const std::string str){
        try{
            return IntMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an element of Int type.",10);
            exit(1);
        }
    }
    double GET_DOUBLE(const std::string str){
        try{
            return DoubleMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an element of Double type.",10);
            exit(1);
        }
    }
    char GET_CHAR(const std::string str){
        try{
            return CharMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an element of Char type.",10);
            exit(1);
        }
    }
    std::string GET_STRING(const std::string str ){
        try{
            return StringMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an element of String type.",10);
            exit(1);
        }
    }
    bool GET_BOOL(const std::string str){
        try{
            return BoolMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an element of Bool type.",10);
            exit(1);
        }
    }
    std::vector<long long int> GET_INT_VECTOR(const std::string str){
        try{
            return VectorIntMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an Vector of Int type.",10);
            exit(1);
        }
    }
    std::vector<double> GET_DOUBLE_VECTOR(const std::string str){
        try{
            return VectorDoubleMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an Vector of Double type.",10);
            exit(1);
        }
    }
    std::vector<char> GET_CHAR_VECTOR(const std::string str){
        try{
            return VectorCharMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an Vector of Char type.",10);
            exit(1);
        }
    }
    std::vector<std::string> GET_STRING_VECTOR(const std::string str){
        try{
            return VectorStringMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an Vector of String type.",10);
            exit(1);
        }
    }
    std::vector<bool> GET_BOOL_VECTOR(const std::string str){
        try{
            return VectorBoolMap.at(str);
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("extracting an Vector of Bool type.",10);
            exit(1);
        }
    }
    ~HashTable(){ }

    //friend int main();
    friend int main(int argc , char **argv);
};

#endif
// int main(){

//     HashTable h1;
//     h1.INSERT("a1",true);
//     string vari = "a1";
//     cout<<h1.GET_BOOL(vari);
    
// }
