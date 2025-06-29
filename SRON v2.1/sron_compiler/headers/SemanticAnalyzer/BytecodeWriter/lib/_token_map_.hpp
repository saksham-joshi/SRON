
#pragma once

#ifndef _TKN_MP_H
#define _TKN_MP_H

//#include "_bytecode_writer_.hpp"

#include "SronToken/_sron_token_.hpp"

namespace TokenMaps
{

    const static std::unordered_map<std::string, const SronToken> token_map{

        {"name", SronToken(TYPE_ATTRIBUTE, "name", Flag_FunctionName)},

        {"if", SronToken(TYPE_ATTRIBUTE, "if", Flag_IfScopeStart)},
        {"elif", SronToken(TYPE_ATTRIBUTE, "elif", Flag_ElifScopeStart)},
        {"else", SronToken(TYPE_ATTRIBUTE, "else", Flag_ElseScopeStart)},

        {"for", SronToken(TYPE_ATTRIBUTE, "for", Flag_ForScopeStart)},
        {"while", SronToken(TYPE_ATTRIBUTE, "while", Flag_WhileScopeStart)},
        {"foreach", SronToken(TYPE_ATTRIBUTE, "foreach", Flag_ForeachScopeStart)},

        {"range", SronToken(TYPE_ATTRIBUTE, "range", Flag_RangeScopeStart)},
        {"condition", SronToken(TYPE_ATTRIBUTE, "condition", Flag_Condition)},
        {"on", SronToken(TYPE_ATTRIBUTE, "on", Flag_ForeachOn)},

        {"args", SronToken(TYPE_ATTRIBUTE, "args", Flag_FunctionArgsScopeStart)},
        {"free", SronToken(TYPE_ATTRIBUTE, "free", Flag_Free)},
        {"return", SronToken(TYPE_ATTRIBUTE, "return", Flag_Return)},

        {"type", SronToken(TYPE_ATTRIBUTE, "type", Flag_ReturnType)},
        {"rotate", SronToken(TYPE_ATTRIBUTE, "rotate", Flag_RotateScopeStart)},
        {"console", SronToken(TYPE_ATTRIBUTE, "console", Flag_ConsoleStart)},

        {"{", SronToken(TYPE_FUNCTION_SCOPE_START, "{", Flag_bydefault)},
        {"}", SronToken(TYPE_FUNCTION_SCOPE_CLOSE, "}", Flag_bydefault)},

        {"(", SronToken(TYPE_OPENING_BRACKETS, "(", Flag_Args_Start)},
        {")", SronToken(TYPE_CLOSING_BRACKETS, ")", Flag_Args_End)},

        {"[", SronToken(TYPE_LIST_OPEN, "[", Flag_ListStart)},
        {"]", SronToken(TYPE_LIST_CLOSE, "]", Flag_ListEnd)},

        {"~{", SronToken(TYPE_MATH_BLOCK, "~{", Flag_EvalStart)},
        {"}~", SronToken(TYPE_MATH_BLOCK, "}~", Flag_EvalEnd)},

        {"Any", SronToken(TYPE_DATATYPE, "Any", Flag_Any)},
        {"Int", SronToken(TYPE_DATATYPE, "Int", Flag_Int)},
        {"Double", SronToken(TYPE_DATATYPE, "Double", Flag_Double)},
        {"Char", SronToken(TYPE_DATATYPE, "Char", Flag_Char)},
        {"Bool", SronToken(TYPE_DATATYPE, "Bool", Flag_Bool)},
        {"String", SronToken(TYPE_DATATYPE, "String", Flag_String)},
        {"List", SronToken(TYPE_DATATYPE, "List", Flag_List)},

        // strict types
        {"Int_s", SronToken(TYPE_DATATYPE, "Int_s", Flag_StrictInt)},
        {"Double_s", SronToken(TYPE_DATATYPE, "Double_s", Flag_StrictDouble)},
        {"Char_s", SronToken(TYPE_DATATYPE, "Char_s", Flag_StrictChar)},
        {"Bool_s", SronToken(TYPE_DATATYPE, "Bool_s", Flag_StrictBool)},
        {"String_s", SronToken(TYPE_DATATYPE, "String_s", Flag_StrictString)},
        {"List_s", SronToken(TYPE_DATATYPE, "List_s", Flag_StrictList)},

        {"PI", SronToken(TYPE_DOUBLE, "3.141592653", Flag_Double_Value)},
        {"true", SronToken(TYPE_BOOL, "true", Flag_True)},
        {"false", SronToken(TYPE_BOOL, "false", Flag_False)},

        {"break", SronToken(TYPE_KEYWORD, "break", Flag_Break)},
        {"continue", SronToken(TYPE_KEYWORD, "continue", Flag_Continue)},
        {"Void", SronToken(TYPE_VOID, "Void", Flag_Void)},

        {"=", SronToken(TYPE_ASSIGN, "=", Flag_Assign)},
        {",", SronToken(TYPE_COMMA, ",", Flag_bydefault)},
        {":", SronToken(TYPE_COLON, ":", Flag_bydefault)},
        {"\n", SronToken(TYPE_NEWLINE, "\n", Flag_bydefault , 1 )},

        // Arithmetic operators...
        {"+", SronToken(TYPE_OPERATOR, "+", Flag_Add)},
        {"-", SronToken(TYPE_OPERATOR, "-", Flag_Minus)},
        {"*", SronToken(TYPE_OPERATOR, "*", Flag_Mult)},
        {"/", SronToken(TYPE_OPERATOR, "/", Flag_Div)},
        {"%", SronToken(TYPE_OPERATOR, "%", Flag_Mod)},
        {"^", SronToken(TYPE_OPERATOR, "^", Flag_Pow)},

        // logical operators...
        {"&&", SronToken(TYPE_OPERATOR, "&&", Flag_And)},
        {"||", SronToken(TYPE_OPERATOR, "||", Flag_Or)},
        {"!", SronToken(TYPE_OPERATOR, "!", Flag_Not)},

        // comparison operators...
        {"!=", SronToken(TYPE_OPERATOR, "!=", Flag_NotEqual)},
        {"==", SronToken(TYPE_OPERATOR, "==", Flag_Compare)},
        {"<", SronToken(TYPE_OPERATOR, "<", Flag_LessThan)},
        {"<=", SronToken(TYPE_OPERATOR, "<=", Flag_LessThanEqual)},
        {">", SronToken(TYPE_OPERATOR, ">", Flag_MoreThan)},
        {">=", SronToken(TYPE_OPERATOR, ">=", Flag_MoreThanEqual)},

        {"===", SronToken(TYPE_OPERATOR, "===", Flag_StrictCompare)},

        // assignment operators...
        {"+=", SronToken(TYPE_CALC_ASSIGN, "+=", Flag_AddAssign)},
        {"-=", SronToken(TYPE_CALC_ASSIGN, "-=", Flag_MinusAssign)},
        {"*=", SronToken(TYPE_CALC_ASSIGN, "*=", Flag_MultAssign)},
        {"/=", SronToken(TYPE_CALC_ASSIGN, "/=", Flag_DivAssign)},
        {"%=", SronToken(TYPE_CALC_ASSIGN, "%=", Flag_ModAssign)},
        {"^=", SronToken(TYPE_CALC_ASSIGN, "^=", Flag_PowAssign)},
        
        {"xor", SronToken(TYPE_OPERATOR, "xor", Flag_Xor)},
        {"lsft", SronToken(TYPE_OPERATOR, "lsft", Flag_Lshift)},
        {"rsft", SronToken(TYPE_OPERATOR, "rsft", Flag_Rshift)},
        {"and", SronToken(TYPE_OPERATOR, "and", Flag_BitwiseAnd )},
        {"or", SronToken(TYPE_OPERATOR, "or", Flag_BitwiseOr )},
        {"not", SronToken(TYPE_OPERATOR, "not", Flag_BitwiseNot )},
        
        // exceptions ...
        {"IndexNotWithinRange", SronToken(TYPE_STRING, "\"IndexNotWithinRange\"", Flag_String_Value)},
        {"DivisionByZeroException", SronToken(TYPE_STRING, "\"DivisionByZeroException\"", Flag_String_Value)},
        {"InputTypeException", SronToken(TYPE_STRING, "\"InputTypeException\"", Flag_String_Value)} };

    
    inline static const SronToken &EXTRACT_TOKEN_FROM_TOKEN_MAP(const std::string& _token)
    {

        const auto& tk = TokenMaps::token_map.find(_token);

        if (tk == TokenMaps::token_map.end())
        {
            throw ThrowException("finding the token in the map. Cannot find the token '" + _token + "'");
        }

        return tk->second;
    }
}

#endif