
/*
 * This class will work as a storage of variables and values.
 * It can store values of type long long int, long double, char, string and bool, List renamed as Int, Double, Char, String and Bool respectively in SRON.
 * It uses the map of string and Any*. string will store the variable name and Any* will store the reference to the values.
 */

#include "_datatypes_.hpp"
#include<map>

#ifndef VariableManager_H
#define VariableManager_H

class VariableManager{
    private:
        std::map<std::string, Any*> vmap;
        const char* function_name;

    public :
        VariableManager(const char* function_name){
            this->function_name = function_name;
        }

        void INSERT(std::string type, std::string variable_name){
           if(type == "Int"){ vmap[variable_name] =  Int::MAKE(); }
           else if(type == "String"){ vmap[variable_name] =  String::MAKE(); }
           else if(type == "List"){ vmap[variable_name] =  List::MAKE(); }
           else if(type == "Double"){ vmap[variable_name] =  Double::MAKE(); }
           else if(type == "Void"){ vmap[variable_name] = Void::MAKE();}
           else if(type == "Char"){ vmap[variable_name] =  Char::MAKE(); }
           else if(type == "Bool"){ vmap[variable_name] =  Bool::MAKE(); }
           else{ DISPLAY_EXCEPTION("declaring and allocating memory space for variables.",13);}
        }

        void FREE(std::string variable_name){
            try{
                auto it = vmap.find(variable_name);
                if(it != vmap.end()){
                    vmap.erase(it);
                }
                throw std::exception();
            }
            catch(const std::exception&){
                DISPLAY_EXCEPTION("freeing up the memory space.",26);
            }
        }

        std::string TYPE(std::string variable_name){
            try{
                return vmap.at(variable_name)->TYPE();
            }
            catch(const std::exception&){
                DISPLAY_EXCEPTION("checking the type of the variable.",26);
            }
            return " ";
        }

        Any* GET(std::string variable_name){
            try{
                return vmap.at(variable_name);
            }
            catch(const std::exception&){
                DISPLAY_EXCEPTION("retreving the value of a variable.",26);
            }
            return nullptr;
        }
        ~VariableManager(){
            vmap.clear();
        }
};

#endif