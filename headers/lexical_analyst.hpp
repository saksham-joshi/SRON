/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 * 
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
*/

#include <stack>
#include "_function_.hpp"
#include "_support_.hpp"

#ifndef _LEXICAL_H
#define _LEXICAL_H

namespace LEXICAL_ANALYSER
{
     // This string will contain the whole code in the .sron file.
     std::string filecode = "";

     std::string function_name = "";

     // This iterator will be used to iterate over "std::string filecode".
     std::string::iterator it;

     // This string will contain the attribute.
     std::string attribute = "";

     // This vector will hold the lex of attributes.
     std::vector<std::string> vec;

     // This vector will contain the Function Structure instance which contains the function name and its LEX pairs.
     std::vector<Function> FunctionVector;

     // This stack is used to keep track of scopes -> "{" and "}".
     std::stack<char> scope_stack;

     // contains the pair of attribute and instructions
     InstructionVector inst_vector;

     bool emptyline_flag = false;
     bool function_scope_flag = false;

     // inline static void FUNCTION_FLOW(const char* func){
     //      printf("\n |> Function = %s <|\n",func);
     // }

     // inline static void LOGS_PRINT(const char* func){
     //      printf("\nFunction= %s\n Character= '%c'\n attribute= '%s'\n Stack size= %d",func, *it,attribute.c_str(),scope_stack.size());
     //      if(scope_stack.size() > 0){
     //           printf("\n Stack top= %c",scope_stack.top() );
     //      }
     //      printf("\n----------------\n");
     // }

     // used to move the iterator to the first non-occurence of a particular character.
     inline static void JUMP_TILL_CHAR_REPEATS(char ch)
     {

          while (it < filecode.end() && *it == ch)
          {
               ++it;
          }
     }

     inline static void JUMP_TO_NEXT_FIRST_OCCURENCE(char ch)
     {

          while (it < filecode.end() && *it != ch)
          {
               ++it;
          }
     }

     inline static void JUMP_SPACE_AND_NEWLINE()
     {

          while (it < filecode.end() && (*it == ' ' || *it == '\n'))
          {
               ++it;
          }
     }

     inline static void ADD_FUNCTION()
     {

          if (inst_vector.size() == 0)
          {

               DISPLAY_EXCEPTION("analysing the code and creating functions.", WrongSyntaxException);
          }

          FunctionVector.push_back(Function(function_name, inst_vector, VariableManager(function_name)));
          inst_vector.clear();
     }

     // used to add the string type values starting with " (quotes) to the vector "vec".
     inline static void HANDLE_SCOPES()
     {
          try
          {
               if (*it == '{')
               {
                    scope_stack.push(*it);
                    function_scope_flag = scope_stack.size() >= 1;
               }
               else if (*it == '}')
               {
                    if (scope_stack.size() > 0 && scope_stack.top() == '{')
                    {
                         scope_stack.pop();
                         function_scope_flag = scope_stack.size() != 0;

                         if (scope_stack.size() == 0)
                         {
                              ADD_FUNCTION();
                         }
                         else if (attribute == "}")
                         {
                              inst_vector.push_back(InstructionPair(attribute, vec));
                         }
                         return;
                    }

                    DISPLAY_EXCEPTION("analyzing the code and handling scopes.", InvalidScopeException);
               }
          }
          catch (const std::exception &)
          {
               DISPLAY_EXCEPTION("analyzing the code and handling scopes.", SystemOutofMemoryException);
          }
     }
     inline static void ADD_STRING()
     {
          std::string val = "\"";
          ++it;
          while (it < filecode.end() && *it != '"')
          {
               val += *it;
               ++it;
          }
          val += '"';
          ++it;
          vec.push_back(val);
     }

     // used to add the char type values starting with ' (single-quote) to the vector "vec".
     inline static void ADD_CHAR()
     {

          if (it < filecode.end() - 2 && *(it + 2) == '\'')
          {
               std::string val = (std::string) "\'" + *(++it) + '\'';
               vec.push_back(val);
               it += 2;

               return;
          }

          DISPLAY_EXCEPTION("extracting value of Char Type.", InvalidValueException);
     }

     // used to add the numeric type values starting with a number to the vector "vec".
     inline static void ADD_NUMBER()
     {

          if (*it == '-' && it < filecode.end() - 1 && !(is_number(*(it + 1)) || *(it + 1) == '.'))
          {
               vec.push_back("-");
               ++it;
               return;
          }
          string val = (*it == '-') ? (std::string) "-" : "";
          while (it < filecode.end() && (is_number(*it) || *it == '.'))
          {
               val += *it;
               ++it;
          }
          vec.push_back(val);
     }

     // used to add the values starting with a underscore or a alphabet to the vector "vec".
     inline static void ADD_IDENTIFIER()
     {
          std::string val = (std::string) "" + *it;
          /* It will iterate until a character other than End of string, alphabet, number or underscore arises.*/
          ++it;
          while (it < filecode.end() && (is_alpha_number(*it) || *it == '_'))
          {
               val += *it;
               ++it;
          }
          vec.push_back(val);
     }

     inline static void BREAK_INSTRUCTION_TO_LEX()
     {

          while (it < filecode.end() && *it != '\n')
          {
               if (*it == ' ')
               {
                    ++it;
                    continue;
               }
               else if (*it == '\n')
               {
                    return;
               }
               else if (*it == '_' || is_alphabet(*it))
               {
                    LEXICAL_ANALYSER::ADD_IDENTIFIER();
                    continue;
               }
               else if (*it == '-' || *it == '.' || is_number(*it))
               {
                    LEXICAL_ANALYSER::ADD_NUMBER();
                    continue;
               }
               else if (*it == '"')
               {
                    LEXICAL_ANALYSER::ADD_STRING();
                    continue;
               }
               else if (*it == '\'')
               {
                    LEXICAL_ANALYSER::ADD_CHAR();
                    continue;
               }
               else if (IS_CURLY_BRACES(*it))
               {
                    vec.push_back((std::string) "" + *it);
                    HANDLE_SCOPES();
                    ++it;
                    break;
               }
               else if (*it == '[' || *it == ']' || *it == '(' || *it == ')' || *it == ',' || *it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '%' || *it == '^' || *it == '~')
               {
                    vec.push_back((std::string) "" + *it);
               }
               else if (*it == '=' || *it == '&' || *it == '|')
               { // characters which can be used as pairs
                    if (it < filecode.end() - 1 && *it == *(it + 1))
                    {
                         vec.push_back((std::string) "" + *it + *it);
                    }
                    else
                    {
                         vec.push_back((std::string) "" + *it);
                    }
               }
               else if (*it == '!')
               {
                    if (it < filecode.end() - 1 && *(it + 1) == '=')
                    {
                         vec.push_back("!=");
                         ++it;
                    }
                    else
                    {
                         vec.push_back("!");
                    }
               }
               else
               {

                    DISPLAY_EXCEPTION("analysing the code.", WrongSyntaxException);
               }
               ++it;
          }
     }

     inline static void ADD_PAIR()
     {

          if (attribute == "}")
          {
               inst_vector.push_back(InstructionPair(attribute, vec));
          }
          else if (attribute.length() == 0 || vec.size() == 0)
          {
               return;
          }
          else if (attribute == "name")
          {
               if (vec.size() == 1)
               {
                    LEXICAL_ANALYSER::function_name = vec[0];
               }
               else
               {

                    DISPLAY_EXCEPTION("analysing the code and extracting the name of the function.", EmptyAttributeCode);
               }
          }
          else
          {
               inst_vector.push_back(InstructionPair(attribute, vec));
          }
          attribute = "";
          vec.clear();
     }

     inline static void GET_ATTRIBUTE()
     {

          if (is_alpha_number(*it))
          {

               LEXICAL_ANALYSER::attribute = (std::string) "" + *it;

               while (it < filecode.end() && is_alpha_number(*(++it)))
               {
                    attribute += *it;
               }

               return;
          }
          else if (IS_CURLY_BRACES(*it))
          {
               attribute = (std::string) "" + *it;
               HANDLE_SCOPES();
               ++it;
          }
          else
          {

               DISPLAY_EXCEPTION("analysing the code.", InvalidAttributeException);
          }
     }

     inline static void LEX(std::string &str)
     {

          LEXICAL_ANALYSER::filecode = str;
          LEXICAL_ANALYSER::it = filecode.begin();

          JUMP_TO_NEXT_FIRST_OCCURENCE('{');
          if (it < filecode.end())
          {
               HANDLE_SCOPES();
               ++it;
               while (it < filecode.end())
               {
                    
                    JUMP_SPACE_AND_NEWLINE();
                    GET_ATTRIBUTE();

                    if (it < filecode.end())
                    {
                         if (attribute == "{" || attribute == "}")
                         {
                              HANDLE_SCOPES();
                              continue;
                         }
                         else if (attribute.length() != 0 && attribute != "comment")
                         {

                              JUMP_TO_NEXT_FIRST_OCCURENCE(':');
                              ++it;
                              JUMP_TILL_CHAR_REPEATS(' ');
                              if (it >= filecode.end() || *it == '\n')
                              {

                                   DISPLAY_EXCEPTION("analysing the code and extracting the instruction of an attribute.", EmptyAttributeCode);
                              }
                              BREAK_INSTRUCTION_TO_LEX();
                              ADD_PAIR();
                              
                         }
                         else if (attribute == "comment")
                         {
                              JUMP_TO_NEXT_FIRST_OCCURENCE('\n');
                         }
                         JUMP_SPACE_AND_NEWLINE();
                    }
                    else
                    {
                         break;
                    }
               }
          }
          else
          {

               DISPLAY_EXCEPTION("analyzing the code.", NoValidCodeFoundException);
          }
     }

}

#endif

// inline static void print_vector(std::vector<std::string> vec)
// {
//      if (vec.size() == 0)
//      {
//           printf("[]");
//           return;
//      }
//      printf("[");
//      std::vector<std::string>::const_iterator it;
//      for (it = vec.begin(); it != vec.end() - 1; ++it)
//      {
//           printf("%s, ", (*it).c_str());
//      }
//      printf("%s]", (*it).c_str());
// }

// for (const auto j : LEXICAL_ANALYSER::FunctionVector)
        // {
        //     printf("\n |> Function =  '%s' <|",j.fnc_name.c_str());
        //     for (const auto i : j.codemap)
        //     {
        //         std::cout << "\nAttribute -> " << i.first << "\n\t Vector -> ";
        //         print_vector(i.second);
        //     }
        // }