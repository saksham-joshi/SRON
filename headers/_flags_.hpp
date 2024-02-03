

/*
 * These flag are used to 
*/
#ifndef FLAG_H
#define FLAG_H

#define AttributeName "name"
#define AttributeType "type"
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

#define Flag_Int "`I"
#define Flag_Double "`D"
#define Flag_Char "`C"
#define Flag_String "`S"
#define Flag_Bool "`B"
#define Flag_List "`L"

#define Flag_FunctionCall "`F"
#define Flag_Args "`A"
#define Flag_Variable "`V"

#define Flag_ScopeStart "`{"
#define Flag_ScopeEnd "`}"

#define Flag_Return "`R"

#define Flag_MathEval "`M"
#define Flag_BoolEval "`E"


#define TYPE_VOID 0
#define TYPE_INT 1
#define TYPE_DOUBLE 2
#define TYPE_CHAR 3
#define TYPE_BOOL 4
#define TYPE_STRING 5
#define TYPE_LIST 6
#define IDENTIFIER 7

#endif