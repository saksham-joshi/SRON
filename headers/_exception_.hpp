#include <exception>
#include<iostream>
#include "static_logs.hpp"

#define ArgumentException "> Reason 1: You passed less arguments than required.\n\t> Reason 2: You passed more arguments than required.\n\t> Reason 3: You passed wrong type arguments.\n\t> Reason 4: You are receiving wrong type of arguments.\n\n\t|> Solution 1: Make sure to pass the correct number of arguments required in that function.\n\n\t|> Solution 2: Make sure to pass the correct type of arguments i.e you cannot pass Int as String argument.\n"

#define DatatypeConversionError "> Reason : You inputted invalid character."

#define EmptyAttributeCode "> Reason: Specified attribute has nothing to execute!\n\n\t|> Solution: Never leave any attribute code empty."

#define FileNotFoundException "> Reason: Specified file not found !\n\t|> Solution 1: Enter the correct file name.\n\t|> Solution 2: If you are accessing file via command line ,then remove spaces from file name.\n"
#define FileNameNotSpecifiedException "> Reason: File name is not specified !\n\n\t|> Solution 1: Type Command like this - sron file_name.sron \n\t|> Solution 2: Avoid spaces in file name.\n"

#define InputTypeException "> Reason 1 : You input Invalid Characters .\n\t> Reason 2 : Maybe System\'s memory is dysfunctioning.\n\t> Reason 3 : In case of Int & Double inputs, if the values are too big, then this exception is thrown.\n"

#define InvalidVariableNameException "> Reason : Invalid Variable Naming.\n\n\t|> Solution 1: Name variable which contain only contain alphabets, numbers and underscore.\n\t\t|> Solution 2 : Remove Special Characters like +, -, *, $ etc.\n\t\t|> Solution 3 : First letter of variable must be a alphabet or underscore"
#define InvalidAttributeException "> Reason : Invalid Attribute found !\n\n\t|> Solution 1: Always type attributes in small-case.\n\t\t|> Solution 2 : Refer to the documentation of SRON to find out all valid attributes out there."
#define InvalidTokenException "> Reason : Invalid Token found !\n\t\t|> Solution : Read the documentation of SRON carefully and write valid tokens.\n"
#define InvalidValueException "> Reason : You inserted wrong value in wrong type.\n\n\t|> Solution 1: Int type can only contain numbers but not decimal values.\n\t|> Solution 2 : Double type can only contain digits and decimal point(.).\n\t|> Solution 3 : Char type is declared using single quote (\') and contains a single ASCII character.\n\t|> Solution 4 : String type is declared using double quotes(\").\n\t|> Solution 5 : Bool type contain only two values(true and false).\n"
#define InvalidVariableSyntaxException "> Reason : Variable Attribute is not having a proper syntax.\n\n\t|> Solution: Correct Syntax = variables: type variable1,type variable2=value,type variable3 .\n\t\t|> Solution 2: Seprate variable and its type with comma(,).\n\t\t|> Solution 3 : Assign value to variable according to its type. e.g. Int val = \"Hello\" <--- This is wrong.\n"
#define InvalidTypeException "> Reason : Invalid type of variable found.\n\n\t|> Solution: Make sure to specify the type of variable in Capitalised form. e.g. Int, Double, Char,String & Double.\n\t\t|> Solution 2 : Only the above specified types and their vector forms are available as datatype till this version of SRON.\n"
#define InvalidVectorDeclaration "> Reason 1: Elements inserted in the vector can have same type and according to the type of vector.\n\t> Reason 2: No proper syntax of vector declaration.\n\n\t|> Solution: Correct Syntax of declaring variables is : Type[] name_of_vector = [element1 ,element2].\n\t\t|> Solution 2: Make sure to store similar types of values inside the vector.\n"

#define SystemOutofMemoryException "> Reason : Your System is out of Memory .\n\t|> Solution : Remove some background applications and free up RAM .\n"
#define StringTooLongException "> Reason : Your System is out of Memory .\n\t|> Solution : Remove some background applications and free up RAM .\n"
#define StringIndexException "> Reason 1: Index is more than or equal to the length of String.\n\t> Reason 2: Index is less than 0.\n\n\t|> Solution : Store elements in string and insert index more than 0 and less than the length of the String .\n"

#define TypeConversionException "> Reason : Characters in the specified parent type is not possible to converted into another type.\n\n\t|> Solution 1: Int type can only contain digits.\n\t|> Solution 2 : Double type can only contain digits and decimal point(.).\n\t|> Solution 3 : Char type is declared using single quote (\') and contains a single ASCII character.\n\t|> Solution 4 : String type can contain multiple ASCII Characters.\n\t|> Solution 5 : Bool type contain only two values(true and false).\n"

#define VectorInputError "> Reason 1: You inserted the wrong character.\n\t> Reason 2: System is out of memory.\n\t|> Solution 1: Insert the valid elements in the vector.\n\t>Solution 2: Remove the background applications running in our system.\n"
#define VectorCreationError "> Reason : Your System is out of Memory .\n\t|> Solution : Remove some background applications and free up RAM .\n"
#define VectorIndexNotWithinRange "> Reason 1: Index is more than or equal to the length of Vector.\n\t> Reason 2: Index is less than 0.\n\t|> Solution : Store elements in vector and insert index more than 0 and less than the length of the Vector .\n"

#define VariableExistAlreadyException "> Reason: Specified Variable already exist !\n\t|> Solution: Enter a different & valid variable name."
#define VariableNotFoundException "> Reason 1: Specified Variable not found !\n\t> Reason 2: Specified variable is freed up before.\n\t> Reason 3: Maybe you or the interpreter misunderstood the type of the variable.\n\n\t|> Solution: Input a valid variable that already exists.\n"

#define UnknownException "> Reason: Unknown exception !\n\t|> Solution: Contact SAKSHAM JOSHI(developer of SRON) via Linkedin or Twitter to fix it!"

#ifndef EXCEPTION_H
#define EXCEPTION_H

void DISPLAY_EXCEPTION(const char *during, const int code){
    printf("\nAt Line %d: \nException Caught :\n|=> While %s \n\t",Logs::GET_LINE_NUMBER() , during);
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
        case 16: 
            printf("%s",FileNameNotSpecifiedException);
            break;
        case 17 :
            printf("%s",TypeConversionException);
            break;
        case 18 :
            printf("%s",InputTypeException);
            break;
        case 19 :
            printf("%s",InvalidVariableSyntaxException);
            break;
        case 20 :
            printf("%s",InvalidTypeException);
            break;
        case 21 :
            printf("%s",InvalidVectorDeclaration);
            break;
        case 22:
            printf("%s",UnknownException);
            break;
        case 23 :
            printf("%s",ArgumentException);
            break;
        default:
            printf("Invalid Exception Code !\n Contact SAKSHAM JOSHI to fix this.");
            break;
    }
    exit(1);
}

#endif