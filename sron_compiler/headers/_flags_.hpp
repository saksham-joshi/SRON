
#pragma once

#ifndef FLAG_H
#define FLAG_H

#define PI_VALUE "3.141592653"


//=================== Attributes Flags

#define AttributeName "name"
#define AttributeVariables "variables"
#define AttributeIf "if"
#define AttributeElif "elif"
#define AttributeElse "else"
#define AttributeFor "for"
#define AttributeWhile "while"
#define AttributeReturn "return"
#define AttributeCondition "condition"
#define AttributeComment "comment"
#define AttributeArgs "args"
#define AttributeRange "range"
#define AttributeFree "free"


//=================== Datatypes Flags
#define Flag_Any "`Any"
#define Flag_Int "`I"
#define Flag_Double "`D"
#define Flag_Char "`C"
#define Flag_String "`S"
#define Flag_Bool "`B"
#define Flag_List "`L"
#define Flag_Void "`void"

#define Flag_Int_Value "`Iv"
#define Flag_Double_Value "`Dv"
#define Flag_Char_Value "`Cv"
#define Flag_Bool_Value "`Bv"
#define Flag_String_Value "`Sv"
//===================

#define Flag_Assign "`="
#define Flag_Free "`fr"

#define Flag_StringScopeStart "`S{"
#define Flag_StringScopeEnd "`S\"}"

#define Flag_FunctionCall "`F"

#define Flag_FunctionArgsScopeStart "`A{"
#define Flag_FunctionArgsScopeEnd "`A}"

#define Flag_Variable "`V"
#define Flag_Break "`Brk"
#define Flag_Continue "`Cntine"

#define Flag_ScopeStart "`{"
#define Flag_ScopeEnd "`}"
#define Flag_Args_Start "`("
#define Flag_Args_End "`)"
#define Flag_ListStart "`["
#define Flag_ListEnd "`]"

#define Flag_Return "`R"
#define Flag_Identifier_Variable "`idntfr"

#define Flag_RangeScopeStart "`rng{"
#define Flag_RangeScopeEnd "`rng}"

#define Flag_ConditionScopeStart "`cndtn{"
#define Flag_ConditionScopeEnd "`cndtn}"



//=================== Flags for control flow statements like for, while, if, elif, else.

#define Flag_ForScopeStart "`for{"
#define Flag_ForScopeEnd "`for}"

#define Flag_WhileScopeStart "`while{"
#define Flag_WhileScopeEnd "`while}"

#define Flag_IfScopeStart "`if{"
#define Flag_IfScopeEnd "`if}"

#define Flag_ElifScopeStart "`elif{"
#define Flag_ElifScopeEnd "`elif}"

#define Flag_ElseScopeStart "`else{"
#define Flag_ElseScopeEnd "`else}"


//=================== Flags for evaluations

#define Flag_EvalStart "`E~{"
#define Flag_EvalEnd "`E~}"


//=================== Flags for Datatypes and Operatos !

#define TYPE_VOID 0
#define TYPE_INT 1
#define TYPE_DOUBLE 2
#define TYPE_CHAR 3
#define TYPE_BOOL 4
#define TYPE_STRING 5
#define TYPE_LIST 6

#define TYPE_LIST_OPEN 7            // '['
#define TYPE_LIST_CLOSE 8           // ']'

#define TYPE_IDENTIFIER 9
#define TYPE_OPERATOR 10
#define TYPE_ATTRIBUTE 11

#define TYPE_CLOSING_BRACKETS 12     // ')'
#define TYPE_OPENING_BRACKETS 13     // '('

#define TYPE_KEYWORD 14
#define TYPE_COLON 15               // ':'
#define TYPE_MATH_BLOCK 16          // '~'

#define TYPE_FUNCTION_SCOPE_START 17 // '{'
#define TYPE_FUNCTION_SCOPE_CLOSE 18 // '}'

#define TYPE_FUNCTION_CALL 19

#define TYPE_NEWLINE 20              // '\n'

#define TYPE_ASSIGN 21               // '='

#define TYPE_DATATYPE 22

#define TYPE_COMMA 23                // ','

#endif