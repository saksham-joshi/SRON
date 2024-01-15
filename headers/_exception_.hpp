#include <exception>
#include <cstdio>
#include <cstdlib>
#include "static_logs.hpp"
#include <string>
#include<fstream>


#ifndef EXCEPTION_H
#define EXCEPTION_H


/*
 * This custom exception is used when we explicitly want to throw exception so that the control can be passed through the catch block.
 */
// struct ThrowException : public std::exception{

//     const char* what() const throw() {
//         return " ";
//     }
// };

void DISPLAY_EXCEPTION(const char *during, const int code)
{

    printf("\nIn %s :\nAt Line %d: \nException Caught :\n|>> While %s \n\t", Logs::filename, Logs::GET_LINE_NUMBER(), during);

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
        filename = "ListIndexNotWithinRange";
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
    default:
        printf("Invalid Exception Code !\n Contact SAKSHAM JOSHI via linkedin or twitter(X) to fix this.");
        break;
    }

    std::ifstream input("Exception/"+filename+".txt");
    std::string content((std::istreambuf_iterator<char>(input)),(std::istreambuf_iterator<char>()));
    
    printf("%s",content.c_str());
    exit(1);
}

#endif