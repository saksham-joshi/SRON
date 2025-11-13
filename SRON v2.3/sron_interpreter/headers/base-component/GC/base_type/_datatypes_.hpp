/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 */

/*----------------------------------------------------------------*/

/*
 This file contains the implementation of all the neccessary datatypes like :
  1. Any.
  2. Void.
  3. Int.
  4. Double.
  5. String.
  6. Char.
  7. Bool.
  8. List.
*/

#pragma once

#ifndef DATATYPES_H
#define DATATYPES_H

#include "_base_interpreter_.hpp"

/*
 'Any' datatype is the base class for all other datatypes.
  It is inherited by Void, Int, Double, String, Char, Bool, Vector and List.
*/
class Any
{
  public:

    // creates a copy of the current value type.
    [[gnu::always_inline]] [[gnu::hot]] [[nodiscard]] inline virtual AnyPtr copy() const = 0;

    // prints the value of the datatype
    [[gnu::always_inline]] [[gnu::hot]] inline virtual void print() const = 0;

    // prints the value in a formatted manner
    [[gnu::always_inline]] [[gnu::hot]] inline virtual void formatPrint() const = 0;

    // function which is called before moving down the value in Garbage Collector
    [[gnu::always_inline]] [[gnu::hot]] inline virtual void preMove() = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void fillObuffer( SronOBuffer&) const = 0;

    inline virtual const char *type() const = 0;

    // prints the type of the datatype
    inline virtual void type(std::string &) const = 0;

    // returns the type number
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronTypeNum typeNum() const = 0;

    // returns the size of the value in bytes
    inline virtual long long int sizeOf() const = 0;

    // returns true if value is a collective type of value like string or list
    [[gnu::always_inline]] [[gnu::hot]] inline virtual bool isCollective() const =0;

    // returns the string form of value
    inline virtual std::string toString() const {
      throw ThrowException("extracting the 'String' from value of type '"+std::string(this->type()) +"' which is not possible");
    }

    // methods to return object's pointers
    [[gnu::always_inline]] [[gnu::hot]] inline virtual ColPtr getCollective() const
    {
      throw ThrowException("extracting the value of type 'Collective' (parent type for type 'List' and 'String' ) from the value of type '" + std::string(this->type()) + "'", SronException::InvalidObjectExtractionException);
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronInt_t getBaseInt() {
      throwInvalidObjectExtractionException("Int", this->type());
      return 0;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronDouble_t getBaseDouble() {
      throwInvalidObjectExtractionException("Double", this->type());
      return 0;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronChar_t getBaseChar() {
      throwInvalidObjectExtractionException("Char", this->type());
      return ' ';
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t getBaseBool() {
      throwInvalidObjectExtractionException("Bool", this->type());
      return false;
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual VoidPtr getVoid() const
    {
      throwInvalidObjectExtractionException("Void", this->type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual IntPtr getInt() const
    {
      throwInvalidObjectExtractionException("Int", this->type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual DoublePtr getDouble() const
    {
      throwInvalidObjectExtractionException("Double", this->type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual StringPtr getString() const
    {
      throwInvalidObjectExtractionException("String", this->type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual CharPtr getChar() const
    {
      throwInvalidObjectExtractionException("Char", this->type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual BoolPtr getBool() const
    {
      throwInvalidObjectExtractionException("Bool", this->type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual ListPtr getList() const
    {
      throwInvalidObjectExtractionException("List", this->type());
      return nullptr;
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __add__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("+", this->type(), __x.type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __sub__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("-", this->type(), __x.type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __mult__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("*", this->type(), __x.type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __div__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("/", this->type(), __x.type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __mod__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("%", this->type(), __x.type());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __pow__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("^", this->type(), __x.type());
      return nullptr;
    }

    inline virtual AnyPtr __xor__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("xor", this->type(), __x.type());
      return nullptr;
    }

    inline virtual AnyPtr __bitAnd__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("bitwise-and", this->type(), __x.type());
      return nullptr;
    }

    inline virtual AnyPtr __bitOr__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("bitwise-or", this->type(), __x.type());
      return nullptr;
    }

    inline virtual AnyPtr __bitNot__() const
    {
      mathEvaluationException("bitwise-not", this->type());
      return nullptr;
    }

    inline virtual AnyPtr __leftShift__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("left-shift", this->type(), __x.type());
      return nullptr;
    }

    inline virtual AnyPtr __rightShift__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("right-shift", this->type(), __x.type());
      return nullptr;
    }


    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __isEqual__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __notEqual__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __and__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("&&", this->type(), __x.type());
      return false;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __or__(Any &__x , SronTypeNum) const
    {
      mathEvaluationException("||", this->type(), __x.type());
      return false;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __not__() const
    {
      mathEvaluationException("!", this->type());
      return false;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __negate__() const
    {
      mathEvaluationException("-", this->type());
      return nullptr;
    }


    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __lessThan__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __lessEqual__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __moreThan__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __moreEqual__(Any &__x , SronTypeNum) const = 0;

    /*
    Calculate and assign operators overload ....!!
    */

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __addAssign__(Any &__x , SronTypeNum)
    {
      mathEvaluationException("+=", this->type(), __x.type());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __subAssign__(Any &__x , SronTypeNum)
    {
      mathEvaluationException("-=", this->type(), __x.type());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __multAssign__(Any &__x , SronTypeNum) 
    {
      mathEvaluationException("*=", this->type(), __x.type());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __divAssign__(Any &__x , SronTypeNum)
    {
      mathEvaluationException("/=", this->type(), __x.type());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __modAssign__(Any &__x , SronTypeNum) 
    {
      mathEvaluationException("%=", this->type(), __x.type());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __powAssign__(Any &__x , SronTypeNum)
    {
      mathEvaluationException("^=", this->type(), __x.type());
    }

    virtual ~Any() {}
};

inline static AnyBindPtr operator==(AnyBind &, AnyBind &);
inline static AnyBindPtr operator&&(AnyBind &, AnyBind &);
inline static AnyBindPtr operator||(AnyBind &, AnyBind &);
inline static AnyBindPtr operator!=(AnyBind &, AnyBind &);
inline static AnyBindPtr operator!(AnyBind &);
inline static AnyBindPtr operator-(AnyBind &);

inline static AnyBindPtr operator<(AnyBind &, AnyBind &);
inline static AnyBindPtr operator<=(AnyBind &, AnyBind &);
inline static AnyBindPtr operator>(AnyBind &, AnyBind &);
inline static AnyBindPtr operator>=(AnyBind &, AnyBind &);

inline static AnyBindPtr operator+(AnyBind &, AnyBind &);
inline static AnyBindPtr operator-(AnyBind &, AnyBind &);
inline static AnyBindPtr operator*(AnyBind &, AnyBind &);
inline static AnyBindPtr operator/(AnyBind &, AnyBind &);
inline static AnyBindPtr operator%(AnyBind &, AnyBind &);
inline static AnyBindPtr operator^(AnyBind &, AnyBind &);

inline static void operator+=(AnyBind &, AnyBind &);
inline static void operator-=(AnyBind &, AnyBind &);
inline static void operator*=(AnyBind &, AnyBind &);
inline static void operator/=(AnyBind &, AnyBind &);
inline static void operator%=(AnyBind &, AnyBind &);
inline static void operator^=(AnyBind &, AnyBind &);

class Void final : public Any
{

public:
  // this object is returned by all the user-available in-built functions defined in _user_fnc_.hpp::Sron namespace which returns 'Void' type value.
  static AnyBindPtr void_object;

  inline Void() noexcept;

  inline virtual AnyPtr copy() const final override;
  inline virtual void print() const final override;
  inline virtual void formatPrint() const final override;
  inline virtual void preMove() final override;
  inline virtual void fillObuffer(SronOBuffer&) const final override;
  inline virtual long long int sizeOf() const final override;
  inline virtual std::string toString() const final override;
  inline virtual bool isCollective() const final override;
  inline virtual const char *type() const final override;
  inline virtual void type(std::string &str) const final override;

  inline virtual SronTypeNum typeNum() const final override;

  inline virtual VoidPtr getVoid() const final override;

  inline virtual SronBool_t __isEqual__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __notEqual__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __lessThan__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __lessEqual__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __moreThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreEqual__(Any &, SronTypeNum) const final override;

  inline ~Void() noexcept;
};

AnyBindPtr Void::void_object;

class Collective : public Any
{
public:

  // pure virtual methods ...
  inline virtual void clear() = 0;
  inline virtual void push(AnyPtr ) = 0;
  inline virtual void pushWithoutCopy(AnyPtr , SronTypeNum ) = 0;
  inline virtual size_t LEN() const = 0;
  inline virtual AnyBindPtr at(size_t) const = 0;

  // returns the value at a particular index
  inline virtual AnyBindPtr at(Int &)
  {
    callingNonDefinedFunction("at", this->type());
    return Void::void_object;
  }

  // returns the number of occurence of a value
  inline virtual long long int count(Any &)
  {
    callingNonDefinedFunction("count", this->type());
    return 0;
  }

  // deletes a value at a particular index.
  inline virtual void drop(Int &)
  {
    callingNonDefinedFunction("delete", this->type());
  }

  // returns the first index of occurence of a value
  inline virtual long long int index(Any &) const
  {
    callingNonDefinedFunction("index", this->type());
    return 0;
  }

  // inserts the value at a particular index
  inline virtual void insert(Int &, AnyPtr &)
  {
    callingNonDefinedFunction("insert", this->type());
  }

  // deletes the values at the top and returns its value
  inline virtual AnyBindPtr pop()
  {
    callingNonDefinedFunction("pop", this->type());

    return Void::void_object;
  }

  // replaces a particular value with another value
  inline virtual void replace(Any &, Any &)
  {
    callingNonDefinedFunction("replace", this->type());
  }

  // reverses the value.
  inline virtual void reverse()
  {
    callingNonDefinedFunction("reverse", this->type());
  }

  // returns the first occurence of a value from last
  inline virtual long long int rIndex(Any &) const
  {
    callingNonDefinedFunction("rindex", this->type());
    return 0;
  }

  // sorts the values.
  inline virtual void sort()
  {
    callingNonDefinedFunction("sort", this->type());
  }

  // sorts the values in revese order
  inline virtual void reverseSort(){
    callingNonDefinedFunction("reverse_sort", this->type());
  }

  // extracts a part of a value within two indexes.
  inline virtual AnyBindPtr subPart(Int &, Int &)
  {
    callingNonDefinedFunction("subpart", this->type());
    return Void::void_object;
  }

  // updates/overrides the value at a particular index
  inline virtual void update(Int &, Any &)
  {
    callingNonDefinedFunction("update", this->type());
  }
};

/*
 * Classes are defined in the following flow :
 * 1. Private values of primitive datatypes in c++.
 * 2. Constructors.
 * 3. Abstract Methods like LEN, print, sizeOf, toString, TYPE etc.
 * 4. object extraction methods
 * 5. operatorive dunder methods
 * 6. dedicated methods only available to that certain class
 * 7. Destructor.
 */



class Double final : public Any
{
private:
  SronDouble_t value = 0;

  static unsigned short precision;

  inline static void PRECISION_PRINT( double __value )
  {
     switch( Double::precision )
     {
      case 1 : std::printf("%.1lf", __value); break;

      case 2 : std::printf("%.2lf", __value); break;

      case 4 : std::printf("%.4lf", __value); break;

      case 5 : std::printf("%.5lf", __value); break;

      case 6 : std::printf("%.6lf", __value); break;

      case 7 : std::printf("%.7lf", __value); break;

      case 8 : std::printf("%.8lf" , __value); break;

      default : std::printf("%.3lf", __value); break;
     }
  }

public:

  inline static unsigned short getPrecision() noexcept 
  {
    return Double::precision;
  }

  inline static void setPrecision(unsigned short __precision) noexcept
  {
      Double::precision = ( __precision < SRON_DOUBLE_MIN_PRECISION || __precision > SRON_DOUBLE_MAX_PRECISION) ? SRON_DOUBLE_DEFAULT_PRECISION : __precision;
  }

  inline Double(const SronDouble_t __val = 0) noexcept ;

  inline Double(std::string &val);

  inline Double operator=(double val);
  inline double &operator*();
  inline operator double() const; 

  inline virtual AnyPtr copy() const final override;

  inline virtual void print() const final override;

  inline virtual void formatPrint() const final override;

  inline virtual void preMove() final override;

  inline virtual void fillObuffer(SronOBuffer&) const final override;

  inline virtual long long int sizeOf() const final override;

  inline virtual std::string toString() const final override;
  inline virtual bool isCollective() const final override;

  inline virtual const char *type() const final override;
  inline virtual void type(std::string &str) const final override;

  inline virtual SronTypeNum typeNum() const final override;

  inline virtual SronInt_t getBaseInt() final override;
  inline virtual SronDouble_t getBaseDouble() final override;
  inline virtual SronBool_t getBaseBool() final override;
  
  inline virtual IntPtr getInt() const final override;
  inline virtual DoublePtr getDouble() const final override;
  inline virtual BoolPtr getBool() const final override;

  inline virtual AnyPtr __add__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __sub__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __mult__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __div__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __mod__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __pow__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __isEqual__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __notEqual__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __lessThan__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __lessEqual__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __moreThan__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __moreEqual__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __negate__() const final override;

  inline virtual SronBool_t __not__() const final override;

  inline virtual void __addAssign__(Any& , SronTypeNum) final override;
  inline virtual void __subAssign__(Any& , SronTypeNum) final override;
  inline virtual void __multAssign__(Any& , SronTypeNum) final override;
  inline virtual void __divAssign__(Any& , SronTypeNum) final override;
  inline virtual void __modAssign__(Any& , SronTypeNum) final override;
  inline virtual void __powAssign__(Any& , SronTypeNum) final override;

  inline ~Double() noexcept;
};

class Int final : public Any
{
private:
  SronInt_t value = 0;

public:

  inline Int(const SronInt_t __val = 0) noexcept;
  inline Int(const std::string &val);

  inline Int operator=(SronInt_t &val);
  inline SronInt_t &operator*();

  inline operator SronInt_t() const;

  inline virtual AnyPtr copy() const final override;

  inline virtual void print() const final override;

  inline virtual void formatPrint() const final override;

  inline virtual void preMove() final override;

  inline virtual void fillObuffer(SronOBuffer&) const final override;

  inline virtual long long int sizeOf() const final override;

  inline virtual const char *type() const final override;
  inline virtual void type(std::string &str) const final override;

  inline virtual SronTypeNum typeNum() const final override;
  inline virtual std::string toString() const final override;
  inline virtual bool isCollective() const final override;

  inline virtual SronInt_t getBaseInt() final override;
  inline virtual SronDouble_t getBaseDouble() final override;
  inline virtual SronChar_t getBaseChar() final override;
  inline virtual SronBool_t getBaseBool() final override;

  inline virtual IntPtr getInt() const final override;
  inline virtual DoublePtr getDouble() const final override;
  inline virtual CharPtr getChar() const final override;
  inline virtual BoolPtr getBool() const final override;


  inline virtual AnyPtr __add__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __sub__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __mult__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __div__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __mod__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __pow__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __isEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __notEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __and__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __or__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __not__() const final override;

  inline virtual AnyPtr __xor__(Any & , SronTypeNum) const final override;
  inline virtual AnyPtr __bitAnd__(Any & , SronTypeNum) const final override;
  inline virtual AnyPtr __bitOr__(Any & , SronTypeNum) const final override;
  inline virtual AnyPtr __bitNot__() const final override;
  inline virtual AnyPtr __leftShift__(Any & , SronTypeNum) const final override;
  inline virtual AnyPtr __rightShift__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __lessThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __lessEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreEqual__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __negate__() const final override;

  inline virtual void __addAssign__(Any& , SronTypeNum) final override;
  inline virtual void __subAssign__(Any& , SronTypeNum) final override;
  inline virtual void __multAssign__(Any& , SronTypeNum) final override;
  inline virtual void __divAssign__(Any& , SronTypeNum) final override;
  inline virtual void __modAssign__(Any& , SronTypeNum) final override;
  inline virtual void __powAssign__(Any& , SronTypeNum) final override;

  inline ~Int() noexcept;
};

class Char final : public Any
{

private:
  SronChar_t value = ' ';

public:

  inline Char(const SronChar_t val = '\0') noexcept;

  inline Char operator=(SronChar_t &val);
  inline SronChar_t &operator*() noexcept;
  inline operator SronChar_t() const;

  inline virtual AnyPtr copy() const final override;
  inline virtual void print() const final override;

  inline virtual void formatPrint() const final override;

  inline virtual void preMove() final override;

  inline virtual void fillObuffer(SronOBuffer&) const final override;

  inline virtual long long int sizeOf() const final override;
  inline virtual std::string toString() const final override;
  inline virtual bool isCollective() const final override;
  inline virtual const char *type() const final override;
  inline virtual void type(std::string &str) const final override;
  inline virtual SronTypeNum typeNum() const final override;

  inline virtual SronInt_t getBaseInt() final override;
  inline virtual SronChar_t getBaseChar() final override;

  inline virtual IntPtr getInt() const final override;
  inline virtual StringPtr getString() const final override;
  inline virtual CharPtr getChar() const final override;

  inline CharPtr toLowercase();
  inline CharPtr toUppercase();

  inline virtual AnyPtr __add__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __sub__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __mult__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __div__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __mod__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __pow__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __isEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __notEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __and__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __or__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __not__() const final override;

  inline virtual SronBool_t __lessThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __lessEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreEqual__(Any & , SronTypeNum) const final override;

  inline virtual void __addAssign__(Any& , SronTypeNum) final override;
  inline virtual void __subAssign__(Any& , SronTypeNum) final override;
  inline virtual void __multAssign__(Any& , SronTypeNum) final override;
  inline virtual void __divAssign__(Any& , SronTypeNum) final override;
  inline virtual void __modAssign__(Any& , SronTypeNum) final override;
  inline virtual void __powAssign__(Any& , SronTypeNum) final override;

  inline ~Char() noexcept;
};

class Bool final : public Any
{

private:
  SronBool_t value;

public:

  static AnyBindPtr __SronTrue;
  static AnyBindPtr __SronFalse;

  inline Bool() noexcept;
  inline Bool(SronBool_t val) noexcept;

  inline SronBool_t operator*() noexcept;

  inline virtual AnyPtr copy() const final override;

  inline virtual void print() const final override;

  inline virtual void formatPrint() const final override;

  inline virtual void preMove() final override;

  inline virtual void fillObuffer(SronOBuffer&) const final override;

  inline virtual long long int sizeOf() const final override;

  inline virtual std::string toString() const final override;
  inline virtual bool isCollective() const final override;

  inline virtual const char *type() const final override;

  inline virtual void type(std::string &str) const final override;
  inline virtual SronTypeNum typeNum() const final override;

  inline virtual SronInt_t getBaseInt() final override;
  inline virtual SronBool_t getBaseBool() final override;
  inline virtual SronDouble_t getBaseDouble() final override;

  inline virtual IntPtr getInt() const final override;
  inline virtual BoolPtr getBool() const final override;

  inline SronBool_t GET() const noexcept;

  inline virtual SronBool_t __isEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __notEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __and__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __or__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __not__() const final override;

  inline virtual SronBool_t __lessThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __lessEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreEqual__(Any & , SronTypeNum) const final override;

  inline ~Bool() noexcept;
};

AnyBindPtr Bool::__SronTrue;
AnyBindPtr Bool::__SronFalse;

class String final : public Collective
{

private:
  std::string value;

public:
  typedef std::string SronString_t;


  inline String();
  inline String(SronChar_t);
  inline String(const char*const, unsigned int);
  inline String(const char *const );
  inline String(const std::string &);
  inline String(std::string&&);

  inline virtual AnyPtr copy() const final override;

  inline virtual void print() const final override;
  inline virtual void formatPrint() const final override;
  inline virtual void preMove() final override;
  inline virtual void fillObuffer(SronOBuffer&) const final override;
  inline virtual long long int sizeOf() const final override;
  inline virtual std::string toString() const final override;
  inline virtual bool isCollective() const final override;

  inline virtual const char *type() const final override;

  inline virtual void type(std::string &str) const final override;
  inline virtual SronTypeNum typeNum() const final override;
  inline virtual StringPtr getString() const final override;
  inline virtual ListPtr getList() const final override;
  inline virtual ColPtr getCollective() const final override;

  /* Implementation of methods in Collective... */
  inline virtual AnyBindPtr at(size_t) const final override;
  inline virtual void clear() final override;
  inline virtual void push(AnyPtr val) final override;
  inline virtual void pushWithoutCopy(AnyPtr , SronTypeNum) final override;
  inline virtual AnyBindPtr at(Int &index) final override;
  inline virtual long long int count(Any &) final override;
  inline virtual void drop(Int &index) final override;
  inline virtual long long int index(Any &val) const final override;
  inline virtual void insert(Int &index, AnyPtr &val) final override;
  inline virtual size_t LEN() const final override;
  inline virtual AnyBindPtr pop() final override;
  inline virtual void replace(Any &replacer, Any &replacement) final override;
  inline virtual void reverse() final override;
  inline virtual long long int rIndex(Any &) const final override;
  inline virtual void sort() final override;
  inline virtual void reverseSort() final override;
  inline virtual AnyBindPtr subPart(Int &start_index, Int &end_index) final override;
  inline virtual void update(Int &index, Any &val) final override;

  inline void replace(const std::string &replacer, const std::string &replacement);

  inline void trim();
  inline ListPtr TO_CHAR_LIST();
  inline ListPtr split(Char &);
  inline StringPtr toLowercase();
  inline StringPtr toUppercase();

  inline virtual AnyPtr __add__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __isEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __notEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __lessThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __lessEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreEqual__(Any & , SronTypeNum) const final override;

  inline virtual void __addAssign__(Any& , SronTypeNum) final override;

  inline std::string &operator*() noexcept;

  inline String &operator=(String &&__other) noexcept;

  inline ~String() noexcept;
};

class List final : public Collective
{
public :
  typedef std::vector<AnyBindPtr> SronList_t;
private:

  SronList_t value;
  GarbageCollector::GcSize_t layer;

  inline void updateLayerOfAllElements() noexcept
  {
      for(auto& i : this->value) i->setLayer( this->layer );
  }
  

public:

  inline List(GarbageCollector::GcSize_t __layer = GarbageCollector::__gcStackTopLoc) : layer(__layer) { }

  inline List(const List::SronList_t&);
  inline List(List&);
  inline List(List&&);

  inline List(AnyPtr a);

  inline virtual AnyPtr copy() const final override;

  inline virtual void print() const final override;

  inline virtual void formatPrint() const final override;

  inline virtual void preMove() final override;

  inline virtual void fillObuffer(SronOBuffer&) const final override;

  inline virtual SronTypeNum typeNum() const final override;

  inline virtual long long int sizeOf() const final override;

  inline virtual bool isCollective() const final override;

  inline virtual const char *type() const final override;
  inline virtual void type(std::string &str) const final override;

  inline virtual ListPtr getList() const final override;
  inline virtual ColPtr getCollective() const final override;

  inline virtual AnyBindPtr at(size_t) const final override;
  inline virtual void clear() final override;
  inline virtual void push(AnyPtr val) final override;
  inline virtual void pushWithoutCopy(AnyPtr , SronTypeNum) final override;
  inline virtual AnyBindPtr at(Int &index) final override;
  inline virtual long long int count(Any &val) final override;
  inline virtual void drop(Int &index) final override;
  inline virtual long long int index(Any &val) const final override;
  inline virtual void insert(Int &index, AnyPtr &val) final override;
  inline virtual size_t LEN() const final override;
  inline virtual AnyBindPtr pop() final override;
  inline virtual void replace(Any &replacer, Any &replacement) final override;
  inline virtual void reverse() final override;
  inline virtual long long int rIndex(Any &) const final override;
  inline virtual void sort() final override;
  inline virtual void reverseSort() final override;
  inline virtual AnyBindPtr subPart(Int &start_index, Int &end_index) final override;
  inline virtual void update(Int &index, Any &val) final override;

  inline virtual AnyPtr __add__(Any & , SronTypeNum) const final override;
  inline virtual SronBool_t __isEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __notEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __lessThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __lessEqual__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreThan__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __moreEqual__(Any & , SronTypeNum) const final override;

  inline virtual void __addAssign__(Any& , SronTypeNum) final override;

  inline auto &operator*();

  inline List &operator=(List &&__other) noexcept;

  inline void APPENDS(List&);

  inline void push( AnyPtr , SronTypeNum);

  inline ~List() noexcept;
};


#ifdef SRON_DEBUG_MODE
  ColPtr colCast( AnyPtr __ptr ) { return (reinterpret_cast<ColPtr>             ( __ptr )); }
  VoidPtr voidCast( AnyPtr __ptr ) { return (reinterpret_cast<VoidPtr>          ( __ptr )); }
  IntPtr intCast( AnyPtr __ptr ) { return (reinterpret_cast<IntPtr>             ( __ptr )); }
  DoublePtr doubleCast( AnyPtr __ptr ) { return (reinterpret_cast<DoublePtr>    ( __ptr )); }
  CharPtr charCast( AnyPtr __ptr ) { return (reinterpret_cast<CharPtr>          ( __ptr )); }
  BoolPtr boolCast ( AnyPtr __ptr ) { return (reinterpret_cast<BoolPtr>         ( __ptr )); }
  StringPtr stringCast( AnyPtr __ptr ) { return (reinterpret_cast<StringPtr>    ( __ptr )); }
  ListPtr listCast( AnyPtr __ptr ) { return (reinterpret_cast<ListPtr>          ( __ptr )); }
#else
  #define colCast(    __ptr )   (reinterpret_cast<ColPtr>    ( __ptr ))
  #define voidCast(   __ptr )   (reinterpret_cast<VoidPtr>   ( __ptr ))
  #define intCast(    __ptr )   (reinterpret_cast<IntPtr>    ( __ptr ))
  #define doubleCast( __ptr )   (reinterpret_cast<DoublePtr> ( __ptr ))
  #define charCast(   __ptr )   (reinterpret_cast<CharPtr>   ( __ptr ))
  #define boolCast(   __ptr )   (reinterpret_cast<BoolPtr>   ( __ptr ))
  #define stringCast( __ptr )   (reinterpret_cast<StringPtr> ( __ptr ))
  #define listCast(   __ptr )   (reinterpret_cast<ListPtr>   ( __ptr ))
#endif


#endif