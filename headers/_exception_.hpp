#include <exception>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>

#include "static_logs.hpp"

#ifndef EXCEPTION_H
#define EXCEPTION_H

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

void DISPLAY_EXCEPTION(const char *during, const int code)
{
    try
    {

        printf("\nIn %s :\nAt Line %d: \nException Caught :\n||>> While %s \n    ", Logs::filename, Logs::GET_LINE_NUMBER(), during);

        std::string filename = "";

        switch (code)
        {
        case 1:
            filename = "ArgumentException";
            break;
        case 2:
            filename = "DatatypeConversionError";
            break;
        case 3:
            filename = "EmptyAttributeCode";
            break;
        case 4:
            filename = "FileNotFoundException";
            break;
        case 5:
            filename = "FileNameNotSpecifiedException";
            break;
        case 6:
            filename = "InputTypeException";
            break;
        case 7:
            filename = "InsertionException";
            break;
        case 8:
            filename = "InvalidVariableNameException";
            break;
        case 9:
            filename = "InvalidAttributeException";
            break;
        case 10:
            filename = "InvalidTokenException";
            break;
        case 11:
            filename = "InvalidValueException";
            break;
        case 12:
            filename = "InvalidVariableSyntaxException";
            break;
        case 13:
            filename = "InvalidTypeException";
            break;
        case 14:
            filename = "InvalidVectorDeclaration";
            break;
        case 15:
            filename = "InvalidScopeException";
            break;
        case 16:
            filename = "RectifyingException";
            break;
        case 17:
            filename = "SystemOutofMemoryException";
            break;
        case 18:
            filename = "StringTooLongException";
            break;
        case 19:
            filename = "StringIndexException";
            break;
        case 20:
            filename = "TypeConversionException";
            break;
        case 21:
            filename = "VectorInputError";
            break;
        case 22:
            filename = "VectorCreationError";
            break;
        case 23:
            filename = "IndexNotWithinRange";
            break;
        case 24:
            filename = "VectorEmptyException";
            break;
        case 25:
            filename = "VariableExistAlreadyException";
            break;
        case 26:
            filename = "VariableNotFoundException";
            break;
        case 27:
            filename = "UnknownIdentifierException";
            break;
        case 28:
            filename = "UnknownException";
            break;
        case 29:
            filename = "WrongSyntaxException";
            break;
        case 30 :
            filename = "NoValidCodeFoundException";
            break;
        default:
            printf("Invalid Exception Code !\n Contact SAKSHAM JOSHI via linkedin(/sakshamjoshi27) or twitter(X) to fix this.");
            break;
        }

       
        std::ifstream input("headers/Exception/" + filename + ".txt");
        std::string content((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));

        printf("%s", content.c_str());
        exit(1);
    }
    catch (const std::exception &)
    {
        printf("\n\n\t\t <||> SERIOUS ERROR <||>\n\t\t Something is going wrong ! Report to SAKSHAM JOSHI(developer of SRON) via linkedin(/sakshamjoshi27) or twitter (X) to fix this.");
    }
}

#endif