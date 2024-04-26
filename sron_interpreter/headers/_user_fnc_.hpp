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
#include "_string_.hpp"
#include "_math_.hpp"

#include <functional>
#include <unordered_map>

using UserFunctionMap = std::unordered_map<std::string, std::function<Any *(Argument_List *)>>;

// this object is returned by all the user-available in-built functions defined in _user_fnc_.hpp::Sron namespace which returns 'Void' type value.
static Void void_object;

inline namespace Sron
{
    inline static Any *ASCII(Argument_List *);

    inline static Any *CLEAR(Argument_List *);
    inline static Any *COPY(Argument_List *);

    inline static Any *GET_EXEC_TIME(Argument_List *);

    // USER INPUT FUNCTIONS
    inline static Any *INPUT_INT(Argument_List *);
    inline static Any *INPUT_DOUBLE(Argument_List *);
    inline static Any *INPUT_CHAR(Argument_List *);
    inline static Any *INPUT_STRING(Argument_List *);

    // CHAR MANIPUALTION FUNCTIONS
    inline static Any *IS_ALPHABET(Argument_List *);
    inline static Any *IS_CONSONANT(Argument_List *);
    inline static Any *IS_NUMBER(Argument_List *);
    inline static Any *IS_VOWEL(Argument_List *);

    inline static Any *LEN(Argument_List *);

    // LIST MANIPULATION FUNCTIONS
    inline static Any *LIST_AT(Argument_List *);
    inline static Any *LIST_UPDATE(Argument_List *);
    inline static Any *LIST_PUSH(Argument_List *);

    inline static Any *PRINT(Argument_List *);
    inline static Any *PRINTLN(Argument_List *);

    inline static Any *SIZE_OF(Argument_List *);

    // type conversion function
    inline static Any *TO_BOOL(Argument_List *);
    inline static Any *TO_DOUBLE(Argument_List *);
    inline static Any *TO_INT(Argument_List *);
    inline static Any *TO_STRING(Argument_List *);

    inline static Any *TO_LOWERCASE(Argument_List *);
    inline static Any *TO_UPPERCASE(Argument_List *);

    // mathematical functions
    inline static Any *ABS(Argument_List *);
    inline static Any *CBRT(Argument_List *);
    inline static Any *CEIL(Argument_List *);
    inline static Any *COS(Argument_List *);
    inline static Any *FLOOR(Argument_List *);
    inline static Any *LOG(Argument_List *);
    inline static Any *LOG2(Argument_List *);
    inline static Any *LOG10(Argument_List *);
    inline static Any *MAX(Argument_List *);
    inline static Any *MIN(Argument_List *);
    inline static Any *SQRT(Argument_List *);
    inline static Any *SIN(Argument_List *);
    inline static Any *TAN(Argument_List *);

    // string manipulation functions...
    inline static Any *TO_CHAR_LIST(Argument_List *);

    inline static Any *TYPE_OF(Argument_List *);

    static UserFunctionMap Fmap{

        {"clear", Sron::CLEAR},
        {"copy", Sron::COPY},

        {"ascii", Sron::ASCII},

        {"get_exec_time", Sron::GET_EXEC_TIME},

        // user input functions...
        {"input_char", Sron::INPUT_CHAR},
        {"input_double", Sron::INPUT_DOUBLE},
        {"input_int", Sron::INPUT_INT},
        {"input_string", Sron::INPUT_STRING},

        {"isvowel", Sron::IS_VOWEL},
        {"isconsonant", Sron::IS_CONSONANT},
        {"isalphabet", Sron::IS_ALPHABET},
        {"isnumber", Sron::IS_NUMBER},

        {"len", Sron::LEN},

        {"list_at", Sron::LIST_AT},
        {"list_update", Sron::LIST_UPDATE},
        {"list_push", Sron::LIST_PUSH},

        {"println", Sron::PRINTLN},
        {"print", Sron::PRINT},

        {"sizeof", Sron::SIZE_OF},

        // type conversion functions...
        {"to_bool", Sron::TO_BOOL},
        {"to_double", Sron::TO_DOUBLE},
        {"to_int", Sron::TO_INT},
        {"to_string", Sron::TO_STRING},

        {"tocharlist", Sron::TO_CHAR_LIST},

        {"tolower", Sron::TO_LOWERCASE},
        {"toupper", Sron::TO_UPPERCASE},

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

    inline static Any *ASCII(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_INT:
            return new Char(val->GET_INT()->GET());
            break;

        case TYPE_CHAR:
            return new Int(val->GET_CHAR()->GET());
            break;

        default:
            DISPLAY_EXCEPTION("converting the value of type '" + val->TYPE() + "' to ascii. Expected argument are of type 'Int' or 'Char'.", NoException, false);
        }

        return &void_object;
    }

    // returns the length of the datatype
    inline static Any *LEN(Argument_List *args)
    {
        // return Int::MAKE((*args)[0]->LEN());
        return new Int(args->GET(0)->LEN());
    }

    inline static Any *CLEAR(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            val->GET_STRING()->CLEAR();
            break;

        case TYPE_LIST:
            val->GET_LIST()->CLEAR();
            break;

        default:
            DISPLAY_EXCEPTION("executing 'clear' function. Argument must be the type of either String or List and you passed value of type '" + val->TYPE() + "'.", NoException);
        }

        return &void_object;
    }

    inline static Any *COPY(Argument_List *args)
    {
        return args->GET(0)->COPY();
    }

    inline static Any *GET_EXEC_TIME(Argument_List *args)
    {
        return new Double(double(clock() - Logs::execution_start_time) / double(CLOCKS_PER_SEC));
    }

    inline static Any *INPUT_INT(Argument_List *args)
    {

        if (args->LEN() > 0)
        {
            args->GET(0)->PRINT();
        }

        return SronInput::INPUT_INT();
    }

    inline static Any *INPUT_DOUBLE(Argument_List *args)
    {
        if (args->LEN() > 0)
        {
            args->GET(0)->PRINT();
        }

        return SronInput::INPUT_DOUBLE();
    }

    inline static Any *INPUT_CHAR(Argument_List *args)
    {

        if (args->LEN() > 0)
        {
            args->GET(0)->PRINT();
        }

        return SronInput::INPUT_CHAR();
    }

    inline static Any *INPUT_STRING(Argument_List *args)
    {

        if (args->LEN() > 0)
        {
            args->GET(0)->PRINT();
        }

        return SronInput::INPUT_STRING();
    }

    inline static Any *IS_ALPHABET(Argument_List *args)
    {

        Char *val = args->GET_CHAR(0);

        return new Bool(SronChar::IS_ALPHABET(val->GET()));
    }
    inline static Any *IS_CONSONANT(Argument_List *args)
    {

        Char *val = args->GET_CHAR(0);

        return new Bool(SronChar::IS_CONSONANT(val->GET()));
    }
    inline static Any *IS_NUMBER(Argument_List *args)
    {

        Char *val = args->GET_CHAR(0);

        return new Bool(SronChar::IS_NUMBER(val->GET()));
    }
    inline static Any *IS_VOWEL(Argument_List *args)
    {

        Char *val = args->GET_CHAR(0);

        return new Bool(SronChar::IS_VOWEL(val->GET()));
    }

    inline static Any *LIST_AT(Argument_List *args)
    {
        // return args->GET(0)->GET_LIST()->AT(args->GET(1)->GET_INT()->GET());
        return args->GET_LIST(0)->AT(args->GET_INT(1)->GET())->COPY();
    }
    inline static Any *LIST_UPDATE(Argument_List *args)
    {

        args->GET_LIST(0)->UPDATE(args->GET_INT(1)->GET(), args->GET(2));

        return &void_object;
    }
    inline static Any *LIST_PUSH(Argument_List *args)
    {

        args->GET_LIST(0)->PUSH(args->GET(1));

        return &void_object;
    }

    inline static Any *SIZE_OF(Argument_List *args)
    {
        return new Int(args->GET(0)->SIZE_OF());
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
        return &void_object;
        ;
    }

    inline static Any *TO_BOOL(Argument_List *args)
    {

        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_INT:
            return new Bool(Converter::TO_BOOL(val->GET_INT()->GET()));

        case TYPE_DOUBLE:
            return new Bool(Converter::TO_BOOL(val->GET_DOUBLE()->GET()));

        case TYPE_STRING:
            return new Bool(Converter::TO_BOOL(val->GET_STRING()->GET()));

        case TYPE_BOOL:
            return new Bool(Converter::TO_BOOL(val->GET_BOOL()->GET()));

        default:
            DISPLAY_EXCEPTION("converting value of type '" + val->TYPE() + "' to type 'Bool'.", TypeConversionException);
        }

        return &void_object;
    }

    inline static Any *TO_DOUBLE(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            return new Double(Converter::TO_DOUBLE(val->GET_STRING()->GET()));

        case TYPE_INT:
            return new Double(Converter::TO_DOUBLE(val->GET_INT()->GET()));

        case TYPE_BOOL:
            return new Double(Converter::TO_DOUBLE(val->GET_BOOL()->GET()));

        case TYPE_DOUBLE:
            return new Double(Converter::TO_DOUBLE(val->GET_DOUBLE()->GET()));

        default:
            DISPLAY_EXCEPTION("converting value of type '" + val->TYPE() + "' to type 'Double'.", TypeConversionException);
        }

        return &void_object;
    }

    inline static Any *TO_INT(Argument_List *args)
    {

        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            return new Int(Converter::TO_INT(val->GET_STRING()->GET()));

        case TYPE_DOUBLE:
            return new Int(Converter::TO_INT(val->GET_DOUBLE()->GET()));

        case TYPE_CHAR:
            return new Int(Converter::TO_INT(val->GET_CHAR()->GET()));

        case TYPE_BOOL:
            return new Int(Converter::TO_INT(val->GET_BOOL()->GET()));

        default:
            DISPLAY_EXCEPTION("converting value of type '" + val->TYPE() + "' to type 'Int'.", TypeConversionException);
        }

        return &void_object;
    }

    inline static Any *TO_LOWERCASE(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            return new String(SronString::TO_LOWERCASE(val->GET_STRING()->GET()));

        case TYPE_CHAR:
            return new Char(SronChar::TO_LOWERCASE(val->GET_CHAR()->GET()));

        default:
            DISPLAY_EXCEPTION("converting value of type '" + val->TYPE() + "' to lowercase. Only type 'String' anc 'Char' can be converted to lowercase.", NoException);
        }

        return &void_object;
    }

    inline static Any *TO_UPPERCASE(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            return new String(SronString::TO_UPPERCASE(val->GET_STRING()->GET()));

        case TYPE_CHAR:
            return new Char(SronChar::TO_UPPERCASE(val->GET_CHAR()->GET()));

        default:
            DISPLAY_EXCEPTION("converting value of type '" + val->TYPE() + "' to uppercase. Only type 'String' anc 'Char' can be converted to uppercase.", NoException);
        }

        return &void_object;
    }

    inline static Any *TO_STRING(Argument_List *args)
    {
        return new String(args->GET(0)->TO_STRING());
    }

    inline static Any *TYPE_OF(Argument_List *args)
    {
        return new String(args->GET(0)->TYPE());
    }

    // args){
    //     Any* val = args->GET(0);
    //     switch(val->TYPE_NUMBER()){
    //         case TYPE_DOUBLE :
    //         case TYPE_INT :

    //         default : DISPLAY_EXCEPTION("executing the '' function. Only value of type 'Double' and 'Int' are allowed. ",NoException, false);
    //     }
    //     return &void_object;
    // }
    inline static Any *ABS(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::ABS(*val->GET_DOUBLE()));
        case TYPE_INT:
            return new Int(SronMath::ABS(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'abs' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }

    inline static Any *CBRT(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::CBRT(*val->GET_DOUBLE()));

        case TYPE_INT:
            return new Double(SronMath::CBRT(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'cbrt' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }

    inline static Any *CEIL(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Int(SronMath::CEIL(*val->GET_DOUBLE()));
        case TYPE_INT:
            return new Int(SronMath::CEIL(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'ceil' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }

    inline static Any *COS(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::COS(*val->GET_DOUBLE()));

        case TYPE_INT:
            return new Double(SronMath::COS(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'cos' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }

    inline static Any *FLOOR(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Int(SronMath::FLOOR(*val->GET_DOUBLE()));

        case TYPE_INT:
            return new Int(SronMath::FLOOR(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'floor' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }
    inline static Any *LOG(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::LOG(*val->GET_DOUBLE()));

        case TYPE_INT:
            return new Double(SronMath::LOG(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'log' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }
    inline static Any *LOG2(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::LOG2(*val->GET_DOUBLE()));

        case TYPE_INT:
            return new Double(SronMath::LOG2(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'log2' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }
    inline static Any *LOG10(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::LOG10(*val->GET_DOUBLE()));

        case TYPE_INT:
            return new Double(SronMath::LOG10(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'log10' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }

    inline static Any *MAX(Argument_List *args)
    {
        Any *val1 = args->GET(0);
        Any *val2 = args->GET(1);

        if (val1->TYPE_NUMBER() != val2->TYPE_NUMBER())
        {
            DISPLAY_EXCEPTION("executing the 'max' function. Both values should be of same datatype and only of type 'Double', 'Int', 'Char' and 'String'.", NoException, false);
        }

        switch (val1->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::MAX(*val1->GET_DOUBLE(), *val2->GET_DOUBLE()));
        case TYPE_INT:
            return new Int(SronMath::MAX(*val1->GET_INT(), *val2->GET_INT()));
        case TYPE_CHAR:
            return new Char(SronMath::MAX(*val1->GET_CHAR(), *val2->GET_CHAR()));
        case TYPE_STRING:
            return new String(SronMath::MAX(*val1->GET_STRING(), *val2->GET_STRING()));

        default:
            DISPLAY_EXCEPTION("executing the 'max' function. Only value of type 'Double', 'Int', 'String' and 'Char' are allowed. ", NoException, false);
        }
        return &void_object;
    }

    inline static Any *MIN(Argument_List *args)
    {
        Any *val1 = args->GET(0);
        Any *val2 = args->GET(1);

        if (val1->TYPE_NUMBER() != val2->TYPE_NUMBER())
        {
            DISPLAY_EXCEPTION("executing the 'min' function. Both values should be of same datatype and only of type 'Double', 'Int', 'Char' and 'String'.", NoException, false);
        }

        switch (val1->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::MIN(*val1->GET_DOUBLE(), *val2->GET_DOUBLE()));
        case TYPE_INT:
            return new Int(SronMath::MIN(*val1->GET_INT(), *val2->GET_INT()));
        case TYPE_CHAR:
            return new Char(SronMath::MIN(*val1->GET_CHAR(), *val2->GET_CHAR()));
        case TYPE_STRING:
            return new String(SronMath::MIN(*val1->GET_STRING(), *val2->GET_STRING()));

        default:
            DISPLAY_EXCEPTION("executing the 'min' function. Only value of type 'Double', 'Int', 'String' and 'Char' are allowed. ", NoException, false);
        }
        return &void_object;
    }
    inline static Any *SQRT(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::SQRT(*val->GET_DOUBLE()));
        case TYPE_INT:
            return new Double(SronMath::SQRT(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'sqrt' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }

    inline static Any *SIN(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::SIN(*val->GET_DOUBLE()));
        case TYPE_INT:
            return new Double(SronMath::SIN(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'sin' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }
    inline static Any *TAN(Argument_List *args)
    {
        Any *val = args->GET(0);
        switch (val->TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return new Double(SronMath::TAN(*val->GET_DOUBLE()));
        case TYPE_INT:
            return new Double(SronMath::TAN(*val->GET_INT()));

        default:
            DISPLAY_EXCEPTION("executing the 'tan' function. Only value of type 'Double' and 'Int' are allowed. ", NoException, false);
        }
        return &void_object;
    }

    inline static Any *TO_CHAR_LIST(Argument_List *args)
    {
        Any *val = args->GET(0);

        if (val->TYPE_NUMBER() == TYPE_STRING)
        {
            List *lst = new List();
            std::string &str = val->GET_STRING()->GET();

            for (auto &i : str)
            {
                lst->PUSH(new Char(i));
            }

            return lst;
        }
        DISPLAY_EXCEPTION("executing the 'tocharlist' functions. Arguments with only 'String' type is allowed not '" + val->TYPE() + "' type.", NoException, false);

        return &void_object;
    }
}

#endif