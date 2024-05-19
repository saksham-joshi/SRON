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

#include "_input_.hpp"
#include "_char_.hpp"
#include "_math_.hpp"
#include "_random_.hpp"

#include <functional>
#include <unordered_map>

// this object is returned by all the user-available in-built functions defined in _user_fnc_.hpp::Sron namespace which returns 'Void' type value.
static Void void_object;

inline namespace Sron
{
    inline static Any *ASCII(Argument_List &);

    inline static Any *BEEP(Argument_List &);

    inline static Any *BOOST_IO(Argument_List &);

    inline static Any *CLEAR(Argument_List &);
    inline static Any *COPY(Argument_List &);

    inline static Any *EXIT(Argument_List &);

    inline static Any *GET_EXEC_TIME(Argument_List &);

    // USER INPUT FUNCTIONS
    inline static Any *INPUT_INT(Argument_List &);
    inline static Any *INPUT_DOUBLE(Argument_List &);
    inline static Any *INPUT_CHAR(Argument_List &);
    inline static Any *INPUT_STRING(Argument_List &);

    // CHAR MANIPUALTION FUNCTIONS
    inline static Any *IS_ALPHABET(Argument_List &);
    inline static Any *IS_CONSONANT(Argument_List &);
    inline static Any *IS_NUMBER(Argument_List &);
    inline static Any *IS_VOWEL(Argument_List &);
    inline static Any *IS_LOWERCASE(Argument_List &);
    inline static Any *IS_UPPERCASE(Argument_List &);

    inline static Any *LEN(Argument_List &);

    // COMMON LIST AND STRING MANIPULATION FUNCTIONS
    inline static Any *AT(Argument_List &);
    inline static Any *COUNT(Argument_List &);
    inline static Any *DELETE_(Argument_List &);
    inline static Any *INDEX(Argument_List &);
    inline static Any *INSERT(Argument_List &);
    inline static Any *PUSH(Argument_List &);
    inline static Any *POP(Argument_List &);
    inline static Any *REPLACE(Argument_List &);
    inline static Any *REVERSE(Argument_List &);
    inline static Any *RINDEX(Argument_List &);
    inline static Any *SORT(Argument_List &);
    inline static Any *UPDATE(Argument_List &);

    inline static Any *PRINT(Argument_List &);
    inline static Any *PRINTLN(Argument_List &);

    // generating random numbers...
    inline static Any *RANDINT(Argument_List &);
    inline static Any *RANDRANGE(Argument_List &);
    inline static Any *RANDDOUBLE(Argument_List &);

    inline static Any *SIZE_OF(Argument_List &);
    inline static Any *SUBLIST(Argument_List &);

    // type conversion function
    inline static Any *TO_BOOL(Argument_List &);
    inline static Any *TO_DOUBLE(Argument_List &);
    inline static Any *TO_INT(Argument_List &);
    inline static Any *TO_STRING(Argument_List &);

    // COMMON STRING AND CHAR FUNCTIONS...
    inline static Any *TO_LOWERCASE(Argument_List &);
    inline static Any *TO_UPPERCASE(Argument_List &);

    // mathematical functions
    inline static Any *ABS(Argument_List &);
    inline static Any *CBRT(Argument_List &);
    inline static Any *CEIL(Argument_List &);
    inline static Any *COS(Argument_List &);
    inline static Any *FLOOR(Argument_List &);
    inline static Any *LOG(Argument_List &);
    inline static Any *LOG2(Argument_List &);
    inline static Any *LOG10(Argument_List &);
    inline static Any *MAX(Argument_List &);
    inline static Any *MIN(Argument_List &);
    inline static Any *SQRT(Argument_List &);
    inline static Any *SIN(Argument_List &);
    inline static Any *TAN(Argument_List &);

    // string manipulation functions...
    inline static Any *TO_CHAR_LIST(Argument_List &);
    inline static Any *SUBSTRING(Argument_List &);
    inline static Any *SPLIT(Argument_List &);
    inline static Any *TRIM(Argument_List &);

    inline static Any *SET_PRECISION(Argument_List &);
    inline static Any *SYS_CMD(Argument_List &);

    inline static Any *TYPE_OF(Argument_List &);

    // returns the version of the function ...
    inline static Any *VERSION(Argument_List &);

    using UserFunctionMap = std::unordered_map<std::string, std::function<Any *(Argument_List &)>>;

    static UserFunctionMap Fmap{

        {"ascii", Sron::ASCII},

        {"beep", Sron::BEEP},

        {"boost_io", Sron::BOOST_IO},

        {"clear", Sron::CLEAR},
        {"copy", Sron::COPY},

        {"exit", Sron::EXIT},

        {"get_exec_time", Sron::GET_EXEC_TIME},

        // user input functions...
        {"input_char", Sron::INPUT_CHAR},
        {"input_double", Sron::INPUT_DOUBLE},
        {"input_int", Sron::INPUT_INT},
        {"input_string", Sron::INPUT_STRING},

        {"isalphabet", Sron::IS_ALPHABET},
        {"isconsonant", Sron::IS_CONSONANT},
        {"isdigit", Sron::IS_NUMBER},
        {"isvowel", Sron::IS_VOWEL},
        {"islower", Sron::IS_LOWERCASE},
        {"isupper", Sron::IS_UPPERCASE},

        {"len", Sron::LEN},

        // common list and string manipulation functions...
        {"at", Sron::AT},
        {"count", Sron::COUNT},
        {"delete", Sron::DELETE_},
        {"index", Sron::INDEX},
        {"insert", Sron::INSERT},
        {"push", Sron::PUSH},
        {"pop", Sron::POP},
        {"replace", Sron::REPLACE},
        {"reverse", Sron::REVERSE},
        {"rindex", Sron::RINDEX},
        {"sort", Sron::SORT},
        {"update", Sron::UPDATE},

        {"println", Sron::PRINTLN},
        {"print", Sron::PRINT},

        // generating random numbers...
        {"randint", Sron::RANDINT},
        {"randrange", Sron::RANDRANGE},
        {"randdouble", Sron::RANDDOUBLE},

        {"setprecision", Sron::SET_PRECISION},
        {"sizeof", Sron::SIZE_OF},

        // type conversion functions...
        {"to_bool", Sron::TO_BOOL},
        {"to_double", Sron::TO_DOUBLE},
        {"to_int", Sron::TO_INT},
        {"to_string", Sron::TO_STRING},

        // string manipulation methods
        {"tocharlist", Sron::TO_CHAR_LIST},
        {"substring", Sron::SUBSTRING},
        {"split", Sron::SPLIT},
        {"trim", Sron::TRIM},

        {"tolower", Sron::TO_LOWERCASE},
        {"toupper", Sron::TO_UPPERCASE},

        // list manipulation methods...
        {"sublist", Sron::SUBLIST},

        // math functions...
        {"abs", Sron::ABS},
        {"max", Sron::MAX},
        {"min", Sron::MIN},
        {"sqrt", Sron::SQRT},
        {"cbrt", Sron::CBRT},
        {"log", Sron::LOG},
        {"log2", Sron::LOG2},
        {"log10", Sron::LOG10},
        {"sin", Sron::SIN},
        {"cos", Sron::COS},
        {"tan", Sron::TAN},
        {"ceil", Sron::CEIL},
        {"floor", Sron::FLOOR},

        {"syscmd", Sron::SYS_CMD},

        {"typeof", Sron::TYPE_OF},

        {"version", Sron::VERSION}};

    inline static bool CHECK_IF_FUNCTION_EXISTS(std::string *str)
    {
        return Sron::Fmap.find(*str) != Sron::Fmap.end();
    }

    /* this function takes the std::string as an argument then finds that in the
    Sron::UserFunctionMap. If the function is found then return that function
    otherwise returns nullptr.*/
    inline static std::function<Any *(Argument_List &)> GET_SRON_FUNCTION(std::string &fnc_name)
    {
        auto temp = Fmap.find(fnc_name);
        if (temp != Fmap.end())
        {
            return temp->second;
        }
        return nullptr;
    }
}

#endif