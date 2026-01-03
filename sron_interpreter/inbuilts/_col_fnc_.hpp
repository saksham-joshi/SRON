#ifndef _COL_INBUILT_FNC_H
#define _COL_INBUILT_FNC_H

#include "_math_fnc_.hpp"

inline static AnyBindPtr Sron::at(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "at", "String/List value, Int index");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);

        if(arg0->canBeCollective() && arg1->type() == SronTypeNum::TYPE_INT)
        {
            ColPtr ptr = colCast(arg0->ptr());

            IntPtr index = intCast(arg1->ptr());

            return ptr->at(*index);
        }
        
        throwArgumentException("at", "String/List, Int");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::clear(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "clear", "String/List value");

        auto arg0 = __args.get(0);

        if(!arg0->canBeCollective()) throwArgumentException("clear", "String/List");
        
        ColPtr ptr = colCast(arg0->ptr());

        ptr->clear();

        return Void::void_object;
    }
// function to count occurrences of a particular value in 'List' or 'String'
    inline static AnyBindPtr Sron::count(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "count", "String/List value, Any value_to_count");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);

        if(arg0->canBeCollective())
        {
            ColPtr ptr = colCast(arg0->ptr());

            return GarbageCollector::registerInt(ptr->count(*arg1));
        }

        throwArgumentException("count", "String/List, Any");
    }

// function to delete a value from 'String' or 'List' ....
    inline static AnyBindPtr Sron::drop(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "drop", "String/List value, Int index");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);

        if(arg0->canBeCollective() && arg1->type() == SronTypeNum::TYPE_INT)
        {   
            ColPtr ptr = colCast(arg0->ptr());
            
            Int *index = intCast(arg1->ptr());
            
            ptr->drop(*index);
        }
        else throwArgumentException("drop", "String/List, Int");

        return Void::void_object;
    }
// function to get the index of a particular value in 'String' and 'List'....
    inline static AnyBindPtr Sron::index(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "index", "String/List value, Any value_to_search");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);

        if(arg0->canBeCollective())
        {
            ColPtr ptr = colCast(arg0->ptr());
            
            return GarbageCollector::registerInt(ptr->index(*arg1));
        }

        throwArgumentException("index", "String/List, Any");

        return Void::void_object;
    }
inline static AnyBindPtr Sron::insert(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(3, "insert", "String/List value, Int index, Any value_to_insert");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);
        auto arg2 = __args.get(2);

        if(arg0->canBeCollective() && arg1->type() == SronTypeNum::TYPE_INT)
        {
            ColPtr val = colCast(arg0->ptr());
            
            Int *index = intCast(arg1->ptr());
            
            val->insert(*index, *arg2);
        }

        else throwArgumentException("insert", "String/List, Int, Any");

        return Void::void_object;
    }

// returns the length of the datatype
    inline static AnyBindPtr Sron::len(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "len", "String / List / FileReader / FileWriter");
        
        AnyBindPtr arg0 = __args.get(0);

        SronInt_t length = 0;

        switch(arg0->type())
        {
            case SronTypeNum::TYPE_STRING : length = (stringCast(arg0->ptr()))->len(); break;

            case SronTypeNum::TYPE_LITERAL_STR : length = (lstrCast(arg0->ptr()))->len(); break;

            case SronTypeNum::TYPE_LIST : length = (listCast(arg0->ptr()))->len(); break;

            case SronTypeNum::TYPE_FILE_READER : length = (freaderCast(arg0->ptr()))->len(); break;

            case SronTypeNum::TYPE_FILE_WRITER : length = (fwriterCast(arg0->ptr()))->len(); break;

            default : throwArgumentException("len", "String / LiteralString / List / FileReader / FileWriter");
        }

        return GarbageCollector::registerMemory(new Int(length), SronTypeNum::TYPE_INT);
    }

    // returns the last element from 'String' or 'List' and deletes it...
    inline static AnyBindPtr Sron::POP(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "pop", "String/List value");

        auto arg0 = __args.get(0);

        if(arg0->canBeCollective()) return colCast(arg0->ptr())->pop();
        
        throwArgumentException("pop", "String/List");

        return Void::void_object;
    }
inline static AnyBindPtr Sron::push(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "push", "String/List value, Any value_to_insert");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);

        if(arg0->canBeCollective())
        {
            ColPtr val = colCast(arg0->ptr());

            val->push( arg1->ptr() );
        }
        else throwArgumentException("push", "String/List, Any");

        return Void::void_object;
    }

// function to replace a value ...
    inline static AnyBindPtr Sron::replace(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(3, "replace", "String/List value, Any value_to_replace, Any replacement");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);
        auto arg2 = __args.get(2);

        if(arg0->canBeCollective())
        {
            ColPtr val = colCast(arg0->ptr());

            val->replace(*arg1, *arg2);
        }
        else throwArgumentException("replace", "String/List, Any, Any");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::reverse(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "reverse", "String/List value");

        auto arg0 = __args.get(0);

        if(arg0->canBeCollective()) colCast(arg0->ptr())->reverse();
        
        else throwArgumentException("reverse", "String/List");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::rIndex(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(2, "rindex", "String/List value, Any value_to_search");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);

        if(arg0->canBeCollective())
        {
            ColPtr val = colCast(arg0->ptr());

            return GarbageCollector::registerInt(val->rIndex(*arg1));
        }
        else throwArgumentException("rindex", "String/List, Any");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::sort(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "sort", "String/List value");

        auto arg0 = __args.get(0);

        if(arg0->canBeCollective()) colCast(arg0->ptr())->sort();
        
        else throwArgumentException("sort", "String/List");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::reverseSort(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(1, "reverseSort", "String/List value");

        auto arg0 = __args.get(0);

        if(arg0->canBeCollective()) colCast(arg0->ptr())->reverseSort();
        
        else throwArgumentException("reverseSort", "String/List");

        return Void::void_object;
    }

    inline static AnyBindPtr Sron::subPart(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(3, "subPart", "Any value, Int start_position, Int end_position");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);
        auto arg2 = __args.get(2);

        if(arg0->canBeCollective() && arg1->type() == SronTypeNum::TYPE_INT && arg2->type() == SronTypeNum::TYPE_INT)
        {
            ColPtr val = colCast(arg0->ptr());
            IntPtr start_pos = intCast(arg1->ptr());
            IntPtr end_pos = intCast(arg2->ptr());

            return val->subPart(*start_pos, *end_pos);
        }
        else throwArgumentException("subPart", "String/List, Int , Int");
    }




inline static AnyBindPtr Sron::update(ArgumentList &__args)
    {
        CHECK_ARGS_COUNT(3, "update", "String/List value, Int index, Any value_to_put");

        auto arg0 = __args.get(0);
        auto arg1 = __args.get(1);
        auto arg2 = __args.get(2);

        if(arg0->canBeCollective() && arg1->type() == SronTypeNum::TYPE_INT)
        {
            ColPtr val = colCast(arg0->ptr());
            
            Int *index = intCast(arg1->ptr());
            
            val->update(*index, *arg2 );
        }
        else throwArgumentException("update", "String/List, Int");

        return Void::void_object;
    }

#endif