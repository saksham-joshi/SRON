/*
 * Copyright (C) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the Creative Commons Attribution-NoDerivs 4.0 International Public License
 *  found in the LICENSE file in the root directory of this source tree.
 *
 * You can freely redistribute it but cannot modify the source code
 * without the permission from the author.
 */
#ifndef USER_FNC_H
#define USER_FNC_H

#include "_argument_list_.hpp"
#include <functional>
#include <unordered_map>

using FunctionMap = std::unordered_map<std::string, std::function<Any *(Argument_List *)>>;

inline namespace Sron
{
    inline Any *LEN(Argument_List *);
    inline Any *SIZE_OF(Argument_List *);
    inline Any *PRINT(Argument_List *);
    inline Any *PRINTLN(Argument_List *);
    inline Any *AT(Argument_List *);


    inline static FunctionMap &GET_FUNCTION_MAP()
    {
        static FunctionMap fmap{
            {"PRINTLN", Sron::PRINTLN},
            {"PRINT", Sron::PRINT},
            {"LEN", Sron::LEN},
            {"SIZE_OF", Sron::SIZE_OF},
            {"AT", Sron::AT}};
        return fmap;
    }

    inline static bool CHECK_IF_FUNCTION_EXISTS(std::string *str)
    {
        static FunctionMap fmap = GET_FUNCTION_MAP();
        return fmap.find(*str) != fmap.end();
    }

    inline Any *LEN(Argument_List *args)
    {
        return Int::MAKE((*args)[0]->LEN());
    }

    inline Any *SIZE_OF(Argument_List *args)
    {
        return Int::MAKE((*args)[0]->SIZE_OF());
    }

    inline Any *PRINT(Argument_List *args)
    {
        for (size_t i = 0; i < (*args).LEN(); ++i)
        {
            (*args)[i]->PRINT();
        }
        return Void::MAKE();
    }

    inline Any *PRINTLN(Argument_List *args)
    {
        PRINT(args);
        std::cout << '\n';
        return Void::MAKE();
    }
    inline Any *AT(Argument_List *args)
    {
        try
        {
            if ((*args)[0]->TYPE() == "List")
            {
                return (*args)[0]->GET_LIST()->AT((*args)[1]->GET_INT()->GET());
            }
            return Char::MAKE((*args)[0]->GET_STRING()->AT((*args)[1]->GET_INT()->GET()));
        }
        catch (std::exception &)
        {
            DISPLAY_EXCEPTION("executing the AT function and extracting elements from it.", ArgumentException);
        }
        return nullptr;
    }
}

#endif