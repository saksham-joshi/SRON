#ifndef _UTIL_INBUILT_FNC_H
#define _UTIL_INBUILT_FNC_H

#include "_col_fnc_.hpp"


inline static AnyBindPtr Sron::beep(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "beep", "Int frequency, Int duration");

        auto frequency = __args.get(0);
        auto duration = __args.get(1);

        if ( frequency->type() == SronTypeNum::TYPE_INT && duration->type() == SronTypeNum::TYPE_INT)
        {
            SronSupport::beep(duration->getBaseInt(),  frequency->getBaseInt());
        }
        else
        {
            throwArgumentException("beep", "Int, Int");
        }
        return Void::void_object;
    }

// function to create a copy of the values passed ...
    inline static AnyBindPtr Sron::copy(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "copy", "Any value");

        auto value = __args.get(0);

        if(value->type() == SronTypeNum::TYPE_VOID) return Void::void_object;
    
        else if(value->type() == SronTypeNum::TYPE_BOOL) return ( value->getBaseBool() )? Bool::__SronTrue : Bool::__SronFalse;
        
        return GarbageCollector::registerMemory( value->ptr()->copy(), value->type() );
    }

// function to exit the program...
    inline static AnyBindPtr Sron::exit(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "exit", "Int exit_code");
        
        AnyBindPtr arg0 = __args.get(0);

        if(arg0->type() != SronTypeNum::TYPE_INT)
        {
            throwArgumentException("exit", "Int");
        }

        throw SronException::UserWantsExit(intCast(arg0->ptr())->getBaseInt());
    }

    // function to get the number of milli seconds taken by the interpreter to execute the code written by the user...
    inline static AnyBindPtr Sron::getExecTime(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(0, "getExecTime", "");

        return GarbageCollector::registerInt(SronSupport::getExecTime(SronSupport::getCurTime(), SronSupport::CODE_START_TIME));
    }
inline static AnyBindPtr Sron::inputInt(ArgumentList &__args)
    {
        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->print();
        }

        return GarbageCollector::registerMemory(SronInput::inputInt(), SronTypeNum::TYPE_INT);
    }

    inline static AnyBindPtr Sron::inputDouble(ArgumentList &__args)
    {
        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->print();
        }

        return GarbageCollector::registerMemory(SronInput::inputDouble() , SronTypeNum::TYPE_DOUBLE);
    }

    inline static AnyBindPtr Sron::inputChar(ArgumentList &__args)
    {
        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->print();
        }

        return GarbageCollector::registerMemory(SronInput::inputChar() , SronTypeNum::TYPE_CHAR);
    }

    inline static AnyBindPtr Sron::inputString(ArgumentList &__args)
    {
        if (__args.len() > 0)
        {
            __args.get(0)->ptr()->print();
        }

        return GarbageCollector::registerMemory(SronInput::inputString() , SronTypeNum::TYPE_STRING);
    }

// function to generate a random numnber of type 'Int'...
    inline static AnyBindPtr Sron::randInt(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(0, "randInt", "");

        return GarbageCollector::registerInt(SronRandom::generateRandomInt());
    }

    // function to generate a random number between a particular range...
    inline static AnyBindPtr Sron::randRange(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "randRange", "Int range_start, Int range_end)  or  (Double range_start, Double range_end");

        auto start = __args.get(0);
        auto end = __args.get(1);

        if (start->type() == SronTypeNum::TYPE_INT && end->type() == SronTypeNum::TYPE_INT)
        {
            return GarbageCollector::registerInt(SronRandom::generateRandomIntWithinRange( intCast( start->ptr() )->getBaseInt() , intCast( end->ptr() )->getBaseInt()));
        }
        else if (start->type() == SronTypeNum::TYPE_DOUBLE && end->type() == SronTypeNum::TYPE_DOUBLE )
        {
            return GarbageCollector::registerDouble(SronRandom::generateRandomDoubleWithinRange( doubleCast( start->ptr() )->getBaseDouble() , doubleCast( end->ptr() )->getBaseDouble()));
        }

        throw ThrowException("executing 'randRange'. Expected arguments are either of type 'Int' or 'Double'. Both arguments should be of same type if one is Int then another should be Int too", SronException::ArgumentException);
    }


    // function to generate a random value of type 'Double' ....
    inline static AnyBindPtr Sron::randDouble(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(0, "randDouble", "");

        return GarbageCollector::registerDouble(SronRandom::generateRandomDouble());
    }

// function to set the number of decimal digits to be printed on command line...
    inline static AnyBindPtr Sron::setPrecision(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "setPrecision", "Int precision");

        auto arg0 = __args.get(0);

        if(arg0->type() == SronTypeNum::TYPE_INT) Double::setPrecision(arg0->getBaseInt());

        else throwArgumentException("setPrecision", "Int");
        
        return Void::void_object;
    }

    // function to get the size of the data in bytes...
    inline static AnyBindPtr Sron::sizeOf(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "sizeof", "Any value");

        return GarbageCollector::registerInt(__args.get(0)->ptr()->sizeOf());
    }

    inline static AnyBindPtr Sron::sleep(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "sleep", "Int duration");

        auto arg0 = __args.get(0);

        if(arg0->type() == SronTypeNum::TYPE_INT) SronSupport::sleep(arg0->getBaseInt());

        else throwArgumentException("sleep", "Int");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::sronCmd( ArgumentList& __args )
    {
        auto value = __args.get(0);

        if ( value->type() == SronTypeNum::TYPE_INT )
        {
            switch( value->getBaseInt() )
            {
                case SRON_CMD_OBUFFER_CLEAR : O_BUFFER.clear(); break;

                case SRON_CMD_IS_OBUFFER_EMPTY : return (O_BUFFER.isempty() ? Bool::__SronTrue : Bool::__SronFalse);

                case SRON_CMD_SIZEOF_OBUFFER : return GarbageCollector::registerInt(O_BUFFER.size());

                case SRON_CMD_GC_STACK_LEN : return GarbageCollector::registerInt( GarbageCollector::__garbageStack.size() );

                case SRON_CMD_IS_BYTECODE_CACHED : return (BytecodeManager::isBytecodeCached( *__args.get(1)) ? Bool::__SronTrue : Bool::__SronFalse);

                case SRON_CMD_NO_OF_BYTECODE_CACHED : return GarbageCollector::registerInt( BytecodeManager::__UserDefinedFncMap__.size());

                case SRON_CMD_IS_FILE_AVAILABLE : return (SronExtra::doesFileExists( __args.get(1)->getCstr()) ? Bool::__SronTrue : Bool::__SronFalse);

                default : throw ThrowException("executing 'sronCmd()'. You have passed an invalid Sron Command '"+ std::to_string(value->getBaseInt()) +"'");
            }
        }
        else throwArgumentException("sronCmd", "Int");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::sysCmd(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "sysCmd", "String cmd");

        auto arg0 = __args.get(0);

        if(arg0->type() == SronTypeNum::TYPE_STRING || arg0->type() == SronTypeNum::TYPE_LITERAL_STR)
        {
            return GarbageCollector::registerInt(std::system(arg0->getCstr()));
        }
        
        throwArgumentException("sysCmd", "String/LiteralString");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::throwException(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "throwException", "String/LiteralString");

        auto arg0 = __args.get(0);

        if(arg0->type() == SronTypeNum::TYPE_STRING || arg0->type() == SronTypeNum::TYPE_LITERAL_STR) throw SronException::ExceptionThrowByUser( arg0->getCstr() );

        throwArgumentException("throwException", "String/LiteralString");

        return Void::void_object;
    }

// function to get the current version of sron...
    inline static AnyBindPtr Sron::version(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(0, "version", "");

        if(Double::__SronVersion) return Double::__SronVersion;

        Double::__SronVersion = GarbageCollector::registerAt( 0, new Double(SRON_VERSION), SronTypeNum::TYPE_DOUBLE);

        return Double::__SronVersion;
    }
#endif