#ifndef _MATH_INBUILT_FNC_H
#define _MATH_INBUILT_FNC_H

#include "_char_fnc_.hpp"


// function to return the absolute value of 'Double' and 'Int' type....
    inline static AnyBindPtr Sron::abs(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "abs", "Int/Double value");
        
        auto value = __args.get(0);

        if(value->canBeDouble()) return GarbageCollector::registerDouble(SronMath::abs(value->getConvertedDouble()));

        else throwArgumentExceptionForMathematicalException("abs");

        return Void::void_object;
    }

    // function to return the cube root of 'Double' and 'Int' type....
    inline static AnyBindPtr Sron::cbrt(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "cbrt", "Int/Double value");

        auto value = __args.get(0);

        if(value->canBeDouble()) return GarbageCollector::registerDouble(SronMath::cbrt(value->getConvertedDouble()));

        else throwArgumentExceptionForMathematicalException("cbrt");
        
        return Void::void_object;
    }

    // function to return the ceil value of 'Double' and 'Int' type...
    inline static AnyBindPtr Sron::ceil(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "ceil", "Int/Double value");

        auto value = __args.get(0);

        if(value->canBeDouble()) return GarbageCollector::registerDouble(SronMath::ceil(value->getConvertedDouble()));

        else throwArgumentExceptionForMathematicalException("ceil");

        return Void::void_object;
    }

    // function to get the cos of 'Double' and 'Int' type values .....
    inline static AnyBindPtr Sron::cos(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "cos", "Int/Double value");

        auto value = __args.get(0);

        if(value->canBeDouble()) return GarbageCollector::registerDouble(SronMath::cos(value->getConvertedDouble()));

        else throwArgumentExceptionForMathematicalException("cos");

        return Void::void_object;
    }

    // function to get the floor of 'Double' and 'Int' type values .....
    inline static AnyBindPtr Sron::floor(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "floor", "Int/Double value");

        auto arg0 = __args.get(0);

        if(arg0->canBeDouble()) return GarbageCollector::registerInt(SronMath::floor(arg0->getConvertedDouble()));

        else throwArgumentExceptionForMathematicalException("floor");
    
        return Void::void_object;
    }

    // function to get the log of 'Double' and 'Int' type values .....
    inline static AnyBindPtr Sron::log(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "log", "Int/Double value");

        auto arg0 = __args.get(0);

        if(arg0->canBeDouble()) return GarbageCollector::registerDouble(SronMath::log(arg0->getConvertedDouble()));

        else throwArgumentExceptionForMathematicalException("log");

        return Void::void_object;
    }

    // function to get the log2 of 'Double' and 'Int' type values .....
    inline static AnyBindPtr Sron::log2(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "log2", "Int/Double value");

        auto arg0 = __args.get(0);

        if(arg0->canBeDouble()) return GarbageCollector::registerDouble(SronMath::log2(arg0->getConvertedDouble()));

        else throwArgumentExceptionForMathematicalException("log2");

        return Void::void_object;
    }

    // function to get the log10 of 'Double' and 'Int' type values .....
    inline static AnyBindPtr Sron::log10(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "log10", "Int/Double value");

        auto arg0 = __args.get(0);

        if(arg0->canBeDouble()) return GarbageCollector::registerDouble(SronMath::log10(arg0->getConvertedDouble()));

        else throwArgumentExceptionForMathematicalException("log10");
        
        return Void::void_object;
    }

    // function to get the maximum of two values .....
    inline static AnyBindPtr Sron::maxValue(ArgumentList &__args)
    {
        if(__args.len() == 0){
            throw ThrowException("executing 'max' function. Too few arguments");
        }

        ArgListLen_t max_value_index = 0;

        ArgListLen_t len = __args.len();

        for (ArgListLen_t i = 1; i < len; ++i)
        {
            max_value_index = __args.unsafeGet(i)->ptr()->__moreThan__(**__args.unsafeGet(max_value_index), __args.unsafeGet(max_value_index)->type()) ? i : max_value_index;
        }
        return __args.unsafeGet(max_value_index);
    }

    // function to get the minimum of two values .....
    inline static AnyBindPtr Sron::minValue(ArgumentList &__args)
    {
        if(__args.len() == 0){
            throw ThrowException("executing 'min' function. Too few arguments", SronException::ArgumentException);
        }

        ArgListLen_t min_value_index = 0;

        ArgListLen_t len = __args.len();

        for (ArgListLen_t i = 1; i < len; ++i)
        {
            min_value_index = __args.unsafeGet(i)->ptr()->__lessThan__(**__args.unsafeGet(min_value_index), __args.unsafeGet(min_value_index)->type()) ? i : min_value_index;
        }

        return __args.unsafeGet(min_value_index);
    }

    // // function to get the square root of 'Double' and 'Int' type values .....
    inline static AnyBindPtr Sron::sqrt(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "sqrt", "Int/Double value");

        auto value = __args.get(0);

        if(value->canBeDouble()) return GarbageCollector::registerDouble(SronMath::sqrt(value->getConvertedDouble()));
        
        else throwArgumentException("sqrt", "Double/Int");

        return Void::void_object;
    }

    // function to get the sin of 'Double' and 'Int' type values .....
    inline static AnyBindPtr Sron::sin(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "sin", "Int/Double value");

        auto value = __args.get(0);

        if(value->canBeDouble()) return GarbageCollector::registerDouble(SronMath::sin(value->getConvertedDouble()));

        else throwArgumentException("sin", "Double/Int");

        return Void::void_object;
    }

    // function to get the tan of 'Double' and 'Int' type values .....
    inline static AnyBindPtr Sron::tan(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "tan", "Int/Double value");

        auto value = __args.get(0);

        if(value->canBeDouble()) return GarbageCollector::registerDouble(SronMath::tan(value->getConvertedDouble()));

        else throwArgumentException("tan", "Double/Int");

        return Void::void_object;
    }


#endif