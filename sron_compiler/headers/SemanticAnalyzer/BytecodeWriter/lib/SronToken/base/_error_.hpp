/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 */

#pragma once

#ifndef EXCEPTION_H
#define EXCEPTION_H


#include "_logs_.hpp"

// used to display no reason and solution to the occured exception.
#define NoException "NoException"

// The exception macro below is used to extract files from the Exception directory and display

#define ByteCodeCannotbeSavedException "ByteCodeCannotbeSavedError"

#define DatatypeConversionError "DatatypeConversionError"
#define DoubleOverflowError "DoubleOverflowError"
#define DivisionByZeroException "DivisionByZeroError"

#define EmptyAttributeCode "EmptyAttributeCodeError"

#define FileNotFoundException "FileNotFoundError"
#define FileNameNotSpecifiedException "FileNameNotSpecifiedError"
#define FunctionNotFoundException "FunctionNotFoundError"

#define IntegerOverflowError "IntegerOverflowError"

#define InvalidFunctionName "InvalidFunctionName"
#define InvalidFunctionCallSyntaxException "InvalidFunctionCallSyntaxError"
#define InvalidForLoopSyntax "InvalidForLoopSyntax"
#define InvalidRangeSyntax "InvalidRangeSyntax"
#define InvalidVariableNameException "InvalidVariableNameError"
#define InvalidAttributeException "InvalidAttributeError"
#define InvalidTokenException "InvalidTokenError"
#define InvalidVariableSyntaxException "InvalidVariableSyntaxError"
#define InvalidTypeException "InvalidTypeError"
#define InvalidScopeException "InvalidScopeError"
#define InvalidArgsSyntaxException "InvalidArgsSyntaxError"
#define InvalidAttributeSyntaxException "InvalidAttributeSyntaxError"

#define MathematicalBlockSyntaxException "MathematicalBlockSyntaxError"

#define SourceCodeChangedException "SourceCodeChangedError"
#define TypeConversionError "TypeConversionError"

#define VariableExistAlreadyException "VariableExistAlreadyError"
#define VariableNotFoundException "VariableNotFoundError"

#define WrongSyntaxException "WrongSyntaxError"

struct SourceCodeFileNotFound : public std::exception{

    inline virtual const char* what() const noexcept{
        return "reading the file from specified path";
    }

};

struct FileNameNotProvidedToCompiler : public std::exception
{
    inline virtual const char* what() const noexcept{
        return "getting the file name";
    }
};

inline static void DISPLAY_ERROR(const char*const &during, const char *const &code, unsigned long __line_number = ULONG_MAX)
{

    std::cerr << "\n--------------------------------\nError: " << code << '\n';

    // displaying the name of the file where error is found
    std::cerr << "In '" << Logs::filename << '\'';

    if (__line_number != ULONG_MAX)
    {
        std::cerr << ":\nAt Line " << __line_number << ':';
    }

    std::cerr << "\n=>> While " << during << ".\n\n";

    if (std::strcmp(code, NoException) == 0)
    {
        return;
    }

    std::ifstream input(std::string(Logs::executable_path) + "meta\\Errors\\" + std::string(code) + ".txt");

    if (input.fail())
    {
        std::cerr << "\n\n+------------------------------------+\n"
                         "|  Exception message file not found  |\n"
                         "+------------------------------------+\n";
    }
    else
    {
        std::cerr << "    " << std::string((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()))<<"\n--------------------------------";
    }

    input.close();

    std::cerr << "\nRead Documentations at https://sron.gitbook.io";
}

inline static void DISPLAY_ERROR(const std::string &during, const char*const& code)
{
    DISPLAY_ERROR(during.c_str(), code);
}

#endif