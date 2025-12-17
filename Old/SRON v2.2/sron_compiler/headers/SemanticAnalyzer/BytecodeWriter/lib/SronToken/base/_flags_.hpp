
#pragma once

#ifndef FLAG_H
#define FLAG_H


#include "../../../../../../../sron_headers/_bytecode_flags_.hpp"


//=================== Attributes Flags

constexpr const char*const AttributeName       = "name"         ;
constexpr const char*const AttributeIf         = "if"           ;
constexpr const char*const AttributeElif       = "elif"         ;
constexpr const char*const AttributeElse       = "else"         ;
constexpr const char*const AttributeFor        = "for"          ;
constexpr const char*const AttributeWhile      = "while"        ;
constexpr const char*const AttributeReturn     = "return"       ;
constexpr const char*const AttributeCondition  = "condition"    ;
constexpr const char*const AttributeRange      = "range"        ;
constexpr const char*const AttributeArgs       = "args"         ;
constexpr const char*const AttributeRotate     = "rotate"       ;
constexpr const char*const AttributeConsole    = "console"      ;
constexpr const char*const AttributeType       = "type"         ;
constexpr const char*const AttributeForeach    = "foreach"      ;
constexpr const char*const AttributeForeachOn  = "on"           ;

constexpr const Flag_t Flag_bydefault = 599U;

//=================== Flags for Datatypes and Operators !

enum SronTokenTypeSet : SronTokenType_t 
{
    TYPE_VOID                    ,
    TYPE_INT                     ,
    TYPE_DOUBLE                  ,
    TYPE_CHAR                    ,
    TYPE_BOOL                    ,
    TYPE_STRING                  ,

    TYPE_LIST_OPEN               ,
    TYPE_LIST_CLOSE              ,

    TYPE_ASSIGN                  ,
    TYPE_CALC_ASSIGN             ,
    TYPE_OPERATOR                ,

    TYPE_IDENTIFIER              ,
    TYPE_IDENTIFIER_WITH_DOT     ,
    TYPE_FUNCTION_CALL           ,

    TYPE_ATTRIBUTE               ,
    TYPE_KEYWORD                 ,
    TYPE_DATATYPE                ,
    TYPE_STRICT_TYPE             ,

    TYPE_MATH_BLOCK              ,
    TYPE_CLOSING_BRACKETS        ,
    TYPE_OPENING_BRACKETS        ,

    TYPE_FUNCTION_SCOPE_START    ,
    TYPE_FUNCTION_SCOPE_CLOSE    ,

    TYPE_NEWLINE                 ,
    TYPE_COLON                   ,
    TYPE_COMMA                   ,
           
};

/*
  If a new type is added here... it must be added to Support::TYPE_FLAG_TO_STRING 
   function for the sake of better debugging of the compiler
*/

#endif