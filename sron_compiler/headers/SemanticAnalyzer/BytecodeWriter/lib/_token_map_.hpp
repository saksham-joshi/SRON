
#pragma once

#ifndef _TKN_MP_H
#define _TKN_MP_H

#include "SronToken/_support_.hpp"

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

namespace TokenMaps
{

    const static std::unordered_map<std::string_view, SronToken> token_map{

        {"name", SronToken( SronTokenType::TYPE_ATTRIBUTE, "name", BytecodeFlags::Flag_FunctionName)}, 

        {"if", SronToken( SronTokenType::TYPE_ATTRIBUTE, "if", BytecodeFlags::Flag_IfScopeStart)},
        {"elif", SronToken( SronTokenType::TYPE_ATTRIBUTE, "elif", BytecodeFlags::Flag_ElifScopeStart)},
        {"else", SronToken( SronTokenType::TYPE_ATTRIBUTE, "else", BytecodeFlags::Flag_ElseScopeStart)},

        {"for", SronToken( SronTokenType::TYPE_ATTRIBUTE, "for", BytecodeFlags::Flag_ForScopeStart)},
        {"while", SronToken( SronTokenType::TYPE_ATTRIBUTE, "while", BytecodeFlags::Flag_WhileScopeStart)},
        {"foreach", SronToken( SronTokenType::TYPE_ATTRIBUTE, "foreach", BytecodeFlags::Flag_ForeachScopeStart)},

        {"range", SronToken( SronTokenType::TYPE_ATTRIBUTE, "range", BytecodeFlags::Flag_RangeScopeStart)},
        {"condition", SronToken( SronTokenType::TYPE_ATTRIBUTE, "condition", BytecodeFlags::Flag_Condition)},
        {"on", SronToken( SronTokenType::TYPE_ATTRIBUTE, "on", BytecodeFlags::Flag_ForeachOn)},

        {"args", SronToken( SronTokenType::TYPE_ATTRIBUTE, "args", BytecodeFlags::Flag_FunctionParamScopeStart)},
        {"return", SronToken( SronTokenType::TYPE_ATTRIBUTE, "return", BytecodeFlags::Flag_Return)},

        {"type", SronToken( SronTokenType::TYPE_ATTRIBUTE, "type", BytecodeFlags::Flag_ReturnType)},
        {"rotate", SronToken( SronTokenType::TYPE_ATTRIBUTE, "rotate", BytecodeFlags::Flag_RotateScopeStart)},
        {"console", SronToken( SronTokenType::TYPE_ATTRIBUTE, "console", BytecodeFlags::Flag_ConsoleStart)},

        {"windows", SronToken( SronTokenType::TYPE_ATTRIBUTE, "windows", BytecodeFlags::Flag_Windows)},
        {"linux", SronToken( SronTokenType::TYPE_ATTRIBUTE, "linux", BytecodeFlags::Flag_Linux)},

        {"{", SronToken( SronTokenType::TYPE_FUNCTION_SCOPE_START, "{", BytecodeFlags::Flag_bydefault)},
        {"}", SronToken( SronTokenType::TYPE_FUNCTION_SCOPE_CLOSE, "}", BytecodeFlags::Flag_bydefault)},

        {"(", SronToken( SronTokenType::TYPE_OPENING_BRACKETS, "(", BytecodeFlags::Flag_Args_Start)},
        {")", SronToken( SronTokenType::TYPE_CLOSING_BRACKETS, ")", BytecodeFlags::Flag_Args_End)},

        {"[", SronToken( SronTokenType::TYPE_LIST_OPEN, "[", BytecodeFlags::Flag_ListStart)},
        {"]", SronToken( SronTokenType::TYPE_LIST_CLOSE, "]", BytecodeFlags::Flag_ListEnd)},

        {"${", SronToken( SronTokenType::TYPE_MATH_BLOCK, "${", BytecodeFlags::Flag_EvalStart)},

        {"Any", SronToken( SronTokenType::TYPE_DATATYPE, "Any", BytecodeFlags::Flag_Any)},
        {"Int", SronToken( SronTokenType::TYPE_DATATYPE, "Int", BytecodeFlags::Flag_Int)},
        {"Double", SronToken( SronTokenType::TYPE_DATATYPE, "Double", BytecodeFlags::Flag_Double)},
        {"Char", SronToken( SronTokenType::TYPE_DATATYPE, "Char", BytecodeFlags::Flag_Char)},
        {"Bool", SronToken( SronTokenType::TYPE_DATATYPE, "Bool", BytecodeFlags::Flag_Bool)},
        {"String", SronToken( SronTokenType::TYPE_DATATYPE, "String", BytecodeFlags::Flag_String)},
        {"List", SronToken( SronTokenType::TYPE_DATATYPE, "List", BytecodeFlags::Flag_List)},
        {"FileReader", SronToken(SronTokenType::TYPE_DATATYPE, "FileReader", BytecodeFlags::Flag_FileReader)},
        {"FileWriter", SronToken(SronTokenType::TYPE_DATATYPE, "FileWriter", BytecodeFlags::Flag_FileWriter)},
        {"LiteralString", SronToken(SronTokenType::TYPE_DATATYPE, "LiteralString", BytecodeFlags::Flag_Lstr)},

        // strict types
        {"Int_s", SronToken( SronTokenType::TYPE_DATATYPE, "Int_s", BytecodeFlags::Flag_StrictInt)},
        {"Double_s", SronToken( SronTokenType::TYPE_DATATYPE, "Double_s", BytecodeFlags::Flag_StrictDouble)},
        {"Char_s", SronToken( SronTokenType::TYPE_DATATYPE, "Char_s", BytecodeFlags::Flag_StrictChar)},
        {"Bool_s", SronToken( SronTokenType::TYPE_DATATYPE, "Bool_s", BytecodeFlags::Flag_StrictBool)},
        {"String_s", SronToken( SronTokenType::TYPE_DATATYPE, "String_s", BytecodeFlags::Flag_StrictString)},
        {"List_s", SronToken( SronTokenType::TYPE_DATATYPE, "List_s", BytecodeFlags::Flag_StrictList)},
        {"FileReader_s", SronToken( SronTokenType::TYPE_DATATYPE, "FileReader_s", BytecodeFlags::Flag_StrictFreader)},
        {"FileWriter_s", SronToken( SronTokenType::TYPE_DATATYPE, "FileWriter_s", BytecodeFlags::Flag_StrictFwriter)},
        {"LiteralString_s", SronToken(SronTokenType::TYPE_DATATYPE, "LiteralString_s", BytecodeFlags::Flag_StrictLstr)},

        {"PI", SronToken( SronTokenType::TYPE_DOUBLE, "3.141592653", BytecodeFlags::Flag_Double_Value)},
        {TRUE_STRING_PRINT_FORMAT, SronToken( SronTokenType::TYPE_BOOL, TRUE_STRING_PRINT_FORMAT, BytecodeFlags::Flag_True)},
        {FALSE_STRING_PRINT_FORMAT, SronToken( SronTokenType::TYPE_BOOL, FALSE_STRING_PRINT_FORMAT, BytecodeFlags::Flag_False)},

        {"break", SronToken( SronTokenType::TYPE_KEYWORD, "break", BytecodeFlags::Flag_Break)},
        {"continue", SronToken( SronTokenType::TYPE_KEYWORD, "continue", BytecodeFlags::Flag_Continue)},
        {"Void", SronToken( SronTokenType::TYPE_VOID, "Void", BytecodeFlags::Flag_Void)},

        {"=", SronToken( SronTokenType::TYPE_ASSIGN, "=", BytecodeFlags::Flag_Assign)},
        {",", SronToken( SronTokenType::TYPE_COMMA, ",", BytecodeFlags::Flag_bydefault)},
        {":", SronToken( SronTokenType::TYPE_COLON, ":", BytecodeFlags::Flag_bydefault)},
        {"\n", SronToken( SronTokenType::TYPE_NEWLINE, "\n", BytecodeFlags::Flag_bydefault)},

        // Arithmetic operators...
        {"+", SronToken( SronTokenType::TYPE_OPERATOR, "+", BytecodeFlags::Flag_Add)},
        {"-", SronToken( SronTokenType::TYPE_OPERATOR, "-", BytecodeFlags::Flag_Minus)},
        {"*", SronToken( SronTokenType::TYPE_OPERATOR, "*", BytecodeFlags::Flag_Mult)},
        {"/", SronToken( SronTokenType::TYPE_OPERATOR, "/", BytecodeFlags::Flag_Div)},
        {"%", SronToken( SronTokenType::TYPE_OPERATOR, "%", BytecodeFlags::Flag_Mod)},
        {"^", SronToken( SronTokenType::TYPE_OPERATOR, "^", BytecodeFlags::Flag_Pow)},

        // logical operators...
        {"&&", SronToken( SronTokenType::TYPE_OPERATOR, "&&", BytecodeFlags::Flag_And)},
        {"||", SronToken( SronTokenType::TYPE_OPERATOR, "||", BytecodeFlags::Flag_Or)},
        {"!", SronToken( SronTokenType::TYPE_OPERATOR, "!", BytecodeFlags::Flag_Not)},

        // comparison operators...
        {"!=", SronToken( SronTokenType::TYPE_OPERATOR, "!=", BytecodeFlags::Flag_NotEqual)},
        {"==", SronToken( SronTokenType::TYPE_OPERATOR, "==", BytecodeFlags::Flag_Compare)},
        {"<", SronToken( SronTokenType::TYPE_OPERATOR, "<", BytecodeFlags::Flag_LessThan)},
        {"<=", SronToken( SronTokenType::TYPE_OPERATOR, "<=", BytecodeFlags::Flag_LessThanEqual)},
        {">", SronToken( SronTokenType::TYPE_OPERATOR, ">", BytecodeFlags::Flag_MoreThan)},
        {">=", SronToken( SronTokenType::TYPE_OPERATOR, ">=", BytecodeFlags::Flag_MoreThanEqual)},

        {"===", SronToken( SronTokenType::TYPE_OPERATOR, "===", BytecodeFlags::Flag_StrictCompare)},

        // assignment operators...
        {"+=", SronToken( SronTokenType::TYPE_CALC_ASSIGN, "+=", BytecodeFlags::Flag_AddAssign)},
        {"-=", SronToken( SronTokenType::TYPE_CALC_ASSIGN, "-=", BytecodeFlags::Flag_MinusAssign)},
        {"*=", SronToken( SronTokenType::TYPE_CALC_ASSIGN, "*=", BytecodeFlags::Flag_MultAssign)},
        {"/=", SronToken( SronTokenType::TYPE_CALC_ASSIGN, "/=", BytecodeFlags::Flag_DivAssign)},
        {"%=", SronToken( SronTokenType::TYPE_CALC_ASSIGN, "%=", BytecodeFlags::Flag_ModAssign)},
        {"^=", SronToken( SronTokenType::TYPE_CALC_ASSIGN, "^=", BytecodeFlags::Flag_PowAssign)},
        
        {"xor", SronToken( SronTokenType::TYPE_OPERATOR, "xor", BytecodeFlags::Flag_Xor)},
        {"lsft", SronToken( SronTokenType::TYPE_OPERATOR, "lsft", BytecodeFlags::Flag_Lshift)},
        {"rsft", SronToken( SronTokenType::TYPE_OPERATOR, "rsft", BytecodeFlags::Flag_Rshift)},
        {"&", SronToken( SronTokenType::TYPE_OPERATOR, "and", BytecodeFlags::Flag_BitwiseAnd )},
        {"|", SronToken( SronTokenType::TYPE_OPERATOR, "or", BytecodeFlags::Flag_BitwiseOr )},
        {"~", SronToken( SronTokenType::TYPE_OPERATOR, "not", BytecodeFlags::Flag_BitwiseNot )},
        
        // exceptions ...
        {"IndexNotWithinRangeException", SronToken( SronTokenType::TYPE_STRING, "IndexNotWithinRangeException", BytecodeFlags::Flag_String_Value)},
        {"DivisionByZeroException", SronToken( SronTokenType::TYPE_STRING, "DivisionByZeroException", BytecodeFlags::Flag_String_Value)},
        {"InputTypeException", SronToken( SronTokenType::TYPE_STRING, "InputTypeException", BytecodeFlags::Flag_String_Value)},
        {"ArgumentException", SronToken( SronTokenType::TYPE_STRING, "ArgumentException", BytecodeFlags::Flag_String_Value)},

        {"OBUFFER" , SronToken( SronTokenType::TYPE_KEYWORD , "OBUFFER" , BytecodeFlags::Flag_OBuffer)},

        {STR_HELPER(SRON_CMD_OBUFFER_CLEAR ), SronToken( SronTokenType::TYPE_INT , STR(SRON_CMD_OBUFFER_CLEAR) , BytecodeFlags::Flag_Int_Value)},
        {STR_HELPER(SRON_CMD_IS_OBUFFER_EMPTY), SronToken( SronTokenType::TYPE_INT , STR(SRON_CMD_IS_OBUFFER_EMPTY) , BytecodeFlags::Flag_Int_Value)},
        {STR_HELPER(SRON_CMD_SIZEOF_OBUFFER), SronToken( SronTokenType::TYPE_INT , STR(SRON_CMD_SIZEOF_OBUFFER) , BytecodeFlags::Flag_Int_Value)},
        {STR_HELPER(SRON_CMD_IS_FILE_AVAILABLE), SronToken( SronTokenType::TYPE_INT , STR(SRON_CMD_IS_FILE_AVAILABLE) , BytecodeFlags::Flag_Int_Value)},
        {STR_HELPER(SRON_CMD_GC_STACK_LEN), SronToken( SronTokenType::TYPE_INT , STR(SRON_CMD_GC_STACK_LEN) , BytecodeFlags::Flag_Int_Value)},
        {STR_HELPER(SRON_CMD_IS_BYTECODE_CACHED), SronToken( SronTokenType::TYPE_INT , STR(SRON_CMD_IS_BYTECODE_CACHED) , BytecodeFlags::Flag_Int_Value)},
        {STR_HELPER(SRON_CMD_NO_OF_BYTECODE_CACHED), SronToken( SronTokenType::TYPE_INT , STR(SRON_CMD_NO_OF_BYTECODE_CACHED) , BytecodeFlags::Flag_Int_Value)},

        {"CLI_DESIGN_RESET", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_RESET, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BOLD", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BOLD, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_DIM", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_DIM, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_ITALIC", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_ITALIC, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_UNDERLINE", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_UNDERLINE, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BLINK", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BLINK, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BLINK_FAST", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BLINK_FAST, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_HIDDEN", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_HIDDEN, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_STRIKE", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_STRIKE, BytecodeFlags::Flag_String_Value)},
        
        {"CLI_DESIGN_BG_BLACK", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BLACK, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_RED", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_RED, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_GREEN", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_GREEN, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_YELLOW", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_YELLOW, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_BLUE", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BLUE, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_MAGENTA", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_MAGENTA, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_CYAN", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_CYAN, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_WHITE", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_WHITE, BytecodeFlags::Flag_String_Value)},

        {"CLI_DESIGN_BG_BRIGHT_BLACK", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BRIGHT_BLACK, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_BRIGHT_RED", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BRIGHT_RED, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_BRIGHT_GREEN", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BRIGHT_GREEN, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_BRIGHT_YELLOW", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BRIGHT_YELLOW, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_BRIGHT_BLUE", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BRIGHT_BLUE, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_BRIGHT_MAGENTA", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BRIGHT_MAGENTA, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_BRIGHT_CYAN", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BRIGHT_CYAN, BytecodeFlags::Flag_String_Value)},
        {"CLI_DESIGN_BG_BRIGHT_WHITE", SronToken(SronTokenType::TYPE_STRING, CLI_DESIGN_BG_BRIGHT_WHITE, BytecodeFlags::Flag_String_Value)},


        {"CLI_COLOR_BLACK", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BLACK, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_RED", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_RED, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_GREEN", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_GREEN, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_YELLOW", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_YELLOW, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_BLUE", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BLUE, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_MAGENTA", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_MAGENTA, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_CYAN", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_CYAN, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_WHITE", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_WHITE, BytecodeFlags::Flag_String_Value)},

        {"CLI_COLOR_BRIGHT_BLACK", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BRIGHT_BLACK, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_BRIGHT_RED", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BRIGHT_RED, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_BRIGHT_GREEN", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BRIGHT_GREEN, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_BRIGHT_YELLOW", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BRIGHT_YELLOW, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_BRIGHT_BLUE", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BRIGHT_BLUE, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_BRIGHT_MAGENTA", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BRIGHT_MAGENTA, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_BRIGHT_CYAN", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BRIGHT_CYAN, BytecodeFlags::Flag_String_Value)},
        {"CLI_COLOR_BRIGHT_WHITE", SronToken(SronTokenType::TYPE_STRING, CLI_COLOR_BRIGHT_WHITE, BytecodeFlags::Flag_String_Value)},

        {"MAX_INT", SronToken(SronTokenType::TYPE_INT, "9223372036854775807", BytecodeFlags::Flag_Int_Value)},
        {"MIN_INT", SronToken(SronTokenType::TYPE_INT, "-9223372036854775808", BytecodeFlags::Flag_Int_Value)}
    };


    inline static const SronToken &EXTRACT_TOKEN_FROM_TOKEN_MAP( const std::string_view& __str )
    {
        const auto tk = TokenMaps::token_map.find(__str);

        if (tk == TokenMaps::token_map.end())
        {
            throw ThrowException("finding the token in the map. Cannot find the token '" + std::string(__str) + "'");
        }

        return tk->second;
    }
}

#endif