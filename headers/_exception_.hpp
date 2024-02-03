/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 * 
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
*/

#include <exception>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include "static_logs.hpp"

#ifndef EXCEPTION_H
#define EXCEPTION_H

struct ThrowException {
    std::string during;
    unsigned short int code;
    ThrowException(const std::string& msg, const unsigned short int num) : during(msg),code(num) {}
};

// used to display no reason and solution to the occured exception.
#define NoException 0

// The exception below which be used
#define ArgumentException 1
#define DatatypeConversionError 2
#define EmptyAttributeCode 3
#define FileNotFoundException 4
#define FileNameNotSpecifiedException 5
#define InputTypeException 6
#define InsertionException 7
#define InvalidVariableNameException 8
#define InvalidAttributeException 9
#define InvalidTokenException 10
#define InvalidValueException 11
#define InvalidVariableSyntaxException 12
#define InvalidTypeException 13
#define InvalidVectorDeclaration 14
#define InvalidScopeException 15
#define RectifyingException 16
#define SystemOutofMemoryException 17
#define StringTooLongException 18
#define StringIndexException 19
#define TypeConversionException 20
#define VectorInputError 21
#define VectorCreationError 22
#define IndexNotWithinRange 23
#define VectorEmptyException 24
#define VariableExistAlreadyException 25
#define VariableNotFoundException 26
#define UnknownIdentifierException 27
#define UnknownException 28
#define WrongSyntaxException 29
#define NoValidCodeFoundException 30
#define FunctionNotFoundException 31
#define MainFunctionNotFoundException 32
#define SourceCodeChangedException 33
#define MathEvaluationException 34
#define DivisionByZeroException 35
#define ByteCodeCannotbeSavedException 36
#define InvalidArgsSyntaxException 37
#define WaveCountIsNotEvenException 38

inline static void DISPLAY_EXCEPTION(const std::string& during, unsigned short int code){
    DISPLAY_EXCEPTION(during.c_str(),code);
}

inline static void DISPLAY_EXCEPTION(const char *during, const unsigned short int code)
{
    try
    {
        printf("\nIn %s :\nAt Line %d: \nException Caught :\n||>> While %s \n    ", Logs::filename, Logs::GET_LINE_NUMBER(), during);

        std::string filename = "";

        switch (code)
        {
        case NoException : exit(0);
        case ArgumentException:
            filename = "ArgumentException";
            break;
        case ByteCodeCannotbeSavedException :
            filename = "ByteCodeCannotBeSavedException";
            break;
        case DatatypeConversionError:
            filename = "DatatypeConversionError";
            break;
        case DivisionByZeroException :
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
        case InputTypeException:
            filename = "InputTypeException";
            break;
        case InsertionException:
            filename = "InsertionException";
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
        case InvalidVectorDeclaration :
            filename = "InvalidVectorDeclaration";
            break;
        case InvalidScopeException:
            filename = "InvalidScopeException";
            break;
        case RectifyingException:
            filename = "RectifyingException";
            break;
        case SystemOutofMemoryException:
            filename = "SystemOutofMemoryException";
            break;
        case StringTooLongException:
            filename = "StringTooLongException";
            break;
        case StringIndexException:
            filename = "StringIndexException";
            break;
        case TypeConversionException:
            filename = "TypeConversionException";
            break;
        case VectorInputError:
            filename = "VectorInputError";
            break;
        case VectorCreationError:
            filename = "VectorCreationError";
            break;
        case IndexNotWithinRange:
            filename = "IndexNotWithinRange";
            break;
        case VectorEmptyException:
            filename = "VectorEmptyException";
            break;
        case VariableExistAlreadyException:
            filename = "VariableExistAlreadyException";
            break;
        case VariableNotFoundException:
            filename = "VariableNotFoundException";
            break;
        case UnknownIdentifierException:
            filename = "UnknownIdentifierException";
            break;
        case UnknownException:
            filename = "UnknownException";
            break;
        case WrongSyntaxException:
            filename = "WrongSyntaxException";
            break;
        case NoValidCodeFoundException :
            filename = "NoValidCodeFoundException";
            break;
        case FunctionNotFoundException : 
            filename = "FunctionNotFoundException";
            break;
        case MainFunctionNotFoundException :
            filename = "MainFunctionNotFoundException";
            break;
        case SourceCodeChangedException :
            filename = "SourceCodeChangedException";
            break;
        case MathEvaluationException : 
            filename = "MathEvaluationException";
            break;
        case InvalidArgsSyntaxException :
            filename = "InvalidArgsSyntaxException";
            break;
        case WaveCountIsNotEvenException :
            filename = "WaveCountIsNotEvenException";
            break;
        default:
            printf("Invalid Exception Code !\n Contact SAKSHAM JOSHI via linkedin(/sakshamjoshi27) or twitter(X) to fix this.");
            break;
        }

        std::ifstream input("headers/Exception/" + filename + ".txt");
        if(input.fail()){
            printf("\n\n Something goes wrong while displaying the exception message. This happen due to unavailability of a particular file.");
        }
        else{
            std::string content((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
            printf("\t%s", content.c_str());
        }
        input.close();
        Logs::mainfile->close();

        exit(-1);
    }
    catch (const std::exception &ex)
    {
        printf("\n | Error : %s.",ex.what());
        printf("\n\n\t\t <||> SERIOUS ERROR <||>\n\t\t Something is going wrong ! Report to SAKSHAM JOSHI(developer of SRON) via linkedin(/sakshamjoshi27) or twitter (X) to fix this.");
    }
}

#endif