
#pragma once

#ifndef _FLAG_H_
#define _FLAG_H_

#include "_bytecode_components_.hpp"

enum class BytecodeFlags : Flag_t
{
    Flag_Any, 
    Flag_Int,
    Flag_Double,
    Flag_Char,
    Flag_String,
    Flag_Bool,
    Flag_List,
    Flag_FileReader,
    Flag_FileWriter,
    Flag_Lstr,

    Flag_IntExtractor,
    Flag_DoubleExtractor,
    Flag_CharExtractor,
    Flag_BoolExtractor,
    Flag_StringExtractor,
    Flag_ListExtractor,
    Flag_FwriteExtractor,
    Flag_FreadExtractor,
    Flag_LstrExtractor,

    Flag_StrictInt,
    Flag_StrictDouble,
    Flag_StrictChar,
    Flag_StrictBool,
    Flag_StrictString,
    Flag_StrictList,
    Flag_StrictFreader,
    Flag_StrictFwriter,
    Flag_StrictLstr,

    Flag_Int_Value,
    Flag_Double_Value,
    Flag_Char_Value,
    Flag_String_Value,
    Flag_ListStart,

    Flag_True,
    Flag_False,
    Flag_Void,

    Flag_AddAssign,
    Flag_MinusAssign,
    Flag_MultAssign,
    Flag_DivAssign,
    Flag_ModAssign,
    Flag_PowAssign,

    Flag_Assign,

    Flag_InBuiltFunctionCall,
    Flag_UserDefinedFunctionCall,

    Flag_FunctionParamScopeStart,

    Flag_Return,

    Flag_Identifier_Variable,

    Flag_ForScopeStart,
    Flag_WhileScopeStart,
    Flag_ForeachScopeStart,

    Flag_IfScopeStart,
    Flag_ElifScopeStart,
    Flag_ElseScopeStart,

    Flag_IfScopeEnd,
    Flag_ElifScopeEnd,
    Flag_ElseScopeEnd,

    Flag_EvalStart,

    Flag_RotateScopeStart,

    Flag_ConsoleStart,

    Flag_CodeCompleted,

    Flag_OBuffer,

    // Flags which are not mapped by Function Map of Execution Engine
    Flag_String_Print,
    Flag_Char_Print,

    Flag_FunctionParamScopeEnd,

    Flag_FunctionName,
    Flag_Break,
    Flag_Continue,

    Flag_Args_Start,
    Flag_Args_End,
    
    Flag_ReturnType,

    Flag_RangeScopeStart,
    Flag_RangeScopeEnd,

    Flag_Condition,
    Flag_ForeachOn,

    Flag_ForeachScopeEnd,
    
    Flag_ForScopeEnd,
    
    Flag_WhileScopeEnd,
    
    Flag_RotateScopeEnd,

    Flag_ConsoleEnd,
    
    Flag_EvalEnd,

    Flag_Operator,
    Flag_UnaryOperator,

    Flag_Add,
    Flag_Minus,
    Flag_Mult,
    Flag_Div,
    Flag_Mod,
    Flag_Pow,

    Flag_And,
    Flag_Or,
    Flag_Not,

    Flag_NotEqual,
    Flag_StrictCompare,
    Flag_Compare,
    Flag_LessThan,
    Flag_LessThanEqual,
    Flag_MoreThan,
    Flag_MoreThanEqual,

    Flag_Negate,

    Flag_Xor,
    Flag_Lshift,
    Flag_Rshift,
    Flag_BitwiseAnd,
    Flag_BitwiseOr,
    Flag_BitwiseNot,

    Flag_ListEnd,

    Flag_Windows,
    Flag_Linux,

    Flag_bydefault
};

#endif