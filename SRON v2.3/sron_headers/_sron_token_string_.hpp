#pragma once

#ifndef _SRON_STRING_H
#define _SRON_STRING_H

#include <cstring>
#include <string>
#include <iostream>
#include "_sron_hasher_.hpp"
#include "_sron_support_.hpp"

static char __Sron_Null_Terminator__ = '\0';

#if defined(__clang__)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined(__GNUC__)
    #pragma gcc diagnostic push
    #pragma gcc diagnostic ignored "-Wdeprecated-declarations"
#else
    #error "This codebase can only be compiled for either Clang or GCC."
#endif

struct SronTokenString
{
    public : 
        typedef unsigned short int TokenLen_t;
private:
    TokenLen_t len = 0;
    char *str = nullptr;


    inline void __INIT__(const char *const __source, const size_t __len = std::string::npos)
    {
        this->len = (__len == std::string::npos) ? std::strlen(__source) : __len;
        this->str = new char[ this->len + 1];
        std::strcpy(this->str, __source);
        this->str[this->len] = __Sron_Null_Terminator__;
    }

    inline void _DELETE_() noexcept
    {
        delete[] this->str;
        this->str = nullptr;
        this->len = 0;
    }

public:
    inline SronTokenString() {  this->__INIT__("", 0);  }

    inline SronTokenString(const char *const __str)
    {
        this->__INIT__(__str);
    }

    inline SronTokenString(const std::string &__str)
    {
        

        this->__INIT__(__str.c_str(), __str.length());
    }

    inline SronTokenString(SronTokenString &&__other) noexcept
    {   
        
        
        if (this != &__other)
        {
            this->str = __other.str;
            this->len = __other.len;
            __other.str = nullptr;
            __other.len = 0;
        }
    }

    inline SronTokenString(const SronTokenString &__other)
    {
        if (this != &__other) this->__INIT__(__other.str, __other.len);
        
    }

    inline SronTokenString &operator=(SronTokenString &&__other) noexcept
    {
        if (this != &__other)
        {
            this->_DELETE_();
            this->str = __other.str;
            this->len = __other.len;
            __other.str = nullptr;
            __other.len = 0;
        }
        return *this;
    }

    inline SronTokenString &operator=(const SronTokenString &__other)
    {
        if (this != &__other)
        {
            this->_DELETE_();

            this->__INIT__(__other.str, __other.len);
        }
        return *this;
    }

    inline SronTokenString &operator=(const char *const __str)
    {
        

        this->_DELETE_();

        this->__INIT__(__str);

        return *this;
    }

    inline SronTokenString &operator=(std::string &&__str)
    {
        
        this->_DELETE_();
        this->__INIT__(__str.c_str(), __str.length());
        return *this;
    }

    inline char &operator[](const TokenLen_t __index) const
    {
        return (__index < this->len) ? (this->str[__index]) : __Sron_Null_Terminator__;
    }

    inline bool operator!=(const char *const right) const
    {
        return std::strcmp(this->str, right) != 0;
    }

    inline bool operator!=(const SronTokenString &_right) const
    {
        return std::strcmp(this->str, _right.str) != 0;
    }

    inline bool operator==(const char *const &right) const
    {
        return std::strcmp(this->str, right) == 0;
    }

    inline bool operator==(const std::string &right) const
    {
        return ((this->len == right.length()) && (right == this->str));
    }

    inline bool operator==(const SronTokenString &_tk) const
    {
        return this->len == _tk.len && (std::strcmp(this->str, _tk.str) == 0);
    }

    inline bool operator<(const SronTokenString &_tk) const
    {
        return std::strcmp(this->str, _tk.str) < 0;
    }

    inline bool operator<=(const SronTokenString &_tk) const
    {
        return std::strcmp(this->str, _tk.str) <= 0;
    }

    inline bool operator>(const SronTokenString &_tk) const
    {
        return std::strcmp(this->str, _tk.str) > 0;
    }

    inline bool operator>=(const SronTokenString &_tk) const
    {
        return std::strcmp(this->str, _tk.str) >= 0;
    }

    inline SronTokenString &operator+=(const SronTokenString &__other)
    {
        if (__other.len > 0)
        {
            auto new_len = this->len + __other.len;

            char *new_str = new char[new_len + 1]; // Allocate space for new string including null terminator

            // Copy the original string
            SronSupport::copyMemory( new_str, this->str, this->len);
            //std::memcpy(new_str, this->str, this->len);

            // Append the new string
            SronSupport::copyMemory(new_str + this->len, __other.str, __other.len + 1);
            //std::memcpy(new_str + this->len, __other.str, __other.len + 1);

            // Free old memory
            delete[] this->str;

            // Update the internal state
            this->str = new_str;
            this->len = new_len;
        }
        return *this;
    }

    inline const char *c_str() const noexcept
    {
        return this->str;
    }

    inline TokenLen_t length() const noexcept
    {
        return this->len;
    }

    inline char *data() noexcept
    {
        return this->str;
    }

    inline void clear() noexcept
    {
        this->_DELETE_();
    }

    /*
        This Hash Function must be same as the hash function of
        sron_headers/_sron_hasher_.hpp::SronHasher::HashFunction

        If this is not done, then the whole compiler's working will disrupts.
    */
    struct HashFunction
    {
        inline std::size_t operator()(const SronTokenString &__s) const noexcept
        {
            return SronHasher(__s.str).GET();
        }
    };

    inline ~SronTokenString()
    {
        this->_DELETE_();
    }

    friend inline std::ostream &operator<<(std::ostream &, const SronTokenString &);
};

inline std::ostream &operator<<(std::ostream &COUT, const SronTokenString &_tk)
{
    return COUT << _tk.str;
}

#if defined(__clang__)
    #pragma clang diagnostic pop
#elif defined(__GNUC__)
    #pragma gcc diagnostic pop
#endif

#endif