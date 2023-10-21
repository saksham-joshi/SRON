#include <iostream>
#include <vector>
#include "headers/_exception_.h"

std::vector<std::string> LEX(std::string str)
{
     std::vector<std::string> vec;
     try
     {
          // if (str.length() <= start)
          // {
          //      DISPLAY_EXCEPTION("executing code within the variable or args attribute.", 11);
          // }

          int inside_string = 0;
          std::string val = "";

          for (std::string::iterator it = str.begin(); it != str.end(); ++it)
          {
               std::cout<<">"<<*it<<"<"<<std::endl;

               if (*it == '\"')
               {
                    inside_string = !inside_string;
                    if (inside_string == 0)
                    {
                         vec.push_back(val);
                         val = "";
                    }
                    continue;
                    // while(it != str.end() || *it != '\"'){
                    //      val+=*it;
                    // }
                    // vec.push_back(val);
                    // val = "";
                    // continue;
               }
               else if (*it == ' ')
               {
                    continue;
               }
               else if (*it == '{' || *it == '}' || *it == '[' || *it == ']' || *it == '(' || *it == ')' || *it == ':' || *it == '=' || *it == ',' || *it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '%' || *it == '\\' || *it == '\n' || *it == '\t')
               {
                    vec.push_back((std::string) "" + *it);
                    val = "";
               }
               else if (isalnum (*it) || *it == '_')
               {
                    while((isalnum(*it) || *it == '.') && it != str.end()){
                         val+=*it;
                         ++it;
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
     }
     return vec;
}

std::ostream &operator<<(std::ostream &COUT, std::vector<std::string> &vec)
{
     if(vec.size() == 0){ 
          std::cout<<"[]"; 
          return COUT;
     }
     std::cout << "[";
     std::vector<std::string>::iterator it;
     for (it = vec.begin(); it != vec.end() - 1; ++it)
     {
          std::cout << *it << ", ";
     }
     std::cout << *it <<"]";
     return COUT;
}

int main()
{
     std::vector<std::string> vec =  LEX("{name: factorial\ntype: int\nargs : (int val)\nvariables: (String st21 = \"Helllo\' guys\" ,int fac1=112,int i1,double d2=123.45)\nforloop:{\nrange: i = [2,eval(val+1)]\n0 : fac = eval(fac*i)\n}\nreturn : fac\n} ");
     std::cout<<vec;
}