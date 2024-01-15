#include <stack>
#include <iostream>
#include "_function_.hpp"

#ifndef _LEXICAL_H
#define _LEXICAL_H

// inline std::vector<_function_> LEX(std::string& str){
//      std::vector<collection> vec;
//      std::stack<char> scope_stack;
//      for(auto it = str.begin() ; it != str.end() ; ++it){
//           if(*it == '{'){
//                scope_stack.push(*it);
//                for(;it != str.end() ; ++it){
//                     if(){

//                     }
//                }
//                break;
//           }
//      }
// }

inline std::vector<Function> LEX(std::string str)
{

     std::vector<Function> f_vector;
     std::unordered_map<std::string, std::vector<std::string>> codemap;
     std::vector<std::string> vec;
     std::stack<char> scope_stack;
     std::string attribute = "";
     bool start_scope = false;

     try
     {
          std::string val = "";

          for (std::string::iterator it = str.begin(); it < str.end(); ++it)
          {
               start_scope = (*it == '{') ? true : false;

               if (start_scope)
               {

                    if (*it == ' ')
                    {
                         continue;
                    }
                    else if (*it == '\n')
                    { // whenever the line ends
                         codemap[attribute] = vec;
                         vec.clear();
                         attribute = "";
                    }
                    else if (*it == '\"') // extracting string values
                    {
                         val = "\"";
                         ++it;
                         while (it != str.end() && *it != '\"')
                         {
                              val += *it;
                              ++it;
                         }
                         vec.push_back(val + '\"');
                         val = "";
                         continue;
                    }
                    else if (*it == '\'')                // extracting char values
                    {
                         if (!(it < str.end() - 2 && *(it + 2) == '\''))
                         {
                              DISPLAY_EXCEPTION("extracting value of Char Type.", 15);
                         }
                         else
                         {
                              val = (std::string) "\'" + *(++it) + '\'';
                              vec.push_back(val);
                              ++it;
                         }
                    }
                    else if (*it == '{')
                    {
                         scope_stack.push(*it);
                    }
                    else if (*it == '}')              // when scope ends
                    {
                         scope_stack.pop();
                         if (scope_stack.empty())
                         {
                              Function fnc(codemap);
                              f_vector.push_back(fnc);
                              start_scope = false;
                         }
                    }
                    else if (*it == '[' || *it == ']' || *it == '(' || *it == ')' || *it == ':' || *it == '&' || *it == '|' || *it == '=' || *it == ',' || *it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '%' || *it == '^' || *it == '!' || *it == '\\' || *it == '\n' || *it == '\t')
                    {
                         if (it != str.end() - 1)
                         {

                              if (*it == '!' && *(it + 1) == '=')
                              {
                                   vec.push_back((std::string) "!=");
                                   ++it;
                                   continue;
                              }
                              else if (*it == '[' && *(it + 1) == ']')
                              {
                                   vec.push_back((std::string) "[]");
                                   ++it;
                                   continue;
                              }
                              else if (*it == '&' && *(it + 1) == '&')
                              {
                                   vec.push_back((std::string) "&&");
                                   ++it;
                                   continue;
                              }
                              else if (*it == '|' && *(it + 1) == '|')
                              {
                                   vec.push_back((std::string) "||");
                                   ++it;
                                   continue;
                              }
                              else if (*it == '=' && *(it + 1) == '=')
                              {
                                   vec.push_back((std::string) "==");
                                   ++it;
                                   continue;
                              }
                         }
                         vec.push_back((std::string) "" + *it);
                         val = "";
                    }
                    else if (isalnum(*it) || *it == '.' || *it == '_')                    // if a alphabet or number comes up
                    {
                         while ((isalnum(*it) || *it == '.' || *it == '_') && it != str.end())
                         {
                              val += *it;
                              ++it;
                         }
                         // if (vec.size() == 0 && val == "comment")
                         // {
                         //      return f_vector;
                         // }
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
     }
     catch (const char *err)
     {
          DISPLAY_EXCEPTION(err, 28);
     }
     catch (const std::exception &)
     {
          DISPLAY_EXCEPTION("analysing the code.", 3);
     }
     return f_vector;
}

// std::ostream& operator<<(std::ostream& COUT, std::vector<std::string>& vec)
// {
//      if(vec.size() == 0){
//           std::cout<<"[]";
//           return COUT;
//      }
//      std::cout << "[";
//      std::vector<std::string>::const_iterator it;
//      for (it = vec.begin(); it != vec.end() - 1; ++it)
//      {
//           std::cout << *it << ", ";
//      }
//      std::cout << *it <<"]";
//      return COUT;
// }

#endif

int main()
{
}