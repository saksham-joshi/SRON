#include <iostream>
#include <vector>
#include "./_exception_.hpp"

#ifndef _LEXICAL_H
#define _LEXICAL_H

std::vector<std::string> LEX(std::string str)
{
     int i=0;
     std::vector<std::string> vec;
     try
     {
          std::string val = "";

          for (std::string::iterator it = str.begin(); it != str.end(); ++it)
          {
               if (*it == ' ')
               {
                    continue;
               }
               else if (*it == '\"')
               {
                    val = "\"";
                    ++it;
                    while(it != str.end() && *it != '\"'){
                         val+=*it;
                         ++it;
                    }
                    vec.push_back(val+'\"');
                    val = "";
                    continue;
               }
               else if(*it == '\''){
                    if(!(it < str.end()-2 && *(it+2) == '\'')){
                         DISPLAY_EXCEPTION("extracting value of Char Type.",15);
                         
                    }
                    else{
                         val = (std::string)"\'"+*(++it)+'\'';
                         vec.push_back(val);
                         ++it;
                    }
               }
               else if (*it == '~' || *it == '{' || *it == '}' || *it == '[' || *it == ']' || *it == '(' || *it == ')' || *it == ':' || *it == '&' || *it == '|' || *it == '=' || *it == ',' || *it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '%' || *it == '^' || *it == '!' || *it == '\\' || *it == '\n' || *it == '\t')
               {
                    if(it != str.end()-1 && *it == '!' && *(it+1) == '='){
                         vec.push_back( (std::string)"!=");
                         ++it;
                         continue;
                    }
                    else if(it != str.end()-1 && *it == '[' && *(it+1) == ']'){
                        vec.push_back((std::string)"[]" );
                        ++it;
                        continue;
                    }
                    else if(it != str.end()-1 && *it == '&' && *(it+1) == '&'){
                        vec.push_back((std::string)"&&" );
                        ++it;
                        continue;
                    }
                    else if(it != str.end()-1 && *it == '|' && *(it+1) == '|'){
                        vec.push_back((std::string)"||" );
                        ++it;
                        continue;
                    }
                    else if(it != str.end()-1 && *it == '=' && *(it+1) == '='){
                        vec.push_back((std::string)"==" );
                        ++it;
                        continue;
                    }
                    vec.push_back((std::string) "" + *it);
                    val = "";
               }
               else if (isalnum (*it) || *it == '.' || *it == '_')
               {
                    while((isalnum(*it) || *it == '.' || *it == '_') && it != str.end()){
                         val+=*it;
                         ++it;
                    }
                    if(vec.size() == 0 && val == "comment"){
                         return vec;   
                    }
                    vec.push_back(val);
                    val = "";
                    --it;
               }
               else
               {
                    DISPLAY_EXCEPTION("analysing the written code.", 14);
               }
          }
     }
     catch (std::exception)
     {
          DISPLAY_EXCEPTION("analysing the code.",3);
     }
     return vec;
}

std::ostream& operator<<(std::ostream& COUT, std::vector<std::string>& vec)
{
     if(vec.size() == 0){ 
          std::cout<<"[]"; 
          return COUT;
     }
     std::cout << "[";
     std::vector<std::string>::const_iterator it;
     for (it = vec.begin(); it != vec.end() - 1; ++it)
     {
          std::cout << *it << ", ";
     }
     std::cout << *it <<"]";
     return COUT;
}

#endif