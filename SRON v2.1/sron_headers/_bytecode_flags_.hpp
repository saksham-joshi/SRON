
#pragma once

#ifndef _FLAG_H_
#define _FLAG_H_

typedef unsigned short int flag_t;
typedef long int byteindex_t;

constexpr static const char* const __void_printable_string__ = "<#-Void-#>";


//=================== Datatypes Flags
constexpr flag_t Flag_Any = 0; //"`A"
constexpr flag_t Flag_Int = 1 ;//"`I";
constexpr flag_t Flag_Double = 2; //"`D";
constexpr flag_t Flag_Char = 3 ;//"`C";
constexpr flag_t Flag_String = 4; //"`S";
constexpr flag_t Flag_Bool = 5; //"`B";
constexpr flag_t Flag_List = 6 ;//"`L";
constexpr flag_t Flag_Void = 7 ;//"`vd";

constexpr flag_t Flag_Int_Value = 8 ;//"`Iv";
constexpr flag_t Flag_Double_Value = 9; //"`Dv";
constexpr flag_t Flag_Char_Value = 10 ;//"`Cv";
constexpr flag_t Flag_Bool_Value = 11;//"`Bv";
constexpr flag_t Flag_String_Value = 12; //"`Sv";

constexpr flag_t Flag_Assign = 13; //"`=";
constexpr flag_t Flag_Free = 14; //"`fr";

constexpr flag_t Flag_String_Print= 15; 
constexpr flag_t Flag_Char_Print = 16; 

constexpr flag_t Flag_InBuiltFunctionCall = 17; //"`F";

constexpr flag_t Flag_FunctionArgsScopeStart = 18; //"`A{";
constexpr flag_t Flag_FunctionArgsScopeEnd = 19; //"`A}";

constexpr flag_t Flag_FunctionName = 20 ;  
constexpr flag_t Flag_Break = 21;        
constexpr flag_t Flag_Continue = 22 ;    

constexpr flag_t Flag_Args_Start = 23;   // Flag to open the argument list passed to a function call
constexpr flag_t Flag_Args_End = 24;     // Flag to close the argument list passed to a function call

constexpr flag_t Flag_ListStart = 25;    // "["
constexpr flag_t Flag_ListEnd = 26;      // "]" 

constexpr flag_t Flag_Return = 27;       //"`R"
constexpr flag_t Flag_Identifier_Variable = 28; //"`id"

constexpr flag_t Flag_RangeScopeStart = 29 ;//"`rng{";
constexpr flag_t Flag_RangeScopeEnd = 30; //"`rng}";

constexpr flag_t Flag_Condition = 31; //"`cnd";

constexpr flag_t Flag_ForScopeStart = 32 ;//"`fr{";
constexpr flag_t Flag_ForScopeEnd = 33 ;//"`fr}";

constexpr flag_t Flag_WhileScopeStart = 34; //"`wh{";
constexpr flag_t Flag_WhileScopeEnd = 35 ;//"`wh}";

constexpr flag_t Flag_IfScopeStart = 36 ;//"`if{";
constexpr flag_t Flag_IfScopeEnd = 37;//"`if}";

constexpr flag_t Flag_ElifScopeStart = 38; //"`el{";
constexpr flag_t Flag_ElifScopeEnd = 39 ;//"`el}";

constexpr flag_t Flag_ElseScopeStart = 40; //"`els{";
constexpr flag_t Flag_ElseScopeEnd = 41; //"`els}";

constexpr flag_t Flag_EvalStart = 42 ;//"`ev{";
constexpr flag_t Flag_EvalEnd = 43; //"`ev}";

constexpr flag_t Flag_RotateScopeStart = 44; //"`rt{";
constexpr flag_t Flag_RotateScopeEnd = 45; //"`rt}";

constexpr flag_t Flag_ConsoleStart = 46; //"`cns{";
constexpr flag_t Flag_ConsoleEnd = 47; //"`cns}";

constexpr flag_t Flag_Operator = 48; //"`op";

constexpr flag_t Flag_Add = 49; // '+'
constexpr flag_t Flag_Minus = 50; // '-'
constexpr flag_t Flag_Mult = 51; // '*'
constexpr flag_t Flag_Div = 52; // '/'
constexpr flag_t Flag_Mod = 53; // '%'
constexpr flag_t Flag_Pow = 54; // '^'

constexpr flag_t Flag_And = 55; // '^'
constexpr flag_t Flag_Or = 56; // '^'
constexpr flag_t Flag_Not = 57; // '^'

constexpr flag_t Flag_NotEqual = 58; // '!='
constexpr flag_t Flag_Compare = 59; // '=='
constexpr flag_t Flag_LessThan = 60; // '<'
constexpr flag_t Flag_LessThanEqual = 61; // '<='
constexpr flag_t Flag_MoreThan = 62; // '>'
constexpr flag_t Flag_MoreThanEqual = 63; // '>='

constexpr flag_t Flag_StrictCompare = 64;  // '==='

constexpr flag_t Flag_AddAssign = 65 ;  // '+='
constexpr flag_t Flag_MinusAssign = 66 ;  // '-='
constexpr flag_t Flag_MultAssign = 67 ;  // '*='
constexpr flag_t Flag_DivAssign = 68 ;  // '/='
constexpr flag_t Flag_ModAssign = 69 ;  // '%='
constexpr flag_t Flag_PowAssign = 70 ;  // '^='

constexpr flag_t Flag_UserDefinedFunctionCall = 71;

constexpr flag_t Flag_Negate = 72; // 

constexpr  flag_t Flag_IntExtractor = 73;
constexpr  flag_t Flag_DoubleExtractor = 74;
constexpr  flag_t Flag_CharExtractor = 75;
constexpr  flag_t Flag_BoolExtractor = 76;
constexpr  flag_t Flag_StringExtractor = 77;
constexpr  flag_t Flag_ListExtractor = 78;

constexpr flag_t Flag_UnaryOperator = 79;

constexpr flag_t Flag_CodeCompleted = 80; // flag to ensure that the execution of the function is completed

constexpr flag_t Flag_True = 81;

constexpr flag_t Flag_False = 82;

constexpr flag_t Flag_StrictInt = 83;
constexpr flag_t Flag_StrictDouble = 84;
constexpr flag_t Flag_StrictChar = 85;
constexpr flag_t Flag_StrictBool = 86;
constexpr flag_t Flag_StrictString = 87;
constexpr flag_t Flag_StrictList = 88;

constexpr flag_t Flag_Xor = 89;
constexpr flag_t Flag_Lshift = 90;
constexpr flag_t Flag_Rshift = 91;
constexpr flag_t Flag_BitwiseAnd = 92;
constexpr flag_t Flag_BitwiseOr = 93;
constexpr flag_t Flag_BitwiseNot = 94;

constexpr flag_t Flag_ReturnType = 95;
constexpr flag_t Flag_ForeachScopeStart = 96;
constexpr flag_t Flag_ForeachScopeEnd = 97;
constexpr flag_t Flag_ForeachOn = 98; // a

#endif