#include <stack>
#include "_function_.hpp"
#include "_support_.hpp"
#include <iostream>
#include "static_logs.hpp"

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

     inline static void FUNCTION_FLOW(const char* func){
          printf("\n |> Function = %s <|\n",func);
     }

     inline static void LOGS_PRINT(const char* func){
          printf("\nFunction = %s\n Character= '%c'\n attribute= '%s'\n---------\n",func, *it,attribute.c_str());
     }

     // used to move the iterator to the first non-occurence of a particular character.
     inline static void JUMP_TILL_CHAR_REPEATS(char ch)
     {
          FUNCTION_FLOW("JUMP_TILL_CHAR_REPEATS");
          while (it < filecode.end() && *it == ch){
               ++it;
          }
          FUNCTION_FLOW("EXIT JUMP_TILL_CHAR_REPEATS");
     }

     inline static void JUMP_TO_NEXT_FIRST_OCCURENCE(char ch)
     {
          
          FUNCTION_FLOW("JUMP_TO_NEXT_FIRST_OCCURENCE");
          while (it < filecode.end() && *it != ch)
          {
               ++it;
          }
          FUNCTION_FLOW("EXIT JUMP_TO_NEXT_FIRST_OCCURENCE");
     }

     inline static void JUMP_SPACE_AND_NEWLINE()
     {
          
          FUNCTION_FLOW("JUMP_SPACE_AND_NEWLINE");
          while (it < filecode.end() && (*it == ' ' || *it == '\n'))
          {
               ++it;
          }
          FUNCTION_FLOW("EXIT JUMP_SPACE_AND_NEWLINE");
     }

     inline static void ADD_FUNCTION()
     {
          
          FUNCTION_FLOW("ADD_FUNCTION");
          if (inst_vector.size() == 0)
          {
               LOGS_PRINT("ADD_FUNCTION");
               DISPLAY_EXCEPTION("analysing the code and creating functions.", WrongSyntaxException);
          }

          FunctionVector.push_back(Function(function_name, inst_vector));
          inst_vector.clear();
          FUNCTION_FLOW("EXIT ADD_FUNCTION");
     }

     // used to add the string type values starting with " (quotes) to the vector "vec".
     inline static void HANDLE_SCOPES()
     {
          
          FUNCTION_FLOW("HANDLE_SCOPES");
          try
          {
               if (*it == '{')
               {
                    scope_stack.push('{');
                    function_scope_flag = scope_stack.size() >= 1;
               }
               else if (*it == '}')
               {
                    if (scope_stack.top() == '{')
                    {
                         scope_stack.pop();
                         function_scope_flag = scope_stack.size() != 0;
                         if (scope_stack.size() == 0)
                         {
                              ADD_FUNCTION();
                         }
                         FUNCTION_FLOW("EXIT HANDLE_SCOPES");
                         return;
                    }
                    LOGS_PRINT("HANDLE_SCOPES");
                    DISPLAY_EXCEPTION("analyzing the code and handling scopes.", InvalidScopeException);
               }
          }
          catch (const std::exception &)
          {
               LOGS_PRINT("HANDLE_SCOPES WITHIN EXCEPTION");
               DISPLAY_EXCEPTION("analyzing the code and handling scopes.", SystemOutofMemoryException);
          }
          
     }
     inline static void ADD_STRING()
     {
          
          FUNCTION_FLOW("ADD_STRING");
          std::string val = "\"" + *it;
          ++it;
          while (it < filecode.end() && *it != '"')
          {
               val += *it;
               ++it;
          }
          val += '"';
          ++it;
          vec.push_back(val);
          FUNCTION_FLOW("EXIT ADD_STRING");
     }

     // used to add the char type values starting with ' (single-quote) to the vector "vec".
     inline static void ADD_CHAR()
     {
          
          FUNCTION_FLOW("ADD_CHAR");
          if (it < filecode.end() - 2 && *(it + 2) == '\'')
          {
               std::string val = (std::string) "\'" + *(++it) + '\'';
               vec.push_back(val);
               it += 2;
               FUNCTION_FLOW("EXIT ADD_CHAR");
               return;
          }
          LOGS_PRINT("ADD_CHAR");
          DISPLAY_EXCEPTION("extracting value of Char Type.", InvalidValueException);
     }

     // used to add the numeric type values starting with a number to the vector "vec".
     inline static void ADD_NUMBER()
     {
          
          FUNCTION_FLOW("ADD_NUMBER");
          LOGS_PRINT("ADD_NUMBER");
          if (!(*it == '-' && it != filecode.end() - 1 && is_number(*(it + 1))))
          {
               vec.push_back("-");
               ++it;
               return;
          }
          ++it;
          string val = "-";
          while (it < filecode.end() && (is_number(*it) || *it == '.'))
          {
               val += *it;
               ++it;
          }
          vec.push_back(val);
          FUNCTION_FLOW("EXIT ADD_NUMBER");
     }

     // used to add the values starting with a underscore or a alphabet to the vector "vec".
     inline static void ADD_IDENTIFIER()
     {
          
          FUNCTION_FLOW("ADD_IDENTIFIER");
          std::string val = (std::string) "" + *it;
          /* It will iterate until a character other than End of string, alphabet, number or underscore arises.*/
          ++it;
          while (it < filecode.end() && (is_alpha_number(*it) || *it == '_'))
          {
               val += *it;
               ++it;
          }
          vec.push_back(val);
          FUNCTION_FLOW("EXIT ADD_IDENTIFIER");
     }

     // used to break the instruction into tokens and save it to the vec.
     inline static void BREAK_INSTRUCTION_TO_LEX()
     {
          
          FUNCTION_FLOW("BREAK_INSTRUCTION_TO_LEX");
          //LOGS_PRINT("BREAK_INSTRUCTION_TO_LEX");
          while (it < filecode.end() && *it != '\n')
          {
               if(*it == ' '){
                    ++it;
                    continue;
               }
               else if(*it == '\n'){
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
                    HANDLE_SCOPES();

               }
               else if (*it == '[' || *it == ']' || *it == '(' || *it == ')' || *it == ',' || *it == '+' || *it == '-' || *it == '*' 
               || *it == '/' || *it == '%' || *it == '^' || *it == '~')
               {
                    vec.push_back((std::string) "" + *it);
               }
               else if(*it == '=' || *it == '&' || *it == '|'){       // characters which can be used as pairs
                    if (it < filecode.end() - 1 && *it == *(it+1))
                    {
                         vec.push_back((std::string) "" + *it+*it);
                    }
                    else{
                         vec.push_back((std::string) "" + *it);
                    }
               }
               else if(*it == '!'){
                    if(it < filecode.end() - 1 && *(it+1) == '='){
                         vec.push_back("!=");
                         ++it;
                    }
                    else{
                         vec.push_back("!");
                    }
               }
               else
               {
                    LOGS_PRINT("BREAK_INSTRUCTION_TO_LEX");
                    DISPLAY_EXCEPTION("analysing the code.", WrongSyntaxException);
               }
               ++it;
          }

          FUNCTION_FLOW("EXIT BREAK_INSTRUCTION_TO_LEX");
     }

     inline static void GET_ATTRIBUTE()
     {
          FUNCTION_FLOW("GET_ATTRIBUTE");
          printf("\n>>>%c",*it);
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
               HANDLE_SCOPES();
          }
          else
          {
               LOGS_PRINT("GET_ATTRIBUTE");
               DISPLAY_EXCEPTION("analysing the code.", InvalidAttributeException);
          }
          FUNCTION_FLOW("EXIT GET_ATTRIBUTE");
     }

     inline static void ADD_PAIR()
     {
          
          FUNCTION_FLOW("ADD_PAIR");
          if (attribute.length() == 0 || vec.size() == 0)
          {
               return;
               // LOGS_PRINT("ADD_PAIR IF");
               // DISPLAY_EXCEPTION("analysing the code.", WrongSyntaxException);
          }
          else if (attribute == "name")
          {
               if (vec.size() == 1)
               {
                    LEXICAL_ANALYSER::function_name = vec[0];
               }
               else
               {
                    LOGS_PRINT("ADD_PAIR ELSE IF");
                    DISPLAY_EXCEPTION("analysing the code and extracting the name of the function.", EmptyAttributeCode);
               }
          }
          else{
               inst_vector.push_back(InstructionPair(attribute, vec));
          }
          attribute = "";
          vec.clear();
          FUNCTION_FLOW("EXIT ADD_PAIR");
          
     }

     inline static void LEX(std::string &str)
     {
          FUNCTION_FLOW("LEX");
          LEXICAL_ANALYSER::filecode = str;
          LEXICAL_ANALYSER::it = filecode.begin();

          JUMP_TO_NEXT_FIRST_OCCURENCE('{');
          ++it;
          if (it < filecode.end())
          {
               while (it < filecode.end())
               {
                    Logs::INCREMENT_LINE_NUMBER();
                    JUMP_SPACE_AND_NEWLINE();
                    GET_ATTRIBUTE();

                    if (it < filecode.end())
                    {
                         if(attribute == "{" || attribute == "}" ){
                              continue;
                         }
                         else if (attribute.length() != 0 && attribute != "comment")
                         {

                              JUMP_TO_NEXT_FIRST_OCCURENCE(':');
                              ++it;
                              JUMP_TILL_CHAR_REPEATS(' ');
                              if (it >= filecode.end() || *it == '\n')
                              {
                                   LOGS_PRINT("LEX - 1");
                                   DISPLAY_EXCEPTION("analysing the code and extracting the instruction of an attribute.", EmptyAttributeCode);
                              }
                              BREAK_INSTRUCTION_TO_LEX();
                              ADD_PAIR();
                              Logs::INCREMENT_LINE_NUMBER();
                         }
                         else if(attribute == "comment"){
                              JUMP_TO_NEXT_FIRST_OCCURENCE('\n');
                              JUMP_SPACE_AND_NEWLINE();
                         }
                    }
                    else
                    {
                         break;
                    }
               }
          }
          else
          {
               LOGS_PRINT("LEX - 2");
               DISPLAY_EXCEPTION("analyzing the code.", NoValidCodeFoundException);
          }
     }

     
}

#endif

inline static void print_vector(std::vector<std::string> vec)
{
     if (vec.size() == 0)
     {
          printf("[]");
          return;
     }
     printf("[");
     std::vector<std::string>::const_iterator it;
     for (it = vec.begin(); it != vec.end() - 1; ++it)
     {
          printf("%s, ", (*it).c_str());
     }
     printf("%s ]", (*it).c_str());
}

// int main()
// {
//      std::string sron_code = "{"
//                              " name : Armstrong"
//                              "args: Int val"
//                              "type: Int"
//                              " variables : Int arm,Int temp,Int len"
//                              "0 : len = LEN(TO_STRING(val))"
//                              "while:{"
//                              "condition:(val != 0)"
//                              "0 : temp = val%10"
//                              "1 : arm = arm+temp^len"
//                              " 2 : val = val%10"
//                              "}"
//                              "return : arm"
//                              "}"
//                              "{"
//                              "name : main"
//                              "variables:Int val"
//                              "0 : val = INPUT_INT(\"\n ==> Enter the value :- \")"
//                              "if:{"
//                              "condition: (val = Armstrong(val))"
//                              "1 : PRINTLN(\"Yes, \",val,\" is an Armstrong Number.\")"
//                              "}"
//                              "else:{"
//                              "1 : PRINTLN(\"No, \",val,\" is not an Armstrong Number.\")"
//                              "}"
//                              "return : 0"
//                              "}";
//      LEXICAL_ANALYSER::LEX(sron_code);

// }