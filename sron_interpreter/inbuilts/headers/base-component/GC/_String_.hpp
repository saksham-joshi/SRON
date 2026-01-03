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
inline AnyPtr String::copy() const
{
    return new String(this->value);
}

// returns the length of the String
inline size_t String::len() const
{
    return this->value.length();
}

// prints the value on the terminal
inline void String::print() const
{
    std::printf("%s", this->value.c_str());
}

// prints the String value with double quotes.
inline void String::formatPrint() const
{
    std::printf("\"%s\"", this->value.c_str());
}

inline void String::preMove(){ }

inline void String::fillObuffer(SronOBuffer& __buffer) const
{
    __buffer.append( this->value.c_str() , this->value.length() );
}

// returns the size in bytes of the value
inline long long int String::sizeOf() const
{
    return sizeof(class String);
}

// returns the
inline std::string String::toString() const
{
    return this->value;
}

inline bool String::isCollective() const
{
    return true;
}


// return the type
inline const char *String::type() const
{
    return "String";
}

// appends the "String" to the passed std::string
inline void String::type(std::string &str) const
{
    str.append("String");
}

// returns the type number used for identifying the type of the value efficiently.
inline SronTypeNum String::typeNum() const
{
    return SronTypeNum::TYPE_STRING;
}

inline ColPtr String::getCollective() const
{

    return (ColPtr)this;
}

inline AnyBindPtr String::at(size_t __index) const
{
    if (this->value.length() >= __index) throw ThrowException("extracting 'Char' from 'String' at index '"+std::to_string(__index)+"'", SronException::IndexNotWithinRangeException);

    return GarbageCollector::registerChar(this->value[__index]);
}


inline void String::clear()
{
    this->value.clear();
}

// converts the passed argument to std::string and appends it to this->value
inline void String::push(AnyPtr val)
{

    this->value.append(val->toString());
}

inline void String::push(const char __ch)
{
    this->value.push_back(__ch);
}

inline void String::pushWithoutCopy(AnyPtr , SronTypeNum) {}

// returns the pointer
inline AnyBindPtr String::at(Int &index)
{
    throwExceptionIfIndexOutOfBound(index.getBaseInt(), this->value.length(), "extraction", "String");

    return GarbageCollector::registerMemory(new Char(this->value.at(index.getBaseInt())) , SronTypeNum::TYPE_CHAR);
}

inline long long int String::count(AnyBind &val)
{
    if(val.type() != SronTypeNum::TYPE_CHAR) throwArgumentException("count", "Char");

    return std::count(this->value.begin(), this->value.end(), val.getBaseChar());
}

inline void String::drop(Int &index)
{
    throwExceptionIfIndexOutOfBound(index.getBaseInt(), this->value.length(), "deletion", "String");

    this->value.erase(index.getBaseInt(), 1);
}

inline long long int String::index(AnyBind &__val) const
{
    switch (__val.type())
    {
        case SronTypeNum::TYPE_CHAR: {
            auto x = this->value.find(__val.getBaseChar());
            return (x == std::string::npos) ? -1 : x; }
        

        case SronTypeNum::TYPE_STRING: {
            auto x = this->value.find(__val.getBaseStr());
            return (x == std::string::npos) ? -1 : x; }

        default : throw ThrowException("searching a value of type '" + __val.typeStr() + "' in 'String'. Expected 'String' or 'Char'", SronException::ArgumentException);
    }

    return -1;
}

inline void String::insert(Int &index, AnyBind &val)
{
    throwExceptionIfIndexOutOfBound(index.getBaseInt(), this->value.length(), "insertion", "String");

    this->value.insert(index, val->toString());
}

inline AnyBindPtr String::pop()
{

    if (this->value.empty())
    {
        throw ThrowException("performing 'pop' operation on value of type 'String'. Length of String is 0 that's why this exception is raised");
    }

    char ch = this->value.back();

    this->value.pop_back();

    return GarbageCollector::registerChar(ch);
}

inline void String::replace(const std::string &replacer, const std::string &replacement)
{
    std::size_t pos = 0;
    while ((pos = value.find(replacer, pos)) != std::string::npos)
    {
        this->value.replace(pos, replacer.length(), replacement);
        pos += replacement.length();
    }
}

inline void String::replace(AnyBind &replacer, AnyBind &replacement)
{

    switch (replacer.type())
    {
        case SronTypeNum::TYPE_STRING:

        case SronTypeNum::TYPE_CHAR: this->replace(replacer.ptr()->toString(), replacement.ptr()->toString()); break;

        default:
            throw ThrowException("performing String replacment on a value of type '" + replacer.typeStr() + "'. Expected 'Char' or 'String' type values", SronException::ArgumentException);
    }
}

inline void String::reverse()
{
    std::reverse(this->value.begin(), this->value.end());
}

// returns the index number if found, otherwise -1
inline long long int String::rIndex(AnyBind &val) const
{
    switch (val.type())
    {

        case SronTypeNum::TYPE_CHAR: {
            auto x = this->value.find_last_of(val.getBaseChar());
            return (x == std::string::npos) ? -1 : x; }
        

        case SronTypeNum::TYPE_STRING: {
            auto x = this->value.find_last_of(val.getBaseStr());
            return (x == std::string::npos) ? -1 : x; }
        
        default : throw ThrowException("searching a value of type '" + val.typeStr() + "' in 'String'. Expected 'String' or 'Char'", SronException::ArgumentException);
    }

    return -1;
}

inline void String::sort()
{
    std::sort(this->value.begin(), this->value.end());
}

inline void String::reverseSort()
{
    std::sort(this->value.begin(), this->value.end(), [](char __ch1, char __ch2)
              { return __ch1 > __ch2; });
}

inline ListPtr String::split(Char &_splitter)
{
    List *lst = new List();

    std::string temp = "";

    for (const auto &i : this->value)
    {
        if (i == _splitter.getBaseChar())
        {
            lst->pushWithoutCopy(new String(temp) , SronTypeNum::TYPE_STRING);
            temp = "";
        }
        else
        {
            temp += i;
        }
    }

    lst->pushWithoutCopy(new String(temp) , SronTypeNum::TYPE_STRING);

    return lst;
}

inline AnyBindPtr String::subPart(Int &start_index, Int &end_index) 
{

    throwExceptionIfIndexOutOfBound(start_index.getBaseInt(), this->value.length(), "extraction", "String");
    throwExceptionIfIndexOutOfBound(end_index.getBaseInt(), this->value.length(), "extraction", "String");

    StringPtr ptr = new String();

    ptr->value.append((this->value.begin() + (start_index.getBaseInt())), (this->value.begin() + (end_index.getBaseInt())));

    return GarbageCollector::registerMemory(ptr , SronTypeNum::TYPE_STRING);
}

inline ListPtr String::toCharList()
{
    ListPtr lst = new List();

    for (const auto &i : this->value)
    {
        lst->pushWithoutCopy(new Char(i), SronTypeNum::TYPE_CHAR);
    }

    return lst;
}

inline AnyBindPtr String::toLowerCase()
{
    StringPtr str = new String();

    str->getBaseString().reserve(this->value.length());

    for(const auto i : this->value) str->push(SronChar::toLowercase(i));

    return GarbageCollector::registerMemory(str, SronTypeNum::TYPE_STRING);
}

inline AnyBindPtr String::toUpperCase()
{
    StringPtr str = new String();

    str->getBaseString().reserve(this->value.length());

    for(const auto i : this->value) str->push(SronChar::toUppercase(i));

    return GarbageCollector::registerMemory(str, SronTypeNum::TYPE_STRING);
}

inline bool String::isLowerCase()
{
    for(const auto i : this->value) if(SronChar::isAlphabet(i) && !SronChar::isLowerCase(i)) return false;

    return true;
}

inline bool String::isUpperCase()
{
    for(const auto i : this->value) if(SronChar::isAlphabet(i) && !SronChar::isUpperCase(i)) return false;

    return true;
}

inline void String::trim()
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

inline void String::update(Int &index, AnyBind &val)
{

    throwExceptionIfIndexOutOfBound(index.getBaseInt(), this->value.length(), "updation", "String");

    if (val.type() != SronTypeNum::TYPE_CHAR) throwArgumentException("update", "Char");

    this->value[index.getBaseInt()] = val.getBaseChar();
}

/* EVALUATION METHODS IMPLEMENTATION STARTS FROM HERE... */
inline AnyPtr String::__add__(Any &__val , SronTypeNum) const
{
    return new String(this->toString().append(__val.toString()));
}

inline SronBool_t String::__isEqual__(Any &__val , SronTypeNum __type) const
{
    if (__type == SronTypeNum::TYPE_STRING) return this->value == stringCast(&__val)->getBaseString();

    else if(__type == SronTypeNum::TYPE_LITERAL_STR) return this->value == lstrCast(&__val)->getBaseLstr();

    return false;
}

inline SronBool_t String::__notEqual__(Any &__val , SronTypeNum __type) const
{
    if (__type == SronTypeNum::TYPE_STRING) return this->value != stringCast(&__val)->getBaseString();

    else if(__type == SronTypeNum::TYPE_LITERAL_STR) return this->value != lstrCast(&__val)->getBaseLstr();
    
    return true;
}

inline SronBool_t String::__lessThan__(Any &__val , SronTypeNum __type) const
{
    if (__type == SronTypeNum::TYPE_STRING) return this->value < stringCast(&__val)->getBaseString();

    else if(__type == SronTypeNum::TYPE_LITERAL_STR) return this->value < lstrCast(&__val)->getBaseLstr();
    
    return this->typeNum() < __type;
}

inline SronBool_t String::__lessEqual__(Any &__val , SronTypeNum __type) const
{
    if (__type == SronTypeNum::TYPE_STRING) return this->value <= stringCast(&__val)->getBaseString();

    else if(__type == SronTypeNum::TYPE_LITERAL_STR) return this->value <= lstrCast(&__val)->getBaseLstr();

    return this->typeNum() <= __type;
}

inline SronBool_t String::__moreThan__(Any &__val , SronTypeNum __type) const
{
    if (__type == SronTypeNum::TYPE_STRING) return this->value > stringCast(&__val)->getBaseString();

    else if(__type == SronTypeNum::TYPE_LITERAL_STR) return this->value > lstrCast(&__val)->getBaseLstr();

    return this->typeNum() > __type;
}

inline SronBool_t String::__moreEqual__(Any &__val , SronTypeNum __type) const
{
    if (__type == SronTypeNum::TYPE_STRING) return this->value >= stringCast(&__val)->getBaseString();

    else if(__type == SronTypeNum::TYPE_LITERAL_STR) return this->value >= lstrCast(&__val)->getBaseLstr();

    return this->typeNum() >= __type;
}

inline void String::__addAssign__(Any &__val , SronTypeNum __type)
{
    switch(__type)
    {
        case SronTypeNum::TYPE_STRING : this->value.append(stringCast(&__val)->value); break;

        case SronTypeNum::TYPE_CHAR : this->value.push_back(charCast(&__val)->getBaseChar()); break;

        case SronTypeNum::TYPE_LITERAL_STR : { 
            const auto& str_to_insert = lstrCast(&__val)->getBaseLstr();
            this->value.append(str_to_insert.data(), str_to_insert.length()); 
             break; }

        default : throw ThrowException("performing 'addAssign'(+=) operation between value of type 'String' and '" + std::string(SronExtra::typenumToString(__type)) +"'");
    }
}

inline String &String::operator=(String &&__other) noexcept
{
    if (this != &__other)
    {
        this->value = std::move(__other.value);
    }

    return *this;
}


inline const char* String::cStr() const noexcept
{
    return this->value.c_str();
}

inline void String::append(const char* __str)
{
    this->value.append(__str);
}

inline SronString_t& String::getBaseString() noexcept
{
    return this->value;
}

inline String::~String() noexcept {}

#endif