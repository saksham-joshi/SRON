/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 */
#ifndef EXCEPTION_H
#define EXCEPTION_H

#pragma once

#include "_throw_exception_.hpp"

// The exception below which be used to extract files from the Exception directory and display
#define ArgumentException "ArgumentException"
#define DatatypeConversionError "DatatypeConversionError"
#define EmptyAttributeCode "EmptyAttributeCode"
#define FileNotFoundException "FileNotFoundException"
#define FileNameNotSpecifiedException "FileNameNotSpecifiedException"
#define InputTypeException "InputTypeException"
#define InsertionException "InsertionException"
#define InvalidVariableNameException "InvalidVariableNameException"
#define InvalidAttributeException "InvalidAttributeException"
#define InvalidTypeException "InvalidTypeException"
#define SystemOutofMemoryException "SystemOutofMemoryException"
#define IndexNotWithinRange "IndexNotWithinRange"
#define VariableNotFoundException "VariableNotFoundException"
#define UnknownException "UnknownException"
#define WrongSyntaxException "WrongSyntaxException"
#define NoValidCodeFoundException "NoValidCodeFoundException"
#define FunctionNotFoundException "FunctionNotFoundException"
#define SourceCodeChangedException "SourceCodeChangedException"
#define MathEvaluationException "MathEvaluationException"
#define DivisionByZeroException "DivisionByZeroException"
#define ByteCodeCannotbeSavedException "ByteCodeCannotbeSavedException"
#define WaveCountIsNotEvenException "WaveCountIsNotEvenException"
#define MathematicalBlockSyntaxException "MathematicalBlockSyntaxException"
#define InvalidByteCodeException "InvalidByteCodeException"
#define InvalidObjectExtractionException "InvalidObjectExtractionException"
#define InvalidFlagException "InvalidFlagException"
#define NullAccessingException "NullAccessingException"

struct NullPointerException {

    inline virtual const char* what() const noexcept{
        return "accessing the non-ownable memory";
    }
};

inline static void LOAD_FILE_AND_PRINT(const char*const& __code)
{
    // now adding the directory path with with the path to exception....
    std::ifstream input(Logs::GET_EXECUTABLE_PATH() + "meta\\Exceptions\\" + std::string(__code) + ".txt");

    if (input.fail())
    {
        std::cerr <<   "\n+------------------------------------+\n"
                         "|  Exception message file not found  |\n"
                         "+------------------------------------+\n";
    }
    else
    {
        std::cerr << std::string((std::istreambuf_iterator<char>(input)), (std::istreambuf_iterator<char>()));
    }

    input.close();
}

inline static void DISPLAY_EXCEPTION(const char *const &__during, const char *const &__code)
{

    std::cerr << "\n--------------------------------\nIn '" << Logs::__FileStack__.back() << "'\n";

    if(std::strcmp(__code, NoException) != 0){
        std::cerr << __code << " caught:\n";
    }

    std::cerr << "||>> While " << __during << ".\n    ";

    if (strcmp(__code, NoException) == 0)
        return;

    LOAD_FILE_AND_PRINT(__code);

    std::cout << "\n\n   <| Read Documentations at https://sron.gitbook.io |>";
}

inline static void DISPLAY_EXCEPTION(const std::string &__during, const char *const &__code)
{
    DISPLAY_EXCEPTION(__during.c_str(), __code);
}

inline static void MATH_EVALUATION_EXCEPTION(const char *const &__operator, const char *const &__type)
{
    throw ThrowException(std::string("performing '" + std::string(__operator) + "' operation on value of type '" +std::string(__type) + "'"), MathEvaluationException);
}

inline static void MATH_EVALUATION_EXCEPTION(const char *const &_operator, const char *const &type1, const char *const &type2)
{
    throw ThrowException(std::string("performing '" + std::string(_operator) + "' operation between values of type '" +
                                      std::string(type1) + "' and '" + std::string(type2) + "'"),
                          MathEvaluationException);
}

inline static void CALLING_NON_DEFINED_FUNCTION(const char *const &_function_name, const char *const &_type)
{
    throw ThrowException("calling function '" + std::string(_function_name) + "' with argument of type '" + std::string(_type) + "'", ArgumentException);
}

inline static void THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(const long long int _current_index, const long long int _end_index, const char *const &_operation_name, const char *const &_type_on_which_operation_is_performed)
{

    if ((_current_index < 0) || (_current_index >= _end_index))
    {
        throw ThrowException("performing '" + std::string(_operation_name) + "' on value of type '" + std::string(_type_on_which_operation_is_performed) + "'", IndexNotWithinRange);
    }
}

inline static void THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION(const char *const &_type_of_object_to_be_extracted, const char *const &_current_object_type)
{
    throw ThrowException("extracting value of type '" + std::string(_type_of_object_to_be_extracted) + "' from type '" + std::string(_current_object_type) + "'", InvalidObjectExtractionException);
}

inline static void THROW_EXCEPTION_FOR_INVALID_ARGUMENTS(const char *const &_function_name, const char *const &_expected_argument_type1, const char *const &_expected_argument_type2)
{
    throw ThrowException("executing '" + std::string(_function_name) + "'. Expected arguments are either of type '" + std::string(_expected_argument_type1) + "' or '" + std::string(_expected_argument_type2) + "'", ArgumentException);
}

inline static void THROW_EXCEPTION_FOR_INVALID_ARGUMENTS(const char *const &_function_name, const char *const &_expected_argument_type1)
{
    throw ThrowException("executing '" + std::string(_function_name) + "'. Expected arguments of type '" + std::string(_expected_argument_type1) + "'", ArgumentException);
}


inline static void THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION(const char *const &_operation_name)
{
     THROW_EXCEPTION_FOR_INVALID_ARGUMENTS(_operation_name, "Double", "Int");
}

inline static void THROW_DIVISION_BY_ZERO_IF_NUMBER_IS_ZERO(double __right_value)
{
    if (__right_value == 0.0)
    {
        throw ThrowException("dividing a value by zero", DivisionByZeroException);
    }
}

inline static long long int SAFE_DIVIDE(long long int __left, long long int __right)
{

    THROW_DIVISION_BY_ZERO_IF_NUMBER_IS_ZERO(__right);

    return __left / __right;
}

inline static double SAFE_DIVIDE(long long int __left, double __right)
{

    THROW_DIVISION_BY_ZERO_IF_NUMBER_IS_ZERO(__right);

    return __left / __right;
}

inline static double SAFE_DIVIDE(double __left, long long int __right)
{

    THROW_DIVISION_BY_ZERO_IF_NUMBER_IS_ZERO(__right);

    return __left / __right;
}

inline static double SAFE_DIVIDE(double __left, double __right)
{

    THROW_DIVISION_BY_ZERO_IF_NUMBER_IS_ZERO(__right);

    return __left / __right;
}

inline static long long int SAFE_MOD(long long int __left, long long int __right)
{

    THROW_DIVISION_BY_ZERO_IF_NUMBER_IS_ZERO(__right);

    return __left % __right;
}

inline static double SAFE_MOD(long long int __left, double __right)
{

    THROW_DIVISION_BY_ZERO_IF_NUMBER_IS_ZERO(__right);

    return std::fmod(__left, __right);
}

inline static double SAFE_MOD(double __left, long long int __right)
{

    THROW_DIVISION_BY_ZERO_IF_NUMBER_IS_ZERO(__right);

    return std::fmod(__left, __right);
}

inline static double SAFE_MOD(double __left, double __right)
{

    THROW_DIVISION_BY_ZERO_IF_NUMBER_IS_ZERO(__right);

    return std::fmod(__left, __right);
}

#endif