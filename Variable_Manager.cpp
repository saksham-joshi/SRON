#include <iostream>
#include <vector>
#include <variant>
#include<map>
#include "headers/_exception_.h"
#include "headers/_converter_.h"

inline static bool CHECK_VALID_VARIABLE_NAME(std::string str)
{
    if (!(str[0] == '_' || isalpha(str[0]) > 0))
    {
        DISPLAY_EXCEPTION("creating a variable.", 2);
    }
    for (std::string::iterator it = str.begin() + 1; it < str.end(); ++it)
    {
        if (!(*it == '_' || isalpha(*it) > 0 || ((int)*it >= 48 && (int)*it <= 57)))
        {
            DISPLAY_EXCEPTION("creating a variable.", 2);
        }
    }
    return true;
}

/*
 * This function will remove the initial single quotes from the string
 * and then takes the char value at 1 as our value if the string is not
 * in the char format then it throws an exception
*/
inline static char string_to_char(std::string value){
    if(value.length() == 3 && value[0]  == '\'' && value[2] == '\''){
        return value[1];
    }
    DISPLAY_EXCEPTION("declaring the variable of type Char.",15);
    return ' ';
}

/* This class will work as a storage of variables and values.
 * It can store values of type long long int, double, char, string and bool renamed as Int, Double, Char, String and Bool respectively in SRON.
 * It uses the map of string and variant. string will store the variable name and variant will store the values.
 */

class VariableManager{
    
    std::map<std::string,std::variant<long long int, double, char, bool, std::string, std::vector<long long int> , std::vector<double> , std::vector<char> , std::vector<bool> , std::vector<std::string>>> Map;

    public :
    std::string function_name;
    VariableManager(std::string function_name){
        this->function_name = function_name;
    }
    /*
     * This function is used to insert a variable    
    */
    inline void INSERT(std::string& type, std::string& variable_name){
        CHECK_VALID_VARIABLE_NAME(variable_name);
        try{
            if(type == "Int"){ 
                Map[variable_name] = (long long int)0;
            }
            else if(type == "Double"){
                Map[variable_name] = (double)0;
            }
            else if(type == "Char"){
                Map[variable_name] = ' ';
            }
            else if(type == "Bool"){
                Map[variable_name] = false;
            }
            else if(type == "String"){
                Map[variable_name] = " ";
            }
            else if(type == "Int[]"){
                std::vector<long long int> vec;
                Map[variable_name] = vec ;
            }
            else if(type == "Double[]"){
                std::vector<double> vec;
                Map[variable_name] = vec ;
            }
            else if(type == "Char[]"){
                std::vector<char> vec;
                Map[variable_name] = vec ;
            }
            else if(type == "Bool[]"){
                std::vector<bool> vec;
                Map[variable_name] = vec ;
            }
            else if(type == "String[]"){
                std::vector<std::string> vec;
                Map[variable_name] = vec ;
            }
            else{
                DISPLAY_EXCEPTION("validating the type of variable.", 20);
            }
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("executing the variable attribute.",3);
        }
        
    }
    inline void INSERT(std::string& type, std::string& variable_name , std::string& value){
        CHECK_VALID_VARIABLE_NAME(variable_name);
        try{
            if(type == "Int"){
                Map[variable_name] = Converter::TOINT(value);
                return;
            }
            else if(type == "Double"){
                Map[variable_name] = Converter::TODOUBLE(value);
                return;
            }
            else if(type == "String"){
                if(value.length() >=2 && value[0] == '\"' && value[value.length()-1] == '\"'){
                    if(value.length() == 2){
                        Map[variable_name] = (std::string)"";
                    }
                    else{
                        Map[variable_name] = value.substr(1,value.length()-2);
                    } 
                    return;
                }
                DISPLAY_EXCEPTION("declaring the variables of type String",15);
            }
            else if(type == "Char"){
                if(value.length() == 3 && value[0]  == '\'' && value[2] == '\''){
                    Map[variable_name] = value[1];
                    return;
                }
                DISPLAY_EXCEPTION("declaring the variable of type Char",15);
            }
            else if(type == "Bool"){
                if(value == "true" && value == "false"){
                    Map[variable_name] = value;
                    return;
                }
                DISPLAY_EXCEPTION("declaring the variable of type Bool",15);
            }
            else{
                DISPLAY_EXCEPTION("validating the type of variable.", 20);
            }
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("executing the variable attribute.",3);
        }
    }

    /*
     * This function will be used to add variables containing vector values.
     * It takes the subvector of the vector gained after lexical analysis.
     */
    inline void INSERT(std::string& type, std::string& variable_name, std::vector<std::string> vec){
        try{
            if(type == "Int[]"){
                std::vector<long long int> fin;
                for(std::vector<std::string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    fin.push_back(Converter::TOINT(*i));
                }
                Map[variable_name] = fin;
                return;
            }
            else if(type == "Double[]"){
                std::vector<double> fin;
                for(std::vector<std::string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    fin.push_back(Converter::TODOUBLE(*i));
                }
                Map[variable_name] = fin;
                return;
            }
            else if(type == "Char[]"){
                std::vector<char> fin;
                for(std::vector<std::string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    fin.push_back(string_to_char(*i));
                }
                Map[variable_name] = fin;
                return;
            }
            else if(type == "Bool[]"){
                std::vector<bool> fin;
                for(std::vector<std::string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    fin.push_back(Converter::TOBOOL(*i));
                }
                Map[variable_name] = fin;
                return;
            }
            else if(type == "String[]"){
                std::vector<std::string> fin;
                for(std::vector<std::string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    std::string temp = *i;
                    if(temp.length() == 2 && temp[0] == '\"' && temp[1] == '\"'){
                        fin.push_back((std::string)"" );
                    }
                    else if(temp.length()>=2 && temp[0] == '\"' && temp[temp.length()-1] == '\"'){    
                        fin.push_back(temp.substr(1,temp.length()-2));
                    }
                    else{
                        DISPLAY_EXCEPTION("declaring a variable of String Vector type.",21);
                    }
                }
                Map[variable_name] = fin;
                return;
            }
            else{
                DISPLAY_EXCEPTION("validating the type of variable.", 20);
            }
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("executing the variable attribute.",3);
        }  
    }

    inline long long int GET_INT(std::string variable_name){
        try{
            return std::get<long long int>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type Int.",10);
        }
        return 0;
    }
    inline double GET_DOUBLE(std::string variable_name){
        try{
            return std::get<double>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type Double.",10);
        }
        return 0;
    }
    inline char GET_CHAR(std::string variable_name){
        try{
            return std::get<char>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type Char.",10);
        }
        return ' ';
    }
    inline bool GET_BOOL(std::string variable_name){
        try{
            return std::get<bool>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type Bool.",10);
        }
        return false;
    }
    inline std::string GET_STRING(std::string variable_name){
        try{
            return std::get<std::string>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type String.",10);
        }
        return (std::string)"";
    }
    inline std::vector<long long int> GET_INT_VECTOR(std::string variable_name){
        try{
            return std::get<std::vector<long long int>>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type Int[].",10);
        }
    }
    inline std::vector<double> GET_DOUBLE_VECTOR(std::string variable_name){
        try{
            return std::get<std::vector<double>>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type Double[].",10);
        }
    }
    inline std::vector<char> GET_CHAR_VECTOR(std::string variable_name){
        try{
            return std::get<std::vector<char>>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type Char[].",10);
        }
    }
    inline std::vector<bool> GET_BOOL_VECTOR(std::string variable_name){
        try{
            return std::get<std::vector<bool>>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type Bool[].",10);
        }
    }
    inline std::vector<std::string> GET_STRING_VECTOR(std::string variable_name){
        try{
            return std::get<std::vector<std::string>>(Map.at(variable_name));
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("getting the value from variable of type String[].",10);
        }
    }
    
    /*
     * Free Method allows users to free up memory on runtime to boost performance and decrease memory usage.
     * This method is not directly called by the user but the function
    */
    inline void FREE(std::string variable_name){
        try{
            Map.erase(variable_name);
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("freeing up the memory usage.",10);
        }
    }
    inline std::string TYPE(std::string variable_name){
        try{
            const auto& element = Map.at(variable_name);
            if(std::holds_alternative<long long int>(element)){
                return "Int";
            }
            else if(std::holds_alternative<double>(element)){
                return "Double";
            }
            else if(std::holds_alternative<char>(element)){
                return "Char";
            }
            else if(std::holds_alternative<bool>(element)){
                return "Bool";
            }
            else if(std::holds_alternative<std::string>(element)){
                return "String";
            }
            else if(std::holds_alternative<std::vector<long long int>>(element)){
                return "Int[]";
            }
            else if(std::holds_alternative<std::vector<double>>(element)){
                return "Double[]";
            }
            else if(std::holds_alternative<std::vector<char>>(element)){
                return "Char[]";
            }
            else if(std::holds_alternative<std::vector<bool>>(element)){
                return "Bool[]";
            }
            else if(std::holds_alternative<std::vector<std::string>>(element)){
                return "String[]";
            }
            else{
                DISPLAY_EXCEPTION("finding the type of given element.",22);
            }
        }
        catch(const std::exception){
            DISPLAY_EXCEPTION("accessing a given variable.",10);
        }
        return (std::string)"";
    }
};

int main() {

    VariableManager vm("main") ;
    std::string type = "Int";
    std::string variable_name = "_";
    std::string value = "123";
    vm.INSERT(type,variable_name,value);
    std::cout<<vm.GET_INT(variable_name);





    // std::vector<std::variant<std::string, bool, char, int, double>> myVector;

    // myVector.push_back("Hello, World!"); // string
    // myVector.push_back(true); // bool
    // myVector.push_back("Ehllo");
    // myVector.push_back('A'); // char
    // myVector.push_back(42); // int
    // myVector.push_back(3.14); // double
    

    // // for (const auto& element : myVector) {
    // //     if (std::holds_alternative<std::string>(element)) {
    // //         std::cout << std::get<std::string>(element) << std::endl;
    // //     } else if (std::holds_alternative<bool>(element)) {
    // //         std::cout << std::get<bool>(element) << std::endl;
    // //     } else if (std::holds_alternative<char>(element)) {
    // //         std::cout << std::get<char>(element) << std::endl;
    // //     } else if (std::holds_alternative<int>(element)) {
    // //         std::cout << std::get<int>(element) << std::endl;
    // //     } else if (std::holds_alternative<double>(element)) {
    // //         std::cout << std::get<double>(element) << std::endl;
    // //     }
    // // }
    // try{
    //     std::cout<<std::get<std::string>(myVector[1]);
    // }
    // catch(const std::exception){
    //     std::cout<<"Invalid";
    // }
    

    // return 0;
}
