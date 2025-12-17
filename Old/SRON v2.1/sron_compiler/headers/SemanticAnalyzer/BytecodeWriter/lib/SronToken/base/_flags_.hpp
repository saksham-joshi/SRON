
#pragma once

#ifndef FLAG_H
#define FLAG_H

// #define SRON_DEVELOPMENT_PHASE
// #define SRON_DEBUG_MODE

#include "../../../../../../../sron_headers/_bytecode_flags_.hpp"


//=================== Attributes Flags

constexpr const char*const AttributeName = "name";
constexpr const char*const AttributeIf = "if";
constexpr const char*const AttributeElif = "elif";
constexpr const char*const AttributeElse = "else";
constexpr const char*const AttributeFor = "for";
constexpr const char*const AttributeWhile = "while";
constexpr const char*const AttributeReturn = "return";
constexpr const char*const AttributeCondition = "condition";
constexpr const char*const AttributeRange = "range";
constexpr const char*const AttributeArgs = "args";
constexpr const char*const AttributeFree = "free";
constexpr const char*const AttributeRotate = "rotate";
constexpr const char*const AttributeConsole = "console";
constexpr const char*const AttributeType = "type";
constexpr const char*const AttributeForeach = "foreach";
constexpr const char*const AttributeForeachOn = "on";

constexpr const flag_t Flag_bydefault = 599U;

//=================== Flags for Datatypes and Operators !
constexpr const unsigned short int TYPE_VOID = 0; // Void
constexpr const unsigned short int TYPE_INT = 1;
constexpr const unsigned short int TYPE_DOUBLE = 2;
constexpr const unsigned short int TYPE_CHAR = 3; // ' '
constexpr const unsigned short int TYPE_BOOL = 4; // true or false
constexpr const unsigned short int TYPE_STRING = 5; // " "
constexpr const unsigned short int TYPE_LIST = 6;

constexpr const unsigned short int TYPE_LIST_OPEN = 7; // [
constexpr const unsigned short int TYPE_LIST_CLOSE = 8; // ]

constexpr const unsigned short int TYPE_IDENTIFIER = 9;
constexpr const unsigned short int TYPE_OPERATOR = 10;
constexpr const unsigned short int TYPE_ATTRIBUTE = 11;

constexpr const unsigned short int TYPE_CLOSING_BRACKETS = 12; // )
constexpr const unsigned short int TYPE_OPENING_BRACKETS = 13; // (

constexpr const unsigned short int TYPE_KEYWORD = 14;
constexpr const unsigned short int TYPE_COLON = 15; // :
constexpr const unsigned short int TYPE_MATH_BLOCK = 16; // ~

constexpr const unsigned short int TYPE_FUNCTION_SCOPE_START = 17; // {
constexpr const unsigned short int TYPE_FUNCTION_SCOPE_CLOSE = 18;  // }

constexpr const unsigned short int TYPE_FUNCTION_CALL = 19;
constexpr const unsigned short int TYPE_NEWLINE = 20;

constexpr const unsigned short int TYPE_ASSIGN = 21; // =
constexpr const unsigned short int TYPE_DATATYPE = 22;

constexpr const unsigned short int TYPE_COMMA = 23; // ,
constexpr const unsigned short int TYPE_IDENTIFIER_WITH_DOT = 24;

constexpr const unsigned short int TYPE_CALC_ASSIGN = 25;

constexpr const unsigned short int TYPE_STRICT_TYPE = 26;
/*
  If a new type is added here... it must be added to Support::TYPE_FLAG_TO_STRING 
   function for the sake of better debugging of the compiler
*/

#endif