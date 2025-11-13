#pragma once

#ifndef _LIST_H
#define _LIST_H

#include "_Bool_.hpp"

/*
  |====================== List ===============================|
 'List' datatype uses std::vector<Any*> to store values.
  > It is dynamic in size as well as in nature so it can store values of different datatype in a single entity. It can store List too but not itself.
  > Syntax in SRON : "List x = [1,123.678, true, false, "Heelo", 'Q' ]" or "List x" or "List x = []"
*/

inline List::List(const List::SronList_t& __val)
{
    for(auto& i : __val) this->pushWithoutCopy(i->ptr()->copy() , i->type());
}
inline List::List(List &__val)
{
    for(auto& i : __val.value) this->pushWithoutCopy(i->ptr()->copy() , i->type() );
}

inline List::List( List&& __list ) : value( std::move( __list.value)) , layer( __list.layer ) 
{ }

inline List::List(AnyPtr __value)
{
    this->push( __value );
}

inline AnyPtr List::copy() const
{
    return new List(this->value);
}

inline void List::print() const
{
    SronOBuffer buffer;

    this->fillObuffer( buffer );

    buffer.flush();
}

inline void List::formatPrint() const
{
    this->print();
}

inline SronTypeNum List::typeNum() const
{
    return SronTypeNum::TYPE_LIST;
}

inline void List::preMove()
{

    --(this->layer);
    this->updateLayerOfAllElements();
}

inline void List::fillObuffer(SronOBuffer& __buffer) const
{
    if ( this->value.empty() )
    {
        __buffer.append("[]" , 2);
        return;
    }

    __buffer << '[';

    List::SronList_t::const_iterator it = this->value.begin();
    List::SronList_t::const_iterator end = this->value.end() - 1;

    auto prepare_buffer = [ &__buffer , &it ] ( ) {

        switch ( (*it)->type() )
        {
            case SronTypeNum::TYPE_CHAR :   __buffer << '\'' << **charCast( (*it)->ptr())    << '\'' ; break;

            case SronTypeNum::TYPE_STRING : __buffer << '\"' << **stringCast( (*it)->ptr() ) << '\"' ; break;

            default : (*it)->ptr()->fillObuffer( __buffer );
        }
    };

    for (; it != end; ++it)
    {
        prepare_buffer();
        __buffer << ", ";
    }

    prepare_buffer();

    __buffer << ']';
}

inline long long int List::sizeOf() const
{
    long long int size = 0;
    for (const auto &i : this->value)
    {
        size += i->ptr()->sizeOf();
    }
    return size;
}

inline bool List::isCollective() const
{
    return true;
}

inline const char *List::type() const
{
    return "List";
}

inline void List::type(std::string &str) const
{
    str.append("List");
}

inline ListPtr List::getList() const
{
    return const_cast<ListPtr>(this);
}

inline ColPtr List::getCollective() const
{
    return (ColPtr)(this);
}

inline AnyBindPtr List::at(size_t __index) const
{
    return this->value[__index];
}

inline void List::clear()
{
    GarbageCollector::__garbageStack[ this->layer ].push( new List( std::move( this->value )));
}

inline void List::push(AnyPtr val)
{
    this->pushWithoutCopy(val->copy() , val->typeNum());
}

inline void List::pushWithoutCopy(AnyPtr __val , SronTypeNum __type)
{
    this->value.push_back(new AnyBind( __val, __type, this->layer));
}

inline AnyBindPtr List::at(Int &index)
{

    throwExceptionIfIndexOutOfBound(*index, this->value.size(), "extraction", "List");

    return this->value.at(*index);
}

inline long long int List::count(Any &val)
{

    long long int _count = 0;

    SronTypeNum type_of_val = val.typeNum();

    for (auto &i : this->value)
    {
        _count += ((i->ptr()->__isEqual__(val,type_of_val)) ? 1 : 0);
    }

    return _count;
}

inline void List::drop(Int &index)
{
    throwExceptionIfIndexOutOfBound(*index, this->value.size(), "deletion", "List");

    auto pos = this->value.begin() + (*index);

    GarbageCollector::registerAt( (*pos)->layer() , (*pos)->ptr() , (*pos)->type() );

    *pos = nullptr;

    this->value.erase(pos);
}

inline long long int List::index(Any &val) const
{
    long long int __index = 0;

    SronTypeNum type_of_val = val.typeNum();

    for (const auto &i : this->value)
    {
        if (i->ptr()->__isEqual__(val , type_of_val))
        {
            return __index;
        }

        ++__index;
    }

    return -1;
}

inline void List::insert(Int &index, AnyPtr &val)
{

    throwExceptionIfIndexOutOfBound(*index, this->value.size(), "insertion", "List");

    this->value.insert((this->value.begin() + (*index)), new AnyBind(val->copy() , val->typeNum(), this->layer));
}

inline size_t List::LEN() const
{
    return this->value.size();
}

inline AnyBindPtr List::pop()
{
    if (this->value.size() == 0)
    {
        throw ThrowException("performing 'pop' operation on value of type 'List'. Size of List is 0 that's why this exception is raised");
    }

    auto last_value = this->value.back()->ptr();

    auto last_value_type = this->value.back()->type();

    this->value.back()->set( nullptr , SronTypeNum::INVALID_TYPE);

    this->value.pop_back();

    return GarbageCollector::registerMemory(last_value , last_value_type);
    
}

inline void List::replace(Any &replacer, Any &replacement)
{
    ListPtr list = new List();

    SronTypeNum type_of_replacement = replacement.typeNum();

    SronTypeNum type_of_replacer = replacer.typeNum();

    for( auto it : this->value )
    {
        if (it->ptr()->__isEqual__(replacer, type_of_replacer))
        {
            /*
               Registering the memory to the garbage collector 
               so if some another values has stored it, the 
               code will not go halt but will be stable.
            */
            list->pushWithoutCopy( it->ptr() , it->type() );

            it->set(replacement.copy(), type_of_replacement);
        }
    }

    if ( list->value.empty() ) delete list;

    else GarbageCollector::registerAt( this->layer , list, SronTypeNum::TYPE_LIST);
}

inline void List::reverse()
{
    std::reverse(this->value.begin(), this->value.end());
}

inline long long int List::rIndex(Any &val) const
{
    SronTypeNum type_of_val = val.typeNum();

    for (auto it = this->value.end() - 1; it >= this->value.begin(); --it)
    {
        if ((*it)->ptr()->__isEqual__(val , type_of_val))
        {
            return it - this->value.begin();
        }
    }

    return -1;
}

inline void List::sort()
{
    std::sort(this->value.begin(), this->value.end(), [](AnyBindPtr __val1, AnyBindPtr __val2){
        return (__val1->ptr()->__lessThan__( **__val2 , __val2->type()));
    });
}

inline void List::reverseSort()
{
    std::sort(this->value.begin(), this->value.end(), [](AnyBindPtr __val1 , AnyBindPtr __val2){
        return (__val1->ptr()->__moreThan__( **__val2 , __val2->type()));
    });
}

inline AnyBindPtr List::subPart(Int &start_index, Int &end_index) 
{
    throwExceptionIfIndexOutOfBound(*start_index, this->value.size(), "extraction", "List");
    throwExceptionIfIndexOutOfBound(*end_index, this->value.size(), "extraction", "List");

    auto i_1 = this->value.begin() + *start_index;
    auto i_2 = this->value.begin() + *end_index;

    ListPtr lst = new List();

    for (; i_1 < i_2; ++i_1)
    {
        lst->push((*i_1)->ptr());
    }

    return GarbageCollector::registerMemory(lst , SronTypeNum::TYPE_LIST);
}


inline void List::update(Int &index, Any &val)
{
    throwExceptionIfIndexOutOfBound(*index, this->value.size(), "updation", "List");

    auto value = this->value[*index];

    GarbageCollector::registerAt( this->layer , value->ptr() , value->type() );

    value->set(val.copy());
}

inline AnyPtr List::__add__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_STRING: return new String(this->toString().append(__val.toString()));

        case SronTypeNum::TYPE_LIST: {
            ListPtr lst = new List(this->value);
            lst->APPENDS(*listCast( &__val));
            return lst; }

        default : mathEvaluationException("+", "List", __val.type());
    }

    return nullptr;
}

inline SronBool_t List::__isEqual__(Any &__val , SronTypeNum __type) const
{
    if (this->typeNum() == __type && this->LEN() == listCast( &__val )->LEN())
    {

        auto _end = this->value.end();

        auto i1 = this->value.begin();
        auto i2 = listCast( &__val )->value.begin();

        for (; i1 < _end; ++i1, ++i2)
        {
            if ((*i1)->ptr()->__notEqual__(***i2 , (*i2)->type()))
            {
                return false;
            }
        }

        return true;
    }
    return false;
}

inline SronBool_t List::__notEqual__(Any &__val , SronTypeNum __type) const
{
    if (this->typeNum() == __type && this->LEN() == listCast( &__val)->LEN())
    {

        auto _end = this->value.end();

        auto i1 = this->value.begin();
        auto i2 = listCast( &__val)->value.begin();

        for (; i1 < _end; ++i1, ++i2)
        {
            if ((*i1)->ptr()->__isEqual__(***i2 , (*i2)->type()))
            {
                return false;
            }
        }

        return true;
    }
    return true;
}

inline SronBool_t List::__lessThan__(Any &__val , SronTypeNum __type) const
{
    if (this->typeNum() == __type)
    {
        auto value = listCast( &__val );

        if (this->LEN() != value->LEN()) return this->LEN() < value->LEN();
        
        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values

        const auto _end = this->value.end();

        auto it1 = this->value.begin();

        auto it2 = value->value.begin();

        for( ; it1 < _end ; ++it1, ++it2 ){

            // if any of the 
            if((*it1)->ptr()->__lessThan__(***it2, (*it2)->type()))
            {
                return true;
            }
        }

        return false;
    }

    return this->typeNum() < __type;
}

inline SronBool_t List::__lessEqual__(Any &__val , SronTypeNum __type) const
{

    if (this->typeNum() == __type)
    {
        auto value = listCast( &__val );

        // return length of both values are not equal, then performing less than or equal between their length
        if (this->LEN() != value->LEN())
        {
            return this->LEN() <= value->LEN();
        }

        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values

        auto it = value->value.begin();

        for( auto& i : this->value )
        {
            if (!( i->ptr()->__lessEqual__(***it, (*it)->type()))) return false;

            ++it;
        }

        return true;
    }

    return this->typeNum() <= __type;
}

inline SronBool_t List::__moreThan__(Any &__val , SronTypeNum __type) const
{
    if (this->typeNum() == __type)
    {
        auto value = listCast( &__val );

        // return this->LEN() < val.getCollective()->LEN();
        if (this->LEN() != value->LEN())
        {
            return this->LEN() > value->LEN();
        }

        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values
        auto it =  value->value.begin();

        for( auto& i : this->value )
        {
            if (!( i->ptr()->__moreThan__( ***it, (*it)->type() ) )) return false;

            ++it;
        }

        return true;
    }

    return this->typeNum() > __type;
}

inline SronBool_t List::__moreEqual__(Any &__val , SronTypeNum __type) const
{
    if (this->typeNum() == __type)
    {

        auto value = listCast( &__val );

        // return this->LEN() < val.getCollective()->LEN();
        if (this->LEN() != value->LEN())
        {
            return this->LEN() >= value->LEN();
        }

        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values
        auto it = value->value.begin();

        for ( auto& i : this->value )
        {
            if ( ! ( i->ptr()->__moreEqual__( ***it , (*it)->type())) ) return false;
        }

        return false;
    }

    return this->typeNum() >= __type;
}

inline void List::__addAssign__(Any &__val , SronTypeNum __type)
{
    this->pushWithoutCopy(__val.copy() , __type);
}
inline auto &List::operator*()
{
    return this->value;
}

inline List &List::operator=(List &&__other) noexcept
{

    if (this != &__other)
    {

        this->value = std::move(__other.value);

    }

    return *this;
}

inline void List::APPENDS(List& __val)
{
    for(auto& i : __val.value) this->pushWithoutCopy(i->ptr()->copy() , i->type()); 
}

inline void List::push( AnyPtr __ptr , SronTypeNum __type )
{
    this->pushWithoutCopy( __ptr->copy() , __type);
}

inline List::~List() noexcept
{
    for( auto ptr : this->value ) delete ptr;
}

#endif