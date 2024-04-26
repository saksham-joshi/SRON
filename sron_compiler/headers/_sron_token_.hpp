
#ifndef SRON_TOKEN_H
#define SRON_TOKEN_H


#include<string>


struct SronToken{
    unsigned short int _type;
    std::string _token;
};

inline bool operator ==(SronToken& left , std::string& right){
    return left._token == right;
}

inline bool operator ==(SronToken& left , const char* right){
    return left._token == right;
}



#endif