
#pragma once

#ifndef _THROW_EXCEP_H
#define _THROW_EXCEP_H

#include "logs/_logs_.hpp"

#define NoException "DefaultException"
#define TypeConversionError "TypeConversionError"

struct ThrowException : std::exception
{

    SronTokenString message__;
    const char* excode__;

    inline ThrowException(const char*const& __message, const char*const& __excode = NoException)
        : message__(__message), excode__(__excode) { }

    inline ThrowException(const std::string &__message, const char*const &__excode = NoException)
        : message__(__message.c_str()), excode__(__excode){ }

    inline virtual const char *what() 
    {
        return this->message__.GET();
    }
};

#endif