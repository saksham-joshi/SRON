#include<iostream>
#include<ctype.h>


inline bool isalphabet(const char ch){
    return isalpha(ch);
}
inline bool isvowel(const char ch){
    if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' || ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U'){ 
        return true; 
    }
    return false;
}
inline bool isconsonant(const char ch){
    if(isalpha(ch) && !isvowel(ch)){
        return true;
    }
    return false;
}
inline bool isnumber(const char ch){
    int ascii = (int)ch;
    if(ascii>=48 && ascii <= 57){
        return true;
    }
    return false;
}
inline char tolowercase(const char ch){
    return tolower(ch);
}
inline char touppercase(const char ch){
    return toupper(ch);
}
inline int toASCII(const char ch){
    return (int)ch;
}
inline char fromASCII(const int ch){
    return (char)ch;
}