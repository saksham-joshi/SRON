#pragma once

#ifndef SUPPORT_H
#define SUPPORT_H

#include "_flags_.hpp"
#include "_error_.hpp"

inline namespace Support
{
    inline static bool CHECK_VALID_IDENTIFIER_NAME(std::string &);

    inline static void DISPLAY_VERSION() noexcept;

    inline static const char *GET_ENDING_FLAG_OF_CONDITIONAL_STATEMENT(std::string &s) noexcept;

    inline static bool IS_CURLY_BRACES(char &) noexcept;
    inline static bool IS_CURLY_BRACES(std::string &) noexcept;

    inline static bool IS_IDENTIFIER(const std::string &) noexcept;

    inline static bool IS_INNER_SCOPE_ATTRIBUTE(std::string &) noexcept;
    inline static bool IS_INBUILT_ATTRIBUTE(std::string &) noexcept;
    inline static bool IS_ATTRIBUTE(std::string &) noexcept;
    inline static bool IS_VALID_ATTRIBUTE_WITH_ROUND_BRACKETS(std::string &) noexcept;

    inline static bool IS_DATATYPE(std::string &) noexcept;
    inline static bool IS_KEYWORD(std::string &) noexcept;
    inline static bool IS_LOGICAL_OPERATOR(std::string &) noexcept;

    inline static bool IS_SQUARE_BRACKET(char &ch) noexcept;

    inline static char TO_LOWER(char &) noexcept;
    inline static std::string TO_LOWER(std::string) noexcept;

    inline static bool IS_UNSIGNED_INTEGER(std::string &) noexcept;
    inline static bool IS_RESERVED_FILENAME(std::string &) noexcept;

    inline static bool IS_FLAG(std::string &) noexcept;
    inline static bool IS_LOOP_OPENING_FLAG(std::string &str) noexcept;
    inline static bool IS_LOOP_ENDING_FLAG(std::string &str) noexcept;

    inline static bool IS_VALID_ATTRIBUTE_FOR_CONDITION_ATTRIBUTE(std::string &) noexcept;
    inline static bool IS_VALID_FUNCTION_NAME(std::string &) noexcept;

    inline static bool IS_VALID_TYPE_AFTER_OPERATOR(const unsigned short int type) noexcept;
    inline static bool IS_VALID_TYPE_BEFORE_OPERATOR(const unsigned short int type) noexcept;

    inline static bool IS_VALID_END(const unsigned short int) noexcept;

    inline static int PRECEDENCE(std::string &str) noexcept;

    inline static const char *TYPE_FLAG_TO_STRING(unsigned short int) noexcept;

    inline static void DISPLAY_VERSION() noexcept
    {
        std::cout << "\n"
                     "+----------------------------+\n"
                     "|      SRON version 1.5      |\n"
                     "|  @Author : Saksham Joshi   |\n"
                     "+----------------------------+\n\n";
    }
}

#endif