#pragma once

#ifndef _STRING_H
#define _STRING_H

#include "_List_.hpp"

/*
  |====================== String ===============================|
 'String' datatype uses std::string to store values.
  > string are dynamic in size so its size depends on the number of characters it stores.
  > Syntax in SRON : 'String x = "SRON is the Best" ' or "String x"
*/
inline String::String() {}

inline String::String(SronChar_t ch)
{
    this->value.push_back(ch);
}

inline String::String(const char*const __str, unsigned int __len ) : value( __str, __len) { }

inline String::String(const char *const str) : value(str) {}

inline String::String(const std::string &str) : value(str) {}

inline String::String(std::string&& __str) : value(__str) {}

// returns the pointer of String
inline AnyPtr String::COPY() const
{
    return new String(this->value);
}

// returns the length of the String
inline size_t String::LEN() const
{
    return this->value.length();
}

// prints the value on the terminal
inline void String::PRINT() const
{
    printf_s("%s", this->value.c_str());
}

// prints the String value with double quotes.
inline void String::F_PRINT() const
{
    printf_s("\"%s\"", this->value.c_str());
}

inline void String::PREMOVE(){ }

inline void String::FILL_OBUFFER(SronOBuffer& __buffer) const
{
    __buffer.append( this->value.c_str() , this->value.length() );
}

// returns the size in bytes of the value
inline long long int String::SIZE_OF() const
{
    return sizeof(this->value);
}

// returns the
inline std::string String::TO_STRING() const
{
    return this->value;
}

inline bool String::IS_COLLECTIVE() const
{
    return true;
}


// return the type
inline const char *String::TYPE() const
{
    return "String";
}

// appends the "String" to the passed std::string
inline void String::TYPE(std::string &str) const
{
    str.append("String");
}

// returns the type number used for identifying the type of the value efficiently.
inline SronTypeNum String::TYPE_NUMBER() const
{
    return SronTypeNum::TYPE_STRING;
}

// returns the StringPtr
inline StringPtr String::GET_STRING() const
{
    return const_cast<StringPtr>(this);
}

inline ListPtr String::GET_LIST() const
{
    ListPtr lst = new List();

    for (const auto &i : this->value)
    {
        lst->PUSH_WITHOUT_COPY(new Char(i) , SronTypeNum::TYPE_CHAR);
    }

    GarbageCollector::REGISTER_MEMORY(lst , SronTypeNum::TYPE_LIST);

    return lst;
}

inline ColPtr String::GET_COLLECTIVE() const
{

    return (ColPtr)this;
}

inline AnyBindPtr String::AT(size_t __index) const
{
    return GarbageCollector::REGISTER_MEMORY(new Char(this->value[__index]) , SronTypeNum::TYPE_CHAR);
}


inline void String::CLEAR()
{
    this->value.clear();
}

// converts the passed argument to std::string and appends it to this->value
inline void String::PUSH(AnyPtr val)
{

    this->value.append(val->TO_STRING());
}

inline void String::PUSH_WITHOUT_COPY(AnyPtr , SronTypeNum) {}

// returns the pointer
inline AnyBindPtr String::AT(Int &index)
{
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.length(), "extraction", "String");

    return GarbageCollector::REGISTER_MEMORY(new Char(this->value.at(*index)) , SronTypeNum::TYPE_CHAR);
}

inline long long int String::COUNT(Any &val)
{

    return std::count(this->value.begin(), this->value.end(), **val.GET_CHAR());
}

inline void String::DELETE_(Int &index)
{

    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.length(), "deletion", "String");

    this->value.erase(*index);
}

inline long long int String::INDEX(Any &__val) const
{
    switch (__val.TYPE_NUMBER())
    {
        case TYPE_CHAR: {
            auto x = this->value.find(**charCast( &__val ));
            return (x == std::string::npos) ? -1 : x; }
        

        case TYPE_STRING: {
            auto x = this->value.find(**stringCast( &__val ));
            return (x == std::string::npos) ? -1 : x; }

        default : throw ThrowException("searching a value of type '" + std::string(__val.TYPE()) + "' in 'String'. Expected 'String' or 'Char'", SronException::ArgumentException);
    }

    return -1;
}

inline void String::INSERT(Int &index, AnyPtr &val)
{
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.length(), "insertion", "String");

    this->value.insert(index, val->TO_STRING());
}

inline AnyBindPtr String::POP()
{

    if (this->value.empty())
    {
        throw ThrowException("performing 'pop' operation on value of type 'String'. Length of String is 0 that's why this exception is raised");
    }

    char ch = this->value.back();

    this->value.pop_back();

    return GarbageCollector::REGISTER_MEMORY(new Char(ch) , SronTypeNum::TYPE_CHAR);
}

inline void String::REPLACE(const std::string &replacer, const std::string &replacement)
{
    std::size_t pos = 0;
    while ((pos = value.find(replacer, pos)) != std::string::npos)
    {
        this->value.replace(pos, replacer.length(), replacement);
        pos += replacement.length();
    }
}

inline void String::REPLACE(Any &replacer, Any &replacement)
{

    switch (replacer.TYPE_NUMBER())
    {
        case TYPE_STRING:

        case TYPE_CHAR: this->REPLACE(replacer.TO_STRING(), replacement.TO_STRING()); break;

        default:
            throw ThrowException("performing String replacment on a value of type '" + std::string(replacer.TYPE()) + "'. Expected 'Char' or 'String' type values", SronException::ArgumentException);
    }
}

inline void String::REVERSE()
{
    std::reverse(this->value.begin(), this->value.end());
}

// returns the index number if found, otherwise -1
inline long long int String::RINDEX(Any &val) const
{
    switch (val.TYPE_NUMBER())
    {

        case TYPE_CHAR: {
            auto x = this->value.find_last_of(**val.GET_CHAR());
            return (x == std::string::npos) ? -1 : x; }
        

        case TYPE_STRING: {
            auto x = this->value.find_last_of(**val.GET_STRING());
            return (x == std::string::npos) ? -1 : x; }
        
        default : throw ThrowException("searching a value of type '" + std::string(val.TYPE()) + "' in 'String'. Expected 'String' or 'Char'", SronException::ArgumentException);
    }

    return -1;
}

inline void String::SORT()
{
    std::sort(this->value.begin(), this->value.end());
}

inline void String::REVERSE_SORT()
{
    std::sort(this->value.begin(), this->value.end(), [](char __ch1, char __ch2)
              { return __ch1 > __ch2; });
}

inline ListPtr String::SPLIT(Char &_splitter)
{
    List *lst = new List();

    std::string temp = "";

    for (const auto &i : this->value)
    {
        if (i == *_splitter)
        {
            lst->PUSH_WITHOUT_COPY(new String(temp) , SronTypeNum::TYPE_STRING);
            temp = "";
        }
        else
        {
            temp += i;
        }
    }

    lst->PUSH_WITHOUT_COPY(new String(temp) , SronTypeNum::TYPE_STRING);

    return lst;
}

inline AnyBindPtr String::SUBPART(Int &start_index, Int &end_index) 
{

    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*start_index, this->value.length(), "extraction", "String");
    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*end_index, this->value.length(), "extraction", "String");

    StringPtr ptr = new String();

    ptr->value.append((this->value.begin() + (*start_index)), (this->value.begin() + (*end_index)));

    return GarbageCollector::REGISTER_MEMORY(ptr , SronTypeNum::TYPE_STRING);
}

inline ListPtr String::TO_CHAR_LIST()
{
    ListPtr lst = new List();

    for (const auto &i : this->value)
    {
        lst->PUSH_WITHOUT_COPY(new Char(i), SronTypeNum::TYPE_CHAR);
    }

    return lst;
}

inline StringPtr String::TO_LOWERCASE()
{
    StringPtr str = new String();

    for (const auto &i : this->value)
    {
        str->value += ((char)std::tolower(i));
    }

    return str;
}
inline StringPtr String::TO_UPPERCASE()
{
    StringPtr str = new String();

    for (const auto &i : this->value)
    {
        str->value += ((char)std::toupper(i));
    }

    return str;
}

inline void String::TRIM()
{
    // Find the first non-whitespace character from the left
    auto left = std::find_if_not(this->value.begin(), this->value.end(), [](unsigned char c)
                                 { return std::isspace(c); });

    // Find the first non-whitespace character from the right
    auto right = std::find_if_not(this->value.rbegin(), this->value.rend(), [](unsigned char c)
                                  { return std::isspace(c); })
                     .base();

    // If all characters are whitespace, return an empty string
    if (left == this->value.end() || right == this->value.begin()) this->value.clear();

    this->value.erase(this->value.begin(), left);
    this->value.erase(right, this->value.end());
}

inline void String::UPDATE(Int &index, Any &val)
{

    THROW_EXCEPTION_IF_INDEX_OUT_OF_BOUND(*index, this->value.length(), "updation", "String");

    this->value[*index] = **val.GET_CHAR();
}

/* EVALUATION METHODS IMPLEMENTATION STARTS FROM HERE... */
inline AnyPtr String::__ADD__(Any &__val , SronTypeNum) const
{
    return new String(this->TO_STRING().append(__val.TO_STRING()));
}

inline SronBool_t String::__IS_EQUAL__(Any &__val , SronTypeNum __type) const
{
    if (__type == TYPE_STRING) return this->value == **stringCast( &__val );

    return false;
}

inline SronBool_t String::__NOT_EQUAL__(Any &__val , SronTypeNum __type) const
{
    if (__type == TYPE_STRING) return this->value != **stringCast( &__val );
    
    return true;
}

inline SronBool_t String::__LESS_THAN__(Any &__val , SronTypeNum __type) const
{
    if (__type == TYPE_STRING) return this->value < **stringCast( &__val );
    
    return this->TYPE_NUMBER() < __type;
}

inline SronBool_t String::__LESS_THAN_EQUAL__(Any &__val , SronTypeNum __type) const
{
    if (__type == TYPE_STRING) return this->value <= **stringCast( &__val );

    return this->TYPE_NUMBER() <= __type;
}

inline SronBool_t String::__MORE_THAN__(Any &__val , SronTypeNum __type) const
{
    if (__type == TYPE_STRING) return this->value > **stringCast( &__val );

    return this->TYPE_NUMBER() > __type;
}

inline SronBool_t String::__MORE_THAN_EQUAL__(Any &__val , SronTypeNum __type) const
{
    if (__type == TYPE_STRING) return this->value >= **stringCast( &__val );

    return this->TYPE_NUMBER() >= __type;
}

inline void String::__ADD_AND_ASSIGN__(Any &__val , SronTypeNum)
{
    this->value.append( __val.TO_STRING());
}

inline std::string &String::operator*() noexcept
{
    return this->value;
}

inline String &String::operator=(String &&__other) noexcept
{
    if (this != &__other)
    {
        this->value = std::move(__other.value);
    }

    return *this;
}

inline String::~String() noexcept {}

#endif