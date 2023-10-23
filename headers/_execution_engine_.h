#include <iostream>
#include <string>
#include <stack>
#include "_string_.h"
#include "_hashtable_.h"
#include "_utility_.h"

inline static bool CHECK_VALID_VARIABLE_NAME(std::string str)
{
    if (!(str[0] == '_' || isalpha(str[0]) > 0))
    {
        DISPLAY_EXCEPTION("creating a variable.", 2);
    }
    for (std::string::iterator it = str.begin() + 1; it < str.end(); ++it)
    {
        if (!(*it == '_' || isalpha(*it) > 0 || ((int)*it >= 48 && (int)*it <= 57)))
        {
            DISPLAY_EXCEPTION("creating a variable.", 2);
        }
    }
    return true;
}
inline static bool CHECK_IF_ATTRIBUTE_IS_NUMBER(std::string str)
{
    for (std::string::iterator it = str.begin(); it < str.end(); ++it)
    {
        if ((int)*it >= 48 && (int)*it <= 57)
        {
            continue;
        }
        return false;
    }
    return true;
}

class Executor
{
    HashTable H;

private:
    friend int main(int argc, char **argv);

public:
    Executor(HashTable &H)
    {
        this->H = H;
    }
    void VARIABLES(std::vector<std::string> vec)
    {
        try
        {
            for (std::vector<std::string>::iterator it = vec.begin() + 3; it != vec.end(); ++it)
            {
                if (*it == "Int")
                {
                    if(it < vec.end()-2){
                        CHECK_VALID_VARIABLE_NAME(*(it+1));
                        H.INSERT(*(it+1),(long long int)0);
                    }
                    

                }
                else if(*it == "Double"){

                }
                else if(*it == "String"){

                }
                else if(*it == "Char"){

                }
                else if(*it == "Bool"){
                    
                }
            }
        }
        catch (const std::exception &e)
        {
            // std::cerr << e.what() << '\n';
            DISPLAY_EXCEPTION("storing the variable from \'variables\' attribute.", 19);
        }
    }
};