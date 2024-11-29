
#pragma once

#ifndef SUPPORT_H
#define SUPPORT_H

#include "_throw_exception_.hpp"

namespace Support
{

    inline static bool CHECK_VALID_VARIABLE_NAME(const std::string &);

    inline static char GET_RESPECTIVE_CLOSING_CHAR(char);

    inline static flag_t GET_RESPECTIVE_ENDING_FLAG(flag_t);

    inline static int HANDLE_CMD_ARGUMENTS(int, char **);

    inline static bool IS_OPERATOR(const char &ch) noexcept;

    inline static bool IS_MATH_OPERATOR(const char &ch) noexcept;

    inline static bool IS_MAIN(SronTokenString&);

    inline static bool IS_NUMBER(int ch) noexcept;

    inline static bool IS_UNARY_OPERATOR(flag_t) noexcept;

    inline static bool IS_RESERVED_FILENAME(const std::string &__str) noexcept;

    inline static bool IS_SCOPE_OPERATOR(char ch) noexcept;

    inline static bool IS_VALID_END(const unsigned short int type) noexcept;

    inline static bool IS_VALUE_TYPE(const unsigned short int &_type) noexcept;

    inline static void REPLACE_CHAR_IN_CHAR_STR(char*, char, char);

    inline static char TO_LOWER(char &val) noexcept;

    inline static std::string TO_LOWER(const std::string &) noexcept;

    inline static const char *FLAG_TO_STRING(flag_t) noexcept;

    inline static const char* TYPE_TO_STRING(unsigned short int __type) noexcept;

}

#endif