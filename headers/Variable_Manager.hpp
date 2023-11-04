#include "_Collections_.hpp"
#include <map>
#include "_converter_.hpp"

#ifndef Variable_Manager_H
#define Variable_Manager_H

inline static bool CHECK_VALID_VARIABLE_NAME(string str)
{
    if (!(str[0] == '_' || isalpha(str[0]) > 0))
    {
        DISPLAY_EXCEPTION("creating a variable.", 2);
    }
    for (string::iterator it = str.begin() + 1; it < str.end(); ++it)
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
 * in the char format then it throws an exception.
*/
inline static char string_to_char(string value){
    if(value.length() == 3 && value[0]  == '\'' && value[2] == '\''){
        return value[1];
    }
    DISPLAY_EXCEPTION("declaring the variable of type Char.",15);
    return ' ';
}

/*
 * This class will work as a storage of variables and values.
 * It can store values of type long long int, double, char, string and bool renamed as Int, Double, Char, String and Bool respectively in SRON.
 * It uses the map of string and variant. string will store the variable name and variant(typdef as collection) will store the values.
 */

class VariableManager{
    
    std::map<string,collection> Map;

    public :
    string function_name;
    VariableManager(){ }
    VariableManager(string function_name){
        this->function_name = function_name;
    }
    /*
     * This function is used to insert a variable    
    */
    inline void INSERT(string type, string variable_name){
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
                vector<long long int> vec;
                Map[variable_name] = vec ;
            }
            else if(type == "Double[]"){
                vector<double> vec;
                Map[variable_name] = vec ;
            }
            else if(type == "Char[]"){
                vector<char> vec;
                Map[variable_name] = vec ;
            }
            else if(type == "Bool[]"){
                vector<bool> vec;
                Map[variable_name] = vec ;
            }
            else if(type == "String[]"){
                vector<string> vec;
                Map[variable_name] = vec ;
            }
            else{
                DISPLAY_EXCEPTION("validating the type of variable.", 20);
            }
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("executing the variable attribute.",3);
        }
        
    }
    inline void INSERT(string type, string variable_name , string value){
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
                        Map[variable_name] = (string)"";
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
                else if(value.length() == 2 && value[0] == '\'' && value[1] == '\'' ){
                    Map[variable_name] = ' ';
                    return;
                }
                DISPLAY_EXCEPTION("declaring the variable of type Char",15);
            }
            else if(type == "Bool"){
                if(value == "true"){
                    Map[variable_name] = true ;
                    return;
                }
                else if(value == "false"){
                    Map[variable_name] = false ;
                    return;
                }
                DISPLAY_EXCEPTION("declaring the variable of type Bool",15);
            }
            else{
                DISPLAY_EXCEPTION("validating the type of variable.", 20);
            }
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("executing the variable attribute.",3);
        }
    }

    /*
     * This function will be used to add variables containing vector values.
     * It takes the subvector of the vector gained after lexical analysis.
     */
    inline void INSERT(string type, string variable_name, vector<string>& vec){
        try{
            if(type == "Int[]"){
                vector<long long int> fin;
                for(vector<string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    fin.push_back(Converter::TOINT(*i));
                }
                Map[variable_name] = fin;
                return;
            }
            else if(type == "Double[]"){
                vector<double> fin;
                for(vector<string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    fin.push_back(Converter::TODOUBLE(*i));
                }
                Map[variable_name] = fin;
                return;
            }
            else if(type == "Char[]"){
                vector<char> fin;
                for(vector<string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    fin.push_back(string_to_char(*i));
                }
                Map[variable_name] = fin;
                return;
            }
            else if(type == "Bool[]"){
                vector<bool> fin;
                for(vector<string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    fin.push_back(Converter::TOBOOL(*i));
                }
                Map[variable_name] = fin;
                return;
            }
            else if(type == "String[]"){
                vector<string> fin;
                for(vector<string>::iterator i = vec.begin(); i != vec.end(); ++i){
                    string temp = *i;
                    if(temp.length() == 2 && temp[0] == '\"' && temp[1] == '\"'){
                        fin.push_back((string)"" );
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
        catch(const std::exception&){
            DISPLAY_EXCEPTION("executing the variable attribute.",3);
        }  
    }

    /*
     * These GET functions are used to get variable's values from the VariableManager variant.
     * They can return Int, Double, Char, String, Bool and their vector forms .
    */

   inline collection GET(string& variable_name){
        try{
            return Map.at(variable_name);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable.",10);
        }
        return 0;
   }

    inline long long int GET_INT(string& variable_name){
        try{
            return std::get<long long int>(Map.at(variable_name));
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type Int.",10);
        }
        return 0;
    }
    inline double GET_DOUBLE(string& variable_name){
        try{
            return std::get<double>(Map.at(variable_name));
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type Double.",10);
        }
        return 0;
    }
    inline char GET_CHAR(string& variable_name){
        try{
            auto val = Map.at(variable_name);
            return std::get<char>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type Char.",10);
        }
        return ' ';
    }
    inline bool GET_BOOL(string& variable_name){
        try{
            return std::get<bool>(Map.at(variable_name));
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type Bool.",10);
        }
        return false;
    }
    inline string GET_STRING(string& variable_name){
        try{
            return std::get<string>(Map.at(variable_name));
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type String.",10);
        }
        return (string)" ";
    }
    inline vector<long long int> GET_INT_VECTOR(string& variable_name){
        try{
            return std::get<vector<long long int>>(Map.at(variable_name));
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type Int[].",10);
        }
        exit(0);
    }
    inline vector<double> GET_DOUBLE_VECTOR(string& variable_name){
        try{
            return std::get<vector<double>>(Map.at(variable_name));
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type Double[].",10);
        }
        exit(0);
    }
    inline vector<char> GET_CHAR_VECTOR(string& variable_name){
        try{
            return std::get<vector<char>>(Map.at(variable_name));
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type Char[].",10);
        }
        exit(0);
    }
    inline vector<bool> GET_BOOL_VECTOR(string& variable_name){
        try{
            return std::get<vector<bool>>(Map.at(variable_name));
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type Bool[].",10);
        }
        exit(0);
    }
    inline vector<string> GET_STRING_VECTOR(string& variable_name){
        try{
            return std::get<vector<string>>(Map.at(variable_name));
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("getting the value from variable of type String[].",10);
        }
        exit(0);
    }
    
    /*
     * Free Method allows users to free up memory on runtime to boost performance and decrease memory usage.
     * This method is not directly called by the user but the function
    */
    inline void FREE(string variable_name){
        try{
            Map.erase(variable_name);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("freeing up the memory usage.",10);
        }
    }
    inline string TYPE(string variable_name){
        try{
            const auto& element = Map.at(variable_name);
            return Collection_::TYPE(element);
            // if(std::holds_alternative<long long int>(element)){
            //     return "Int";
            // }
            // else if(std::holds_alternative<double>(element)){
            //     return "Double";
            // }
            // else if(std::holds_alternative<char>(element)){
            //     return "Char";
            // }
            // else if(std::holds_alternative<bool>(element)){
            //     return "Bool";
            // }
            // else if(std::holds_alternative<string>(element)){
            //     return "String";
            // }
            // else if(std::holds_alternative<vector<long long int>>(element)){
            //     return "Int[]";
            // }
            // else if(std::holds_alternative<vector<double>>(element)){
            //     return "Double[]";
            // }
            // else if(std::holds_alternative<vector<char>>(element)){
            //     return "Char[]";
            // }
            // else if(std::holds_alternative<vector<bool>>(element)){
            //     return "Bool[]";
            // }
            // else if(std::holds_alternative<vector<string>>(element)){
            //     return "String[]";
            // }
            // else{
            //     DISPLAY_EXCEPTION("finding the type of given element.",22);
            // }
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("accessing a given variable.",10);
        }
        return (string)"";
    }

    ~VariableManager(){ }
};

#endif

// template<typename t> std::ostream& operator<<(std::ostream& COUT, vector<t>& vec)
// {
//      if(vec.size() == 0){ 
//           std::cout<<"[]"; 
//           return COUT;
//      }
//      COUT << "[";
//      typename vector<t>::const_iterator it ;
//      for (it = vec.begin(); it != vec.end()-1; ++it)
//      {
//           COUT << *it << ", ";
//      }
//      COUT << *it <<"]";
//      return COUT;
// }

