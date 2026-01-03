#pragma once

#ifndef _INT_H
#define _INT_H

#include "_Double_.hpp"

/*
  |====================== INT ===============================|
 'Int' datatype implements integer type with long long modifier.
 > SronInt_t takes 8 bytes.
 > Syntax in SRON : "Int x = 10" or "Int x"
*/

inline Int::Int(const SronInt_t __value) noexcept : value(__value) {}

inline Int::Int(const std::string &val) : value(Converter::toInt(val)) {}

inline Int Int::operator=(SronInt_t &val)
{
    return Int(val);
}

inline Int::operator SronInt_t() const
{
    return this->value;
}

inline AnyPtr Int::copy() const
{
    return new Int(this->value);
}

inline void Int::print() const
{
    std::printf("%lld", this->value);
}

inline void Int::formatPrint() const
{
    this->print();
}

inline void Int::preMove(){ }

inline void Int::fillObuffer(SronOBuffer& __buffer) const
{
    __buffer << this->value;
}

inline long long int Int::sizeOf() const
{
    return sizeof(class Int);
}

inline const char *Int::type() const
{
    return "Int";
}

inline void Int::type(std::string &str) const
{
    str.append("Int");
}

inline SronTypeNum Int::typeNum() const
{
    return SronTypeNum::TYPE_INT;
}

inline std::string Int::toString() const
{
    return std::to_string(this->value);
}

inline bool Int::isCollective() const
{
    return false;
}

inline SronInt_t Int::getBaseInt() const noexcept
{
    return this->value;
}

// inline SronInt_t Int::getBaseInt()
// {
//     return this->value;
// }

// inline SronDouble_t Int::getBaseDouble(){
//     return this->value;
// }

// inline SronChar_t Int::getBaseChar()
// {
//     return this->value;
// }

// inline SronBool_t Int::getBaseBool()
// {
//     return this->value;
// }

// inline IntPtr Int::getInt() const
// {
//     return const_cast<IntPtr>(this);
// }

// inline DoublePtr Int::getDouble() const
// {
//     DoublePtr ptr = new Double(this->value);

//     GarbageCollector::registerMemory(ptr , SronTypeNum::TYPE_DOUBLE);

//     return ptr;
// }

// inline CharPtr Int::getChar() const
// {
//     CharPtr ptr = new Char(this->value);

//     GarbageCollector::registerMemory(ptr , SronTypeNum::TYPE_CHAR);

//     return ptr;
// }

// inline BoolPtr Int::getBool() const
// {
//     return reinterpret_cast<BoolPtr>( this->value  ? Bool::__SronTrue->ptr() : Bool::__SronFalse->ptr());
// }

inline AnyPtr Int::__add__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT:
            return new Int(this->value + intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE:
            return new Double(this->value + doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR:
            return new Int(this->value + charCast(&__val)->getBaseChar());

        case SronTypeNum::TYPE_STRING:
            return new String(this->toString().append(stringCast(&__val)->getBaseString()));

        default : mathEvaluationException("+", "Int", __val.type());
    } 

    return nullptr;
}

inline AnyPtr Int::__sub__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT:
            return new Int(this->value - intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE:
            return new Double(this->value - doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR:
            return new Int(this->value - charCast(&__val)->getBaseChar());

        default : mathEvaluationException("-", "Int", __val.type());
    }

    

    return nullptr;
}

inline AnyPtr Int::__mult__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT:
            return new Int(this->value * (intCast(&__val)->getBaseInt()));

        case SronTypeNum::TYPE_DOUBLE:
            return new Double(this->value * (doubleCast(&__val)->getBaseDouble()));

        case SronTypeNum::TYPE_CHAR:
            return new Int(this->value * (charCast(&__val)->getBaseChar()));

        default : mathEvaluationException("*", "Int", __val.type());
    }

    return nullptr;
}

inline AnyPtr Int::__div__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT:
            return new Int(safeDivide(this->value, intCast(&__val)->getBaseInt()));

        case SronTypeNum::TYPE_DOUBLE:
            return new Double(safeDivide(this->value, doubleCast(&__val)->getBaseDouble()));

        case SronTypeNum::TYPE_CHAR:
            return new Int(safeDivide(this->value,(SronInt_t)charCast(&__val)->getBaseChar()));

        default : mathEvaluationException("/", "Int", __val.type());
    }

    

    return nullptr;
}

inline AnyPtr Int::__mod__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT:
            return new Int(SAFE_MOD(this->value , intCast(&__val)->getBaseInt()));

        case SronTypeNum::TYPE_DOUBLE:
            return new Double(SAFE_MOD(this->value, doubleCast(&__val)->getBaseDouble()));

        case SronTypeNum::TYPE_CHAR:
            return new Int(SAFE_MOD(this->value,(SronInt_t) charCast(&__val)->getBaseChar()));

        default : mathEvaluationException("%", "Int", __val.type());
    }

    

    return nullptr;
}

inline AnyPtr Int::__pow__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT:
            return new Int(std::pow((SronDouble_t)this->value, (SronDouble_t)intCast(&__val)->getBaseInt()));

        case SronTypeNum::TYPE_DOUBLE:
            return new Double(std::pow((SronDouble_t)this->value, doubleCast(&__val)->getBaseDouble()));

        case SronTypeNum::TYPE_CHAR:
            return new Int(std::pow((SronDouble_t)this->value, (SronDouble_t)charCast(&__val)->getBaseChar()));

        default : mathEvaluationException("^", "Int", __val.type());
    }

    return nullptr;
}

inline AnyPtr Int::__xor__(Any &__val , SronTypeNum __type) const
{
    switch(__type){

        case SronTypeNum::TYPE_INT : return new Int( this->value ^ intCast(&__val)->getBaseInt() );

        case SronTypeNum::TYPE_DOUBLE : return new Int( this->value ^ (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return new Int(this->value ^ (SronInt_t)charCast(&__val)->getBaseChar() );

        default : mathEvaluationException("xor", this->type(), __val.type());
    }

    return nullptr;
}

inline AnyPtr Int::__bitAnd__(Any &__val , SronTypeNum __type) const
{
    switch(__type){

        case SronTypeNum::TYPE_INT : return new Int( this->value & intCast(&__val)->getBaseInt());

        case SronTypeNum::TYPE_DOUBLE : return new Int( this->value & (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return new Int(this->value & charCast(&__val)->getBaseChar());

        default : mathEvaluationException("bitwise-and", this->type(), __val.type());
    }

    return nullptr;
}

inline AnyPtr Int::__bitOr__(Any &__val , SronTypeNum __type) const 
{
    switch(__type){

        case SronTypeNum::TYPE_INT : return new Int( this->value | intCast(&__val)->getBaseInt() );

        case SronTypeNum::TYPE_DOUBLE : return new Int( this->value | (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return new Int(this->value | (SronInt_t)charCast(&__val)->getBaseChar() );

        default : mathEvaluationException("bitwise-or", this->type(), __val.type());
    }

    return nullptr;
}

inline AnyPtr Int::__bitNot__() const
{
    return new Int(~(this->value));
}

inline AnyPtr Int::__leftShift__(Any &__val , SronTypeNum __type) const
{

    switch(__type){

        case SronTypeNum::TYPE_INT : return new Int( this->value << intCast(&__val)->getBaseInt() );

        case SronTypeNum::TYPE_DOUBLE : return new Int( this->value << (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return new Int(this->value << (SronInt_t)charCast(&__val)->getBaseChar() );

        default : mathEvaluationException("lsft", this->type(), __val.type());
    }

    return nullptr;
}

inline AnyPtr Int::__rightShift__(Any &__val , SronTypeNum __type) const
{
    switch(__type)
    {
        case SronTypeNum::TYPE_INT : return new Int( this->value >> intCast(&__val)->getBaseInt() );

        case SronTypeNum::TYPE_DOUBLE : return new Int( this->value >> (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return new Int(this->value >> (SronInt_t)charCast(&__val)->getBaseChar() );

        default : mathEvaluationException("rsft", this->type(), __val.type());
    }
    
    return nullptr;
}

inline SronBool_t Int::__isEqual__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT : return this->value == intCast(&__val)->getBaseInt();

        case SronTypeNum::TYPE_DOUBLE : return ( this->value == (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return (this->value == (SronInt_t)charCast(&__val)->getBaseChar() );

        default : { }
    }

    return false;
}

inline SronBool_t Int::__notEqual__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT : return this->value != intCast(&__val)->getBaseInt();

        case SronTypeNum::TYPE_DOUBLE : return ( this->value != (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return (this->value != (SronInt_t)charCast(&__val)->getBaseChar() );

        default : { }
    }

    return true;
}

inline SronBool_t Int::__and__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT : return this->value && intCast(&__val)->getBaseInt();

        case SronTypeNum::TYPE_BOOL : return ( this->value && (SronInt_t)boolCast( &__val )->getBaseBool());

        case SronTypeNum::TYPE_CHAR : return (this->value && (SronInt_t)charCast(&__val)->getBaseChar() );

        default : mathEvaluationException("&&", "Int", __val.type());
    }

    return false;
}

inline SronBool_t Int::__or__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT : return this->value || intCast(&__val)->getBaseInt();

        case SronTypeNum::TYPE_BOOL : return ( this->value || (SronInt_t)boolCast( &__val )->getBaseBool());

        case SronTypeNum::TYPE_CHAR : return (this->value || (SronInt_t)charCast(&__val)->getBaseChar() );

        default : mathEvaluationException("||", "Int", __val.type());
    }

    return false;
}

inline SronBool_t Int::__not__() const
{
    return (!(this->value > 0));
}

inline SronBool_t Int::__lessThan__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT : return this->value < intCast(&__val)->getBaseInt() ;

        case SronTypeNum::TYPE_DOUBLE : return ( this->value < (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return (this->value < (SronInt_t)charCast(&__val)->getBaseChar() );

        default : mathEvaluationException("<", "Int", __val.type());
    }

    return false;
}

inline SronBool_t Int::__lessEqual__(Any &__val , SronTypeNum __type) const
{

    switch (__type)
    {
        case SronTypeNum::TYPE_INT : return this->value <= intCast(&__val)->getBaseInt() ;

        case SronTypeNum::TYPE_DOUBLE : return ( this->value <= (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return (this->value <= (SronInt_t)charCast(&__val)->getBaseChar());

        default : mathEvaluationException("<=", "Int", __val.type());
    }

    return false;
}

inline SronBool_t Int::__moreThan__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT : return this->value > intCast(&__val)->getBaseInt();

        case SronTypeNum::TYPE_DOUBLE : return ( this->value > (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return (this->value > (SronInt_t)charCast(&__val)->getBaseChar() );

        default : mathEvaluationException(">", "Int", __val.type());
    }

    return false;
}

inline SronBool_t Int::__moreEqual__(Any &__val , SronTypeNum __type) const
{
    switch (__type)
    {
        case SronTypeNum::TYPE_INT : return this->value >= intCast(&__val)->getBaseInt();

        case SronTypeNum::TYPE_DOUBLE : return ( this->value >= (SronInt_t)doubleCast(&__val)->getBaseDouble());

        case SronTypeNum::TYPE_CHAR : return (this->value >= (SronInt_t)charCast(&__val)->getBaseChar() );

        default : mathEvaluationException(">=", "Int", __val.type());
    }

    return false;
}

inline AnyPtr Int::__negate__() const
{
    return new Int(-this->value);
}

inline void Int::__addAssign__(Any &__val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value+= (intCast(&__val)->getBaseInt()); break;

        case SronTypeNum::TYPE_DOUBLE : this->value+= (doubleCast(&__val)->getBaseDouble()); break;

        case SronTypeNum::TYPE_CHAR : this->value+= ((SronInt_t)charCast(&__val)->getBaseChar()); break;

        default : mathEvaluationException("+=", this->type(), __val.type());
    }
}

inline void Int::__subAssign__(Any &__val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value-= (intCast(&__val)->getBaseInt()); break;

        case SronTypeNum::TYPE_DOUBLE : this->value-= (doubleCast(&__val)->getBaseDouble()); break;

        case SronTypeNum::TYPE_CHAR : this->value-= ((SronInt_t) charCast(&__val)->getBaseChar()); break;

        default : mathEvaluationException("-=", this->type() , __val.type());
    }
}

inline void Int::__multAssign__(Any &__val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value*= (intCast(&__val)->getBaseInt()); break;

        case SronTypeNum::TYPE_DOUBLE : this->value*= (doubleCast(&__val)->getBaseDouble()); break;

        case SronTypeNum::TYPE_CHAR : this->value*= ((SronInt_t) charCast(&__val)->getBaseChar()); break;

        default : mathEvaluationException("*=", this->type() , __val.type());
    }
}

inline void Int::__divAssign__(Any &__val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value/= (intCast(&__val)->getBaseInt()); break;

        case SronTypeNum::TYPE_DOUBLE : this->value/= (doubleCast(&__val)->getBaseDouble()); break;

        case SronTypeNum::TYPE_CHAR : this->value/= ((SronInt_t) charCast(&__val)->getBaseChar()); break;

        default : mathEvaluationException("/=", this->type() , __val.type());
    }
}

inline void Int::__modAssign__(Any &__val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value %= (intCast(&__val)->getBaseInt()); break;

        case SronTypeNum::TYPE_DOUBLE : this->value%= ((SronInt_t)doubleCast(&__val)->getBaseDouble()); break;

        case SronTypeNum::TYPE_CHAR : this->value%= ((SronInt_t) charCast(&__val)->getBaseChar()); break;

        default : mathEvaluationException("%=", this->type() , __val.type());
    }
}

inline void Int::__powAssign__(Any &__val , SronTypeNum __type){

    switch(__type){

        case SronTypeNum::TYPE_INT : this->value = std::pow(this->value, (intCast(&__val)->getBaseInt())); break;

        case SronTypeNum::TYPE_DOUBLE : this->value= std::pow(this->value, (doubleCast(&__val)->getBaseDouble())); break;

        case SronTypeNum::TYPE_CHAR : this->value = std::pow(this->value, ((SronInt_t) charCast(&__val)->getBaseChar())); break;

        default : mathEvaluationException("^=", this->type() , __val.type());
    }
}

inline Int::~Int() noexcept{}

#endif