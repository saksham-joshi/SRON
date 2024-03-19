#include "_rectifier_.hpp"
#include<cctype>
#include<cstring>
#include "Argument_List.hpp"

class Char{
public :

    //============================================================================== TO ADD GIVEN Char AND MAKE THEIR String
    inline static string ADD(ArgumentList& args){
        try{
            std::string str="";
            for(int i=0; i<args.LEN(); ++i){
                str+=args.GET_CHAR(i);
            }
            return str;
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("adding up Char.",3);
        }
        return " ";
    }
    inline static std::string ADD(char ch1,char ch2){
        return ch1+(std::string)""+ch2;
    }

    // ============================================================================== TO CHECK IF THE GIVEN CHAR IS ALPHABET OR NOT
    inline static bool IS_ALPHABET(ArgumentList& args){
        return ISALPHABET(args.GET_CHAR(0));
    }
    inline static bool IS_ALPHABET(const char ch){
        return (bool)isalpha(ch);
    }

     // ============================================================================== TO CHECK IF THE GIVEN CHAR IS VOWEL OR NOT
    inline static bool iSVOWEL(ArgumentList& args){
        return ISVOWEL(args.GET_CHAR(0));
    }
    inline static bool ISVOWEL(const char ch){
        if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U'){ 
            return true; 
        }
        return false;
    }

    // ============================================================================== TO CHECK IF THE GIVEN CHAR IS CONSONANT
    inline static bool iSCONSONANT(ArgumentList& args){
        return ISCONSONANT(args.GET_CHAR(0));
    }
    inline static bool ISCONSONANT(const char ch){
        if(isalpha(ch) && !ISVOWEL(ch)){
            return true;
        }
        return false;
    }

    // ============================================================================== TO CHECK IF THE CHAR IS A NUMBER
    inline static bool ISNUMBER(ArgumentList& args){
        return ISNUMBER(args.GET_CHAR(0));
    }
    inline static bool ISNUMBER(const char ch){
        int ascii = (int)ch;
        if(ascii>=48 && ascii <= 57){
            return true;
        }
        return false;
    }

    // ============================================================================== TO LOWERCASE
    inline static char TOLOWERCASE(ArgumentList& args){
        return TOLOWERCASE(args.GET_CHAR(0));
    }
    inline static char TOLOWERCASE(const char ch){
        return tolower(ch);
    }

    // ============================================================================== TO UPPERCASE
    inline static char TOUPPERCASE(ArgumentList& args){
        return TOUPPERCASE(args.GET_CHAR(0));
    }
    inline static char TOUPPERCASE(const char ch){
        return toupper(ch);
    }


    // ============================================================================== TO AND FROM ASCII
    inline static int TOASCII(ArgumentList& args){
        return TOASCII(args.GET_CHAR(0));
    }
    inline static int TOASCII(const char ch){
        return (int)ch;
    }

    inline static char FROM_ASCII(ArgumentList& args){
        return FROM_ASCII(args.GET_INT(0));
    }
    inline static char FROM_ASCII(const int ch){
        return (char)ch;
    }
    ~Char(){ }
};