#pragma once

#ifndef SUPPORT_H
#define SUPPORT_H

#include "_flags_.hpp"
#include "_exception_.hpp"

inline namespace Support
{
    // this function will return if the passed is a flag or not!
    inline static bool IS_FLAG(std::string &str);

    inline static bool IS_LOOP_OPENING_FLAG(std::string &str);
    inline static bool IS_LOOP_ENDING_FLAG(std::string &str);
    

    inline static const char *GET_ENDING_FLAG_OF_CONDITIONAL_STATEMENT(std::string &str);

    /* this function will return a function vector from Logs::_LOADED_FUNCTION_MAP_, if the fnc is already loaded before and
     * if it is not loaded before then it will create one return it.
     */
    inline static void GET_FUNCTION_VECTOR(std::string &function_name, std::vector<std::string>::iterator ar[2] );
}

#endif