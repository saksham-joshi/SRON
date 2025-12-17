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
    for(auto& i : __val) this->PUSH_WITHOUT_COPY(i->ptr()->COPY() , i->type());
}
inline List::List(List &__val)
{
    for(auto& i : __val.value) this->PUSH_WITHOUT_COPY(i->ptr()->COPY() , i->type() );
}

inline List::List( List&& __list ) : value( std::move( __list.value)) , layer( __list.layer ) 
{ }

inline List::List(AnyPtr __value)
{
    this->PUSH( __value );
}

inline AnyPtr List::COPY() const
{
    return new List(this->value);
}

inline void List::PRINT() const
{
    SronOBuffer buffer;

    this->FILL_OBUFFER( buffer );

    buffer.flush();
}

inline void List::F_PRINT() const
{
    this->PRINT();
}

inline SronTypeNum List::TYPE_NUMBER() const
{
    return SronTypeNum::TYPE_LIST;
}

inline void List::PREMOVE()
{

    --(this->layer);
    this->UPDATE_LAYER_OF_ALL_ELEMENTS();
}

inline void List::FILL_OBUFFER(SronOBuffer& __buffer) const
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
            case TYPE_CHAR :   __buffer << '\'' << **charCast( (*it)->ptr())    << '\'' ; break;

            case TYPE_STRING : __buffer << '\"' << **stringCast( (*it)->ptr() ) << '\"' ; break;

            default : (*it)->ptr()->FILL_OBUFFER( __buffer );
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

inline long long int List::SIZE_OF() const
{
    long long int size = 0;
    for (const auto &i : this->value)
    {
        size += i->ptr()->SIZE_OF();
    }
    return size;
}

inline bool List::IS_COLLECTIVE() const
{
    return true;
}

inline const char *List::TYPE() const
{
    return "List";
}

inline void List::TYPE(std::string &str) const
{
    str.append("List");
}

inline ListPtr List::GET_LIST() const
{
    return const_cast<ListPtr>(this);
}

inline ColPtr List::GET_COLLECTIVE() const
{
    return (ColPtr)(this);
}

inline AnyBindPtr List::AT(size_t __index) const
{
    return this->value[__index];
}

inline void List::CLEAR()
{
    GarbageCollector::__garbageStack[ this->layer ].push( new List( std::move( this->value )));
}

inline void List::PUSH(AnyPtr val)
{
    this->PUSH_WITHOUT_COPY(val->COPY() , val->TYPE_NUMBER());
}

inline void List::PUSH_WITHOUT_COPY(AnyPtr __val , SronTypeNum __type)
{
    this->value.push_back(new AnyBind( __val, __type, this->layer));
}

inline AnyBindPtr List::AT(Int &index)
{

    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.size(), "extraction", "List");

    return this->value.at(*index);
}

inline long long int List::COUNT(Any &val)
{

    long long int _count = 0;

    SronTypeNum type_of_val = val.TYPE_NUMBER();

    for (auto &i : this->value)
    {
        _count += ((i->ptr()->__IS_EQUAL__(val,type_of_val)) ? 1 : 0);
    }

    return _count;
}

inline void List::DELETE_(Int &index)
{
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.size(), "deletion", "List");

    auto pos = this->value.begin() + (*index);

    GarbageCollector::REGISTER_AT( (*pos)->layer() , (*pos)->ptr() , (*pos)->type() );

    *pos = nullptr;

    this->value.erase(pos);
}

inline long long int List::INDEX(Any &val) const
{
    long long int __index = 0;

    SronTypeNum type_of_val = val.TYPE_NUMBER();

    for (const auto &i : this->value)
    {
        if (i->ptr()->__IS_EQUAL__(val , type_of_val))
        {
            return __index;
        }

        ++__index;
    }

    return -1;
}

inline void List::INSERT(Int &index, AnyPtr &val)
{

    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.size(), "insertion", "List");

    this->value.insert((this->value.begin() + (*index)), new AnyBind(val->COPY() , val->TYPE_NUMBER(), this->layer));
}

inline size_t List::LEN() const
{
    return this->value.size();
}

inline AnyBindPtr List::POP()
{
    if (this->value.size() == 0)
    {
        throw ThrowException("performing 'pop' operation on value of type 'List'. Size of List is 0 that's why this exception is raised");
    }

    auto last_value = this->value.back()->ptr();

    auto last_value_type = this->value.back()->type();

    this->value.back()->set( nullptr , SronTypeNum::INVALID_TYPE);

    this->value.pop_back();

    return GarbageCollector::REGISTER_MEMORY(last_value , last_value_type);
    
}

inline void List::REPLACE(Any &replacer, Any &replacement)
{
    ListPtr list = new List();

    SronTypeNum type_of_replacement = replacement.TYPE_NUMBER();

    SronTypeNum type_of_replacer = replacer.TYPE_NUMBER();

    for( auto it : this->value )
    {
        if (it->ptr()->__IS_EQUAL__(replacer, type_of_replacer))
        {
            /*
               Registering the memory to the garbage collector 
               so if some another values has stored it, the 
               code will not go halt but will be stable.
            */
            list->PUSH_WITHOUT_COPY( it->ptr() , it->type() );

            it->set(replacement.COPY(), type_of_replacement);
        }
    }

    if ( list->value.empty() ) delete list;

    else GarbageCollector::REGISTER_AT( this->layer , list, SronTypeNum::TYPE_LIST);
}

inline void List::REVERSE()
{
    std::reverse(this->value.begin(), this->value.end());
}

inline long long int List::RINDEX(Any &val) const
{
    SronTypeNum type_of_val = val.TYPE_NUMBER();

    for (auto it = this->value.end() - 1; it >= this->value.begin(); --it)
    {
        if ((*it)->ptr()->__IS_EQUAL__(val , type_of_val))
        {
            return it - this->value.begin();
        }
    }

    return -1;
}

inline void List::SORT()
{
    std::sort(this->value.begin(), this->value.end(), [](AnyBindPtr __val1, AnyBindPtr __val2){
        return (__val1->ptr()->__LESS_THAN__( **__val2 , __val2->type()));
    });
}

inline void List::REVERSE_SORT()
{
    std::sort(this->value.begin(), this->value.end(), [](AnyBindPtr __val1 , AnyBindPtr __val2){
        return (__val1->ptr()->__MORE_THAN__( **__val2 , __val2->type()));
    });
}

inline AnyBindPtr List::SUBPART(Int &start_index, Int &end_index) 
{
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*start_index, this->value.size(), "extraction", "List");
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*end_index, this->value.size(), "extraction", "List");

    auto i_1 = this->value.begin() + *start_index;
    auto i_2 = this->value.begin() + *end_index;

    ListPtr lst = new List();

    for (; i_1 < i_2; ++i_1)
    {
        lst->PUSH((*i_1)->ptr());
    }

    return GarbageCollector::REGISTER_MEMORY(lst , SronTypeNum::TYPE_LIST);
}


inline void List::UPDATE(Int &index, Any &val)
{
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.size(), "updation", "List");

    auto value = this->value[*index];

    GarbageCollector::REGISTER_AT( this->layer , value->ptr() , value->type() );

    value->set(val.COPY());
}

inline AnyPtr List::__ADD__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case TYPE_STRING: return new String(this->TO_STRING().append(__val.TO_STRING()));

        case TYPE_LIST: {
            ListPtr lst = new List(this->value);
            lst->APPENDS(*listCast( &__val));
            return lst; }

        default : MATH_EVALUATION_EXCEPTION("+", "List", __val.TYPE());
    }

    return nullptr;
}

inline SronBool_t List::__IS_EQUAL__(Any &__val , SronTypeNum __type) const
{
    if (this->TYPE_NUMBER() == __type && this->LEN() == listCast( &__val )->LEN())
    {

        auto _end = this->value.end();

        auto i1 = this->value.begin();
        auto i2 = listCast( &__val )->value.begin();

        for (; i1 < _end; ++i1, ++i2)
        {
            if ((*i1)->ptr()->__NOT_EQUAL__(***i2 , (*i2)->type()))
            {
                return false;
            }
        }

        return true;
    }
    return false;
}

inline SronBool_t List::__NOT_EQUAL__(Any &__val , SronTypeNum __type) const
{
    if (this->TYPE_NUMBER() == __type && this->LEN() == listCast( &__val)->LEN())
    {

        auto _end = this->value.end();

        auto i1 = this->value.begin();
        auto i2 = listCast( &__val)->value.begin();

        for (; i1 < _end; ++i1, ++i2)
        {
            if ((*i1)->ptr()->__IS_EQUAL__(***i2 , (*i2)->type()))
            {
                return false;
            }
        }

        return true;
    }
    return true;
}

inline SronBool_t List::__LESS_THAN__(Any &__val , SronTypeNum __type) const
{
    if (this->TYPE_NUMBER() == __type)
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
            if((*it1)->ptr()->__LESS_THAN__(***it2, (*it2)->type()))
            {
                return true;
            }
        }

        return false;
    }

    return this->TYPE_NUMBER() < __type;
}

inline SronBool_t List::__LESS_THAN_EQUAL__(Any &__val , SronTypeNum __type) const
{

    if (this->TYPE_NUMBER() == __type)
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
            if (!( i->ptr()->__LESS_THAN_EQUAL__(***it, (*it)->type()))) return false;

            ++it;
        }

        return true;
    }

    return this->TYPE_NUMBER() <= __type;
}

inline SronBool_t List::__MORE_THAN__(Any &__val , SronTypeNum __type) const
{
    if (this->TYPE_NUMBER() == __type)
    {
        auto value = listCast( &__val );

        // return this->LEN() < val.GET_COLLECTIVE()->LEN();
        if (this->LEN() != value->LEN())
        {
            return this->LEN() > value->LEN();
        }

        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values
        auto it =  value->value.begin();

        for( auto& i : this->value )
        {
            if (!( i->ptr()->__MORE_THAN__( ***it, (*it)->type() ) )) return false;

            ++it;
        }

        return true;
    }

    return this->TYPE_NUMBER() > __type;
}

inline SronBool_t List::__MORE_THAN_EQUAL__(Any &__val , SronTypeNum __type) const
{
    if (this->TYPE_NUMBER() == __type)
    {

        auto value = listCast( &__val );

        // return this->LEN() < val.GET_COLLECTIVE()->LEN();
        if (this->LEN() != value->LEN())
        {
            return this->LEN() >= value->LEN();
        }

        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values
        auto it = value->value.begin();

        for ( auto& i : this->value )
        {
            if ( ! ( i->ptr()->__MORE_THAN_EQUAL__( ***it , (*it)->type())) ) return false;
        }

        return false;
    }

    return this->TYPE_NUMBER() >= __type;
}

inline void List::__ADD_AND_ASSIGN__(Any &__val , SronTypeNum __type)
{
    this->PUSH_WITHOUT_COPY(__val.COPY() , __type);
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
    for(auto& i : __val.value) this->PUSH_WITHOUT_COPY(i->ptr()->COPY() , i->type()); 
}

inline void List::PUSH( AnyPtr __ptr , SronTypeNum __type )
{
    this->PUSH_WITHOUT_COPY( __ptr->COPY() , __type);
}

inline List::~List() noexcept
{
    for( auto ptr : this->value ) delete ptr;
}

#endif