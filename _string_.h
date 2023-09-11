#include <cstring>
#include <ctype.h>
#include <iostream>
#include <vector>

class String
{

public:
    inline static std::string STRIP(const std::string str)
    {
        std::string fin = "";
        int string_end_index = 0;
        for (int i = str.length() - 1; i >= 0; i--)
        {
            if (str[i] != ' ')
            {
                break;
            }
            string_end_index++;
        }
        for (int i = 0; i < strlen(str.c_str()); i++)
        {
            if (str[i] != ' ')
            {
                for (int j = i; j < str.length() - string_end_index; j++)
                {
                    fin += str[j];
                }
                break;
            }
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

    inline static std::string CAPITALIZE(std::string str)
    {
        try
        {
            str[0] = toupper(str[0]);
        }
        catch (std::exception e)
        {
        }
        return str;
    }

    inline static std::string SUBSTRING(std::string str, int start, int end)
    {
        std::string fin = "";
        end = (end > str.length()) ? str.length() : end;
        start = (start < 0) ? 0 : start;
        try
        {
            for(std::string::iterator it = str.begin()+start ; it != str.begin()+end ; it++ ){
                fin+=*it;
            }
        }
        catch (std::exception e)
        {
        }
        return fin;
    }

    inline static int LEN(const std::string str)
    {
        return str.length();
    }
    inline static void CLEAR(std::string &str)
    {
        str = "";
    }
    inline static std::string COPY(std::string str)
    {
        std::string fin = "";
        for(std::string::iterator it = str.begin() ; it != str.end() ; it++){
            fin+=*it;
        }
        return fin;
    }
    inline static std::string REVERSE(std::string str)
    {
        std::string fin = "";
        
        for(std::string::iterator it = str.end()-1 ; it!=str.begin()-1 ; it-- ){
            fin+=*it;
        }
        return fin;
    }

    inline static int COUNT(std::string str, const char ch)
    {
        int count = 0;
        for(std::string::iterator it = str.begin() ; it != str.end() ; it++){
            if(*it == ch){
                count++;
            }
        }
        return count;
    }
    // inline static int COUNT(const string str,const string counter){

    // }

    inline static std::string REPLACE(std::string str, const char from, const char with)
    {
        std::string fin = "";
        for(std::string::iterator it = str.begin() ; it!= str.end() ; it++){
            if(*it == from){
                fin+=with;
                continue;
            }
            fin+=*it;
        }
        return fin;
    }

    // inline static string REPLACE(const string str , const string from , const string with){

    // }

    inline static std::vector<std::string> SPLIT(std::string str, const char splitter)
    {
        std::vector<std::string> vec;
        std::string temp = "";
        for(std::string::iterator it = str.begin() ; it != str.end() ; it++){
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

    // inline static vector<string> SPLIT(const string str , const string splitter){

    // }

    inline static std::string ToLOWERCASE(std::string str){
        std::string fin = "";
        for(std::string::iterator it= str.begin() ; it != str.end() ; it++){
            fin+=tolower(*it);
        }
        return fin;
    }
    inline static std::string ToUPPERCASE(std::string str){
        std::string fin = "";
        for(std::string::iterator it = str.begin(); it != str.end() ; it++){
            fin+=toupper(*it);
        }
        return fin;
    }

    ~String(){ }
};