#ifndef _LSTR_H_
#define _LSTR_H_

#include "_FileWriter_.hpp"

inline LiteralString::LiteralString(const char* __str) : value(__str) { }

inline LiteralString::LiteralString(const char* __str, const SronInt_t __len) : value(__str, __len){ }

inline LiteralString::LiteralString(const LiteralString& __str) : value(__str.value){ }

inline LiteralString::LiteralString(LiteralString&& __str) : value(std::move(__str.value)) { }

inline AnyPtr LiteralString::copy() const
{
    return new LiteralString(this->value.data(), this->value.length());
}

inline void LiteralString::print() const
{
    for(const auto i : this->value) printf("%c", i);
}

inline void LiteralString::formatPrint() const
{
    putchar('"');
    this->print();
    putchar('"');
}

inline void LiteralString::preMove() { }

inline void LiteralString::fillObuffer(SronOBuffer& __buffer) const 
{
    __buffer.append(this->value.data(), this->value.length());
}

inline const char* LiteralString::type() const 
{
    return "LiteralString";
}

inline void LiteralString::type(std::string& __str) const
{
    __str += (this->type());
}

inline SronTypeNum LiteralString::typeNum() const 
{
    return SronTypeNum::TYPE_LITERAL_STR;
}

inline long long int LiteralString::sizeOf() const 
{
    return sizeof(class LiteralString);
}

inline bool LiteralString::isCollective() const 
{
    return true;
}

inline std::string LiteralString::toString() const 
{
    return std::string(this->value);
}

inline ColPtr LiteralString::getCollective() const 
{
    return (ColPtr)this;
}

inline SronBool_t LiteralString::__isEqual__(Any& __obj, SronTypeNum __type) const 
{
    switch(__type)
    {
        case SronTypeNum::TYPE_STRING : return this->value == stringCast(&__obj)->getBaseString();

        case SronTypeNum::TYPE_LITERAL_STR : return this->value == lstrCast(&__obj)->value;

        default : {}
    }
    return false;
}

inline SronBool_t LiteralString::__notEqual__(Any& __obj, SronTypeNum __type) const 
{
    switch(__type)
    {
        case SronTypeNum::TYPE_STRING : return this->value != stringCast(&__obj)->getBaseString();

        case SronTypeNum::TYPE_LITERAL_STR : return this->value != lstrCast(&__obj)->value;

        default : {}
    }
    return true;
}

inline SronBool_t LiteralString::__lessThan__(Any& __obj, SronTypeNum __type) const 
{
    switch(__type)
    {
        case SronTypeNum::TYPE_STRING : return this->value < stringCast(&__obj)->getBaseString();

        case SronTypeNum::TYPE_LITERAL_STR : return this->value < lstrCast(&__obj)->value;

        default : {}
    }
    return this->typeNum() < __type;
}

inline SronBool_t LiteralString::__lessEqual__(Any& __obj, SronTypeNum __type) const 
{
    switch(__type)
    {
        case SronTypeNum::TYPE_STRING : return this->value <= stringCast(&__obj)->getBaseString();

        case SronTypeNum::TYPE_LITERAL_STR : return this->value <= lstrCast(&__obj)->value;

        default : {}
    }
    return this->typeNum() <= __type;
}

inline SronBool_t LiteralString::__moreThan__(Any& __obj, SronTypeNum __type) const 
{
    switch(__type)
    {
        case SronTypeNum::TYPE_STRING : return this->value > stringCast(&__obj)->getBaseString();

        case SronTypeNum::TYPE_LITERAL_STR : return this->value > lstrCast(&__obj)->value;

        default : {}
    }
    return this->typeNum() > __type;
}

inline SronBool_t LiteralString::__moreEqual__(Any& __obj, SronTypeNum __type) const 
{
    switch(__type)
    {
        case SronTypeNum::TYPE_STRING : return this->value >= stringCast(&__obj)->getBaseString();

        case SronTypeNum::TYPE_LITERAL_STR : return this->value >= lstrCast(&__obj)->value;

        default : {}
    }
    return this->typeNum() >= __type;
}

inline void LiteralString::clear()
{
    throw ThrowException("clearing the value of type 'LiteralString'. It is immutable so you cannot make changes to it");
}

inline void LiteralString::push(AnyPtr)
{
    throw ThrowException("trying to insert value into a 'LiteralString'. Remember, LiteralString is a compile-time constant string and cannot be modified");
}

inline void LiteralString::pushWithoutCopy(AnyPtr, SronTypeNum)
{
    this->push(nullptr);
}

inline size_t LiteralString::len() const 
{
    return this->value.length();
}

inline AnyBindPtr LiteralString::at( size_t __index) const 
{
    if(__index >= this->value.length()) throw ThrowException("extracting character from out of bound in a 'LiteralString'", SronException::IndexNotWithinRangeException);

    return GarbageCollector::registerChar(this->value[__index]);
}

inline long long int LiteralString::count(AnyBind& __obj) 
{
    long long cnt = 0;

    switch(__obj.type())
    {
        case SronTypeNum::TYPE_CHAR : cnt = std::count(this->value.begin(), this->value.end(), __obj.getBaseChar());  break;

        case SronTypeNum::TYPE_STRING : cnt = SronExtra::countSubString(this->value, std::string_view(__obj.getStr()->getBaseString())); break;

        case SronTypeNum::TYPE_LITERAL_STR : cnt = SronExtra::countSubString(this->value, __obj.getBaseLstr()); break;

        default : throwArgumentException("count", "LiteralString, Char/String/LiteralString");
    }

    return cnt;
}

inline long long int LiteralString::index(AnyBind& __bind) const
{
    size_t idx = 0;

    switch(__bind.type())
    {
        case SronTypeNum::TYPE_CHAR: idx = this->value.find(__bind.getBaseChar()); break;

        case SronTypeNum::TYPE_STRING: idx = this->value.find(__bind.getBaseStr()); break;

        case SronTypeNum::TYPE_LITERAL_STR : idx = this->value.find(__bind.getBaseLstr()); break;

        default : throwArgumentException("index", "LiteralString, Char/String/LiteralString");
    }

    return (idx == std::string_view::npos) ? -1 : idx;
}

inline long long int LiteralString::rIndex(AnyBind& __bind) const
{
    size_t idx = 0;

    switch(__bind.type())
    {
        case SronTypeNum::TYPE_CHAR: idx = this->value.rfind(__bind.getBaseChar()); break;

        case SronTypeNum::TYPE_STRING: idx = this->value.rfind(__bind.getBaseStr()); break;

        case SronTypeNum::TYPE_LITERAL_STR : idx = this->value.rfind(__bind.getBaseLstr()); break;

        default : throwArgumentException("rIndex", "LiteralString, Char/String/LiteralString");
    }

    return (idx == std::string_view::npos) ? -1 : idx;
}

inline AnyBindPtr LiteralString::subPart(Int& __left, Int& __right)
{
    SronInt_t left = __left.getBaseInt();
    SronInt_t right = __right.getBaseInt();

    if( left >= right ) return GarbageCollector::registerMemory(new LiteralString("", 0), SronTypeNum::TYPE_LITERAL_STR);

    else if(left < 0 || right > (SronInt_t)this->value.length()) throw ThrowException("executing 'subPart' function. Extract values within the bounds of LiteralString", SronException::IndexNotWithinRangeException);

    return GarbageCollector::registerMemory(new LiteralString(this->value.data() + left , right - left), SronTypeNum::TYPE_LITERAL_STR);
}

inline LiteralString::SronLstr_t& LiteralString::getBaseLstr()
{
    return this->value;
}

inline AnyBindPtr LiteralString::toLowerCase()
{
    StringPtr str = new String();

    String::SronString_t& base_str = str->getBaseString();

    base_str.reserve(this->value.length());

    for(const auto i : this->value ) base_str.push_back( SronChar::toLowercase(i));

    return GarbageCollector::registerMemory(str, SronTypeNum::TYPE_STRING);
}

inline AnyBindPtr LiteralString::toUpperCase()
{
    StringPtr str = new String();

    String::SronString_t& base_str = str->getBaseString();
    
    base_str.reserve(this->value.length());

    for(const auto i : this->value ) base_str.push_back( SronChar::toUppercase(i));

    return GarbageCollector::registerMemory(str, SronTypeNum::TYPE_STRING);
}

inline bool LiteralString::isLowerCase()
{
    for(const auto i : this->value ) if(SronChar::isAlphabet(i) && !SronChar::isLowerCase(i)) return false;

    return true;
}

inline bool LiteralString::isUpperCase()
{
    for(const auto i : this->value ) if( SronChar::isAlphabet(i) && !SronChar::isUpperCase(i) ) return false;

    return true;
}

inline AnyBindPtr LiteralString::split( const char __delim)
{
    ListPtr lst = new List();

    StringPtr str = new String();

    for(const auto i : this->value)
    {
        if(i == __delim)
        {
            lst->push(str, SronTypeNum::TYPE_STRING);
            str->clear();
        }

        else str->push(i);
    }

    lst->pushWithoutCopy(str, SronTypeNum::TYPE_STRING);

    return GarbageCollector::registerMemory(lst, SronTypeNum::TYPE_LIST);
}

inline LiteralString::~LiteralString() noexcept
{ }


#endif