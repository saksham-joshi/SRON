#include <exception>
#include<iostream>
#include "static_logs.h"

#define DatatypeConversionError "> Reason : You inputted invalid character."

#define EmptyAttributeCode "> Reason: Specified attribute has nothing to execute!\n\t> Solution: Never leave any attribute code empty."

#define FileNotFoundException "> Reason: Specified file not found !\n\t> Solution: Enter the correct file name."

#define InvalidVariableNameException "> Reason : Invalid Variable Naming.\n\t\t> Solution 1 : Name variable which contain only contain alphabets, numbers and underscore.\n\t\t> Solution 2 : Remove Special Characters like +, -, *, $ etc.\n\t\t> Solution 3 : First letter of variable must be a alphabet or underscore"
#define InvalidAttributeException "> Reason : Invalid Attribute found !\n\t\t> Solution 1 : Always type attributes in small-case.\n\t\t> Solution 2 : Refer to the documentation of SRON to find out all valid attributes out there."
#define InvalidTokenException "> Reason : Invalid Token found !\n\t\t> Solution : Read the documentation of SRON carefully and write valid tokens.\n"
#define InvalidValueException "> Reason : You inserted wrong value in wrong type.\n\t\t> Solution 1 : Int type can only contain numbers but not decimal values.\n\t\t> Solution 2 : Double type can only contain digits and decimal point(.).\n\t\t> Solution 3 : Char type is declared using single quote (\') and contains a single ASCII character.\n\t\t> Solution 4 : String type is declared using double quotes(\").\n\t\t> Solution 5 : Bool type contain only two values(true and false).\n"

#define SystemOutofMemoryException "> Reason : Your System is out of Memory .\n\t> Solution : Remove some background applications and free up RAM .\n"
#define StringTooLongException "> Reason : Your System is out of Memory .\n\t> Solution : Remove some background applications and free up RAM .\n"
#define StringIndexException "> Reason 1: Index is more than or equal to the length of String.\n\t> Reason 2: Index is less than 0.\n\t> Solution : Store elements in string and insert index more than 0 and less than the length of the String .\n"

#define VectorInputError "> Reason 1: You inserted the wrong character.\n\t> Reason 2: System is out of memory.\n\t> Solution 1: Insert the valid elements in the vector.\n\t>Solution 2: Remove the background applications running in our system.\n"
#define VectorCreationError "> Reason : Your System is out of Memory .\n\t> Solution : Remove some background applications and free up RAM .\n"
#define VectorIndexNotWithinRange "> Reason 1: Index is more than or equal to the length of Vector.\n\t> Reason 2: Index is less than 0.\n\t> Solution : Store elements in vector and insert index more than 0 and less than the length of the Vector .\n"

#define VariableExistAlreadyException "> Reason: Specified Variable already exist !\n\t> Solution: Enter a different & valid variable name."
#define VariableNotFoundException "> Reason: Specified Variable not found !\n\t> Solution: Enter a valid variable name that already exist."


#ifndef EXCEPTION_H
#define EXCEPTION_H

void DISPLAY_EXCEPTION(const char *during, const int code){
    printf("\nAt Line %d: \nException Caught :\n > While %s \n\t",Logs::GET_LINE_NUMBER() , during);
    switch (code){
        case 1:
            printf("%s", FileNotFoundException);
            break;
        case 2:
            printf("%s", InvalidVariableNameException);
            break;
        case 3:
            printf("%s", SystemOutofMemoryException);
            break;
        case 4:
            printf("%s", StringTooLongException);
            break;
        case 5:
            printf("%s", VectorInputError);
            break;
        case 6:
            printf("%s", VectorCreationError);
            break;
        case 7:
            printf("%s", VectorIndexNotWithinRange);
            break;
        case 8 :
            printf("%s",InvalidAttributeException);
            break;
        case 9 :
            printf("%s",VariableExistAlreadyException );
            break;
        case 10 :
            printf("%s",VariableNotFoundException );
            break;
        case 11 : 
            printf("%s",EmptyAttributeCode);
            break;
        case 12 :
            printf("%s" , StringIndexException);
            break;
        case 13 :
            printf("%s" , StringIndexException);
            break;
        case 14 :
            printf("%s",InvalidTokenException);
            break;
        case 15 :
            printf("%s" , InvalidValueException);
            break;
        default:
            printf("Invalid Exception Code !\n Contact SAKSHAM JOSHI to fix this.");
            break;
    }
    exit(1);
}

#endif