
#pragma once

#ifndef _THROW_EXCEP_H
#define _THROW_EXCEP_H

#include "_error_.hpp"

struct ThrowException : std::exception
{

    std::string _message;
    const char* _excode;
    unsigned long _file_index;

    explicit inline ThrowException(const char *const __message, const char *const excode = SronError::DefaultError,  const unsigned long __file_index = ULONG_MAX)
        : _message(__message), _excode(excode), _file_index(__file_index) {}

    explicit inline ThrowException(const std::string &__message, const char *const excode = SronError::DefaultError, const unsigned long __file_index = ULONG_MAX)
        : _message(__message), _excode(excode), _file_index(__file_index) {}


    explicit inline ThrowException(const char* const __message, unsigned long __file_index, const char*const __excode = SronError::DefaultError)
        : _message(__message) , _excode(__excode) , _file_index(__file_index) { }
    
    explicit inline ThrowException(const std::string&__message, unsigned long __file_index, const char*const __excode = SronError::DefaultError)
        : _message(__message) , _excode(__excode) , _file_index(__file_index) { }

    inline ThrowException( const ThrowException& __other ) noexcept
    {
        this->_message = std::move( __other._message );
        this->_excode = __other._excode;
        this->_file_index = __other._file_index;
    }

    inline ThrowException( ThrowException&& __other ) noexcept
    {
        this->_message = std::move(__other._message);
        this->_excode = __other._excode;
        this->_file_index = __other._file_index;
    }
 
    inline virtual const char* what() const noexcept override
    {
        return _message.c_str();
    }
};

inline static void THROW_TYPE_CONVERSION_ERROR( const std::string& __converting_value , const std::string& __converting_from_type ,  const std::string& __converting_to_type )
{
    throw ThrowException("converting `" + __converting_value + "` which is a value of type '" + __converting_from_type + "' to type '" + __converting_to_type + "'", SronError::TypeConversionError);
}

#endif