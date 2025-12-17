
#pragma once

#ifndef _THROW_EXCEP_H
#define _THROW_EXCEP_H

#include "_error_.hpp"

struct ThrowException : std::exception
{

    SronTokenString _message;
    const char* _excode;
    unsigned long _file_index;

    explicit inline ThrowException(const char *const &__message, const char *const &excode = NoException,  const unsigned long __file_index = ULONG_MAX)
        : _message(__message), _excode(excode), _file_index(__file_index) {}

    explicit inline ThrowException(const std::string &__message, const char *const &excode = NoException, const unsigned long __file_index = ULONG_MAX)
        : _message(__message.c_str()), _excode(excode), _file_index(__file_index) {}


    explicit inline ThrowException(const char* const& __message, unsigned long __file_index, const char*const& __excode = NoException)
        : _message(__message) , _excode(__excode) , _file_index(__file_index) { }
    
    explicit inline ThrowException(const std::string&__message, unsigned long __file_index, const char*const& __excode = NoException)
        : _message(__message.c_str()) , _excode(__excode) , _file_index(__file_index) { }
 

    inline const char *what()
    {
        return _message.GET();
    }
};

#endif