
#pragma once

#ifndef _SRON_FNC_H_
#define _SRON_FNC_H_

#include "_bytecode_file_mng_.hpp"

struct SronFunction
{
    SronByteCodeFileManip _codefile;

    // this variable contains the variables
    VariableManager _Vmanager;

    // ArgumentList containing the values passed to the function
    ArgListPtr _arglist;

    AnyBindPtr _return_value;

    inline SronFunction( const char*const&__function_name, ArgListPtr __args, AnyBindPtr __returnValue = Void::void_object) 
    : _codefile(__function_name), _arglist(__args) , _return_value(__returnValue)
               {  Logs::__FileStack__.push_back(__function_name);  }

    inline SronFunction(std::string &__function_name, ArgListPtr __args, AnyBindPtr __returnValue = Void::void_object) 
    : _codefile(__function_name.c_str()) , _arglist(__args) , _return_value(__returnValue) 
               {  Logs::__FileStack__.push_back(__function_name);  }

    ~SronFunction() { }
};

typedef SronFunction* SronFncPtr;

#endif


inline const char* FLAG_TO_STRING(flag_t __flag){

        switch(__flag){

            case Flag_Any : return "Any";

            case Flag_Int : return "Int";

            case Flag_Double : return "Double";

            case Flag_Char : return "Char";

            case Flag_String : return "String";

            case Flag_Bool : return "Bool";

            case Flag_List : return "List";

            case Flag_Void : return "Void";

            case Flag_Int_Value : return "Int-value";

            case Flag_Double_Value : return "Double-value";

            case Flag_Char_Value : return "Char-value";

            case Flag_String_Value : return "String-value";

            case Flag_Bool_Value : return "Bool-value";

            case Flag_Assign : return "Assign";

            case Flag_Free : return "Free";

            case Flag_InBuiltFunctionCall : return "In-built Fnc";

            case Flag_FunctionArgsScopeStart : return "args{";

            case Flag_FunctionArgsScopeEnd : return "args}";

            case Flag_Break : return "break";

            case Flag_Continue : return "continue";

            case Flag_Args_Start : return "(";

            case Flag_Args_End : return ")";

            case Flag_ListStart : return "[";
            
            case Flag_ListEnd : return "]";

            case Flag_Return : return "return";

            case Flag_Identifier_Variable : return "identifier";

            case Flag_RangeScopeStart : return "range{";

            case Flag_RangeScopeEnd : return "range}";

            case Flag_Condition : return "condition";

            case Flag_ForScopeStart : return "for{";

            case Flag_ForScopeEnd : return "for}";

            case Flag_WhileScopeStart : return "while{";

            case Flag_WhileScopeEnd : return "while}";

            case Flag_IfScopeStart : return "if{";

            case Flag_IfScopeEnd : return "if}";

            case Flag_ElifScopeStart : return "elif{";

            case Flag_ElifScopeEnd : return "elif}";

            case Flag_ElseScopeStart : return "else{";

            case Flag_ElseScopeEnd : return "else}";

            case Flag_EvalStart : return "~{";

            case Flag_EvalEnd : return "~}";

            case Flag_RotateScopeStart : return "rotate{";

            case Flag_RotateScopeEnd : return "rotate}";

            case Flag_ConsoleStart : return "console{";

            case Flag_ConsoleEnd : return "console}";

            case Flag_Operator : return "operator";

            case Flag_Add : return "+";

            case Flag_Minus : return "-";

            case Flag_Mult : return "*";

            case Flag_Div : return "/";

            case Flag_Mod : return "%";

            case Flag_Pow : return "^";

            case Flag_And : return "&&";

            case Flag_Or : return "||";

            case Flag_Not : return "!";

            case Flag_NotEqual : return "!=";

            case Flag_Compare : return "==";

            case Flag_LessThan : return "<";

            case Flag_LessThanEqual : return "<=";

            case Flag_MoreThan : return ">";

            case Flag_MoreThanEqual : return ">=";

            case Flag_StrictCompare : return "===";

            case Flag_AddAssign : return "+=";

            case Flag_MinusAssign : return "-=";

            case Flag_MultAssign : return "*=";

            case Flag_DivAssign : return "/=";

            case Flag_ModAssign : return "%=";

            case Flag_PowAssign : return "^=";

            case Flag_UserDefinedFunctionCall : return "user-defined FNC";

            case Flag_Negate : return "Negate";

            case Flag_IntExtractor : return "Int-Extractor";

            case Flag_DoubleExtractor : return "Double-Extractor";

            case Flag_CharExtractor : return "Char-Extractor";

            case Flag_BoolExtractor : return "Bool-Extractor";

            case Flag_StringExtractor : return "String-Extractor";

            case Flag_ListExtractor : return "List-Extractor";

            case Flag_UnaryOperator : return "Unary-Operator";

            case Flag_CodeCompleted : return "Code-done";

            case Flag_True : return "true";

            case Flag_False : return "false";

            case Flag_BitwiseAnd : return "Bitwise-and";

            case Flag_BitwiseOr : return "Bitwise-or";

            case Flag_BitwiseNot : return "Bitwise-not";

            case Flag_Lshift : return "Bitwise-LeftShift";

            case Flag_Rshift : return "Bitwise-RightShift";

            case Flag_Xor : return "Bitwise-Xor";

            default : return "Unidentified-Flag";
        
        }
    }