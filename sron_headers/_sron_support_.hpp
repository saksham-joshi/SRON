
#ifndef _SRON_SUPPORT_H
#define _SRON_SUPPORT_H

#include "_bytecode_flags_.hpp"
#include <cstdio>
#include <climits>
#include <chrono>
#include <thread>

#ifdef _WIN64
    #include<Windows.h>
#elif defined(__linux__)
    #include<unistd.h>
#else
    #error "Cannot include OS specific header"
#endif

namespace SronSupport
{

    [[gnu::always_inline]] [[gnu::hot]] inline static bool compareString(const char* __left, const char* __right) noexcept
    {
        if ( __left && __right )
        {
            while( *__left && *__right && *__left == *__right )
            {
                ++__left;
                ++__right;
            }

            return *__left == *__right;
        }

        return false;
    }

    inline static void safeOpenFile( FILE** __fileobj, const char*const __filename, const char*const __mode)
    {
        #ifdef _WIN64
            fopen_s( __fileobj, __filename, __mode);
        #else 
            *__fileobj = std::fopen( __filename, __mode);
        #endif
    }

    inline static std::string getFilePath( const std::string& __full_path )
    {
        auto revit = __full_path.cend() - 1;
        const auto start = __full_path.cbegin();

        for(; start <= revit ; --revit )
        {
            if ( *revit == '\\' || *revit == '/') break;
        }

        return ( revit < start ) ? "" : (__full_path.substr(0, revit - start) + "/");

    }

    inline static std::string getExecutablePath()
    {
        #ifdef _WIN64
            char path[MAX_PATH] = { 0 };

            DWORD length = GetModuleFileName(NULL, path, MAX_PATH);

            if (length == 0)
            {
                std::cerr << "\n =| Failed to get the executable's path |=\n";
                exit(1);
            }

            return SronSupport::getFilePath(path);

        #elif __linux__
            char path[PATH_MAX + 1] = { 0 };

            ssize_t length = readlink("/proc/self/exe", path, PATH_MAX);
            if (length == -1)
            {
                std::cerr << "Error reading /proc/self/exe" << std::endl;
                exit(1);
            }
            path[length] = '\0';

            return SronSupport::getFilePath( path );

        #else
            #error "This codebase is only maintained for Windows x64 and Linux x64"
        #endif
    }

    inline static void sleep( SronInt_t __milliseconds ) noexcept 
    {
        if ( __milliseconds > 0) std::this_thread::sleep_for(std::chrono::milliseconds( __milliseconds));
    }

    inline static void beep( SronInt_t __duration, SronInt_t __frequency ) noexcept 
    {
        #ifdef _WIN64
            ::Beep( __frequency, __duration);
        #elif defined(__linux__)
            
            std::string dur_in_sec = std::to_string( double(__duration)/double(1000) );

            std::string cmd = "speaker-test -t sine -f "+ std::to_string(__frequency) + " -l "+ std::to_string(__duration) +" -P 2 > /dev/null 2>&1 & sleep "+ dur_in_sec +" && kill -9 $!";
            
            system(cmd.c_str());
        #endif
    }

    [[gnu::hot]] [[gnu::always_inline]] inline static void copyMemory ( void* __destination, const void* __source, unsigned long long __length )
    {
        #if defined(_WIN64)
            std::memcpy( __destination , __source, __length);
        #else
            char* dest = reinterpret_cast<char*>( __destination );

            const char* src = reinterpret_cast<const char*>( __source );
            
            while ( __length-- ) *dest++ = *src++;
        #endif
    }

    [[gnu::hot]] [[gnu::always_inline]] inline static unsigned long long stringLen( const char* __str )
    {
        const char*const start = __str;

        while ( *__str ) ++__str;

        return __str - start;
    }

    [[gnu::always_inline]] inline static clock_t getCurTime() noexcept
    {
        return clock();
    }

    // returns in milliseconds
    [[gnu::always_inline]] inline static unsigned long long getExecTime(const clock_t __finish_time, const clock_t __start_time)
    {
        return ((double)(__finish_time - __start_time)/(double)(CLOCKS_PER_SEC)) * 1000;
    }

    const auto CODE_START_TIME = SronSupport::getCurTime();

    inline const char* flagToString(BytecodeFlags __flag){

        switch(__flag){

            case BytecodeFlags::Flag_Any : return "Any";

            case BytecodeFlags::Flag_Int : return "Int";

            case BytecodeFlags::Flag_Double : return "Double";

            case BytecodeFlags::Flag_Char : return "Char";

            case BytecodeFlags::Flag_String : return "String";

            case BytecodeFlags::Flag_Bool : return "Bool";

            case BytecodeFlags::Flag_List : return "List";

            case BytecodeFlags::Flag_Void : return "Void";

            case BytecodeFlags::Flag_FileReader : return "FileReader";

            case BytecodeFlags::Flag_FileWriter : return "FileWriter";

            case BytecodeFlags::Flag_Lstr : return "LiteralString";

            case BytecodeFlags::Flag_Int_Value : return "Int-value";

            case BytecodeFlags::Flag_Double_Value : return "Double-value";

            case BytecodeFlags::Flag_Char_Value : return "Char-value";

            case BytecodeFlags::Flag_String_Value : return "String-value";

            case BytecodeFlags::Flag_Assign : return "Assign";

            case BytecodeFlags::Flag_InBuiltFunctionCall : return "In-built Fnc";

            case BytecodeFlags::Flag_FunctionParamScopeStart : return "args{";

            case BytecodeFlags::Flag_FunctionParamScopeEnd : return "args}";

            case BytecodeFlags::Flag_Break : return "break";

            case BytecodeFlags::Flag_Continue : return "continue";

            case BytecodeFlags::Flag_Args_Start : return "(";

            case BytecodeFlags::Flag_Args_End : return ")";

            case BytecodeFlags::Flag_ListStart : return "[";
            
            case BytecodeFlags::Flag_ListEnd : return "]";

            case BytecodeFlags::Flag_Return : return "return";

            case BytecodeFlags::Flag_Identifier_Variable : return "variable";

            case BytecodeFlags::Flag_RangeScopeStart : return "range{";

            case BytecodeFlags::Flag_RangeScopeEnd : return "range}";

            case BytecodeFlags::Flag_Condition : return "condition";

            case BytecodeFlags::Flag_ForScopeStart : return "for{";

            case BytecodeFlags::Flag_ForScopeEnd : return "for}";

            case BytecodeFlags::Flag_WhileScopeStart : return "while{";

            case BytecodeFlags::Flag_WhileScopeEnd : return "while}";

            case BytecodeFlags::Flag_IfScopeStart : return "if{";

            case BytecodeFlags::Flag_IfScopeEnd : return "if}";

            case BytecodeFlags::Flag_ElifScopeStart : return "elif{";

            case BytecodeFlags::Flag_ElifScopeEnd : return "elif}";

            case BytecodeFlags::Flag_ElseScopeStart : return "else{";

            case BytecodeFlags::Flag_ElseScopeEnd : return "else}";

            case BytecodeFlags::Flag_EvalStart : return "${";

            case BytecodeFlags::Flag_EvalEnd : return "}$";

            case BytecodeFlags::Flag_RotateScopeStart : return "rotate{";

            case BytecodeFlags::Flag_RotateScopeEnd : return "rotate}";

            case BytecodeFlags::Flag_ConsoleStart : return "console{";

            case BytecodeFlags::Flag_ConsoleEnd : return "console}";

            case BytecodeFlags::Flag_Operator : return "operator";

            case BytecodeFlags::Flag_Add : return "+";

            case BytecodeFlags::Flag_Minus : return "-";

            case BytecodeFlags::Flag_Mult : return "*";

            case BytecodeFlags::Flag_Div : return "/";

            case BytecodeFlags::Flag_Mod : return "%";

            case BytecodeFlags::Flag_Pow : return "^";

            case BytecodeFlags::Flag_And : return "&&";

            case BytecodeFlags::Flag_Or : return "||";

            case BytecodeFlags::Flag_Not : return "!";

            case BytecodeFlags::Flag_NotEqual : return "!=";

            case BytecodeFlags::Flag_Compare : return "==";

            case BytecodeFlags::Flag_LessThan : return "<";

            case BytecodeFlags::Flag_LessThanEqual : return "<=";

            case BytecodeFlags::Flag_MoreThan : return ">";

            case BytecodeFlags::Flag_MoreThanEqual : return ">=";

            case BytecodeFlags::Flag_StrictCompare : return "===";

            case BytecodeFlags::Flag_AddAssign : return "+=";

            case BytecodeFlags::Flag_MinusAssign : return "-=";

            case BytecodeFlags::Flag_MultAssign : return "*=";

            case BytecodeFlags::Flag_DivAssign : return "/=";

            case BytecodeFlags::Flag_ModAssign : return "%=";

            case BytecodeFlags::Flag_PowAssign : return "^=";

            case BytecodeFlags::Flag_UserDefinedFunctionCall : return "user-defined FNC";

            case BytecodeFlags::Flag_Negate : return "Negate";

            case BytecodeFlags::Flag_IntExtractor : return "Int-Extractor";

            case BytecodeFlags::Flag_DoubleExtractor : return "Double-Extractor";

            case BytecodeFlags::Flag_CharExtractor : return "Char-Extractor";

            case BytecodeFlags::Flag_BoolExtractor : return "Bool-Extractor";

            case BytecodeFlags::Flag_StringExtractor : return "String-Extractor";

            case BytecodeFlags::Flag_ListExtractor : return "List-Extractor";

             case BytecodeFlags::Flag_FreadExtractor : return "FileReader-Extractor";

            case BytecodeFlags::Flag_FwriteExtractor : return "FileWriter-Extractor";

            case BytecodeFlags::Flag_LstrExtractor : return "LiteralString-Extractor";

            case BytecodeFlags::Flag_UnaryOperator : return "Unary-Operator";

            case BytecodeFlags::Flag_CodeCompleted : return "Code-done";

            case BytecodeFlags::Flag_True : return "true";

            case BytecodeFlags::Flag_False : return "false";

            case BytecodeFlags::Flag_BitwiseAnd : return "Bitwise-and";

            case BytecodeFlags::Flag_BitwiseOr : return "Bitwise-or";

            case BytecodeFlags::Flag_BitwiseNot : return "Bitwise-not";

            case BytecodeFlags::Flag_Lshift : return "Bitwise-LeftShift";

            case BytecodeFlags::Flag_Rshift : return "Bitwise-RightShift";

            case BytecodeFlags::Flag_Xor : return "Bitwise-Xor";

            case BytecodeFlags::Flag_OBuffer : return "OBuffer";

            case BytecodeFlags::Flag_Windows : return "WindowsOs-scope";

            case BytecodeFlags::Flag_Linux : return "LinuxOs-scope";

            case BytecodeFlags::Flag_ForeachScopeStart : return "Foreach-ScopeStart";

            case BytecodeFlags::Flag_ForeachScopeEnd : return "Foreach-ScopeEnd";

            case BytecodeFlags::Flag_String_Print : return "String-Print";

            case BytecodeFlags::Flag_Char_Print : return "Char-Print";

            case BytecodeFlags::Flag_FunctionName : return "Function-Name";

            case BytecodeFlags::Flag_ReturnType : return "Return-Type";

            case BytecodeFlags::Flag_ForeachOn : return "Foreach-On";

            case BytecodeFlags::Flag_StrictInt : return "Strict-Int";

            case BytecodeFlags::Flag_StrictDouble : return "Strict-Double";

            case BytecodeFlags::Flag_StrictChar : return "Strict-Char";

            case BytecodeFlags::Flag_StrictBool : return "Strict-Bool";

            case BytecodeFlags::Flag_StrictString : return "Strict-String";

            case BytecodeFlags::Flag_StrictList : return "Strict-List";

            case BytecodeFlags::Flag_StrictFreader : return "Strict-FileReader";

            case BytecodeFlags::Flag_StrictFwriter : return "Strict-FileWriter";

            case BytecodeFlags::Flag_StrictLstr : return "Strict-LiteralString";

            case BytecodeFlags::Flag_bydefault : return "Default";
        }

        return "Unidentified-flag";
    }

}

#endif