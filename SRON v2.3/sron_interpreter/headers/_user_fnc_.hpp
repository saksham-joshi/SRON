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
    
    inline static AnyBindPtr ascii(ArgumentList &);

    inline static AnyBindPtr beep(ArgumentList &);
    inline static AnyBindPtr copy(ArgumentList &);

    [[noreturn]] inline static AnyBindPtr exit(ArgumentList &);
    inline static AnyBindPtr getExecTime(ArgumentList &);

    // USER INPUT FUNCTIONS
    inline static AnyBindPtr inputInt(ArgumentList &);
    inline static AnyBindPtr inputDouble(ArgumentList &);
    inline static AnyBindPtr inputChar(ArgumentList &);
    inline static AnyBindPtr inputString(ArgumentList &);

    // CHAR MANIPUALTION FUNCTIONS
    inline static AnyBindPtr isAlphabet(ArgumentList &);
    inline static AnyBindPtr isConsonant(ArgumentList &);
    inline static AnyBindPtr isNumber(ArgumentList &);
    inline static AnyBindPtr isVowel(ArgumentList &);
    inline static AnyBindPtr isLowerCase(ArgumentList &);
    inline static AnyBindPtr isUpperCase(ArgumentList &);

    // type check functions ...
    inline static AnyBindPtr isVoid(ArgumentList &);
    inline static AnyBindPtr isInt(ArgumentList &);
    inline static AnyBindPtr isDouble(ArgumentList &);
    inline static AnyBindPtr isChar(ArgumentList &);
    inline static AnyBindPtr isBool(ArgumentList &);
    inline static AnyBindPtr isCollective(ArgumentList &);
    inline static AnyBindPtr isString(ArgumentList &);
    inline static AnyBindPtr isList(ArgumentList &);

    // COMMON LIST AND STRING MANIPULATION FUNCTIONS
    inline static AnyBindPtr at(ArgumentList &);
    inline static AnyBindPtr clear(ArgumentList &);
    inline static AnyBindPtr count(ArgumentList &);
    inline static AnyBindPtr drop(ArgumentList &);
    inline static AnyBindPtr index(ArgumentList &);
    inline static AnyBindPtr insert(ArgumentList &);
    inline static AnyBindPtr LEN(ArgumentList &);
    inline static AnyBindPtr push(ArgumentList &);
    inline static AnyBindPtr POP(ArgumentList &);
    inline static AnyBindPtr replace(ArgumentList &);
    inline static AnyBindPtr reverse(ArgumentList &);
    inline static AnyBindPtr rIndex(ArgumentList &);
    inline static AnyBindPtr sort(ArgumentList &);
    inline static AnyBindPtr reverseSort(ArgumentList &);
    inline static AnyBindPtr subPart(ArgumentList &);
    inline static AnyBindPtr update(ArgumentList &);

    [[gnu::hot]] inline static AnyBindPtr print(ArgumentList &);
    [[gnu::hot]] inline static AnyBindPtr println(ArgumentList &);

    // generating random numbers...
    inline static AnyBindPtr randInt(ArgumentList &);
    inline static AnyBindPtr randRange(ArgumentList &);
    inline static AnyBindPtr randDouble(ArgumentList &);

    inline static AnyBindPtr sizeOf(ArgumentList &);

    // type conversion function
    inline static AnyBindPtr toBool(ArgumentList &);
    inline static AnyBindPtr toDouble(ArgumentList &);
    inline static AnyBindPtr toInt(ArgumentList &);
    inline static AnyBindPtr toString(ArgumentList &);

    // COMMON STRING AND CHAR FUNCTIONS...
    inline static AnyBindPtr toLowercase(ArgumentList &);
    inline static AnyBindPtr toUppercase(ArgumentList &);

    // mathematical functions
    inline static AnyBindPtr abs(ArgumentList &);
    inline static AnyBindPtr cbrt(ArgumentList &);
    inline static AnyBindPtr ceil(ArgumentList &);
    inline static AnyBindPtr cos(ArgumentList &);
    inline static AnyBindPtr floor(ArgumentList &);
    inline static AnyBindPtr log(ArgumentList &);
    inline static AnyBindPtr log2(ArgumentList &);
    inline static AnyBindPtr log10(ArgumentList &);
    inline static AnyBindPtr maxValue(ArgumentList &);
    inline static AnyBindPtr minValue(ArgumentList &);
    inline static AnyBindPtr sqrt(ArgumentList &);
    inline static AnyBindPtr sin(ArgumentList &);
    inline static AnyBindPtr tan(ArgumentList &);

    // string manipulation functions...
    inline static AnyBindPtr split(ArgumentList &);
    inline static AnyBindPtr trim(ArgumentList &);

    inline static AnyBindPtr setPrecision(ArgumentList &);
    inline static AnyBindPtr sleep(ArgumentList& args);
    inline static AnyBindPtr sronCmd( ArgumentList&);
    inline static AnyBindPtr sysCmd(ArgumentList &);
    inline static AnyBindPtr throwException(ArgumentList &);

    inline static AnyBindPtr typeOf(ArgumentList &);

    // returns the version of the function ...
    inline static AnyBindPtr version(ArgumentList &);

    typedef AnyBindPtr (*SronInBuiltFnc) (ArgumentList&);

    struct SronInBuiltFncBinder
    {
        const char* _fnc_name;
        SronInBuiltFnc _fnc;
    };

    constexpr static struct SronInBuiltFncBinder Fmap[] = {

        {"ascii" , Sron::ascii},

        {"beep", Sron::beep},

        {"clear", Sron::clear},
        {"copy", Sron::copy},

        {"exit", Sron::exit},

        {"get_exec_time", Sron::getExecTime},

        // user input functions...
        {"input_char", Sron::inputChar},
        {"input_double", Sron::inputDouble},
        {"input_int", Sron::inputInt},
        {"input_string", Sron::inputString},

        {"isalphabet", Sron::isAlphabet},
        {"isconsonant", Sron::isConsonant},
        {"isdigit", Sron::isNumber},
        {"isvowel", Sron::isVowel},
        {"islower", Sron::isLowerCase},
        {"isupper", Sron::isUpperCase},

        {"is_void", Sron::isVoid},
        {"is_int", Sron::isInt},
        {"is_double", Sron::isDouble},
        {"is_char", Sron::isChar},
        {"is_bool", Sron::isBool},
        {"is_collective", Sron::isCollective},
        {"is_string", Sron::isString},
        {"is_list", Sron::isList},

        // common list and string manipulation functions...
        {"at", Sron::at},
        {"count", Sron::count},
        {"delete", Sron::drop},
        {"index", Sron::index},
        {"insert", Sron::insert},
        {"len", Sron::LEN},
        {"push", Sron::push},
        {"pop", Sron::POP},
        {"replace", Sron::replace},
        {"reverse", Sron::reverse},
        {"rindex", Sron::rIndex},
        {"sort", Sron::sort},
        {"reverse_sort", Sron::reverseSort},
        {"subpart", Sron::subPart},
        {"update", Sron::update},

        {"println", Sron::println},
        {"print", Sron::print},

        // generating random numbers...
        {"randint", Sron::randInt},
        {"randrange", Sron::randRange},
        {"randdouble", Sron::randDouble},

        {"setprecision", Sron::setPrecision},
        {"sizeof", Sron::sizeOf},

        // type conversion functions...
        {"to_bool", Sron::toBool},
        {"to_double", Sron::toDouble},
        {"to_int", Sron::toInt},
        {"to_string", Sron::toString},

        // string manipulation methods
        {"split", Sron::split},
        {"trim", Sron::trim},

        {"tolower", Sron::toLowercase},
        {"toupper", Sron::toUppercase},

        // math functions...
        {"abs", Sron::abs},
        {"max", Sron::maxValue},
        {"min", Sron::minValue},
        {"sqrt", Sron::sqrt},
        {"cbrt", Sron::cbrt},
        {"log", Sron::log},
        {"log2", Sron::log2},
        {"log10", Sron::log10},
        {"sin", Sron::sin},
        {"cos", Sron::cos},
        {"tan", Sron::tan},
        {"ceil", Sron::ceil},
        {"floor", Sron::floor},

        {"sleep", Sron::sleep},
        {"sron_cmd", Sron::sronCmd},
        {"syscmd", Sron::sysCmd},
        {"throw_exception", Sron::throwException},

        {"typeof", Sron::typeOf},

        {"version", Sron::version}
    };

    inline static SronInBuiltFnc getSronFunction( const SronInBuiltFncIndex_t __fnc_index )
    {
        if ( __fnc_index < sizeof(Fmap)/sizeof(Fmap[0])) [[likely]] return Fmap[__fnc_index]._fnc;

        throw ThrowException("searching for an in-built function", SronException::FunctionNotFoundException);
    }


    inline static AnyBindPtr ascii(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch ( value->type() )
        {
            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Char( **intCast(value->ptr())) , SronTypeNum::TYPE_CHAR);

            case SronTypeNum::TYPE_CHAR: return GarbageCollector::registerMemory(new Int( **charCast(value->ptr())) , SronTypeNum::TYPE_INT);

            default : throwArgumentException("ascii", "Int", "Char");
        }        

        return Void::void_object;
    }

    inline static AnyBindPtr at(ArgumentList &__args)
    {

        ColPtr ptr = __args.getCollective(0);

        Int &index = *__args.getInt(1);

        return ptr->at(index);
        
    }

    inline static AnyBindPtr beep(ArgumentList &__args)
    {
        auto frequency = __args.get(0);
        auto duration = __args.get(1);

        if ( frequency->type() == SronTypeNum::TYPE_INT && duration->type() == SronTypeNum::TYPE_INT)
        {
            SronSupport::beep(**intCast(duration->ptr()), **intCast(frequency->ptr()));
        }
        else
        {
            throw ThrowException("executing the 'beep' function. Both arguments should be of type 'Int'", SronException::DefaultException);
        }
        return Void::void_object;
    }

    inline static AnyBindPtr clear(ArgumentList &__args)
    {
        ColPtr ptr = __args.getCollective(0);

        ptr->clear();

        return Void::void_object;
    }

    // function to create a copy of the values passed ...
    inline static AnyBindPtr copy(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if(value->type() == SronTypeNum::TYPE_VOID) return Void::void_object;
    
        else if(value->type() == SronTypeNum::TYPE_BOOL) return ( **boolCast(value->ptr()) )? Bool::__SronTrue : Bool::__SronFalse;
        
        return GarbageCollector::registerMemory( value->ptr()->copy(), value->type() );
    }

    // function to count occurrences of a particular value in 'List' or 'String'
    inline static AnyBindPtr count(ArgumentList &__args)
    {
        ColPtr ptr = __args.getCollective(0);

        return GarbageCollector::registerMemory(new Int(ptr->count(**__args.get(1))) , SronTypeNum::TYPE_INT);
    }

    // function to delete a value from 'String' or 'List' ....
    inline static AnyBindPtr drop(ArgumentList &__args)
    {
        ColPtr ptr = __args.getCollective(0);

        Int &index = *__args.getInt(1);

        ptr->drop(index);

        return Void::void_object;
    }

    // function to exit the program...
    inline static AnyBindPtr exit(ArgumentList &__args)
    {
        auto code = **__args.getInt(0);

        GarbageCollector::totalDestruction();

        std::exit(code);
    }

    // function to get the number of milli seconds taken by the interpreter to execute the code written by the user...
    inline static AnyBindPtr getExecTime(ArgumentList &)
    {
        return GarbageCollector::registerMemory(new Int(SronSupport::getExecTime() - SronSupport::CODE_START_TIME), SronTypeNum::TYPE_INT);
    }
    

    // function to get the index of a particular value in 'String' and 'List'....
    inline static AnyBindPtr index(ArgumentList &__args)
    {
        ColPtr ptr = __args.getCollective(0);

        Any &val = **__args.get(1);

        return GarbageCollector::registerMemory(new Int(ptr->index(val)), SronTypeNum::TYPE_INT);
    }

    inline static AnyBindPtr inputInt(ArgumentList &__args)
    {

        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->print();
        }

        return GarbageCollector::registerMemory(SronInput::inputInt(), SronTypeNum::TYPE_INT);
    }

    inline static AnyBindPtr inputDouble(ArgumentList &__args)
    {
        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->print();
        }

        return GarbageCollector::registerMemory(SronInput::inputDouble() , SronTypeNum::TYPE_DOUBLE);
    }

    inline static AnyBindPtr inputChar(ArgumentList &__args)
    {

        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->print();
        }

        return GarbageCollector::registerMemory(SronInput::inputChar() , SronTypeNum::TYPE_CHAR);
    }

    inline static AnyBindPtr inputString(ArgumentList &__args)
    {

        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->print();
        }

        return GarbageCollector::registerMemory(SronInput::inputString() , SronTypeNum::TYPE_STRING);
    }

    inline static AnyBindPtr insert(ArgumentList &__args)
    {
        ColPtr val = __args.getCollective(0);

        Int &index = *__args.getInt(1);

        auto ptr = __args.get(2)->ptr();

        val->insert(index, ptr);

        return Void::void_object;
    }

    inline static AnyBindPtr isAlphabet(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::isAlphabet( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isalphabet()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->type()) + "'");
    }
    inline static AnyBindPtr isConsonant(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::isConsonant( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isconsonant()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->type()) + "'");
    }

    // function to check if the given character is number or not....
    inline static AnyBindPtr isNumber(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::isNumber( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isdigit()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->type()) + "'");
    }

    // function to check if the given character is vowel or what
    inline static AnyBindPtr isVowel(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::isVowel( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isvowel()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->type()) + "'");
    }

    inline static AnyBindPtr isLowerCase(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::isLowerCase( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'islower()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->type()) + "'");
    }

    inline static AnyBindPtr isUpperCase(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_CHAR ) return SronChar::isUpperCase( **charCast(value->ptr()) ) ? Bool::__SronTrue : Bool::__SronFalse;

        throw ThrowException("executing 'isupper()'. Expected argument of type 'Char' but found value of type '" + std::string(value->ptr()->type()) + "'");
    }


    // type checking functions ...
    inline static AnyBindPtr isVoid(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_VOID) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr isInt(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_INT) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr isDouble(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_DOUBLE) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr isChar(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_CHAR) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr isBool(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_BOOL) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    inline static AnyBindPtr isCollective(ArgumentList&__args)
    {
        return (__args.get(0)->ptr()->isCollective() )? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr isString(ArgumentList&__args)
    {
        return (__args.get(0)->type()== SronTypeNum::TYPE_STRING) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    inline static AnyBindPtr isList(ArgumentList&__args)
    {
        return (__args.get(0)->type() == SronTypeNum::TYPE_LIST) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    // returns the length of the datatype
    inline static AnyBindPtr LEN(ArgumentList &__args)
    {
        return GarbageCollector::registerMemory(new Int(__args.getCollective(0)->LEN()), SronTypeNum::TYPE_INT);
    }

    // returns the last element from 'String' or 'List' and deletes it...
    inline static AnyBindPtr POP(ArgumentList &__args)
    {
        return __args.getCollective(0)->pop();
    }

    // function to print data on the command line...
    inline static AnyBindPtr print(ArgumentList &__args)
    {
        SronOBuffer buffer;

        for (ArgListLen_t i = 0; i < __args.len(); ++i)
        {
            auto value = __args.get(i);

            switch( value->type() )
            {
                case SronTypeNum::TYPE_VOID:    voidCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_INT:     intCast( value->ptr() )->fillObuffer ( buffer ); break;

                case SronTypeNum::TYPE_DOUBLE:  doubleCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_CHAR :   charCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_BOOL :   boolCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_STRING : stringCast( value->ptr() )->fillObuffer( buffer ); break;

                case SronTypeNum::TYPE_LIST :   listCast( value->ptr() )->fillObuffer( buffer ); break;

                default: value->ptr()->fillObuffer( buffer ); 
            }
        }

        buffer.flush();

        return Void::void_object;
    }

    // function to print data on the command line with a newline in the end....
    inline static AnyBindPtr println(ArgumentList &__args)
    {
        Sron::print(__args);
        puts("");
        return Void::void_object;
    }

    inline static AnyBindPtr push(ArgumentList &__args)
    {
        ColPtr val = __args.getCollective(0);

        val->push(__args.get(1)->ptr());

        return Void::void_object;
    }

    // function to generate a random numnber of type 'Int'...
    inline static AnyBindPtr randInt(ArgumentList &)
    {
        return GarbageCollector::registerMemory(new Int(SronRandom::generateRandomInt()) , SronTypeNum::TYPE_INT);
    }

    // function to generate a random number between a particular range...
    inline static AnyBindPtr randRange(ArgumentList &__args)
    {
        auto start = __args.get(0);
        auto end = __args.get(1);


        if (start->type() == SronTypeNum::TYPE_INT && end->type() == SronTypeNum::TYPE_INT)
        {
            return GarbageCollector::registerMemory(new Int(SronRandom::generateRandomIntWithinRange( **intCast( start->ptr() ) , **intCast( end->ptr() ))) , SronTypeNum::TYPE_INT);
        }
        else if (start->type() == SronTypeNum::TYPE_DOUBLE && end->type() == SronTypeNum::TYPE_DOUBLE )
        {
            return GarbageCollector::registerMemory(new Double(SronRandom::generateRandomDoubleWithinRange( **doubleCast( start->ptr() ) , **doubleCast( end->ptr() ))) , SronTypeNum::TYPE_DOUBLE);
        }

        throw ThrowException("executing 'randrange'. Expected arguments are either of type 'Int' or 'Double'. Both arguments should be of same type if one is Int then another should be Int too", SronException::ArgumentException);
    }


    // function to generate a random value of type 'Double' ....
    inline static AnyBindPtr randDouble(ArgumentList &)
    {
        return GarbageCollector::registerMemory(new Double(SronRandom::generateRandomDouble()) , SronTypeNum::TYPE_DOUBLE);
    }

    // function to replace a value ...
    inline static AnyBindPtr replace(ArgumentList &__args)
    {
        ColPtr val = __args.getCollective(0);

        val->replace(**__args.get(1), **__args.get(2));

        return Void::void_object;
    }

    inline static AnyBindPtr reverse(ArgumentList &__args)
    {
        __args.getCollective(0)->reverse();

        return Void::void_object;
    }

    inline static AnyBindPtr rIndex(ArgumentList &__args)
    {
        ColPtr val = __args.getCollective(0);

        return GarbageCollector::registerMemory(new Int(val->rIndex(**__args.get(1))) , SronTypeNum::TYPE_INT);
    }

    inline static AnyBindPtr sort(ArgumentList &__args)
    {
        __args.getCollective(0)->sort();

        return Void::void_object;
    }

    inline static AnyBindPtr reverseSort(ArgumentList &__args)
    {
        __args.getCollective(0)->reverseSort();

        return Void::void_object;
    }

    inline static AnyBindPtr subPart(ArgumentList &__args){

        ColPtr val = __args.getCollective(0);

        return val->subPart(*__args.getInt(1) , *__args.getInt(2));

    }

    // function to return the absolute value of 'Double' and 'Int' type....
    inline static AnyBindPtr abs(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::abs( **doubleCast( value->ptr() ))) , SronTypeNum::TYPE_DOUBLE);
            
            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::abs( **intCast( value->ptr() ))) , SronTypeNum::TYPE_DOUBLE);
            
            default: throwArgumentExceptionForMathematicalException("abs");
        }
        

        return Void::void_object;
    }

    // function to return the cube root of 'Double' and 'Int' type....
    inline static AnyBindPtr cbrt(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE:
                return GarbageCollector::registerMemory(new Double(SronMath::cbrt( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case SronTypeNum::TYPE_INT:
                return GarbageCollector::registerMemory(new Double(SronMath::cbrt( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : throwArgumentExceptionForMathematicalException("cbrt");
        }
        
        return Void::void_object;
    }

    // function to return the ceil value of 'Double' and 'Int' type...
    inline static AnyBindPtr ceil(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::ceil( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::ceil( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : throwArgumentExceptionForMathematicalException("ceil");
        }

        return Void::void_object;
    }

    // function to get the cos of 'Double' and 'Int' type values .....
    inline static AnyBindPtr cos(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::cos( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::cos( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : throwArgumentExceptionForMathematicalException("cos");
        }

        return Void::void_object;
    }

    // function to get the floor of 'Double' and 'Int' type values .....
    inline static AnyBindPtr floor(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::floor( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::floor( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : throwArgumentExceptionForMathematicalException("floor");
        }
    
        return Void::void_object;
    }

    // function to get the log of 'Double' and 'Int' type values .....
    inline static AnyBindPtr log(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::log( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::log( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : throwArgumentExceptionForMathematicalException("log");
        }

        return Void::void_object;
    }

    // function to get the log2 of 'Double' and 'Int' type values .....
    inline static AnyBindPtr log2(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::log2( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::log2( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : throwArgumentExceptionForMathematicalException("log2");
        }

        return Void::void_object;
    }

    // function to get the log10 of 'Double' and 'Int' type values .....
    inline static AnyBindPtr log10(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::log10( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::log10( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : throwArgumentExceptionForMathematicalException("log10");
        }
        
        return Void::void_object;
    }

    // function to get the maximum of two values .....
    inline static AnyBindPtr maxValue(ArgumentList &__args)
    {
        if(__args.len() == 0){
            throw ThrowException("executing 'max' function. Too few arguments");
        }

        ArgListLen_t max_value_index = 0;

        ArgListLen_t len = __args.len();

        for (ArgListLen_t i = 1; i < len; ++i)
        {
            auto output = (*__args.get(i) > *__args.get(max_value_index));

            max_value_index  = (**boolCast( output->ptr())) ? i : max_value_index;
        }
        return __args.get(max_value_index);
    }

    // function to get the minimum of two values .....
    inline static AnyBindPtr minValue(ArgumentList &__args)
    {
        if(__args.len() == 0){
            throw ThrowException("executing 'min' function. Too few arguments", SronException::ArgumentException);
        }

        ArgListLen_t min_value_index = 0;

        ArgListLen_t len = __args.len();

        for (ArgListLen_t i = 1; i < len; ++i)
        {   
            auto output = (*__args.get(i) < *__args.get(min_value_index));

            min_value_index = (**boolCast( output->ptr())) ? i : min_value_index;
        }
        return __args.get(min_value_index);
    }

    // // function to get the square root of 'Double' and 'Int' type values .....
    inline static AnyBindPtr sqrt(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::sqrt( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::sqrt( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);

            default : throwArgumentExceptionForMathematicalException("sqrt");
        }
        

        return Void::void_object;
    }

    // function to get the sin of 'Double' and 'Int' type values .....
    inline static AnyBindPtr sin(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::sin( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::sin( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            default : throwArgumentExceptionForMathematicalException("sin");
        }
        
        return Void::void_object;
    }

    // function to get the tan of 'Double' and 'Int' type values .....
    inline static AnyBindPtr tan(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_DOUBLE: return GarbageCollector::registerMemory(new Double(SronMath::tan( **doubleCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            case SronTypeNum::TYPE_INT: return GarbageCollector::registerMemory(new Double(SronMath::tan( **intCast( value->ptr() ))), SronTypeNum::TYPE_DOUBLE);
            
            default : throwArgumentExceptionForMathematicalException("tan");
        }
        

        return Void::void_object;
    }

    // function to set the number of decimal digits to be printed on command line...
    // if the passed 'Int' value is less than 0 and greater than 10, then
    inline static AnyBindPtr setPrecision(ArgumentList &__args)
    {
        Double::setPrecision( __args.get(0)->ptr()->getBaseInt() );
        
        return Void::void_object;
    }

    // function to get the size of the data in bytes...
    inline static AnyBindPtr sizeOf(ArgumentList &__args)
    {
        return GarbageCollector::registerMemory(new Int(__args.get(0)->ptr()->sizeOf()), SronTypeNum::TYPE_INT);
    }

    // function to split a string .....
    inline static AnyBindPtr split(ArgumentList &__args)
    {
        String &str = *__args.getString(0);

        return GarbageCollector::registerMemory(str.split(*__args.getChar(1)));
    }

    inline static AnyBindPtr sleep(ArgumentList &__args)
    {
        SronSupport::sleep(__args.get(0)->ptr()->getBaseInt());

        return Void::void_object;
    }

    inline static AnyBindPtr sronCmd( ArgumentList& __args )
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_INT )
        {
            switch( **intCast( value->ptr()) )
            {
                case SRON_CMD_OBUFFER_CLEAR : O_BUFFER.clear(); break;

                case SRON_CMD_IS_OBUFFER_EMPTY : return (O_BUFFER.isempty() ? Bool::__SronTrue : Bool::__SronFalse);

                case SRON_CMD_SIZEOF_OBUFFER : return GarbageCollector::registerMemory(new Int(O_BUFFER.size()) , SronTypeNum::TYPE_INT);

                case SRON_CMD_IS_FILE_AVAILABLE : return (SronExtra::doesFileExists( *__args.get(1)) ? Bool::__SronTrue : Bool::__SronFalse);

                case SRON_CMD_GC_STACK_LEN : return GarbageCollector::registerMemory( new Int( GarbageCollector::__garbageStack.size() ) , SronTypeNum::TYPE_INT );

                case SRON_CMD_IS_BYTECODE_CACHED : return (BytecodeManager::isBytecodeCached( *__args.get(1)) ? Bool::__SronTrue : Bool::__SronFalse);

                case SRON_CMD_NO_OF_BYTECODE_CACHED : return GarbageCollector::registerMemory( new Int( BytecodeManager::__UserDefinedFncMap__.size()) , SronTypeNum::TYPE_INT);

                default : throw ThrowException("executing 'sron_cmd()'. You have passed an invalid Sron Command '"+ std::to_string(**intCast( value->ptr()) ) + "'");
            }

            return Void::void_object;
        }
        
        throw ThrowException("executing 'sron_cmd()'. Expected a 'Int' type argument but found value of type '" + std::string( value->ptr()->type()) + "'");
    }

    inline static AnyBindPtr sysCmd(ArgumentList &__args)
    {
        std::string &cmd = **__args.getString(0);

        if (std::system(cmd.c_str()) != 0)
        {
            throw ThrowException("executing the 'syscmd' function. This command ''" + cmd + "'' is invalid", SronException::DefaultException);
        }

        return Void::void_object;
    }

    inline static AnyBindPtr throwException(ArgumentList &__args)
    {
        throw ExceptionThrowByUser(__args.getString(0));
    }

    // function to convert a datatype to 'Bool' type...
    inline static AnyBindPtr toBool(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch ( value->type() )
        {
            case SronTypeNum::TYPE_BOOL : return value;

            case SronTypeNum::TYPE_STRING : return Converter::toBool( **stringCast( value->ptr() ) ) ? Bool::__SronTrue : Bool::__SronFalse;

            default : { }
        }
        
        return ( value->ptr()->getBaseBool() )? Bool::__SronTrue : Bool::__SronFalse;

    }

    // function to convert a data to 'Double' type
    inline static AnyBindPtr toDouble(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch( value->type() )
        {
            case SronTypeNum::TYPE_DOUBLE : return value;

            case SronTypeNum::TYPE_STRING : return GarbageCollector::registerMemory(new Double( **stringCast(value->ptr()) ) , SronTypeNum::TYPE_DOUBLE);

            default : { }
        }

        return GarbageCollector::registerMemory(new Double(value->ptr()->getBaseDouble()) , SronTypeNum::TYPE_DOUBLE);
    }

    // function to convert the data to 'Int' type...
    inline static AnyBindPtr toInt(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch ( value->type() )
        {
            case SronTypeNum::TYPE_INT : return value;

            case SronTypeNum::TYPE_STRING : return GarbageCollector::registerMemory(new Int(**stringCast( value->ptr())) , SronTypeNum::TYPE_INT);

            default : { }
        }
        
        return GarbageCollector::registerMemory(new Int(value->ptr()->getBaseInt()) , SronTypeNum::TYPE_INT);
    }

    // function to convert a Char or String type value to lowercase ....
    inline static AnyBindPtr toLowercase(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch ( value->type() )
        {
            case SronTypeNum::TYPE_STRING: return GarbageCollector::registerMemory( stringCast(value->ptr())->toLowercase() );

            case SronTypeNum::TYPE_CHAR: return GarbageCollector::registerMemory(new Char(SronChar::toLowercase( **charCast( value->ptr()))) , SronTypeNum::TYPE_CHAR);

            default : throwArgumentException("tolower", "String", "Char");
        }
        
        return Void::void_object;
    }

    // function to convert a Char or String type value to uppercase ....
    inline static AnyBindPtr toUppercase(ArgumentList &__args)
    {
        auto value = __args.get(0);

        switch (value->type())
        {
            case SronTypeNum::TYPE_STRING: return GarbageCollector::registerMemory( stringCast(value->ptr())->toUppercase());

            case SronTypeNum::TYPE_CHAR: return GarbageCollector::registerMemory(new Char(SronChar::toUppercase( **charCast( value->ptr() ))));
            
            default : throwArgumentException("toupper", "String", "Char");
        }
        

        return Void::void_object;
    }

    // function to convert a datatype to 'String' type ....
    inline static AnyBindPtr toString(ArgumentList &__args)
    {
        return GarbageCollector::registerMemory(new String(__args.get(0)->ptr()->toString()) , SronTypeNum::TYPE_STRING);
    }

    // function to trim a string...
    inline static AnyBindPtr trim(ArgumentList &__args)
    {
        auto value = __args.get(0);

        if(value->type() == SronTypeNum::TYPE_STRING)
        {
            stringCast( value->ptr() )->trim();
            
            return Void::void_object;
        }
        
        throwArgumentException("trim", "String");

        return Void::void_object;
    }

    // returns the type of the passed value...
    inline static AnyBindPtr typeOf(ArgumentList &__args)
    {
        return GarbageCollector::registerMemory(new String(__args.get(0)->ptr()->type()), SronTypeNum::TYPE_STRING);
    }

    inline static AnyBindPtr update(ArgumentList &__args)
    {

        ColPtr val = __args.get(0)->ptr()->getCollective();

        Int &index = *__args.getInt(1);

        Any &x = **__args.get(2);

        val->update(index, x);

        return Void::void_object;
    }


    // function to get the current version of sron...
    inline static AnyBindPtr version(ArgumentList &)
    {
        return GarbageCollector::registerMemory(new Double( SRON_VERSION), SronTypeNum::TYPE_DOUBLE);
    }
}

#endif