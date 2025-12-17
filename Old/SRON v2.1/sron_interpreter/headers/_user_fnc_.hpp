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
#include "_function_.hpp"

namespace Sron
{
    
    inline static AnyBindPtr ASCII(ArgumentList &);

    inline static AnyBindPtr BEEP(ArgumentList &);
    inline static AnyBindPtr COPY(ArgumentList &);

    inline static AnyBindPtr EXIT(ArgumentList &);
    inline static AnyBindPtr GET_EXEC_TIME(ArgumentList &);

    // USER INPUT FUNCTIONS
    inline static AnyBindPtr INPUT_INT(ArgumentList &);
    inline static AnyBindPtr INPUT_DOUBLE(ArgumentList &);
    inline static AnyBindPtr INPUT_CHAR(ArgumentList &);
    inline static AnyBindPtr INPUT_STRING(ArgumentList &);

    // CHAR MANIPUALTION FUNCTIONS
    inline static AnyBindPtr IS_ALPHABET(ArgumentList &);
    inline static AnyBindPtr IS_CONSONANT(ArgumentList &);
    inline static AnyBindPtr IS_NUMBER(ArgumentList &);
    inline static AnyBindPtr IS_VOWEL(ArgumentList &);
    inline static AnyBindPtr IS_LOWERCASE(ArgumentList &);
    inline static AnyBindPtr IS_UPPERCASE(ArgumentList &);

    // type check functions ...
    inline static AnyBindPtr IS_VOID(ArgumentList &);
    inline static AnyBindPtr IS_INT(ArgumentList &);
    inline static AnyBindPtr IS_DOUBLE(ArgumentList &);
    inline static AnyBindPtr IS_CHAR(ArgumentList &);
    inline static AnyBindPtr IS_BOOL(ArgumentList &);
    inline static AnyBindPtr IS_COLLECTIVE(ArgumentList &);
    inline static AnyBindPtr IS_STRING(ArgumentList &);
    inline static AnyBindPtr IS_LIST(ArgumentList &);

    // COMMON LIST AND STRING MANIPULATION FUNCTIONS
    inline static AnyBindPtr AT(ArgumentList &);
    inline static AnyBindPtr CLEAR(ArgumentList &);
    inline static AnyBindPtr COUNT(ArgumentList &);
    inline static AnyBindPtr DELETE_(ArgumentList &);
    inline static AnyBindPtr INDEX(ArgumentList &);
    inline static AnyBindPtr INSERT(ArgumentList &);
    inline static AnyBindPtr LEN(ArgumentList &);
    inline static AnyBindPtr PUSH(ArgumentList &);
    inline static AnyBindPtr POP(ArgumentList &);
    inline static AnyBindPtr REPLACE(ArgumentList &);
    inline static AnyBindPtr REVERSE(ArgumentList &);
    inline static AnyBindPtr RINDEX(ArgumentList &);
    inline static AnyBindPtr SORT(ArgumentList &);
    inline static AnyBindPtr REVERSE_SORT(ArgumentList &);
    inline static AnyBindPtr SUBPART(ArgumentList &);
    inline static AnyBindPtr UPDATE(ArgumentList &);

    inline static AnyBindPtr PRINT(ArgumentList &);
    inline static AnyBindPtr PRINTLN(ArgumentList &);

    // generating random numbers...
    inline static AnyBindPtr RANDINT(ArgumentList &);
    inline static AnyBindPtr RANDRANGE(ArgumentList &);
    inline static AnyBindPtr RANDDOUBLE(ArgumentList &);

    inline static AnyBindPtr SIZE_OF(ArgumentList &);

    // type conversion function
    inline static AnyBindPtr TO_BOOL(ArgumentList &);
    inline static AnyBindPtr TO_DOUBLE(ArgumentList &);
    inline static AnyBindPtr TO_INT(ArgumentList &);
    inline static AnyBindPtr TO_STRING(ArgumentList &);

    // COMMON STRING AND CHAR FUNCTIONS...
    inline static AnyBindPtr TO_LOWERCASE(ArgumentList &);
    inline static AnyBindPtr TO_UPPERCASE(ArgumentList &);

    // mathematical functions
    inline static AnyBindPtr ABS(ArgumentList &);
    inline static AnyBindPtr CBRT(ArgumentList &);
    inline static AnyBindPtr CEIL(ArgumentList &);
    inline static AnyBindPtr COS(ArgumentList &);
    inline static AnyBindPtr FLOOR(ArgumentList &);
    inline static AnyBindPtr LOG(ArgumentList &);
    inline static AnyBindPtr LOG2(ArgumentList &);
    inline static AnyBindPtr LOG10(ArgumentList &);
    inline static AnyBindPtr MAX(ArgumentList &);
    inline static AnyBindPtr MIN(ArgumentList &);
    inline static AnyBindPtr SQRT(ArgumentList &);
    inline static AnyBindPtr SIN(ArgumentList &);
    inline static AnyBindPtr TAN(ArgumentList &);

    // string manipulation functions...
    inline static AnyBindPtr SPLIT(ArgumentList &);
    inline static AnyBindPtr TRIM(ArgumentList &);

    inline static AnyBindPtr SET_PRECISION(ArgumentList &);
    inline static AnyBindPtr SLEEP(ArgumentList& args);
    inline static AnyBindPtr SYS_CMD(ArgumentList &);
    inline static AnyBindPtr THROW_EXCEPTION(ArgumentList &);

    inline static AnyBindPtr TYPE_OF(ArgumentList &);

    // returns the version of the function ...
    inline static AnyBindPtr VERSION(ArgumentList &);

    using UserFunctionMap = std::unordered_map<SronTokenString, std::function<AnyPtr &(ArgumentList &)> , SronTokenString::HashFunction>;

    /*
     Future idea :

        // the SronTokenString in Sron::UserFunctionMap will be replaced with a struct which in its constructor hashes the const char*const values
        // to size_t values resulting in faster and immense speeed of std::unordered_map but it may arise slower loading of interpreter's load time
    */

    static const std::unordered_map<SronHasher, std::function<AnyBindPtr(ArgumentList &)> , SronHasher::HashFunction>Fmap{

        {"ascii" , Sron::ASCII},

        {"beep", Sron::BEEP},

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

        {"is_void", Sron::IS_VOID},
        {"is_int", Sron::IS_INT},
        {"is_double", Sron::IS_DOUBLE},
        {"is_char", Sron::IS_CHAR},
        {"is_bool", Sron::IS_BOOL},
        {"is_collective", Sron::IS_COLLECTIVE},
        {"is_string", Sron::IS_STRING},
        {"is_list", Sron::IS_LIST},

        // common list and string manipulation functions...
        {"at", Sron::AT},
        {"count", Sron::COUNT},
        {"delete", Sron::DELETE_},
        {"index", Sron::INDEX},
        {"insert", Sron::INSERT},
        {"len", Sron::LEN},
        {"push", Sron::PUSH},
        {"pop", Sron::POP},
        {"replace", Sron::REPLACE},
        {"reverse", Sron::REVERSE},
        {"rindex", Sron::RINDEX},
        {"sort", Sron::SORT},
        {"reverse_sort", Sron::REVERSE_SORT},
        {"subpart", Sron::SUBPART},
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
        {"split", Sron::SPLIT},
        {"trim", Sron::TRIM},

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

        {"sleep", Sron::SLEEP},
        {"syscmd", Sron::SYS_CMD},
        {"display_exception", Sron::THROW_EXCEPTION},

        {"typeof", Sron::TYPE_OF},

        {"version", Sron::VERSION}};

    /* this function takes the std::size_t as an argument then finds that in the
    Sron::UserFunctionMap. If the function is found then return that function
    otherwise returns nullptr.*/
    inline static auto& GET_SRON_FUNCTION(const size_t __fnc_id)
    {
        auto fnc = Fmap.find(__fnc_id);
        
        if (fnc != Fmap.end())
        {
            return fnc->second;
        }
        throw ThrowException("searching for an in-built function", FunctionNotFoundException);
    }



    inline static AnyBindPtr ASCII(ArgumentList &__args)
    {
        auto& val = __args.GET(0)->ptr_;

        switch (val->TYPE_NUMBER())
        {

        case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Char(val->GET_CHAR_ABS()));

        case TYPE_CHAR: return GarbageCollector::REGISTER_MEMORY(new Int(val->GET_INT_ABS()));
        }

        THROW_EXCEPTION_FOR_INVALID_ARGUMENTS("ascii", "Int", "Char");

        return Void::void_object;
    }

    inline static AnyBindPtr AT(ArgumentList &__args)
    {

        ColPtr ptr = __args.GET_COLLECTIVE(0);

        Int &index = *__args.GET_INT(1);

        return ptr->AT(index);
        
    }

    inline static AnyBindPtr BEEP(ArgumentList &__args)
    {

        if (__args.GET(0)->ptr_->TYPE_NUMBER() == TYPE_INT && __args.GET(1)->ptr_->TYPE_NUMBER() == TYPE_INT)
        {
            Beep(__args.GET(0)->ptr_->GET_INT_ABS(), __args.GET(1)->ptr_->GET_INT_ABS());
        }
        else
        {
            throw ThrowException("executing the 'beep' function. Both arguments should be of type 'Int'", NoException);
        }
        return Void::void_object;
    }

    inline static AnyBindPtr CLEAR(ArgumentList &__args)
    {
        ColPtr ptr = __args.GET_COLLECTIVE(0);

        ptr->CLEAR();

        return Void::void_object;
    }

    // function to create a copy of the values passed ...
    inline static AnyBindPtr COPY(ArgumentList &__args)
    {
        auto& value = __args.GET(0)->ptr_;

        if(value->TYPE_NUMBER() == TYPE_VOID)
        {
            return Void::void_object;
        }
        else if(value->TYPE_NUMBER() == TYPE_BOOL)
        {
            return (value->GET_BOOL_ABS())? Bool::__SronTrue : Bool::__SronFalse;
        }

        return GarbageCollector::REGISTER_MEMORY(__args.GET(0)->ptr_->COPY());
    }

    // function to count occurrences of a particular value in 'List' or 'String'
    inline static AnyBindPtr COUNT(ArgumentList &__args)
    {
        ColPtr ptr = __args.GET_COLLECTIVE(0);

        return GarbageCollector::REGISTER_MEMORY(new Int(ptr->COUNT(**__args.GET(1))));
    }

    // function to delete a value from 'String' or 'List' ....
    inline static AnyBindPtr DELETE_(ArgumentList &__args)
    {
        ColPtr ptr = __args.GET_COLLECTIVE(0);

        Int &index = *__args.GET_INT(1);

        ptr->DELETE_(index);

        return Void::void_object;
    }

    // function to exit the program...
    inline static AnyBindPtr EXIT(ArgumentList &__args)
    {

        auto code = **__args.GET_INT(0);

        GarbageCollector::TOTAL_DESTRUCTION();

        std::exit(code);

        return Void::void_object;
    }

    // function to get the number of seconds taken by the interpreter to execute the code written by the user...
    inline static AnyBindPtr GET_EXEC_TIME(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Double(double(clock()) / double(CLOCKS_PER_SEC)));
    }

    // function to get the index of a particular value in 'String' and 'List'....
    inline static AnyBindPtr INDEX(ArgumentList &__args)
    {
        ColPtr ptr = __args.GET_COLLECTIVE(0);

        Any &val = **__args.GET(1);

        return GarbageCollector::REGISTER_MEMORY(new Int(ptr->INDEX(val)));
    }

    inline static AnyBindPtr INPUT_INT(ArgumentList &__args)
    {

        if (__args.LEN() > 0)
        {
            __args.GET(0)->ptr_->PRINT();
        }

        return GarbageCollector::REGISTER_MEMORY(SronInput::INPUT_INT());
    }

    inline static AnyBindPtr INPUT_DOUBLE(ArgumentList &__args)
    {
        if (__args.LEN() > 0)
        {
            __args.GET(0)->ptr_->PRINT();
        }

        return GarbageCollector::REGISTER_MEMORY(SronInput::INPUT_DOUBLE());
    }

    inline static AnyBindPtr INPUT_CHAR(ArgumentList &__args)
    {

        if (__args.LEN() > 0)
        {
            __args.GET(0)->ptr_->PRINT();
        }

        return GarbageCollector::REGISTER_MEMORY(SronInput::INPUT_CHAR());
    }

    inline static AnyBindPtr INPUT_STRING(ArgumentList &__args)
    {

        if (__args.LEN() > 0)
        {
            __args.GET(0)->ptr_->PRINT();
        }

        return GarbageCollector::REGISTER_MEMORY(SronInput::INPUT_STRING());
    }

    inline static AnyBindPtr INSERT(ArgumentList &__args)
    {
        ColPtr val = __args.GET_COLLECTIVE(0);

        Int &index = *__args.GET_INT(1);

        val->INSERT(index, __args.GET(2)->ptr_);

        return Void::void_object;
    }

    inline static AnyBindPtr IS_ALPHABET(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Bool(SronChar::IS_ALPHABET(__args.GET(0)->ptr_->GET_CHAR_ABS())));
    }
    inline static AnyBindPtr IS_CONSONANT(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Bool(SronChar::IS_CONSONANT(__args.GET(0)->ptr_->GET_CHAR_ABS())));
    }

    // function to check if the given character is number or not....
    inline static AnyBindPtr IS_NUMBER(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Bool(SronChar::IS_NUMBER(__args.GET(0)->ptr_->GET_CHAR_ABS())));
    }

    // function to check if the given character is vowel or what
    inline static AnyBindPtr IS_VOWEL(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Bool(SronChar::IS_VOWEL(__args.GET(0)->ptr_->GET_CHAR_ABS())));
    }

    inline static AnyBindPtr IS_LOWERCASE(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Bool(SronChar::IS_LOWERCASE(__args.GET(0)->ptr_->GET_CHAR_ABS())));
    }
    inline static AnyBindPtr IS_UPPERCASE(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Bool(SronChar::IS_UPPERCASE(__args.GET(0)->ptr_->GET_CHAR_ABS())));
    }


    // type checking functions ...
    inline static AnyBindPtr IS_VOID(ArgumentList&__args)
    {
        return (__args.GET(0)->ptr_->TYPE_NUMBER() == TYPE_VOID) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_INT(ArgumentList&__args)
    {
        return (__args.GET(0)->ptr_->TYPE_NUMBER() == TYPE_INT) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_DOUBLE(ArgumentList&__args)
    {
        return (__args.GET(0)->ptr_->TYPE_NUMBER() == TYPE_DOUBLE) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_CHAR(ArgumentList&__args)
    {
        return (__args.GET(0)->ptr_->TYPE_NUMBER() == TYPE_CHAR) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_BOOL(ArgumentList&__args)
    {
        return (__args.GET(0)->ptr_->TYPE_NUMBER() == TYPE_BOOL) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    inline static AnyBindPtr IS_COLLECTIVE(ArgumentList&__args)
    {
        return (__args.GET(0)->ptr_->IS_COLLECTIVE())? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_STRING(ArgumentList&__args)
    {
        return (__args.GET(0)->ptr_->TYPE_NUMBER() == TYPE_STRING) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    inline static AnyBindPtr IS_LIST(ArgumentList&__args)
    {
        return (__args.GET(0)->ptr_->TYPE_NUMBER() == TYPE_LIST) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    // returns the length of the datatype
    inline static AnyBindPtr LEN(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Int(__args.GET_COLLECTIVE(0)->LEN()));
    }

    // returns the last element from 'String' or 'List' and deletes it...
    inline static AnyBindPtr POP(ArgumentList &__args)
    {
        return __args.GET_COLLECTIVE(0)->POP();
    }

    // function to print data on the command line...
    inline static AnyBindPtr PRINT(ArgumentList &__args)
    {
        for (unsigned short int i = 0; i < __args.LEN(); ++i)
        {
            __args.GET(i)->ptr_->PRINT();
        }

        return Void::void_object;
    }

    // function to print data on the command line with a newline in the end....
    inline static AnyBindPtr PRINTLN(ArgumentList &__args)
    {
        PRINT(__args);
        std::cout << '\n';
        return Void::void_object;
    }

    inline static AnyBindPtr PUSH(ArgumentList &__args)
    {
        ColPtr val = __args.GET_COLLECTIVE(0);

        val->PUSH(__args.GET(1)->ptr_);

        return Void::void_object;
    }

    // function to generate a random numnber of type 'Int'...
    inline static AnyBindPtr RANDINT(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Int(SronRandom::GENERATE_RANDOM_INT()));
    }

    // function to generate a random number between a particular range...
    inline static AnyBindPtr RANDRANGE(ArgumentList &__args)
    {

        Any &start = **__args.GET(0);
        Any &end = **__args.GET(1);

        if (start.TYPE_NUMBER() == TYPE_INT)
        {
            return GarbageCollector::REGISTER_MEMORY(new Int(SronRandom::GENERATE_RANDOM_INT_RANGE(start.GET_INT_ABS(), end.GET_INT_ABS())));
        }
        else if (start.TYPE_NUMBER() == TYPE_DOUBLE)
        {
            return GarbageCollector::REGISTER_MEMORY(new Double(SronRandom::GENERATE_RANDOM_DOUBLE_RANGE(start.GET_DOUBLE_ABS(), end.GET_DOUBLE_ABS())));
        }

        THROW_EXCEPTION_FOR_INVALID_ARGUMENTS("randrange", "Int", "Double");

        return Void::void_object;
    }

    // function to generate a random value of type 'Double' ....
    inline static AnyBindPtr RANDDOUBLE(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Double(SronRandom::GENERATE_RANDOM_DOUBLE()));
    }

    // function to replace a value ...
    inline static AnyBindPtr REPLACE(ArgumentList &__args)
    {
        ColPtr val = __args.GET_COLLECTIVE(0);

        val->REPLACE(**__args.GET(1), **__args.GET(2));

        return Void::void_object;
    }

    inline static AnyBindPtr REVERSE(ArgumentList &__args)
    {
        ColPtr ptr = __args.GET_COLLECTIVE(0);

        ptr->REVERSE();

        return Void::void_object;
    }

    inline static AnyBindPtr RINDEX(ArgumentList &__args)
    {
        ColPtr val = __args.GET_COLLECTIVE(0);

        return GarbageCollector::REGISTER_MEMORY(new Int(val->RINDEX(**__args.GET(1))));
    }

    inline static AnyBindPtr SORT(ArgumentList &__args)
    {
        ColPtr val = __args.GET_COLLECTIVE(0);

        val->SORT();

        return Void::void_object;
    }

    inline static AnyBindPtr REVERSE_SORT(ArgumentList &__args)
    {
        ColPtr val = __args.GET_COLLECTIVE(0);

        val->REVERSE_SORT();

        return Void::void_object;
    }

    inline static AnyBindPtr SUBPART(ArgumentList &__args){

        ColPtr val = __args.GET_COLLECTIVE(0);

        return val->SUBPART(*__args.GET_INT(1) , *__args.GET_INT(2));

    }

    // function to return the absolute value of 'Double' and 'Int' type....
    inline static AnyBindPtr ABS(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);

        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Int(SronMath::ABS(val.GET_DOUBLE_ABS() )));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Int(SronMath::ABS(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("abs");

        return Void::void_object;
    }

    // function to return the cube root of 'Double' and 'Int' type....
    inline static AnyBindPtr CBRT(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);

        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::CBRT(val.GET_DOUBLE_ABS())));

        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::CBRT(val.GET_INT_ABS())));
        }

        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("cbrt");

        return Void::void_object;
    }

    // function to return the ceil value of 'Double' and 'Int' type...
    inline static AnyBindPtr CEIL(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);
        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Int(SronMath::CEIL(val.GET_DOUBLE_ABS())));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Int(SronMath::CEIL(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("ceil");

        return Void::void_object;
    }

    // function to get the cos of 'Double' and 'Int' type values .....
    inline static AnyBindPtr COS(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);

        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::COS(val.GET_DOUBLE_ABS())));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::COS(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("cos");

        return Void::void_object;
    }

    // function to get the floor of 'Double' and 'Int' type values .....
    inline static AnyBindPtr FLOOR(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);

        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Int(SronMath::FLOOR(val.GET_DOUBLE_ABS())));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Int(SronMath::FLOOR(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("floor");

        return Void::void_object;
    }

    // function to get the log of 'Double' and 'Int' type values .....
    inline static AnyBindPtr LOG(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);
        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG(val.GET_DOUBLE_ABS())));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("log");

        return Void::void_object;
    }

    // function to get the log2 of 'Double' and 'Int' type values .....
    inline static AnyBindPtr LOG2(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);

        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG2(val.GET_DOUBLE_ABS())));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG2(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("log2");

        return Void::void_object;
    }

    // function to get the log10 of 'Double' and 'Int' type values .....
    inline static AnyBindPtr LOG10(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);
        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG10(val.GET_DOUBLE_ABS())));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG10(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("log10");

        return Void::void_object;
    }

    // function to get the maximum of two values .....
    inline static AnyBindPtr MAX(ArgumentList &__args)
    {
        if(__args.LEN() == 0){
            throw ThrowException("executing 'max' function. Too few arguments");
        }

        unsigned short int max = 0;

        unsigned short int len = __args.LEN();

        for (unsigned short int i = 1; i < len; ++i)
        {

            max = (__args.GET(i))->ptr_->__MORE_THAN__(**__args.GET(max)) ? i : max;
        }
        return __args.GET(max);
    }

    // function to get the minimum of two values .....
    inline static AnyBindPtr MIN(ArgumentList &__args)
    {

        if(__args.LEN() == 0){
            throw ThrowException("executing 'min' function. Too few arguments");
        }

        unsigned short int min = 0;

        unsigned short int len = __args.LEN();

        for (unsigned short int i = 1; i < len; ++i)
        {   
            min = ((*__args.GET(i))->__LESS_THAN__(**__args.GET(min))) ? i : min;
            
        }
        return __args.GET(min);
    }

    // // function to get the square root of 'Double' and 'Int' type values .....
    inline static AnyBindPtr SQRT(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);
        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::SQRT(val.GET_DOUBLE_ABS())));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::SQRT(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("sqrt");

        return Void::void_object;
    }

    // function to get the sin of 'Double' and 'Int' type values .....
    inline static AnyBindPtr SIN(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);
        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::SIN(val.GET_DOUBLE_ABS())));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::SIN(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("sin");

        return Void::void_object;
    }

    // function to get the tan of 'Double' and 'Int' type values .....
    inline static AnyBindPtr TAN(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);
        switch (val.TYPE_NUMBER())
        {
        case TYPE_DOUBLE:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::TAN(val.GET_DOUBLE_ABS())));
        case TYPE_INT:
            return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::TAN(val.GET_INT_ABS())));
        }
        THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("tan");

        return Void::void_object;
    }

    // function to set the number of decimal digits to be printed on command line...
    // if the passed 'Int' value is less than 0 and greater than 10, then
    inline static AnyBindPtr SET_PRECISION(ArgumentList &__args)
    {

        std::cout << std::fixed << std::setprecision(__args.GET(0)->ptr_->GET_INT_ABS());

        return Void::void_object;
    }

    // function to get the size of the data in bytes...
    inline static AnyBindPtr SIZE_OF(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Int(__args.GET(0)->ptr_->SIZE_OF()));
    }

    // function to split a string .....
    inline static AnyBindPtr SPLIT(ArgumentList &__args)
    {
        String &str = *__args.GET_STRING(0);

        return GarbageCollector::REGISTER_MEMORY(str.SPLIT(*__args.GET_CHAR(1)));
    }

    inline static AnyBindPtr SLEEP(ArgumentList &__args){

        Sleep(__args.GET(0)->ptr_->GET_INT_ABS());

        return Void::void_object;
    }

    inline static AnyBindPtr SYS_CMD(ArgumentList &__args)
    {
        std::string &cmd = **__args.GET_STRING(0);

        if (std::system(cmd.c_str()) != 0)
        {
            throw ThrowException("executing the 'syscmd' function. This command ''" + cmd + "'' is invalid", NoException);
        }

        return Void::void_object;
    }

    inline static AnyBindPtr THROW_EXCEPTION(ArgumentList &__args)
    {
        throw ExceptionThrowByUser(__args.GET_STRING(0));
    }

    // function to convert a datatype to 'Bool' type...
    inline static AnyBindPtr TO_BOOL(ArgumentList &__args)
    {

        auto& val = *__args.GET(0);

        if(val->TYPE_NUMBER() == TYPE_STRING)
        {
            return (Converter::TO_BOOL(**val->GET_STRING())) ? Bool::__SronTrue : Bool::__SronFalse;
        }
        
        return (__args.GET(0)->ptr_->GET_BOOL_ABS())? Bool::__SronTrue : Bool::__SronFalse;

    }

    // function to convert a data to 'Double' type
    inline static AnyBindPtr TO_DOUBLE(ArgumentList &__args)
    {

        auto& val = *__args.GET(0);

        if(val->TYPE_NUMBER() == TYPE_STRING)
        {
            return GarbageCollector::REGISTER_MEMORY(new Double(**val->GET_STRING()));
        }

        return GarbageCollector::REGISTER_MEMORY(new Double(val->GET_DOUBLE_ABS()));
    }

    // function to convert the data to 'Int' type...
    inline static AnyBindPtr TO_INT(ArgumentList &__args)
    {

        auto& val = *__args.GET(0);

        if(val->TYPE_NUMBER() == TYPE_STRING)
        {
            return GarbageCollector::REGISTER_MEMORY(new Int(**val->GET_STRING()));
        }
        
        return GarbageCollector::REGISTER_MEMORY(new Int(val->GET_INT_ABS()));

    }

    // function to convert a Char or String type value to lowercase ....
    inline static AnyBindPtr TO_LOWERCASE(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);

        switch (val.TYPE_NUMBER())
        {

        case TYPE_STRING:
            return GarbageCollector::REGISTER_MEMORY(val.GET_STRING()->TO_LOWERCASE());

        case TYPE_CHAR:
            return GarbageCollector::REGISTER_MEMORY(new Char(SronChar::TO_LOWERCASE(val.GET_CHAR_ABS())));
        }
        THROW_EXCEPTION_FOR_INVALID_ARGUMENTS("tolower", "String", "Char");

        return Void::void_object;
    }

    // function to convert a Char or String type value to uppercase ....
    inline static AnyBindPtr TO_UPPERCASE(ArgumentList &__args)
    {
        Any &val = **__args.GET(0);

        switch (val.TYPE_NUMBER())
        {

        case TYPE_STRING:
            return GarbageCollector::REGISTER_MEMORY(val.GET_STRING()->TO_UPPERCASE());

        case TYPE_CHAR:
            return GarbageCollector::REGISTER_MEMORY(new Char(SronChar::TO_UPPERCASE(val.GET_CHAR_ABS())));
        }
        THROW_EXCEPTION_FOR_INVALID_ARGUMENTS("toupper", "String", "Char");

        return Void::void_object;
    }

    // function to convert a datatype to 'String' type ....
    inline static AnyBindPtr TO_STRING(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new String(std::move(__args.GET(0)->ptr_->TO_STRING())));
    }

    // function to trim a string...
    inline static AnyBindPtr TRIM(ArgumentList &__args)
    {
        if(__args.GET(0)->ptr_->TYPE_NUMBER() == TYPE_STRING){
            __args.GET_STRING(0)->TRIM();

            return Void::void_object;
        }
        
        THROW_EXCEPTION_FOR_INVALID_ARGUMENTS("trim", "String");

        return Void::void_object;
    }

    // returns the type of the passed value...
    inline static AnyBindPtr TYPE_OF(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new String(__args.GET(0)->ptr_->TYPE()));
    }

    inline static AnyBindPtr UPDATE(ArgumentList &__args)
    {

        ColPtr val = __args.GET(0)->ptr_->GET_COLLECTIVE();

        Int &index = *__args.GET_INT(1);

        Any &x = **__args.GET(2);

        val->UPDATE(index, x);

        return Void::void_object;
    }

    // function to get the current version of sron...
    inline static AnyBindPtr VERSION(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Double(Logs::__SronVersion__ ));
    }
}

#endif