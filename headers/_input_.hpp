#include <exception>
#include <string>
#include <iostream>
#include "./_exception_.hpp"

/* This Exception is thrown when the user will
   input wrong datatype
*/
struct TypeError : public std::exception
{
    const char *what() const throw()
    {
        return " ";
    }
};

class Input
{
public :

    inline static std::string INPUT_STRING(){
        std::string str = "";
        try
        {
            getline(std::cin, str);
        }
        catch (const std::exception&)
        {
            DISPLAY_EXCEPTION("taking String type input value from user via console.",18);
        }
        return str;
    }
    inline static std::string INPUT_STRING(std::string msg)
    {
        printf("%s", msg.c_str());
        return INPUT_STRING();
    }

    inline static double INPUT_DOUBLE(){
        double d = 0;
        try
        {
            if (!scanf("%lf", &d))
            {
                throw " ";
            }
        }
        catch (const char*)
        {
            DISPLAY_EXCEPTION("taking Double type input value from user via console.",18);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("taking Double type input value from user via console.",18);
        }
        return d;
    }


    inline static double INPUT_DOUBLE(std::string msg)
    {
        printf("%s", msg.c_str());
        return INPUT_DOUBLE();
    }

    inline static long long int INPUT_INT(){
        double val = 0;
        try
        {
            if (!scanf("%lf", &val))
            {
                throw " ";
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("taking Int type input value from user via console.",18);
        }
        catch (const std::exception&)
        {
            DISPLAY_EXCEPTION("taking Int type input value from user via console.",18);
        }
        return (long long int)val;
    }

    inline static long long int INPUT_INT(std::string msg)
    {
        printf("%s", msg.c_str());
        return INPUT_INT();
    }

    inline static char INPUT_CHAR(){
        char ch = ' ' ;
        try
        {
            scanf("%c", &ch);
        }
        catch (const std::exception&)
        {
            DISPLAY_EXCEPTION("taking Char type input value from user via console.",18);
        }
        return ch;
    }
    inline static char INPUT_CHAR(std::string msg)
    {
        printf("%s", msg.c_str());
        return INPUT_CHAR();
        
    }

    ~Input(){ }
};