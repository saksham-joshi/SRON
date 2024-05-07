#pragma once

#ifndef SUPPORT_H
#define SUPPORT_H

#include "_flags_.hpp"
#include "_exception_.hpp"

inline namespace Support
{
    // this function will return if the passed is a flag or not!
    inline static bool IS_FLAG(std::string &str)
    {

        /*
        Suppose a case when user creates a char value '`' then the
        interpreter may consider it as flag that's why this condition
        is mentioned here that if the passed std::string is tilt(`),
        then it can't be a flag.
        */
        if (str.length() == 0 || str == "`" || str[0] != '`')
        {
            return false;
        }
        return true;
    }

    inline static bool IS_LOOP_OPENING_FLAG(std::string &str)
    {
        return (str == Flag_ForScopeStart || str == Flag_WhileScopeStart);
    }
    inline static bool IS_LOOP_ENDING_FLAG(std::string &str)
    {
        return (str == Flag_ForScopeEnd || str == Flag_WhileScopeEnd);
    }

    inline static const char *GET_ENDING_FLAG_OF_CONDITIONAL_STATEMENT(std::string &str)
    {
        if (str == Flag_IfScopeStart)
        {
            return Flag_IfScopeEnd;
        }
        else if (str == Flag_ElifScopeStart)
        {
            return Flag_ElifScopeEnd;
        }
        return Flag_ElseScopeEnd;
    }
}

#endif