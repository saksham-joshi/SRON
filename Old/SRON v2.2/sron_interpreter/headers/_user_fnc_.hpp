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

    [[noreturn]] inline static AnyBindPtr EXIT(ArgumentList &);
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

    [[gnu::hot]] inline static AnyBindPtr PRINT(ArgumentList &);
    [[gnu::hot]] inline static AnyBindPtr PRINTLN(ArgumentList &);

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
    inline static AnyBindPtr SRON_CMD( ArgumentList&);
    inline static AnyBindPtr SYS_CMD(ArgumentList &);
    inline static AnyBindPtr THROW_EXCEPTION(ArgumentList &);

    inline static AnyBindPtr TYPE_OF(ArgumentList &);

    // returns the version of the function ...
    inline static AnyBindPtr VERSION(ArgumentList &);

    typedef AnyBindPtr (*SronInBuiltFnc) (ArgumentList&);

    struct SronInBuiltFncBinder
    {
        const char* _fnc_name;
        SronInBuiltFnc _fnc;
    };

    constexpr static struct SronInBuiltFncBinder Fmap[] = {

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
        {"sron_cmd", Sron::SRON_CMD},
        {"syscmd", Sron::SYS_CMD},
        {"throw_exception", Sron::THROW_EXCEPTION},

        {"typeof", Sron::TYPE_OF},

        {"version", Sron::VERSION}
    };

    inline static SronInBuiltFnc GET_SRON_FUNCTION( const SronInBuiltFncIndex_t __fnc_index )
    {
        if ( __fnc_index < sizeof(Fmap)/sizeof(Fmap[0])) [[likely]] return Fmap[__fnc_index]._fnc;

        throw ThrowException("searching for an in-built function", SronException::FunctionNotFoundException);
    }


    inline static AnyBindPtr ASCII(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch ( value->type() )
        {
            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Char( **intCast(value->ptr())) , SronTypeNum::TYPE_CHAR);

            case TYPE_CHAR: return GarbageCollector::REGISTER_MEMORY(new Int( **charCast(value->ptr())) , SronTypeNum::TYPE_INT);

            default : THROW_EXCEPTION_FOR_INVALID_ARGUMENTS("ascii", "Int", "Char");
        }        

        return Void::void_object;
    }

    inline static AnyBindPtr AT(ArgumentList &__args)
    {

        ColPtr ptr = __args.getCollective(0);

        Int &index = *__args.getInt(1);

        return ptr->AT(index);
        
    }

    inline static AnyBindPtr BEEP(ArgumentList &__args)
    {
        auto frequency = __args.get(0);
        auto duration = __args.get(1);

        if ( frequency->type() == TYPE_INT && duration->type() == TYPE_INT)
        {
            Beep( **intCast(frequency->ptr()), **intCast(duration->ptr()));
        }
        else
        {
            throw ThrowException("executing the 'beep' function. Both arguments should be of type 'Int'", SronException::DefaultException);
        }
        return Void::void_object;
    }

    inline static AnyBindPtr CLEAR(ArgumentList &__args)
    {
        ColPtr ptr = __args.getCollective(0);

        ptr->CLEAR();

        return Void::void_object;
    }

    // function to create a copy of the values passed ...
    inline static AnyBindPtr COPY(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if(value->type() == TYPE_VOID) return Void::void_object;
    
        else if(value->type() == TYPE_BOOL) return ( **boolCast(value->ptr()) )? Bool::__SronTrue : Bool::__SronFalse;
        
        return GarbageCollector::REGISTER_MEMORY( value->ptr()->COPY(), value->type() );
    }

    // function to count occurrences of a particular value in 'List' or 'String'
    inline static AnyBindPtr COUNT(ArgumentList &__args)
    {
        ColPtr ptr = __args.getCollective(0);

        return GarbageCollector::REGISTER_MEMORY(new Int(ptr->COUNT(**__args.get(1))) , SronTypeNum::TYPE_INT);
    }

    // function to delete a value from 'String' or 'List' ....
    inline static AnyBindPtr DELETE_(ArgumentList &__args)
    {
        ColPtr ptr = __args.getCollective(0);

        Int &index = *__args.getInt(1);

        ptr->DELETE_(index);

        return Void::void_object;
    }

    // function to exit the program...
    inline static AnyBindPtr EXIT(ArgumentList &__args)
    {
        auto code = **__args.getInt(0);

        GarbageCollector::TOTAL_DESTRUCTION();

        std::exit(code);
    }

    // function to get the number of seconds taken by the interpreter to execute the code written by the user...
    inline static AnyBindPtr GET_EXEC_TIME(ArgumentList &)
    {
        return GarbageCollector::REGISTER_MEMORY(new Double(double(clock()) / double(CLOCKS_PER_SEC)) , SronTypeNum::TYPE_DOUBLE);
    }
    

    // function to get the index of a particular value in 'String' and 'List'....
    inline static AnyBindPtr INDEX(ArgumentList &__args)
    {
        ColPtr ptr = __args.getCollective(0);

        Any &val = **__args.get(1);

        return GarbageCollector::REGISTER_MEMORY(new Int(ptr->INDEX(val)), SronTypeNum::TYPE_INT);
    }

    inline static AnyBindPtr INPUT_INT(ArgumentList &__args)
    {

        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->PRINT();
        }

        return GarbageCollector::REGISTER_MEMORY(SronInput::INPUT_INT(), SronTypeNum::TYPE_INT);
    }

    inline static AnyBindPtr INPUT_DOUBLE(ArgumentList &__args)
    {
        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->PRINT();
        }

        return GarbageCollector::REGISTER_MEMORY(SronInput::INPUT_DOUBLE() , SronTypeNum::TYPE_DOUBLE);
    }

    inline static AnyBindPtr INPUT_CHAR(ArgumentList &__args)
    {

        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->PRINT();
        }

        return GarbageCollector::REGISTER_MEMORY(SronInput::INPUT_CHAR() , SronTypeNum::TYPE_CHAR);
    }

    inline static AnyBindPtr INPUT_STRING(ArgumentList &__args)
    {

        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->PRINT();
        }

        return GarbageCollector::REGISTER_MEMORY(SronInput::INPUT_STRING() , SronTypeNum::TYPE_STRING);
    }

    inline static AnyBindPtr INSERT(ArgumentList &__args)
    {
        ColPtr val = __args.getCollective(0);

        Int &index = *__args.getInt(1);

        auto ptr = __args.get(2)->ptr();

        val->INSERT(index, ptr);

        return Void::void_object;
    }

    inline static AnyBindPtr IS_ALPHABET(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::IS_ALPHABET( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isalphabet()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->TYPE()) + "'");
    }
    inline static AnyBindPtr IS_CONSONANT(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::IS_CONSONANT( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isconsonant()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->TYPE()) + "'");
    }

    // function to check if the given character is number or not....
    inline static AnyBindPtr IS_NUMBER(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::IS_NUMBER( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isdigit()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->TYPE()) + "'");
    }

    // function to check if the given character is vowel or what
    inline static AnyBindPtr IS_VOWEL(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::IS_VOWEL( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isvowel()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->TYPE()) + "'");
    }

    inline static AnyBindPtr IS_LOWERCASE(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::IS_LOWERCASE( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'islower()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->TYPE()) + "'");
    }

    inline static AnyBindPtr IS_UPPERCASE(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::IS_UPPERCASE( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isupper()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->TYPE()) + "'");
    }


    // type checking functions ...
    inline static AnyBindPtr IS_VOID(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_VOID) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_INT(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_INT) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_DOUBLE(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_DOUBLE) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_CHAR(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_CHAR) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_BOOL(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_BOOL) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    inline static AnyBindPtr IS_COLLECTIVE(ArgumentList&__args)
    {
        return (__args.get(0)->ptr()->IS_COLLECTIVE() )? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr IS_STRING(ArgumentList&__args)
    {
        return (__args.get(0)->type()== SronTypeNum::TYPE_STRING) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    inline static AnyBindPtr IS_LIST(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_LIST) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    // returns the length of the datatype
    inline static AnyBindPtr LEN(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Int(__args.getCollective(0)->LEN()), SronTypeNum::TYPE_INT);
    }

    // returns the last element from 'String' or 'List' and deletes it...
    inline static AnyBindPtr POP(ArgumentList &__args)
    {
        return __args.getCollective(0)->POP();
    }

    // function to print data on the command line...
    inline static AnyBindPtr PRINT(ArgumentList &__args)
    {
        SronOBuffer buffer;

        for (ArgListLen_t i = 0; i < __args.len(); ++i)
        {
            auto value = __args.get(i);

            switch( value->type() )
            {
                case SronTypeNum::TYPE_VOID:    voidCast( value->ptr() )->FILL_OBUFFER( buffer ); break;

                case SronTypeNum::TYPE_INT:     intCast( value->ptr() )->FILL_OBUFFER ( buffer ); break;

                case SronTypeNum::TYPE_DOUBLE:  doubleCast( value->ptr() )->FILL_OBUFFER( buffer ); break;

                case SronTypeNum::TYPE_CHAR :   charCast( value->ptr() )->FILL_OBUFFER( buffer ); break;

                case SronTypeNum::TYPE_BOOL :   boolCast( value->ptr() )->FILL_OBUFFER( buffer ); break;

                case SronTypeNum::TYPE_STRING : stringCast( value->ptr() )->FILL_OBUFFER( buffer ); break;

                case SronTypeNum::TYPE_LIST :   listCast( value->ptr() )->FILL_OBUFFER( buffer ); break;

                default: value->ptr()->FILL_OBUFFER( buffer ); 
            }
        }

        buffer.flush();

        return Void::void_object;
    }

    // function to print data on the command line with a newline in the end....
    inline static AnyBindPtr PRINTLN(ArgumentList &__args)
    {
        PRINT(__args);
        puts("");
        return Void::void_object;
    }

    inline static AnyBindPtr PUSH(ArgumentList &__args)
    {
        ColPtr val = __args.getCollective(0);

        val->PUSH(__args.get(1)->ptr());

        return Void::void_object;
    }

    // function to generate a random numnber of type 'Int'...
    inline static AnyBindPtr RANDINT(ArgumentList &)
    {
        return GarbageCollector::REGISTER_MEMORY(new Int(SronRandom::GENERATE_RANDOM_INT()) , SronTypeNum::TYPE_INT);
    }

    // function to generate a random number between a particular range...
    inline static AnyBindPtr RANDRANGE(ArgumentList &__args)
    {
        auto start = __args.get(0);
        auto end = __args.get(1);


        if (start->type() == TYPE_INT && end->type() == TYPE_INT)
        {
            return GarbageCollector::REGISTER_MEMORY(new Int(SronRandom::GENERATE_RANDOM_INT_RANGE( **intCast( start->ptr() ) , **intCast( end->ptr() ))) , SronTypeNum::TYPE_INT);
        }
        else if (start->type() == TYPE_DOUBLE && end->type() == TYPE_DOUBLE )
        {
            return GarbageCollector::REGISTER_MEMORY(new Double(SronRandom::GENERATE_RANDOM_DOUBLE_RANGE( **doubleCast( start->ptr() ) , **doubleCast( end->ptr() ))) , SronTypeNum::TYPE_DOUBLE);
        }

        throw ThrowException("executing 'randrange'. Expected arguments are either of type 'Int' or 'Double'. Both arguments should be of same type if one is Int then another should be Int too", SronException::ArgumentException);
    }


    // function to generate a random value of type 'Double' ....
    inline static AnyBindPtr RANDDOUBLE(ArgumentList &)
    {
        return GarbageCollector::REGISTER_MEMORY(new Double(SronRandom::GENERATE_RANDOM_DOUBLE()) , SronTypeNum::TYPE_DOUBLE);
    }

    // function to replace a value ...
    inline static AnyBindPtr REPLACE(ArgumentList &__args)
    {
        ColPtr val = __args.getCollective(0);

        val->REPLACE(**__args.get(1), **__args.get(2));

        return Void::void_object;
    }

    inline static AnyBindPtr REVERSE(ArgumentList &__args)
    {
        __args.getCollective(0)->REVERSE();

        return Void::void_object;
    }

    inline static AnyBindPtr RINDEX(ArgumentList &__args)
    {
        ColPtr val = __args.getCollective(0);

        return GarbageCollector::REGISTER_MEMORY(new Int(val->RINDEX(**__args.get(1))) , SronTypeNum::TYPE_INT);
    }

    inline static AnyBindPtr SORT(ArgumentList &__args)
    {
        __args.getCollective(0)->SORT();

        return Void::void_object;
    }

    inline static AnyBindPtr REVERSE_SORT(ArgumentList &__args)
    {
        __args.getCollective(0)->REVERSE_SORT();

        return Void::void_object;
    }

    inline static AnyBindPtr SUBPART(ArgumentList &__args){

        ColPtr val = __args.getCollective(0);

        return val->SUBPART(*__args.getInt(1) , *__args.getInt(2));

    }

    // function to return the absolute value of 'Double' and 'Int' type....
    inline static AnyBindPtr ABS(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::ABS( **doubleCast( value->ptr() ))) , SronTypeNum::TYPE_DOUBLE);
            
            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::ABS( **intCast( value->ptr() ))) , SronTypeNum::TYPE_DOUBLE);
            
            default: THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("abs");
        }
        

        return Void::void_object;
    }

    // function to return the cube root of 'Double' and 'Int' type....
    inline static AnyBindPtr CBRT(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE:
                return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::CBRT( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case TYPE_INT:
                return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::CBRT( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("cbrt");
        }
        
        return Void::void_object;
    }

    // function to return the ceil value of 'Double' and 'Int' type...
    inline static AnyBindPtr CEIL(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::CEIL( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::CEIL( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("ceil");
        }

        return Void::void_object;
    }

    // function to get the cos of 'Double' and 'Int' type values .....
    inline static AnyBindPtr COS(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::COS( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::COS( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("cos");
        }

        return Void::void_object;
    }

    // function to get the floor of 'Double' and 'Int' type values .....
    inline static AnyBindPtr FLOOR(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::FLOOR( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::FLOOR( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("floor");
        }
    
        return Void::void_object;
    }

    // function to get the log of 'Double' and 'Int' type values .....
    inline static AnyBindPtr LOG(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("log");
        }

        return Void::void_object;
    }

    // function to get the log2 of 'Double' and 'Int' type values .....
    inline static AnyBindPtr LOG2(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG2( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG2( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("log2");
        }

        return Void::void_object;
    }

    // function to get the log10 of 'Double' and 'Int' type values .....
    inline static AnyBindPtr LOG10(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG10( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::LOG10( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("log10");
        }
        
        return Void::void_object;
    }

    // function to get the maximum of two values .....
    inline static AnyBindPtr MAX(ArgumentList &__args)
    {
        if(__args.len() == 0){
            throw ThrowException("executing 'max' function. Too few arguments");
        }

        ArgListLen_t max = 0;

        ArgListLen_t len = __args.len();

        for (ArgListLen_t i = 1; i < len; ++i)
        {
            auto output = (*__args.get(i) > *__args.get(max));

            max  = (**boolCast( output->ptr())) ? i : max;
        }
        return __args.get(max);
    }

    // function to get the minimum of two values .....
    inline static AnyBindPtr MIN(ArgumentList &__args)
    {
        if(__args.len() == 0){
            throw ThrowException("executing 'min' function. Too few arguments", SronException::ArgumentException);
        }

        ArgListLen_t min = 0;

        ArgListLen_t len = __args.len();

        for (ArgListLen_t i = 1; i < len; ++i)
        {   
            auto output = (*__args.get(i) < *__args.get(min));

            min  = (**boolCast( output->ptr())) ? i : min;
        }
        return __args.get(min);
    }

    // // function to get the square root of 'Double' and 'Int' type values .....
    inline static AnyBindPtr SQRT(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::SQRT( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::SQRT( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("sqrt");
        }
        

        return Void::void_object;
    }

    // function to get the sin of 'Double' and 'Int' type values .....
    inline static AnyBindPtr SIN(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::SIN( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::SIN( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("sin");
        }
        
        return Void::void_object;
    }

    // function to get the tan of 'Double' and 'Int' type values .....
    inline static AnyBindPtr TAN(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case TYPE_DOUBLE: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::TAN( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case TYPE_INT: return GarbageCollector::REGISTER_MEMORY(new Double(SronMath::TAN( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            default : THROW_ARGUMENT_EXCEPTION_FOR_MATHEMATICAL_EXCEPTION("tan");
        }
        

        return Void::void_object;
    }

    // function to set the number of decimal digits to be printed on command line...
    // if the passed 'Int' value is less than 0 and greater than 10, then
    inline static AnyBindPtr SET_PRECISION(ArgumentList &__args)
    {
        Double::setPrecision( __args.get(0)->ptr()->GET_INT_ABS() );
        
        return Void::void_object;
    }

    // function to get the size of the data in bytes...
    inline static AnyBindPtr SIZE_OF(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new Int(__args.get(0)->ptr()->SIZE_OF()), SronTypeNum::TYPE_INT);
    }

    // function to split a string .....
    inline static AnyBindPtr SPLIT(ArgumentList &__args)
    {
        String &str = *__args.getString(0);

        return GarbageCollector::REGISTER_MEMORY(str.SPLIT(*__args.getChar(1)));
    }

    inline static AnyBindPtr SLEEP(ArgumentList &__args)
    {
        Sleep(__args.get(0)->ptr()->GET_INT_ABS());

        return Void::void_object;
    }

    inline static AnyBindPtr SRON_CMD( ArgumentList& __args )
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_INT )
        {
            switch( **intCast( value->ptr()) )
            {
                case SRON_CMD_OBUFFER_CLEAR : O_BUFFER.clear(); break;

                case SRON_CMD_IS_OBUFFER_EMPTY : return (O_BUFFER.isempty() ? Bool::__SronTrue : Bool::__SronFalse);

                case SRON_CMD_SIZEOF_OBUFFER : return GarbageCollector::REGISTER_MEMORY(new Int(O_BUFFER.size()) , SronTypeNum::TYPE_INT);

                case SRON_CMD_IS_FILE_AVAILABLE : return (SronExtra::doesFileExists( *__args.get(1)) ? Bool::__SronTrue : Bool::__SronFalse);

                case SRON_CMD_GC_STACK_LEN : return GarbageCollector::REGISTER_MEMORY( new Int( GarbageCollector::__garbageStack.size() ) , SronTypeNum::TYPE_INT );

                case SRON_CMD_IS_BYTECODE_CACHED : return (BytecodeManager::isBytecodeCached( *__args.get(1)) ? Bool::__SronTrue : Bool::__SronFalse);

                case SRON_CMD_NO_OF_BYTECODE_CACHED : return GarbageCollector::REGISTER_MEMORY( new Int( BytecodeManager::__UserDefinedFncMap__.size()) , SronTypeNum::TYPE_INT);

                default : throw ThrowException("executing 'sron_cmd()'. You have passed an invalid Sron Command '"+ std::to_string(**intCast( value->ptr()) ) + "'");
            }

            return Void::void_object;
        }
        
        throw ThrowException("executing 'sron_cmd()'. Expected a 'Int' type argument but found value of type '" + std::string( value->ptr()->TYPE()) + "'");
    }

    inline static AnyBindPtr SYS_CMD(ArgumentList &__args)
    {
        std::string &cmd = **__args.getString(0);

        if (std::system(cmd.c_str()) != 0)
        {
            throw ThrowException("executing the 'syscmd' function. This command ''" + cmd + "'' is invalid", SronException::DefaultException);
        }

        return Void::void_object;
    }

    inline static AnyBindPtr THROW_EXCEPTION(ArgumentList &__args)
    {
        throw ExceptionThrowByUser(__args.getString(0));
    }

    // function to convert a datatype to 'Bool' type...
    inline static AnyBindPtr TO_BOOL(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch ( value->type() )
        {
            case SronTypeNum::TYPE_BOOL : return value;

            case SronTypeNum::TYPE_STRING : return Converter::TO_BOOL( **stringCast( value->ptr() ) ) ? Bool::__SronTrue : Bool::__SronFalse;

            default : { }
        }
        
        return ( value->ptr()->GET_BOOL_ABS() )? Bool::__SronTrue : Bool::__SronFalse;

    }

    // function to convert a data to 'Double' type
    inline static AnyBindPtr TO_DOUBLE(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch( value->type() )
        {
            case SronTypeNum::TYPE_DOUBLE : return value;

            case SronTypeNum::TYPE_STRING : return GarbageCollector::REGISTER_MEMORY(new Double( **stringCast(value->ptr()) ) , SronTypeNum::TYPE_DOUBLE);

            default : { }
        }

        return GarbageCollector::REGISTER_MEMORY(new Double(value->ptr()->GET_DOUBLE_ABS()) , SronTypeNum::TYPE_DOUBLE);
    }

    // function to convert the data to 'Int' type...
    inline static AnyBindPtr TO_INT(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch ( value->type() )
        {
            case SronTypeNum::TYPE_INT : return value;

            case SronTypeNum::TYPE_STRING : return GarbageCollector::REGISTER_MEMORY(new Int(**stringCast( value->ptr())) , SronTypeNum::TYPE_INT);

            default : { }
        }
        
        return GarbageCollector::REGISTER_MEMORY(new Int(value->ptr()->GET_INT_ABS()) , SronTypeNum::TYPE_INT);
    }

    // function to convert a Char or String type value to lowercase ....
    inline static AnyBindPtr TO_LOWERCASE(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch ( value->type() )
        {
            case TYPE_STRING: return GarbageCollector::REGISTER_MEMORY( stringCast(value->ptr())->TO_LOWERCASE() );

            case TYPE_CHAR: return GarbageCollector::REGISTER_MEMORY(new Char(SronChar::TO_LOWERCASE( **charCast( value->ptr()))) , SronTypeNum::TYPE_CHAR);

            default : THROW_EXCEPTION_FOR_INVALID_ARGUMENTS("tolower", "String", "Char");
        }
        
        return Void::void_object;
    }

    // function to convert a Char or String type value to uppercase ....
    inline static AnyBindPtr TO_UPPERCASE(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_STRING: return GarbageCollector::REGISTER_MEMORY( stringCast(value->ptr())->TO_UPPERCASE());

            case SronTypeNum::TYPE_CHAR: return GarbageCollector::REGISTER_MEMORY(new Char(SronChar::TO_UPPERCASE( **charCast( value->ptr() ))));
            
            default : THROW_EXCEPTION_FOR_INVALID_ARGUMENTS("toupper", "String", "Char");
        }
        

        return Void::void_object;
    }

    // function to convert a datatype to 'String' type ....
    inline static AnyBindPtr TO_STRING(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new String(__args.get(0)->ptr()->TO_STRING()) , SronTypeNum::TYPE_STRING);
    }

    // function to trim a string...
    inline static AnyBindPtr TRIM(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if(value->type() == SronTypeNum::TYPE_STRING)
        {
            stringCast( value->ptr() )->TRIM();
            
            return Void::void_object;
        }
        
        THROW_EXCEPTION_FOR_INVALID_ARGUMENTS("trim", "String");

        return Void::void_object;
    }

    // returns the type of the passed value...
    inline static AnyBindPtr TYPE_OF(ArgumentList &__args)
    {
        return GarbageCollector::REGISTER_MEMORY(new String(__args.get(0)->ptr()->TYPE()), SronTypeNum::TYPE_STRING);
    }

    inline static AnyBindPtr UPDATE(ArgumentList &__args)
    {

        ColPtr val = __args.get(0)->ptr()->GET_COLLECTIVE();

        Int &index = *__args.getInt(1);

        Any &x = **__args.get(2);

        val->UPDATE(index, x);

        return Void::void_object;
    }


    // function to get the current version of sron...
    inline static AnyBindPtr VERSION(ArgumentList &)
    {
        return GarbageCollector::REGISTER_MEMORY(new Double( SRON_VERSION), SronTypeNum::TYPE_DOUBLE);
    }
}

#endif