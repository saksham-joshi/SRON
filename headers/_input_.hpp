#include <exception>
#include <string>
#include <iostream>
#include "./_exception_.hpp"
#include "Argument_List.hpp"

class Input
{
public :

    // ========================================================================== FOR STRING USER INPUTS
    inline static std::string STRING(){
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
    inline static std::string STRING(std::string msg)
    {
        printf("%s", msg.c_str());
        return STRING();
    }
    inline static std::string STRING(ArgumentList& args){
        if(args.LEN() == 0){
            return STRING();
        }
        return STRING(args.GET_STRING(0));
    }


    // ========================================================================== FOR DOUBLE USER INPUTS
    inline static double DOUBLE(){
        double d = 0;
        try
        {
            if (!scanf("%lf", &d))
            {
                throw ThrowException() ;
            }
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("taking Double type input value from user via console.",18);
        }
        return d;
    }
    inline static double DOUBLE(std::string msg)
    {
        printf("%s", msg.c_str());
        return DOUBLE();
    }
    inline static double DOUBLE(ArgumentList& args){
        if(args.LEN() == 0){
            return DOUBLE();
        }
        return DOUBLE(args.GET_STRING(0));
    }


    // ============================================================================ FOR INT USER INPUTS 
    inline static long long int INT(){
        double val = 0;
        try
        {
            if (!scanf("%lf", &val))
            {
                throw ThrowException();
            }
        }
        catch (const std::exception&)
        {
            DISPLAY_EXCEPTION("taking Int type input value from user via console.",18);
        }
        return (long long int)val;
    }
    inline static long long int INT(std::string msg){
        printf("%s", msg.c_str());
        return INT();
    }
    inline static long long int INT(ArgumentList& args){
        if(args.LEN() == 0){
            return INT();
        }
        return INT(args.GET_STRING(0));
    }

    // ========================================================================== FOR CHAR USER INPUTS
    inline static char CHAR(){
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
    inline static char CHAR(std::string msg)
    {
        printf("%s", msg.c_str());
        return CHAR();
        
    }
    inline static char CHAR(ArgumentList& args){
        if(args.LEN() == 0){
            return CHAR();
        }
        return CHAR(args.GET_STRING(0));
    }

    ~Input(){ }
};