
#ifndef _CHAR_INBUILT_FNC_H
#define _CHAR_INBUILT_FNC_H

#include "_user_fnc_.hpp"

inline static AnyBindPtr Sron::ascii(ArgumentList &__args)
{
    CHECK_ARGS_COUNT(1, "ascii", "Int/Char value");

    auto value = __args.get(0);

    switch ( value->type() )
    {
        case SronTypeNum::TYPE_INT: return GarbageCollector::registerChar(intCast(value->ptr())->getBaseInt());

        case SronTypeNum::TYPE_CHAR: return GarbageCollector::registerInt(charCast(value->ptr())->getBaseChar());

        default : throwArgumentException("ascii", "Int/Char");
    }        

    return Void::void_object;
}

inline static AnyBindPtr Sron::isAlphabet(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "isAlphabet", "Char value");

        auto value = __args.get(0);

        if(value->canBeChar()) return SronChar::isAlphabet(value->getConvertedChar()) ? Bool::__SronTrue : Bool::__SronFalse;

        throwArgumentException("isAlphabet", "Char value");
    }
    inline static AnyBindPtr Sron::isConsonant(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "isConsonant", "Char value");

        auto value = __args.get(0);

        if(value->canBeChar()) return SronChar::isConsonant(value->getConvertedChar()) ? Bool::__SronTrue : Bool::__SronFalse;

        throwArgumentException("isConsonant", "Char value");
    }

    // function to check if the given character is number or not....
    inline static AnyBindPtr Sron::isDigit(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "isDigit", "Char value");

        auto value = __args.get(0);

        if(value->canBeChar()) return SronChar::isDigit(value->getConvertedChar()) ? Bool::__SronTrue : Bool::__SronFalse;

        throwArgumentException("isDigit", "Char value");
    }

    // function to check if the given character is vowel or what
    inline static AnyBindPtr Sron::isVowel(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "isVowel", "Char value");

        auto value = __args.get(0);

        if(value->canBeChar()) return SronChar::isVowel(value->getConvertedChar()) ? Bool::__SronTrue : Bool::__SronFalse; 

        throwArgumentException("isVowel", "Char value");
    }

    inline static AnyBindPtr Sron::isLowerCase(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "isLower", "Char/String/LiteralString value");

        auto value = __args.get(0);

        switch(value->type())
        {
            case SronTypeNum::TYPE_CHAR : return charCast(value->ptr())->isLowerCase() ? Bool::__SronTrue : Bool::__SronFalse;

            case SronTypeNum::TYPE_STRING : return stringCast(value->ptr())->isLowerCase() ? Bool::__SronTrue : Bool::__SronFalse;

            case SronTypeNum::TYPE_LITERAL_STR : return lstrCast(value->ptr())->isLowerCase() ? Bool::__SronTrue : Bool::__SronFalse;

            default : { }
        }

        throwArgumentException("isLower", "Char/String/LiteralString");
    }

    inline static AnyBindPtr Sron::isUpperCase(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "isUpper", "Char/String/LiteralString value");

        auto value = __args.get(0);

        switch(value->type())
        {
            case SronTypeNum::TYPE_CHAR : return charCast(value->ptr())->isUpperCase() ? Bool::__SronTrue : Bool::__SronFalse;

            case SronTypeNum::TYPE_STRING : return stringCast(value->ptr())->isUpperCase() ? Bool::__SronTrue : Bool::__SronFalse;

            case SronTypeNum::TYPE_LITERAL_STR : return lstrCast(value->ptr())->isUpperCase() ? Bool::__SronTrue : Bool::__SronFalse;

            default : { }
        }

        throwArgumentException("isUpper", "Char/String/LiteralString");
    }

    inline static AnyBindPtr Sron::isAlphaNum(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "isAlphaNum", "Char value");

        auto value = __args.get(0);

        if(value->canBeChar()) return SronChar::isAlphaNum(value->getConvertedChar()) ? Bool::__SronTrue : Bool::__SronFalse;

        throwArgumentException("isAlphaNum", "Char");
    }

#endif