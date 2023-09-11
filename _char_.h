#include<iostream>
#include<cctype>

class Char{
public :
    inline static bool ISALPHABET(const char ch){
        return isalpha(ch);
    }
    inline static bool ISVOWEL(const char ch){
        if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U'){ 
            return true; 
        }
        return false;
    }
    inline static bool ISCONSONANT(const char ch){
        if(isalpha(ch) && !ISVOWEL(ch)){
            return true;
        }
        return false;
    }
    inline static bool ISNUMBER(const char ch){
        int ascii = (int)ch;
        if(ascii>=48 && ascii <= 57){
            return true;
        }
        return false;
    }
    inline static char ToLOWERCASE(const char ch){
        return tolower(ch);
    }
    inline static char ToUPPERCASE(const char ch){
        return toupper(ch);
    }
    inline static int ToASCII(const char ch){
        return (int)ch;
    }
    inline static char FromASCII(const int ch){
        return (char)ch;
    }
    ~Char(){ }
};