#include<exception>

struct DivisionByZeroException : public std::exception{
    const char* what() const throw(){
        return "Exception Caught :\n > Division by zero leads to infinity !";
    }
};

struct EmptyCharacterException : public std::exception{
    const char* what() const throw(){
        return "Exception Caught :\n > Empty char type variables are not allowed !";
    }
};

struct MemoryException : public std::exception{
    const char* what() const throw(){
        return "Exception Caught :\n > Your System is out of Memory .\n\t --> Fix it by removing unneccesary background applications .";
    }
};

struct TypeConversionError : public std::exception{
    const char* what() const throw(){
        return "Exception Caught :\n > Error while Converting datatypes";
    }
};