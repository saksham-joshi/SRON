#pragma once

#ifndef SRON_TOKEN_H
#define SRON_TOKEN_H

#include "_converter_.hpp"

struct SronToken
{

    unsigned short int _type;
    SronTokenString _token;
    flag_t _flag;
    unsigned long _file_index = 0;
    unsigned short int __cache_value;

    inline SronToken() {}

    inline SronToken(const unsigned short int type, const char *const &token, flag_t flag , const unsigned short int newline_count = 0U) : _type(type), _token(token), _flag(flag){}

    inline SronToken(const SronToken& __another) : _type(__another._type), _token(__another._token), _flag(__another._flag), _file_index(__another._file_index){}
    
    inline SronToken(SronToken&& __another) : _type(__another._type), _token(std::move(__another._token)), _flag(__another._flag), _file_index(__another._file_index){ }

    inline SronToken& operator=(const SronToken& __another){ 
        _type = __another._type; 
        _token = __another._token; 
        _flag = __another._flag;
        _file_index = __another._file_index;

        return *this;
    }

    inline ~SronToken() noexcept {}
};

// inline static std::ostream &operator<<(std::ostream &COUT, const SronToken& obj)
// {
//     COUT << "\n Type: " << obj._type << "\t Token: " << obj._token << "\t Flag: " << obj._flag << "\t Newline count: " << obj._newline_count << "\n";
//     return COUT;
// }

typedef std::vector<SronToken> TokenVector;

#endif