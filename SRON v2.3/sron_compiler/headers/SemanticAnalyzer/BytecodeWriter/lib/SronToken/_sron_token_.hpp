#pragma once

#ifndef SRON_TOKEN_H
#define SRON_TOKEN_H

#include "_converter_.hpp"

struct SronToken
{

    typedef std::string TokenElement_t;

    SronTokenType _type;
    SronToken::TokenElement_t _token;
    BytecodeFlags _flag;
    FilePos_t _file_index = 0;
    TokenCache_t _cache_value = 0;

    inline SronToken() {}

    inline SronToken(const SronTokenType __type, const char *const __token, BytecodeFlags __flag) : _type(__type), _token(__token), _flag(__flag){}

    inline SronToken(const SronToken& __another) : _type(__another._type), _token(__another._token), 
    _flag(__another._flag), _file_index(__another._file_index) , _cache_value(__another._cache_value) { }
    
    inline SronToken(SronToken&& __another) : _type(__another._type), _token(std::move(__another._token)), 
     _flag(__another._flag), _file_index(__another._file_index), _cache_value(__another._cache_value) { }

    inline SronToken& operator=(const SronToken& __another){ 
        _type = __another._type; 
        _token = __another._token; 
        _flag = __another._flag;
        _file_index = __another._file_index;
        _cache_value = __another._cache_value;
        return *this;
    }

    inline ~SronToken() noexcept {}
};

#ifdef SRON_DEVELOPMENT_PHASE
    inline static std::ostream &operator<<(std::ostream &COUT, const SronToken& obj)
    {
        COUT << "\n Type: " << static_cast<unsigned short>(obj._type) << "\t Token: " << obj._token << "\t Flag: " << static_cast<unsigned short>(obj._flag )<< "\t Cache value: " << obj._cache_value << "\n";
        return COUT;
    }
#endif

typedef std::vector<SronToken> TokenVector;

#endif