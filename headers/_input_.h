#include <exception>
#include <string>
#include <iostream>

/* This Exception is thrown when the user will
   input wrong datatype
*/
struct TypeError : public std::exception
{
    const char *what() const throw()
    {
        return "";
    }
};

class Input
{
public :
    inline static std::string INPUT_STRING(std::string msg)
    {
        printf("%s", msg.c_str());
        std::string str = "";
        try
        {
            getline(std::cin, str);
        }
        catch (std::exception e)
        {
            printf("\nException Caught :\n > While taking string type value from user via console .\n\t> Reason 1 : You input Invalid Characters .\n\t> Reason 2 : Memory Error.\n");
            exit(1);
        }
        return str;
    }
    inline static double INPUT_DOUBLE(std::string msg)
    {
        printf("%s", msg.c_str());
        double d = 0;
        try
        {
            if (!scanf("%lf", &d))
            {
                throw TypeError();
            }
        }
        catch (std::exception e)
        {
            printf("\nException Caught :\n > While taking double type value from user via console.\n\t> Reason 1 : You input Invalid Characters .\n\t> Reason 2 : Memory Error.\n");
            exit(1);
        }
        return d;
    }
    inline static int INPUT_INT(std::string msg)
    {
        printf("%s", msg.c_str());
        double val = 0;
        try
        {
            if (!scanf("%lf", &val))
            {
                throw TypeError();
            }
        }
        catch (std::exception e)
        {
            printf("\nException Caught :\n > While taking int type value from user via console.\n\t> Reason 1 : You input Invalid Characters .\n\t> Reason 2 : Memory Error.\n");
            exit(1);
        }
        return (long long int)val;
    }
    inline static char INPUT_CHAR(std::string msg)
    {
        printf("%s", msg.c_str());
        char ch;
        try
        {
            scanf("%c", &ch);
        }
        catch (std::exception e)
        {
            printf("\nException Caught :\n > While taking char type value from user via console.\n\t> Reason 1 : You input Invalid Characters .\n\t> Reason 2 : Memory Error.\n");
            exit(1);
        }
        return ch;
    }
    ~Input(){ }
};