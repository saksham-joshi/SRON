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

#include <exception>
#include <string>
#include <windows.h>
#include "static_logs.hpp"

// used to display no reason and solution to the occured exception.
#define NoException 0

// The exception below which be used to extract files from the Exception directory and display
#define ArgumentException 1
#define DatatypeConversionError 2
#define EmptyAttributeCode 3
#define FileNotFoundException 4
#define FileNameNotSpecifiedException 5
#define InputTypeException 6
#define InvalidVariableNameException 8
#define InvalidAttributeException 9
#define InvalidTokenException 10
#define InvalidValueException 11
#define InvalidVariableSyntaxException 12
#define InvalidTypeException 13
#define InvalidScopeException 15
#define SystemOutofMemoryException 17
#define TypeConversionException 20
#define VariableExistAlreadyException 25
#define VariableNotFoundException 26
#define UnknownIdentifierException 27
#define UnknownException 28
#define WrongSyntaxException 29
#define NoValidCodeFoundException 30
#define FunctionNotFoundException 31
#define SourceCodeChangedException 33
#define MathEvaluationException 34
#define DivisionByZeroException 35
#define ByteCodeCannotbeSavedException 36
#define InvalidArgsSyntaxException 37
#define WaveCountIsNotEvenException 38
#define InvalidCommentSyntaxException 39
#define InvalidAttributeSyntaxException 40
#define MathematicalBlockSyntaxException 41
#define InvalidFunctionName 44

inline static void DISPLAY_EXCEPTION(const char *during, const unsigned short int code, bool print_line_number = true)
{
    try
    {
        std::cout << "\nIn '" << Logs::filename<<'\'';

        if (print_line_number)
        {
            std::cout << ":\nAt Line " << Logs::line_number << ':';
        }
        std::cout << "\nException Caught :\n||>> While " << during << "\n";
        std::string filename = "";

        switch (code)
        {
        case NoException:
            exit(0);
        case ByteCodeCannotbeSavedException:
            filename = "ByteCodeCannotBeSavedException";
            break;
        case DivisionByZeroException:
            filename = "DivisionByZeroException";
            break;
        case EmptyAttributeCode:
            filename = "EmptyAttributeCode";
            break;
        case FileNotFoundException:
            filename = "FileNotFoundException";
            break;
        case FileNameNotSpecifiedException:
            filename = "FileNameNotSpecifiedException";
            break;
        case InvalidFunctionName :
            filename = "InvalidFunctionName";
            break; 
        case InvalidVariableNameException:
            filename = "InvalidVariableNameException";
            break;
        case InvalidAttributeException:
            filename = "InvalidAttributeException";
            break;
        case InvalidTokenException:
            filename = "InvalidTokenException";
            break;
        case InvalidValueException:
            filename = "InvalidValueException";
            break;
        case InvalidVariableSyntaxException:
            filename = "InvalidVariableSyntaxException";
            break;
        case InvalidTypeException:
            filename = "InvalidTypeException";
            break;
        case InvalidScopeException:
            filename = "InvalidScopeException";
            break;
        case SystemOutofMemoryException:
            filename = "SystemOutofMemoryException";
            break;
        case VariableExistAlreadyException:
            filename = "VariableExistAlreadyException";
            break;
        case VariableNotFoundException:
            filename = "VariableNotFoundException";
            break;
        case UnknownException:
            filename = "UnknownException";
            break;
        case WrongSyntaxException:
            filename = "WrongSyntaxException";
            break;
        case NoValidCodeFoundException:
            filename = "NoValidCodeFoundException";
            break;
        case FunctionNotFoundException:
            filename = "FunctionNotFoundException";
            break;
        case InvalidArgsSyntaxException:
            filename = "InvalidArgsSyntaxException";
            break;
        case WaveCountIsNotEvenException:
            filename = "WaveCountIsNotEvenException";
            break;
        case InvalidCommentSyntaxException:
            filename = "InvalidCommentSyntaxException";
            break;
        case InvalidAttributeSyntaxException:
            filename = "InvalidAttributeSyntaxException";
            break;
        case MathematicalBlockSyntaxException:
            filename = "MathematicalBlockSyntaxException";
            break;
        case TypeConversionException :
            filename = "TypeConversionException";
            break;
        default:
            std::cerr << "Invalid Exception Code !\n Contact SAKSHAM JOSHI via linkedin(/sakshamjoshi27) or twitter(X) to fix this.";
            break;
        }

        char path[MAX_PATH];
        DWORD length = GetModuleFileName(NULL,path, MAX_PATH);

        if (length == 0){
            std::cerr<<"\n =| Failed to get the executable's path |=\n";
            exit(1);
        }

        Logs::filename = Logs::executable_path + "meta\\Errors\\" + filename + ".txt";
        
        std::ifstream input(Logs::filename);

        if (input.fail())
        {
            std::cerr << "\n\n Something goes wrong while displaying the exception message. This happens due to unavailability of a particular file.";
        }
        else
        {
            std::cerr<<"    " << std::string ((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
        }

        input.close();
        Logs::mainfile->close();

        exit(-1);
    }
    catch (const std::exception &ex)
    {
        std::cerr << "\n | Error : " << ex.what();
        std::cerr << "\n\n\t\t <||> SERIOUS ERROR <||>\n\t\t Something is going wrong ! Report to SAKSHAM JOSHI(developer of SRON) via linkedin(/sakshamjoshi27) or twitter(X - @sakshamjoshi27) to fix this.";
    }
}

inline static void DISPLAY_EXCEPTION(const std::string &during, unsigned short int code, bool print_line_number = true)
{
    DISPLAY_EXCEPTION(during.c_str(), code, print_line_number);
}

#endif