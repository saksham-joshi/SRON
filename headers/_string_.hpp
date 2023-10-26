#include <string>
#include <ctype.h>
#include <iostream>
#include <vector>
#include "_exception_.hpp"

#ifndef STRING_H
#define STRING_H

class String{
public:
    inline static std::string STRIP(std::string str){
        std::string fin = "";
        try{
            int string_end_index = 0;

            for(std::string::iterator it = str.end()-1 ; *it == ' ' ; --it){
                ++string_end_index;
            }

            for(std::string::iterator it = str.begin()  ; it != str.end()-string_end_index ; ++it){
                if(*it != ' '){
                    for( ;it != str.end()-string_end_index ; ++it ){
                        fin+=*it;
                    }
                    break;
                }
            }
        }
        catch(std::exception){
            DISPLAY_EXCEPTION("extracting the string.",3 );
        }
        return fin;
    }

    inline static std::string CONCAT(std::string str1, const std::string str2)
    {
        return str1.append(str2);
    }
    inline static std::string CONCAT(std::string str, char ch)
    {
        return str + ch;
    }
    inline static std::string CONCAT(std::string str, double d)
    {
        return str + std::to_string(d);
    }
    inline static std::string CONCAT(std::string str, long long int x)
    {
        return str + std::to_string(x);
    }

    inline static char AT(std::string str,int index){
        if(index < 0 || index >= str.length()){
            DISPLAY_EXCEPTION("extracting an element of string type.",12);
        }
        return str[index];
    }

    inline static std::string CAPITALIZE(std::string str){
        try{
            str[0] = toupper(str[0]);
        }
        catch (std::exception e) {}
        return str;
    }

    inline static std::string SUBSTRING(std::string str, int start, int end){
        std::string fin = "";
        end = (end > str.length()) ? str.length() : end;
        start = (start < 0) ? 0 : start;
        try
        {
            for(std::string::iterator it = str.begin()+start ; it != str.begin()+end ; ++it ){
                fin+=*it;
            }
        }
        catch (std::exception e){
            DISPLAY_EXCEPTION("extracting a substring from passed string.",3);
         }
        return fin;
    }

    inline static int LEN(const std::string str){
        return str.length();
    }
    inline static void CLEAR(std::string &str){
        str = "";
    }
    inline static std::string COPY(std::string str){
        std::string fin = "";
        for(std::string::iterator it = str.begin() ; it != str.end() ; ++it){
            fin+=*it;
        }
        return fin;
    }
    inline static std::string REVERSE(std::string str){
        std::string fin = "";
        
        for(std::string::iterator it = str.end()-1 ; it!=str.begin()-1 ; --it ){
            fin+=*it;
        }
        return fin;
    }

    inline static int COUNT(std::string str, const char ch){
        int count = 0;
        for(std::string::iterator it = str.begin() ; it != str.end() ; ++it){
            if(*it == ch){
                count++;
            }
        }
        return count;
    }

    inline static std::string REPLACE(std::string str, const char from, const char with){
        std::string fin = "";
        try{   
            for(std::string::iterator it = str.begin() ; it!= str.end() ; ++it){
                if(*it == from){
                    fin+=with;
                    continue;
                }
                fin+=*it;
            }
            return fin;
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("replacing a character from a String .",3);
        }
        return fin;
    }

    inline static std::vector<std::string> SPLIT(std::string str, const char splitter){
        try{
            std::vector<std::string> vec;
            std::string temp = "";
            for(std::string::iterator it = str.begin() ; it != str.end() ; ++it){
                if(*it == splitter){
                    vec.push_back(temp);
                    temp = "";
                    continue;
                }
                temp+=*it;
            }
            vec.push_back(temp);
            return vec;
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("splitting a string.",3);
        }    
    }

    inline static std::string ToLOWERCASE(std::string str){
        std::string fin = "";
        try{   
            for(std::string::iterator it= str.begin() ; it != str.end() ; ++it){
                fin+=tolower(*it);
            }
            return fin;
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("converting a String to lowercase.",3);
        }
        return fin;
        
    }
    inline static std::string ToUPPERCASE(std::string str){     
        std::string fin = "";
        try{
            for(std::string::iterator it = str.begin(); it != str.end() ; ++it){
                fin+=toupper(*it);
            }
            return fin;
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("converting a String to Uppercase.",3);
        }     
    }
    ~String(){ }
};

#endif