#ifndef _TYPE_INBUILT_FNC_H
#define _TYPE_INBUILT_FNC_H

#include "_util_fnc_.hpp"

// type checking functions ...
    inline static AnyBindPtr Sron::isVoid(ArgumentList&__args)
    {
        CHECK_ARGS_COUNT(1, "isVoid", "Any value");

        return (__args.get(0)->type() == SronTypeNum::TYPE_VOID) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr Sron::isInt(ArgumentList&__args)
    {
        CHECK_ARGS_COUNT(1, "isInt", "Any value");

        return (__args.get(0)->type() == SronTypeNum::TYPE_INT) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr Sron::isDouble(ArgumentList&__args)
    {
        CHECK_ARGS_COUNT(1, "isDouble", "Any value");

        return (__args.get(0)->type() == SronTypeNum::TYPE_DOUBLE) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr Sron::isChar(ArgumentList&__args)
    {
        CHECK_ARGS_COUNT(1, "isChar", "Any value");

        return (__args.get(0)->type() == SronTypeNum::TYPE_CHAR) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr Sron::isBool(ArgumentList&__args)
    {
        CHECK_ARGS_COUNT(1, "isBool", "Any value");

        return (__args.get(0)->type() == SronTypeNum::TYPE_BOOL) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    inline static AnyBindPtr Sron::isCollective(ArgumentList&__args)
    {
        CHECK_ARGS_COUNT(1, "isCollective", "Any value");

        return (__args.get(0)->ptr()->isCollective() )? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr Sron::isString(ArgumentList&__args)
    {
        CHECK_ARGS_COUNT(1, "isString", "Any value");

        return (__args.get(0)->type()== SronTypeNum::TYPE_STRING) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    inline static AnyBindPtr Sron::isList(ArgumentList&__args)
    {
        CHECK_ARGS_COUNT(1, "isList", "Any value");

        return (__args.get(0)->type() == SronTypeNum::TYPE_LIST) ? Bool::__SronTrue : Bool::__SronFalse;        
    }

    inline static AnyBindPtr Sron::isFileReader(ArgumentList& __args)
    {
        CHECK_ARGS_COUNT(1, "isFileReader", "Any value");

        return (__args.unsafeGet(0)->type() == SronTypeNum::TYPE_FILE_READER) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr Sron::isFileWriter(ArgumentList& __args)
    {
        CHECK_ARGS_COUNT(1, "isFileWriter", "Any value");

        return (__args.unsafeGet(0)->type() == SronTypeNum::TYPE_FILE_WRITER) ? Bool::__SronTrue : Bool::__SronFalse;
    }

    inline static AnyBindPtr Sron::isLiteralString(ArgumentList& __args)
    {
        CHECK_ARGS_COUNT(1, "isLiteralString", "Any value");

        return (__args.unsafeGet(0)->type() == SronTypeNum::TYPE_LITERAL_STR) ? Bool::__SronTrue : Bool::__SronFalse;
    }

// function to convert a datatype to 'Bool' type...
    inline static AnyBindPtr Sron::toBool(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "toBool", "Any value");

        auto arg0 = __args.get(0);

        if(arg0->type() == SronTypeNum::TYPE_BOOL) return arg0;

        SronBool_t value;

        switch(arg0->type())
        {
            case SronTypeNum::TYPE_INT : value = arg0->getBaseInt(); break;

            case SronTypeNum::TYPE_DOUBLE : value = arg0->getBaseDouble(); break;

            case SronTypeNum::TYPE_CHAR : value = arg0->getBaseChar(); break;

            default : throw ThrowException("converting a value of type '"+ arg0->typeStr() +"' to 'Bool'", SronException::TypeConversionException);
        }

        return value ? Bool::__SronTrue : Bool::__SronFalse;
    }

    // function to convert a data to 'Double' type
    inline static AnyBindPtr Sron::toDouble(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "toDouble", "Any value");

        auto arg0 = __args.get(0);

        if(arg0->type() == SronTypeNum::TYPE_DOUBLE) return arg0;

        SronDouble_t value;

        switch( arg0->type() )
        {
            case SronTypeNum::TYPE_INT : value = arg0->getBaseInt(); break;

            case SronTypeNum::TYPE_CHAR : value = arg0->getBaseChar(); break;

            case SronTypeNum::TYPE_STRING : value = Converter::toDouble(arg0->getBaseStr()); break;

            case SronTypeNum::TYPE_LITERAL_STR : value = Converter::toDouble(arg0->getBaseLstr().data()); break;

            case SronTypeNum::TYPE_BOOL : value = arg0->getBaseBool(); break;

            default : throw ThrowException("converting a value of type '"+ arg0->typeStr() +"' to 'Double'", SronException::TypeConversionException);
        }

        return GarbageCollector::registerDouble(value);
    }

    // function to convert the data to 'Int' type...
    inline static AnyBindPtr Sron::toInt(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "toInt", "Any value");

        auto arg0 = __args.get(0);

        if(arg0->type() == SronTypeNum::TYPE_INT) return arg0;

        SronInt_t value;

        switch( arg0->type() )
        {
            case SronTypeNum::TYPE_DOUBLE : value = arg0->getBaseDouble(); break;

            case SronTypeNum::TYPE_CHAR : value = arg0->getBaseChar(); break;

            case SronTypeNum::TYPE_STRING : value = Converter::toInt(arg0->getBaseStr()); break;

            case SronTypeNum::TYPE_LITERAL_STR : value = Converter::toInt(arg0->getBaseLstr().data()); break;

            case SronTypeNum::TYPE_BOOL : value = arg0->getBaseBool(); break;

            default : throw ThrowException("converting a value of type '"+ arg0->typeStr() +"' to 'Int'", SronException::TypeConversionException);
        }

        return GarbageCollector::registerInt(value);
    }
// function to convert a datatype to 'String' type ....
    inline static AnyBindPtr Sron::toString(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "toString", "Any value");

        auto arg0 = __args.get(0);

        if(arg0->type() == SronTypeNum::TYPE_STRING) return arg0;

        return GarbageCollector::registerString(arg0->ptr()->toString());
    }

// returns the type of the passed value...
    inline static AnyBindPtr Sron::typeOf(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "typeof", "Any value");

        return GarbageCollector::registerString(__args.get(0)->typeStr());
    }

#endif 