
#include<cctype>

namespace SronChar{

    // ============================================================================== TO CHECK IF THE GIVEN CHAR IS ALPHABET OR NOT
    
    inline static bool IS_ALPHABET(const char ch){
        return (bool)isalpha(ch);
    }

     // ============================================================================== TO CHECK IF THE GIVEN CHAR IS VOWEL OR NOT
    
    inline static bool IS_VOWEL(const char ch){
        if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U'){ 
            return true; 
        }
        return false;
    }

    inline static bool IS_CONSONANT(const char ch){
        if(isalpha(ch) && !IS_VOWEL(ch)){
            return true;
        }
        return false;
    }

    inline static bool IS_NUMBER(const char ch){
        int ascii = (int)ch;
        if(ascii>=48 && ascii <= 57){
            return true;
        }
        return false;
    }

    inline static char TO_LOWERCASE(const char ch){
        return std::tolower(ch);
    }

    inline static char TO_UPPERCASE(const char ch){
        return std::toupper(ch);
    }

    inline static bool IS_LOWERCASE(const char ch){
        return (ch >= 97 && ch <= 122);
    }

    inline static bool IS_UPPERCASE(const char ch){
        return (ch >= 65 && ch <= 90 );
    }

    inline static int TO_ASCII(const char ch){
        return (int)ch;
    }

    inline static char FROM_ASCII(const int& ch){
        return (char)ch;
    }
}