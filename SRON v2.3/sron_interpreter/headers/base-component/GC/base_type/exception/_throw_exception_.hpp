
#pragma once

#ifndef _THROW_EXCEP_H
#define _THROW_EXCEP_H

#include "_exception_.hpp"

struct ThrowException : std::exception
{

    std::string message__;
    const char* excode__;
    const char* filename__ = "terminal";
    bool filename_assigned__ = false;
    SronExitCodes exitcode__ = SronExitCodes::BASIC_EXCEPTION;

    inline ThrowException(const char*const& __message, const char*const __excode = SronException::DefaultException, SronExitCodes __exitcode = SronExitCodes::BASIC_EXCEPTION)
        : message__(__message), excode__(__excode), exitcode__(__exitcode) { }

    inline ThrowException(const std::string &__message, const char*const __excode = SronException::DefaultException, SronExitCodes __exitcode = SronExitCodes::BASIC_EXCEPTION)
        : message__(__message.c_str()), excode__(__excode), exitcode__(__exitcode){ }

    inline ThrowException( ThrowException&& __excep ) : message__(std::move(__excep.message__)) ,
          excode__(__excep.excode__) , filename__(__excep.filename__) , filename_assigned__(__excep.filename_assigned__)
          , exitcode__(__excep.exitcode__) { }

    inline const char *what() const noexcept override
    {
        return this->message__.c_str();
    }

    inline void setFileName( const char*const __filename )
    {
        if ( this->filename_assigned__ ) return;

        this->filename__ = __filename;

        this->filename_assigned__ = true;
    }
};


inline static void mathEvaluationException(const char *const __operator, const char *const __type)
{
    throw ThrowException(std::string("performing '" + std::string(__operator) + "' operation on value of type '" +std::string(__type) + "'"), SronException::MathEvaluationException);
}

inline static void mathEvaluationException(const char*const _operator, const char*const type1, const char*const type2)
{
    throw ThrowException(std::string("performing '" + std::string(_operator) + "' operation between values of type '" +
                                      std::string(type1) + "' and '" + std::string(type2) + "'"),
                          SronException::MathEvaluationException);
}

inline static void callingNonDefinedFunction(const char*const _function_name, const char*const _type)
{
    throw ThrowException("calling function '" + std::string(_function_name) + "' with argument of type '" + std::string(_type) + "'", SronException::ArgumentException);
}

inline static void throwExceptionIfIndexOutOfBound(const SronInt_t _current_index, const SronInt_t _end_index, const char*const _operation_name, const char*const _type_on_which_operation_is_performed)
{

    if ((_current_index < 0) || (_current_index >= _end_index))
    {
        throw ThrowException("performing '" + std::string(_operation_name) + "' on value of type '" + std::string(_type_on_which_operation_is_performed) + "'", SronException::IndexNotWithinRangeException);
    }
}

inline static void throwInvalidObjectExtractionException(const char*const _type_of_object_to_be_extracted, const char*const _current_object_type)
{
    throw ThrowException("extracting value of type '" + std::string(_type_of_object_to_be_extracted) + "' from type '" + std::string(_current_object_type) + "'", SronException::InvalidObjectExtractionException);
}

inline static void throwArgumentException(const char*const _function_name, const char*const _expected_argument_type1, const char*const _expected_argument_type2)
{
    throw ThrowException("executing '" + std::string(_function_name) + "'. Expected arguments are either of type '" + std::string(_expected_argument_type1) + "' or '" + std::string(_expected_argument_type2) + "'", SronException::ArgumentException);
}

inline static void throwArgumentException(const char*const _function_name, const char*const _expected_argument_type1)
{
    throw ThrowException("executing '" + std::string(_function_name) + "'. Expected arguments of type '" + std::string(_expected_argument_type1) + "'", SronException::ArgumentException);
}


inline static void throwArgumentExceptionForMathematicalException(const char*const _operation_name)
{
    throwArgumentException(_operation_name, "SronDouble_t", "Int");
}

inline static void throwDivisonByZeroIfNumberIsZero(SronDouble_t __right_value)
{
    if (__right_value == 0.0)
    {
        throw ThrowException("dividing a value by zero", SronException::DivisionByZeroException);
    }
}

inline static SronInt_t safeDivide(SronInt_t __left, SronInt_t __right)
{

    throwDivisonByZeroIfNumberIsZero(__right);

    return __left / __right;
}

inline static SronDouble_t safeDivide(SronInt_t __left, SronDouble_t __right)
{

    throwDivisonByZeroIfNumberIsZero(__right);

    return __left / __right;
}

inline static SronDouble_t safeDivide(SronDouble_t __left, SronInt_t __right)
{

    throwDivisonByZeroIfNumberIsZero(__right);

    return __left / __right;
}

inline static SronDouble_t safeDivide(SronDouble_t __left, SronDouble_t __right)
{

    throwDivisonByZeroIfNumberIsZero(__right);

    return __left / __right;
}

inline static SronInt_t SAFE_MOD(SronInt_t __left, SronInt_t __right)
{

    throwDivisonByZeroIfNumberIsZero(__right);

    return __left % __right;
}

inline static SronDouble_t SAFE_MOD(SronInt_t __left, SronDouble_t __right)
{

    throwDivisonByZeroIfNumberIsZero(__right);

    return std::fmod(__left, __right);
}

inline static SronDouble_t SAFE_MOD(SronDouble_t __left, SronInt_t __right)
{

    throwDivisonByZeroIfNumberIsZero(__right);

    return std::fmod(__left, __right);
}

inline static SronDouble_t SAFE_MOD(SronDouble_t __left, SronDouble_t __right)
{

    throwDivisonByZeroIfNumberIsZero(__right);

    return std::fmod(__left, __right);
}

#endif