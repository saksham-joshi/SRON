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

using UserFunctionMap = std::unordered_map<std::string, std::function<Any *(Argument_List *)>>;

// this object is returned by all the user-available in-built functions defined in _user_fnc_.hpp::Sron namespace which returns 'Void' type value.
static Void void_object;

inline namespace Sron
{
    inline static Any *ASCII(Argument_List *);

    inline static Any *BEEP(Argument_List *);

    inline static Any *BOOST_IO(Argument_List *);

    inline static Any *CLEAR(Argument_List *);
    inline static Any *COPY(Argument_List *);

    inline static Any *EXIT(Argument_List *);

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

    // COMMON LIST AND STRING MANIPULATION FUNCTIONS
    inline static Any *AT(Argument_List *);
    inline static Any *COUNT(Argument_List *);
    inline static Any *DELETE_(Argument_List *);
    inline static Any *INDEX(Argument_List *);
    inline static Any *INSERT(Argument_List *);
    inline static Any *PUSH(Argument_List *);
    inline static Any *POP(Argument_List *);
    inline static Any *REPLACE(Argument_List *);
    inline static Any *REVERSE(Argument_List *);
    inline static Any *RINDEX(Argument_List *);
    inline static Any *SORT(Argument_List *);
    inline static Any *UPDATE(Argument_List *);

    inline static Any *PRINT(Argument_List *);
    inline static Any *PRINTLN(Argument_List *);

    // generating random numbers...
    inline static Any *RANDINT(Argument_List *);
    inline static Any *RANDRANGE(Argument_List *);
    inline static Any *RANDDOUBLE(Argument_List *);

    inline static Any *SIZE_OF(Argument_List *);
    inline static Any *SUBLIST(Argument_List *);

    // type conversion function
    inline static Any *TO_BOOL(Argument_List *);
    inline static Any *TO_DOUBLE(Argument_List *);
    inline static Any *TO_INT(Argument_List *);
    inline static Any *TO_STRING(Argument_List *);

    // COMMON STRING AND CHAR FUNCTIONS...
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
    inline static Any *SUBSTRING(Argument_List *);
    inline static Any *SPLIT(Argument_List *);
    inline static Any *TRIM(Argument_List *);

    inline static Any *SET_PRECISION(Argument_List *);

    inline static Any *TYPE_OF(Argument_List *);

    // returns the version of the function ...
    inline static Any *VERSION(Argument_List *);

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
        {"isnumber", Sron::IS_NUMBER},
        {"isvowel", Sron::IS_VOWEL},

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

        {"typeof", Sron::TYPE_OF},

        {"version", Sron::VERSION}};

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

    inline static Any *AT(Argument_List *args)
    {
        if (args->GET(0)->TYPE_NUMBER() == TYPE_STRING && args->GET(1)->TYPE_NUMBER() == TYPE_INT)
        {
            return new Char(args->GET_STRING(0)->AT(args->GET_INT(1)->GET()));
        }
        else if (args->GET(0)->TYPE_NUMBER() == TYPE_LIST && args->GET(1)->TYPE_NUMBER() == TYPE_INT)
        {
            return args->GET_LIST(0)->AT(args->GET_INT(0)->GET());
        }

        DISPLAY_EXCEPTION("executing the 'at' function. Expected 'String' or 'List' type as first argument and second argument must be of type 'Int'.", NoException);

        return &void_object;
    }

    inline static Any *BEEP(Argument_List *args)
    {

        if (args->GET(0)->TYPE_NUMBER() == TYPE_INT && args->GET(1)->TYPE_NUMBER() == TYPE_INT)
        {
            Beep(args->GET(0)->GET_INT()->GET(), args->GET(1)->GET_INT()->GET());
        }
        else
        {
            DISPLAY_EXCEPTION("executing the 'beep' function. Both arguments should be of type 'Int'.", NoException, false);
        }
        return &void_object;
    }

    inline static Any *BOOST_IO(Argument_List *args)
    {
        std::ios::sync_with_stdio(false);
        std::cout.tie(NULL);
        std::cin.tie(NULL);

        return &void_object;
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

    // function to create a copy of the values passed ...
    inline static Any *COPY(Argument_List *args)
    {
        return args->GET(0)->COPY();
    }

    // function to count occurrences of a particular value in 'List' or 'String'
    inline static Any *COUNT(Argument_List *args)
    {

        switch (args->GET(0)->TYPE_NUMBER())
        {

        case TYPE_LIST:
            return new Int(args->GET_LIST(0)->COUNT(args->GET(1)));

        case TYPE_STRING:
        {
            switch (args->GET(1)->TYPE_NUMBER())
            {

            case TYPE_CHAR:
                return new Int(args->GET_STRING(0)->COUNT(args->GET_CHAR(1)));

            case TYPE_STRING:
                return new Int(args->GET_STRING(0)->COUNT(args->GET_STRING(1)));
            }
        }
        }

        DISPLAY_EXCEPTION("executing the count function. Expected arguments type is 'List' with 'Any' and 'String' with 'Char'.", NoException, false);

        return &void_object;
    }

    // function to delete a value from 'String' or 'List' ....
    inline static Any *DELETE_(Argument_List *args)
    {
        switch (args->GET(0)->TYPE_NUMBER())
        {

        case TYPE_STRING:
            args->GET_STRING(0)->DELETE_(args->GET_INT(1)->GET());
            break;

        case TYPE_LIST:
            args->GET_LIST(0)->DELETE_(args->GET_INT(1));
            break;

        default:
            DISPLAY_EXCEPTION("executing the 'delete' function. Expected arguments are of type 'String' or 'List' and 'Int'.", NoException, false);
        }

        return &void_object;
    }

    // function to exit the program...
    inline static Any *EXIT(Argument_List *args)
    {
        std::exit(args->GET_INT(0)->GET());

        return &void_object;
    }

    // function to get the number of seconds taken by the interpreter to execute the code written by the user...
    inline static Any *GET_EXEC_TIME(Argument_List *args)
    {
        return new Double(double(clock()) / double(CLOCKS_PER_SEC));
    }

    // function to get the index of a particular value in 'String' and 'List'....
    inline static Any *INDEX(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            return new Int(val->GET_STRING()->INDEX(args->GET_CHAR(1)));

        case TYPE_LIST:
            return new Int(val->GET_LIST()->INDEX(args->GET(1)));

        default:
            DISPLAY_EXCEPTION("executing the 'index' function. Expected argument's type are 'String' or 'List' and 'Int'.", NoException);
        }

        return &void_object;
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

    inline static Any *INSERT(Argument_List *args)
    {
        Any* val = args->GET(0);

        switch(val->TYPE_NUMBER()){

            case TYPE_STRING : {
                long long int index = args->GET_INT(1)->GET();

                Any* value_to_insert = args->GET(2);

                val->GET_STRING()->INSERT(index, *value_to_insert);

            } break;
            //val->GET_STRING()->INSERT()

            case TYPE_LIST : {
                long long int index = args->GET_INT(1)->GET();

                Any* value_to_insert = args->GET(2);

                val->GET_LIST()->INSERT(index, value_to_insert);
            } break;

            default : DISPLAY_EXCEPTION("executing the 'insert' function. Expected arguments are 'List' or 'String' , 'Int' and 'Any'.", NoException, false);
        }
        return &void_object;
    }

    inline static Any *IS_ALPHABET(Argument_List *args)
    {
        return new Bool(SronChar::IS_ALPHABET(args->GET_CHAR(0)->GET()));
    }
    inline static Any *IS_CONSONANT(Argument_List *args)
    {
        return new Bool(SronChar::IS_CONSONANT(args->GET_CHAR(0)->GET()));
    }

    // function to check if the given character is number or not....
    inline static Any *IS_NUMBER(Argument_List *args)
    {
        return new Bool(SronChar::IS_NUMBER(args->GET_CHAR(0)->GET()));
    }

    // function to check if the given character is vowel or what
    inline static Any *IS_VOWEL(Argument_List *args)
    {

        return new Bool(SronChar::IS_VOWEL(args->GET_CHAR(0)->GET()));
    }

    // returns the length of the datatype
    inline static Any *LEN(Argument_List *args)
    {
        return new Int(args->GET(0)->LEN());
    }

    // returns the last element from 'String' or 'List' and deletes it...
    inline static Any *POP(Argument_List *args)
    {
        switch (args->GET(0)->TYPE_NUMBER())
        {

        case TYPE_STRING:
            return new Char(args->GET_STRING(0)->POP_BACK());

        case TYPE_LIST:
            return args->GET_LIST(0)->POP();
        }
        DISPLAY_EXCEPTION("executing the 'pop' function. Expected argument of type 'List' or 'String'.", NoException, false);

        return &void_object;
    }

    // function to print data on the command line...
    inline static Any *PRINT(Argument_List *args)
    {
        for (unsigned short int i = 0; i < args->LEN(); ++i)
        {
            args->GET(i)->PRINT();
        }

        return &void_object;
    }

    // function to print data on the command line with a newline in the end....
    inline static Any *PRINTLN(Argument_List *args)
    {
        PRINT(args);
        std::cout << '\n';
        return &void_object;
    }

    inline static Any *PUSH(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            val->GET_STRING()->APPENDS(args->GET(1));
            break;

        case TYPE_LIST:
            val->GET_LIST()->PUSH(args->GET(1));
            break;

        default:
            DISPLAY_EXCEPTION("executing the 'push' function. Only arguments of type 'String' and 'List' are allowed.", NoException, false);
        }
        return &void_object;
    }

    // function to generate a random numnber of type 'Int'...
    inline static Any *RANDINT(Argument_List *args)
    {
        return new Int(SronRandom::GENERATE_RANDOM_INT());
    }

    // function to generate a random number between a particular range...
    inline static Any *RANDRANGE(Argument_List *args)
    {

        Any *start = args->GET(0);
        Any *end = args->GET(1);

        if (start->TYPE_NUMBER() == TYPE_INT && end->TYPE_NUMBER() == TYPE_INT)
        {
            return new Int(SronRandom::GENERATE_RANDOM_INT_RANGE(start->GET_INT()->GET(), end->GET_INT()->GET()));
        }
        else if (start->TYPE_NUMBER() == TYPE_DOUBLE && end->TYPE_NUMBER() == TYPE_DOUBLE)
        {
            return new Double(SronRandom::GENERATE_RANDOM_DOUBLE_RANGE(start->GET_DOUBLE()->GET(), end->GET_DOUBLE()->GET()));
        }

        DISPLAY_EXCEPTION("executing the 'randrange' function. Both arguments must be of same type either of 'Int' or 'Double'.", NoException, false);

        return &void_object;
    }

    // function to generate a random value of type 'Double' ....
    inline static Any *RANDDOUBLE(Argument_List *args)
    {
        return new Double(SronRandom::GENERATE_RANDOM_DOUBLE());
    }

    // function to replace a value ...
    inline static Any *REPLACE(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            val->GET_STRING()->REPLACE(args->GET_CHAR(1), args->GET(2));
            break;

        case TYPE_LIST:
            val->GET_LIST()->REPLACE(args->GET(1), args->GET(2));
            break;

        default:
            DISPLAY_EXCEPTION("executing 'replace' function. Expected argument must be of type 'String' or 'List'.", NoException, false);
        }
        return &void_object;
    }

    inline static Any *REVERSE(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            args->GET_STRING(0)->REVERSE();
            break;

        case TYPE_LIST:
            args->GET_LIST(0)->REVERSE();
            break;

        default:
            DISPLAY_EXCEPTION("executing 'reverse' function. Expected arguments must be type of 'String' or 'List'.", NoException, false);
        }
        return &void_object;
    }

    inline static Any *RINDEX(Argument_List *args)
    {

        Any *val = args->GET(0);
        Any *index = args->GET(1);

        if (val->TYPE_NUMBER() == TYPE_STRING && index->TYPE_NUMBER() == TYPE_CHAR)
        {
            return new Int(val->GET_STRING()->RINDEX(index->GET_CHAR()));
        }
        else if (val->TYPE_NUMBER() == TYPE_STRING && index->TYPE_NUMBER() == TYPE_STRING)
        {
            return new Int(val->GET_STRING()->RINDEX(index->GET_STRING()));
        }
        else if (val->TYPE_NUMBER() == TYPE_LIST)
        {
            return new Int(val->GET_LIST()->RINDEX(args->GET(1)));
        }

        DISPLAY_EXCEPTION("executing 'rindex' function. Expected arguments are of types 'List' or 'String' and 'Char' or 'String'.", NoException, false);

        return &void_object;
    }

    inline static Any *SORT(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            val->GET_STRING()->SORT();
            break;

        case TYPE_LIST:
            val->GET_LIST()->SORT();
            break;

        default:
            DISPLAY_EXCEPTION("executing 'sort' function. Expected arguments are of types 'List' or 'String'.", NoException, false);
        }
        return &void_object;
    }

    // function to return the absolute value of 'Double' and 'Int' type....
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

    // function to return the cube root of 'Double' and 'Int' type....
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

    // function to return the ceil value of 'Double' and 'Int' type...
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

    // function to get the cos of 'Double' and 'Int' type values .....
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

    // function to get the floor of 'Double' and 'Int' type values .....
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

    // function to get the log of 'Double' and 'Int' type values .....
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

    // function to get the log2 of 'Double' and 'Int' type values .....
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

    // function to get the log10 of 'Double' and 'Int' type values .....
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

    // function to get the maximum of two values .....
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

    // function to get the minimum of two values .....
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

    // // function to get the square root of 'Double' and 'Int' type values .....
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

    // function to get the sin of 'Double' and 'Int' type values .....
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

    // function to get the tan of 'Double' and 'Int' type values .....
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

    // function to set the number of decimal digits to be printed on command line...
    // if the passed 'Int' value is less than 0 and greater than 10, then
    inline static Any *SET_PRECISION(Argument_List *args)
    {

        if (args->GET(0)->TYPE_NUMBER() == TYPE_INT)
        {
            long long int val = args->GET_INT(0)->GET();
            std::cout << std::setprecision((val < 0 || val > 10) ? 5 : val);
        }
        else
        {
            DISPLAY_EXCEPTION("executing 'setprecision' function. Only one value of type 'int' is allowed.", NoException);
        }
        return &void_object;
    }

    // function to get the size of the data in bytes...
    inline static Any *SIZE_OF(Argument_List *args)
    {
        return new Int(args->GET(0)->SIZE_OF());
    }

    // function to split a string .....
    inline static Any *SPLIT(Argument_List *args)
    {
        if (args->GET(0)->TYPE_NUMBER() != TYPE_STRING)
        {
            return args->GET_STRING(0)->SPLIT(args->GET_CHAR(1));
        }

        DISPLAY_EXCEPTION("executing 'split' function. Expected arguments is of type 'String'.", NoException, false);

        return &void_object;
    }

    // function to get a sub part of the List ....
    inline static Any *SUBLIST(Argument_List *args)
    {

        if (args->GET(0)->TYPE_NUMBER() == TYPE_LIST)
        {
            return args->GET_LIST(0)->SUBLIST(args->GET_INT(1)->GET(), args->GET_INT(2)->GET());
        }

        DISPLAY_EXCEPTION("executing the 'sublist' method. Expected argument of type 'List' but '" + args->GET(0)->TYPE() + "' was given.", NoException, false);

        return &void_object;
    }

    // function to get a sub part of the String ....
    inline static Any *SUBSTRING(Argument_List *args)
    {

        if (args->GET(0)->TYPE_NUMBER() == TYPE_STRING)
        {
            return new String(args->GET_STRING(0)->SUBSTRING(args->GET_INT(1)->GET(), args->GET_INT(2)->GET()));
        }

        DISPLAY_EXCEPTION("executing the 'substring' method. Expected argument of type 'String' and two values of type 'Int'.", NoException, false);

        return &void_object;
    }

    // function to get the 'List' of characters in 'String' values....
    inline static Any *TO_CHAR_LIST(Argument_List *args)
    {
        Any *val = args->GET(0);

        if (val->TYPE_NUMBER() == TYPE_STRING)
        {
            return val->GET_STRING()->TO_CHAR_LIST();
        }
        DISPLAY_EXCEPTION("executing the 'tocharlist' functions. Arguments with only 'String' type is allowed not '" + val->TYPE() + "' type.", NoException, false);

        return &void_object;
    }

    // function to convert a datatype to 'Bool' type...
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

    // function to convert a data to 'Double' type
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

    // function to convert the data to 'Int' type...
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

    // function to convert a Char or String type value to lowercase ....
    inline static Any *TO_LOWERCASE(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
        {

            String *str = new String("");
            for (auto &i : args->GET_STRING(0)->GET())
            {
                str->APPENDS(std::tolower(i));
            }
            return str;
        }

        case TYPE_CHAR:
            return new Char(std::tolower(val->GET_CHAR()->GET()));

        default:
            DISPLAY_EXCEPTION("converting value of type '" + val->TYPE() + "' to lowercase. Only type 'String' anc 'Char' can be converted to lowercase.", NoException);
        }

        return &void_object;
    }

    // function to convert a Char or String type value to uppercase ....
    inline static Any *TO_UPPERCASE(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
        {

            String *str = new String("");
            for (auto &i : args->GET_STRING(0)->GET())
            {
                str->APPENDS(std::toupper(i));
            }
            return str;
        }

        case TYPE_CHAR:
            return new Char(std::toupper(val->GET_CHAR()->GET()));

        default:
            DISPLAY_EXCEPTION("converting value of type '" + val->TYPE() + "' to uppercase. Only type 'String' anc 'Char' can be converted to uppercase.", NoException);
        }

        return &void_object;
    }

    // function to convert a datatype to 'String' type ....
    inline static Any *TO_STRING(Argument_List *args)
    {
        return new String(args->GET(0)->TO_STRING());
    }

    // function to trim a string...
    inline static Any *TRIM(Argument_List *args)
    {
        if (args->GET(0)->TYPE_NUMBER() == TYPE_STRING)
        {
            return new String(args->GET_STRING(0)->TRIM());
        }

        DISPLAY_EXCEPTION("executing the 'trim' method. Expected argument of type 'String'.", NoException, false);

        return &void_object;
    }

    // returns the type of the passed value...
    inline static Any *TYPE_OF(Argument_List *args)
    {
        return new String(args->GET(0)->TYPE());
    }

    inline static Any *UPDATE(Argument_List *args)
    {
        Any *val = args->GET(0);

        switch (val->TYPE_NUMBER())
        {

        case TYPE_STRING:
            args->GET_STRING(0)->UPDATE(args->GET_INT(1)->GET(), args->GET_CHAR(2));
            break;

        case TYPE_LIST:
            args->GET_LIST(0)->UPDATE(args->GET_INT(1)->GET(), args->GET(2));
            break;

        default:
            DISPLAY_EXCEPTION("executing 'update' function. Expected arguments are of type 'String' or 'List' and 'Int' and 'Char' or 'Any'.", NoException, false);
        }
        return &void_object;
    }

    // function to get the current version of sron...
    inline static Any *VERSION(Argument_List *args)
    {
        return new Double(Logs::version);
    }
}

#endif