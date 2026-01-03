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
    unsigned int _pair_index = 0;

    inline SronToken() {}

    inline SronToken(const SronTokenType __type, const char *const __token, BytecodeFlags __flag) : _type(__type), _token(__token), _flag(__flag){}

    inline SronToken(const SronToken& __another) : _type(__another._type), _token(__another._token), 
    _flag(__another._flag), _file_index(__another._file_index) , _cache_value(__another._cache_value),
    _pair_index(__another._pair_index) { }
    
    inline SronToken(SronToken&& __another) : _type(__another._type), _token(std::move(__another._token)), 
     _flag(__another._flag), _file_index(__another._file_index), _cache_value(__another._cache_value),
    _pair_index(__another._pair_index) { }

    inline SronToken& operator=(const SronToken& __another){ 
        _type = __another._type; 
        _token = __another._token; 
        _flag = __another._flag;
        _file_index = __another._file_index;
        _cache_value = __another._cache_value;
        _pair_index = __another._pair_index;
        return *this;
    }

    [[gnu::leaf]] constexpr inline static bool isUnaryOperator(const BytecodeFlags __op) noexcept
    {
        return (__op == BytecodeFlags::Flag_BitwiseNot || __op == BytecodeFlags::Flag_Not || __op == BytecodeFlags::Flag_Negate);
    }

    inline bool isUnaryOperator() const noexcept
    {
        return SronToken::isUnaryOperator(this->_flag);
    }

    [[gnu::leaf]] inline bool isOperator() const noexcept
    {
        return (this->_type == SronTokenType::TYPE_OPERATOR);
    }

    [[gnu::leaf]] inline bool isValueType() const noexcept
    {
        return ( this->_type == SronTokenType::TYPE_VOID || this->_type == SronTokenType::TYPE_INT || this->_type == SronTokenType::TYPE_DOUBLE
                || this->_type == SronTokenType::TYPE_CHAR || this->_type == SronTokenType::TYPE_BOOL || this->_type == SronTokenType::TYPE_STRING
                || this->_type == SronTokenType::TYPE_LIST_OPEN || this->_type == SronTokenType::TYPE_IDENTIFIER || this->_type == SronTokenType::TYPE_FUNCTION_CALL
                || this->_type == SronTokenType::TYPE_MATH_BLOCK
        );
    }

    // returns true for the types whose type cannot be predicted during compile-time
    [[gnu::leaf]] inline bool isIndefiniteValueType() const noexcept
    {
        return ( this->_type == SronTokenType::TYPE_MATH_BLOCK ||
                 this->_type == SronTokenType::TYPE_IDENTIFIER ||
                 this->_type == SronTokenType::TYPE_FUNCTION_CALL
        );
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