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

inline List::List(GcSize_t __layer = GarbageCollector::__gcStackTopLoc) : layer(__layer) {}

inline List::List(const List::SronList_t& __val)
{
    
    for(auto& i : __val)
    {
        this->value.push_back(new AnyBind(i->ptr_->COPY(), this->layer));
    }
}
inline List::List(List &__val)
{
    for(auto& i : __val.value)
    {
        this->PUSH(i->ptr_);
    }
}

inline List::List(AnyPtr a)
{
    this->value.push_back(new AnyBind(a->COPY(), this->layer));
}

inline AnyPtr List::COPY() const
{
    return new List(this->value);
}

inline void List::PRINT() const
{
    if (this->value.size() == 0)
    {
        std::cout << "[]";
        return;
    }

    std::cout << "[";

    List::SronList_t::const_iterator it = this->value.begin();

    for (; it != this->value.end() - 1; ++it)
    {
        (*it)->ptr_->F_PRINT();
        std::cout << ", ";
    }

    (*it)->ptr_->F_PRINT();

    std::cout << "]";
}

inline void List::F_PRINT() const
{
    this->PRINT();
}

inline const unsigned short int List::TYPE_NUMBER() const
{
    return TYPE_LIST;
}

inline void List::PREMOVE()
{

    --(this->layer);
    this->UPDATE_LAYER_OF_ALL_ELEMENTS();
}

inline long long int List::SIZE_OF() const
{
    long long int size = 0;
    for (const auto &i : this->value)
    {
        size += i->ptr_->SIZE_OF();
    }
    return size;
}

inline bool List::IS_COLLECTIVE() const
{
    return true;
}


//
inline const char *List::TYPE() const
{
    return "List";
}

//
inline void List::TYPE(std::string &str) const
{
    str.append("List");
}

//
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

//
inline void List::CLEAR()
{
    for(auto& i : this->value){
        
        GarbageCollector::REGISTER_AT(*i, i->layer_);
    }

    this->value.clear();
}

//
inline void List::PUSH(AnyPtr val)
{
    this->PUSH_WITHOUT_COPY(val->COPY());
}

//
inline void List::PUSH_WITHOUT_COPY(AnyPtr val)
{
    this->value.push_back(new AnyBind(val, this->layer));
}

//
inline AnyBindPtr List::AT(Int &index)
{

    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.size(), "extraction", "List");

    return this->value.at(*index);
}

//
inline long long int List::COUNT(Any &val)
{

    long long int _count = 0;

    for (auto &i : this->value)
    {
        _count += ((i->ptr_->__IS_EQUAL__(val)) ? 1 : 0);
    }

    return _count;
}

//
inline void List::DELETE_(Int &index)
{
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.size(), "deletion", "List");

    auto pos = this->value.begin() + (*index);

    GarbageCollector::REGISTER_AT(**pos, (*pos)->layer_);

    this->value.erase(pos);
}

//
inline long long int List::INDEX(Any &val) const
{
    long long int __index = 0;

    for (const auto &i : this->value)
    {
        if (i->ptr_->__IS_EQUAL__(val))
        {
            return __index;
        }

        ++__index;
    }

    return -1;
}

//
inline void List::INSERT(Int &index, AnyPtr &val)
{

    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.size(), "insertion", "List");

    this->value.insert((this->value.begin() + (*index)), new AnyBind(val->COPY(), this->layer));

}

//
inline size_t List::LEN() const
{
    return this->value.size();
}

//
inline AnyBindPtr List::POP()
{
    if (this->value.size() == 0)
    {
        throw ThrowException("performing 'pop' operation on value of type 'List'. Size of List is 0 that's why this exception is raised");
    }

    auto last_value = this->value.back()->ptr_;

    this->value.back()->ptr_ = nullptr;

    this->value.pop_back();

    return GarbageCollector::REGISTER_MEMORY(last_value);
    
}

//
inline void List::REPLACE(Any &replacer, Any &replacement)
{
    auto end__ = this->value.end();

    for (auto it = this->value.begin(); it != end__; ++it)
    {
        if ((*it)->ptr_->__IS_EQUAL__(replacer))
        {
            /*
               Registering the memory to the garbage collector 
               so if some another values has stored it, the 
               code will not go halt but will be stable.
            */
            GarbageCollector::REGISTER_AT(**it, (*it)->layer_);

            (*it)->ptr_ = replacement.COPY();
        }
    }
}

//
inline void List::REVERSE()
{
    std::reverse(this->value.begin(), this->value.end());
}

//
inline long long int List::RINDEX(Any &val) const
{

    for (auto it = this->value.end() - 1; it >= this->value.begin(); --it)
    {
        if ((*it)->ptr_->__IS_EQUAL__(val))
        {
            return it - this->value.begin();
        }
    }

    return -1;
}


inline void List::SET(AnyBind &val)
{
    if (val->TYPE_NUMBER() != this->TYPE_NUMBER())
    {

        throw ThrowException("setting a new value to type 'List'", ArgumentException);
    }

    this->CLEAR();

    for (auto &i : val->GET_LIST()->value)
    {
        this->PUSH(i->ptr_);
    }


}

//
inline void List::SORT()
{

    std::sort(this->value.begin(), this->value.end(), [](AnyBindPtr __val1, AnyBindPtr __val2)
              { return List::_ASCENDING_SORT_ROUTINE_METHOD_(**__val1, **__val2); });
}

inline void List::REVERSE_SORT(){
    std::sort(this->value.begin(), this->value.end(), [](AnyBindPtr __val1 , AnyBindPtr __val2){
        return List::_DESCENDING_SORT_ROUTINE_METHOD_(**__val1, **__val2);
    });
}

//
inline AnyBindPtr List::SUBPART(Int &start_index, Int &end_index) 
{
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*start_index, this->value.size(), "extraction", "List");
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*end_index, this->value.size(), "extraction", "List");

    auto i_1 = this->value.begin() + *start_index;
    auto i_2 = this->value.begin() + *end_index;

    ListPtr lst = new List();

    for (; i_1 < i_2; ++i_1)
    {
        lst->PUSH((*i_1)->ptr_);
    }

    return GarbageCollector::REGISTER_MEMORY(lst);
}

//
inline void List::UPDATE(Int &index, Any &val)
{
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.size(), "updation", "List");

    auto& value = this->value[*index];

    GarbageCollector::REGISTER_AT(*value, value->layer_);

    (this->value[*index])->ptr_ = val.COPY();
}

inline AnyPtr List::__ADD__(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {
    case TYPE_STRING:
        return new String(this->TO_STRING().append(val.TO_STRING()));

    case TYPE_LIST:
        ListPtr lst = new List(this->value);
        lst->APPENDS(*(val.GET_LIST()));
        return lst;
    }

    MATH_EVALUATION_EXCEPTION("+", "List", val.TYPE());

    return nullptr;
}

inline bool List::__IS_EQUAL__(Any &val) const
{
    if (this->TYPE_NUMBER() == val.TYPE_NUMBER() && this->LEN() == val.GET_LIST()->LEN())
    {

        auto _end = this->value.end();

        auto i1 = this->value.begin();
        auto i2 = val.GET_LIST()->value.begin();

        for (; i1 < _end; ++i1, ++i2)
        {
            if ((*i1)->ptr_->__NOT_EQUAL__(***i2))
            {
                return false;
            }
        }

        return true;
    }
    return false;
}

inline bool List::__NOT_EQUAL__(Any &val) const
{
    if (this->TYPE_NUMBER() == val.TYPE_NUMBER() && this->LEN() == val.GET_LIST()->LEN())
    {

        auto _end = this->value.end();

        auto i1 = this->value.begin();
        auto i2 = val.GET_LIST()->value.begin();

        for (; i1 < _end; ++i1, ++i2)
        {
            if ((*i1)->ptr_->__IS_EQUAL__(***i2))
            {
                return false;
            }
        }

        return true;
    }
    return true;
}

inline bool List::__LESS_THAN__(Any &val) const
{
    if (this->TYPE_NUMBER() == val.TYPE_NUMBER())
    {
        // return 
        if (this->LEN() != val.GET_COLLECTIVE()->LEN())
        {
            return this->LEN() < val.GET_COLLECTIVE()->LEN();
        }

        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values

        const auto _end = this->value.end();

        auto it1 = this->value.begin();

        auto it2 = val.GET_COLLECTIVE()->GET_LIST()->value.begin();

        for( ; it1 < _end ; ++it1, ++it2 ){

            // if any of the 
            if((*it1)->ptr_->__LESS_THAN__(***it2))
            {
                return true;
            }
        }

        return false;
    }

    return this->TYPE_NUMBER() < val.TYPE_NUMBER();
}

inline bool List::__LESS_THAN_EQUAL__(Any &val) const
{

    if (this->TYPE_NUMBER() == val.TYPE_NUMBER())
    {
        // return length of both values are not equal, then performing less than or equal between their length
        if (this->LEN() != val.GET_COLLECTIVE()->LEN())
        {
            return this->LEN() <= val.GET_COLLECTIVE()->LEN();
        }

        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values

        const auto _end = this->value.end();

        auto it1 = this->value.begin();

        auto it2 = val.GET_COLLECTIVE()->GET_LIST()->value.begin();

        for( ; it1 < _end ; ++it1, ++it2 ){

            // if any of the 
            if((*it1)->ptr_->__LESS_THAN_EQUAL__(***it2))
            {
                return true;
            }
        }

        return false;
    }

    return this->TYPE_NUMBER() <= val.TYPE_NUMBER();
}

inline bool List::__MORE_THAN__(Any &val) const
{
    if (this->TYPE_NUMBER() == val.TYPE_NUMBER())
    {
        // return this->LEN() < val.GET_COLLECTIVE()->LEN();
        if (this->LEN() != val.GET_COLLECTIVE()->LEN())
        {
            return this->LEN() > val.GET_COLLECTIVE()->LEN();
        }

        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values

        const auto _end = this->value.end();

        auto it1 = this->value.begin();

        auto it2 = val.GET_COLLECTIVE()->GET_LIST()->value.begin();

        for( ; it1 < _end ; ++it1, ++it2 ){

            // if any of the 
            if((*it1)->ptr_->__MORE_THAN__(***it2))
            {
                return true;
            }
        }

        return false;
    }

    return this->TYPE_NUMBER() > val.TYPE_NUMBER();
}

inline bool List::__MORE_THAN_EQUAL__(Any &val) const
{
    if (this->TYPE_NUMBER() == val.TYPE_NUMBER())
    {
        // return this->LEN() < val.GET_COLLECTIVE()->LEN();
        if (this->LEN() != val.GET_COLLECTIVE()->LEN())
        {
            return this->LEN() >= val.GET_COLLECTIVE()->LEN();
        }

        // here, it is confirmed that both values has same type and same length,
        // now to compare both of them, we need to values

        const auto _end = this->value.end();

        auto it1 = this->value.begin();

        auto it2 = val.GET_COLLECTIVE()->GET_LIST()->value.begin();

        for( ; it1 < _end ; ++it1, ++it2 ){

            // if any of the 
            if((*it1)->ptr_->__MORE_THAN_EQUAL__(***it2))
            {
                return true;
            }
        }

        return false;
    }

    return this->TYPE_NUMBER() >= val.TYPE_NUMBER();
}

inline void List::__ADD_AND_ASSIGN__(Any &val)
{
    this->PUSH_WITHOUT_COPY(val.COPY());
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

inline void List::APPENDS(List& __val){

    for(auto& i : __val.value)
    {
        this->PUSH(i->ptr_);
    }
}

inline List::~List() noexcept
{
    for(auto& i : this->value){
        delete i;
    }
    this->value.clear();
}

#endif