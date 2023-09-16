#include<exception>

#define FileNotFoundException "Exception Caught :\n\t> Reason: Specified file not found !\n\t> Solution: Enter the correct file name."

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

// printf("\nException Caught :\n > While taking string type value from user via console .\n\t> Reason 1 : You input Invalid Characters .\n\t> Reason 2 : Memory Error.\n");
//             exit(0);

// printf("\nException Caught :\n > While creating vector of type int .\n\t> Reason : Your System is out of Memory .\n\t> Solution : Remove some background applications and free up RAM .\n");
//             exit(0);