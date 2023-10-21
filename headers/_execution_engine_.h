#include<iostream>
#include<string>
#include<stack>
#include "_string_.h"
#include "_hashtable_.h"
#include "_utility_.h"

class Executor{

    HashTable H;
    private :

        inline static String_and_Int GET_ATTRIBUTE(std::string str){
            std::string attribute = "";
            std::string::iterator it;
            int a=0;
            for(it=str.begin(); it!=str.end(); ++it,++a){
                if(!(isalpha(*it) || isdigit(*it) ) ){
                    while(it!= str.end() && *it != ':'){
                        ++it;
                        ++a;
                    }
                    break;
                }
                attribute+=*it;
            }
            String_and_Int obj(attribute,a);
       
            return obj;
        }
        

        inline static bool CHECK_VALID_VARIABLE_NAME(std::string str){     
            if(!(str[0] == '_' || isalpha(str[0])>0 ) ){
                DISPLAY_EXCEPTION("creating a variable.",2);
            }
            for(std::string::iterator it = str.begin()+1 ; it < str.end() ; ++it){
                if (!(*it == '_' || isalpha(*it)>0 || ((int)*it>=48 && (int)*it <=57 ))){
                    DISPLAY_EXCEPTION("creating a variable.",2);
                }
            }
            return true;
        }

        inline static bool CHECK_IF_ATTRIBUTE_IS_NUMBER(std::string str){
            for(std::string::iterator it = str.begin() ; it< str.end() ; ++it){
                if((int)*it >= 48 && (int)*it <= 57){
                    continue;
                }
                return false;
            }
            return true;
        }
        friend int main(int argc, char **argv);

    public :
        Executor(HashTable &H ){
            this->H = H;
        }
        void ADD_VARIABLES(std::string str){
            
        } 
};