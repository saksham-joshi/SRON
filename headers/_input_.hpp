/*
 * This file contains the implementation of user input functions.
 * It contains the methods to handle input for these datatypes :
 *              1. String.
 *              2. Double.
 *              3. Int.
 *              4. Char. 
*/

#include "_argument_list_.hpp"

#ifndef INPUT_H
#define INPUT_H
// ====================================FOR STRING USER INPUTS
inline static std::string INPUT_STRING(){
    char* x = nullptr;
    char c;
    size_t size = 0;

 
    while ((c = getchar()) != '\n' && c != EOF) {
       
        x = (char*)realloc(x, (size + 1) * sizeof(char));

        if (x == nullptr) {
            DISPLAY_EXCEPTION("taking string user input from user.",SystemOutofMemoryException);
        }
        x[size++] = c;
    }

    x = (char*)realloc(x, (size + 1) * sizeof(char));
    if (x == nullptr) {
        DISPLAY_EXCEPTION("taking string user input from user.",SystemOutofMemoryException); 
    }
    x[size] = '\0';
    return std::string(x);
}

inline static std::string INPUT_STRING(std::string msg)
{
    printf("%s", msg.c_str());
    return INPUT_STRING();
}

// ========================================================================== FOR DOUBLE USER INPUTS
inline static double INPUT_DOUBLE()
{
    double d = 0;
    try
    {
        if (!scanf("%lf", &d))
        {
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("taking Double type input value from user via console.", InputTypeException);
    }
    return d;
}
inline static double INPUT_DOUBLE(std::string msg)
{
    printf("%s", msg.c_str());
    return INPUT_DOUBLE();
}


// =============================== FOR INT USER INPUTS
inline static long long int INPUT_INT()
{
    long long int val = 0;
    try{
        if (!scanf("%lld", &val)){
            throw std::exception();
        }
    }
    catch (const std::exception &){
        DISPLAY_EXCEPTION("taking Int type input value from user via console.", InputTypeException);
    }
    return val;
}
inline static long long int INPUT_INT(std::string msg){
    printf("%s", msg.c_str());
    return INPUT_INT();
}

// ================================== FOR CHAR USER INPUTS
inline static char INPUT_CHAR()
{
    char ch = ' ';
    try{
        if(!scanf("%c", &ch)){
            throw std::exception();
        }
        return ch;
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("taking Char type input value from user via console.", InputTypeException);
    }
    return ch;
}
inline static char INPUT_CHAR(std::string msg)
{
    printf("%s", msg.c_str());
    return INPUT_CHAR();
}

#endif