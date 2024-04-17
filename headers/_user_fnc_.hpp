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

using UserFunctionMap = std::unordered_map<std::string, std::function<Any *(Argument_List *)>>;

static Void void_object;

inline namespace Sron
{
    inline static Any *COPY(Argument_List *);

    inline static Any *INPUT_INT(Argument_List *);
    inline static Any *INPUT_DOUBLE(Argument_List *);
    inline static Any *INPUT_CHAR(Argument_List *);
    inline static Any *INPUT_STRING(Argument_List *);

    inline static Any *LEN(Argument_List *);

    inline static Any *LIST_AT(Argument_List *);
    inline static Any *LIST_UPDATE(Argument_List *);
    inline static Any *LIST_PUSH(Argument_List *);


    inline static Any *PRINT(Argument_List *);
    inline static Any *PRINTLN(Argument_List *);

    inline static Any *SIZE_OF(Argument_List *);

    inline static Any* TYPE_OF(Argument_List *);

    static UserFunctionMap Fmap{

        {"copy", Sron::COPY},

        {"input_char", Sron::INPUT_CHAR},
        {"input_double", Sron::INPUT_DOUBLE},
        {"input_char", Sron::INPUT_INT},
        {"input_string", Sron::INPUT_STRING},

        {"len", Sron::LEN},

        {"list_at", Sron::LIST_AT},
        {"list_update", Sron::LIST_UPDATE},
        {"list_push", Sron::LIST_PUSH},

        {"println", Sron::PRINTLN},
        {"print", Sron::PRINT},

        {"sizeof", Sron::SIZE_OF},

        {"typeof", Sron::TYPE_OF}

        };

    inline static bool CHECK_IF_FUNCTION_EXISTS(std::string *str)
    {
        return Sron::Fmap.find(*str) != Sron::Fmap.end();
    }

    /* this function takes the std::string as an argument then finds that in the
    Sron::UserFunctionMap. If the function is found then return that function
    otherwise returns nullptr.*/
    inline static std::function<Any *(Argument_List *)> GET_SRON_FUNCTION(std::string &fnc_name)
    {
        auto temp = Fmap.find(fnc_name);
        if (temp != Fmap.end())
        {
            return temp->second;
        }
        return nullptr;
    }

    // returns the length of the datatype
    inline static Any *LEN(Argument_List *args)
    {
        return Int::MAKE((*args)[0]->LEN());
    }

    inline static Any *COPY(Argument_List *args){
        return args->GET(0)->COPY();
    }

    inline static Any *INPUT_INT(Argument_List *args)
    {
        try
        {
            if (args->LEN() > 0)
            {
                args->GET(0)->PRINT();
            }

            long long int value = 0;

            std::cin >> value;

            return new Int(value);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking 'Int' input from terminal.", InputTypeException , false);
        }
        return &void_object;
    }

    inline static Any *INPUT_DOUBLE(Argument_List *args)
    {
        try
        {
            if (args->LEN() > 0)
            {
                args->GET(0)->PRINT();
            }

            double value = 0;

            std::cin >> value;

            return new Double(value);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking 'Double' input from terminal.", InputTypeException , false);
        }
        return &void_object;
    }

    inline static Any *INPUT_CHAR(Argument_List *args)
    {
        try
        {
            if (args->LEN() > 0)
            {
                args->GET(0)->PRINT();
            }

            char value = ' ';

            std::cin >> value;

            return new Char(value);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking 'Char' input from terminal.", InputTypeException , false);
        }
        return &void_object;
    }

    inline static Any *INPUT_STRING(Argument_List *args)
    {
        try
        {
            if (args->LEN() > 0)
            {
                args->GET(0)->PRINT();
            }

            std::string value(" ");

            std::getline(std::cin , value);

            return new String(value);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("taking 'String' input from terminal.", InputTypeException , false);
        }
        return &void_object;
    }

    inline static Any *LIST_AT(Argument_List *args){
        return args->GET(0)->GET_LIST()->AT(args->GET(1)->GET_INT()->GET());
    }
    inline static Any *LIST_UPDATE(Argument_List *args){

        args->GET(0)->GET_LIST()->UPDATE( args->GET(1)->GET_INT()->GET() , args->GET(2));

        return &void_object;
    }
    inline static Any *LIST_PUSH(Argument_List *args){

        args->GET(0)->GET_LIST()->PUSH(args->GET(1));

        return &void_object;
    }

    inline static Any *SIZE_OF(Argument_List *args)
    {
        return Int::MAKE((*args)[0]->SIZE_OF());
    }

    inline static Any *PRINT(Argument_List *args)
    {
        for (unsigned short int i = 0; i < args->LEN(); ++i)
        {
            args->GET(i)->PRINT();
            
        }
        return &void_object;
    }

    inline static Any *PRINTLN(Argument_List *args)
    {
        PRINT(args);
        std::cout << '\n';
        return &void_object; ;
    }

    inline static Any* TYPE_OF(Argument_List *args){
        return new String(args->GET(0)->TYPE());
    }
}

#endif