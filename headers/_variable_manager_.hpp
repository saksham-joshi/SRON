
/*
 * This class will work as a storage of variables and values.
 * It can store values of type long long int, long double, char, string and bool, List renamed as Int, Double, Char, String and Bool respectively in SRON.
 * It uses the map of string and Any*. string will store the variable name and Any* will store the reference to the values.
 */
#ifndef VariableManager_H
#define VariableManager_H

#include "_datatypes_.hpp"
#include<unordered_map>

class VariableManager{
    private:
        std::unordered_map<std::string, Any*> vmap;
        
    public :

        inline void INSERT(std::string& type, std::string& variable_name){
           if(type == Flag_Int ){ vmap[variable_name] =  new Int() ; }
           else if(type == Flag_String){ vmap[variable_name] =  new String(); }
           else if(type == Flag_List ){ vmap[variable_name] =  new List() ; }
           else if(type == Flag_Double ){ vmap[variable_name] =  new Double() ; }
           else if(type == Flag_Void ){ vmap[variable_name] = new Void();}
           else if(type == Flag_Char ){ vmap[variable_name] =  new Char(); }
           else if(type == Flag_Bool ){ vmap[variable_name] =  new Bool(); }
           else{ DISPLAY_EXCEPTION("declaring and allocating memory space for variables.",InvalidTypeException);}
        }
        inline void INSERT(std::string variable_name, Any* value){
            try{
                vmap[variable_name] = value;
            }
            catch(const std::exception&){
                DISPLAY_EXCEPTION("allocating memory for variables.",SystemOutofMemoryException);
            }
        }

        inline void FREE(std::string variable_name){
            try{
                auto it = vmap.find(variable_name);
                if(it != vmap.end()){
                    vmap.erase(it);
                }
                throw std::exception();
            }
            catch(const std::exception&){
                DISPLAY_EXCEPTION("freeing up the memory space.",VariableNotFoundException);
            }
        }

        inline std::string TYPE(std::string variable_name){
            try{
                return vmap.at(variable_name)->TYPE();
            }
            catch(const std::exception&){
                DISPLAY_EXCEPTION("checking the type of the variable.",VariableNotFoundException);
            }
            return " ";
        }

        inline Any* GET(std::string variable_name){
            try{
                return vmap.at(variable_name);
            }
            catch(const std::exception&){
                DISPLAY_EXCEPTION("retreving the value of a variable '"+variable_name+"'.",VariableNotFoundException);
            }
            return nullptr;
        }
        inline void CLEAR(){
            vmap.clear();
        }
        ~VariableManager(){         
            for(auto& i : this->vmap){
                i.first.~basic_string();
                free(i.second);
            }
            vmap.clear();
        }
};

#endif