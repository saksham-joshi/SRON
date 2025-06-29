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

#include "exception/_exception_.hpp"
#include "exception/_converter_.hpp"

struct AnyBind;
class Any;
class Collective;
class Void;
class Int;
class Double;
class String;
class Char;
class Bool;
class List;

typedef Any *AnyPtr;
typedef Collective *ColPtr;
typedef Void *VoidPtr;
typedef Int *IntPtr;
typedef Double *DoublePtr;
typedef Char *CharPtr;
typedef Bool *BoolPtr;
typedef String *StringPtr;
typedef List *ListPtr;

typedef std::list<AnyBind> GcLayer;
typedef std::vector<GcLayer> GcStack;
typedef unsigned long GcSize_t;

struct AnyBind final
{
  
  AnyPtr ptr_ = nullptr;
  GcSize_t layer_;

  inline AnyBind(){}

  inline AnyBind& operator=(AnyBind&);

  inline AnyBind(AnyBind&);

  inline AnyBind(AnyPtr, GcSize_t);

  inline AnyBind(AnyBind&&);

  inline Any& operator*();

  inline AnyPtr operator->();

  inline ~AnyBind() noexcept;
};

typedef AnyBind* AnyBindPtr;
typedef AnyBind& AnyBindRef;

/*
 'Any' datatype is the base class for all other datatypes.
  It is inherited by Void, Int, Double, String, Char, Bool, Vector and List.
*/
class Any
{
  public:

    // creates a copy of the current value type.
    inline virtual AnyPtr COPY() const = 0;

    // prints the value of the datatype
    inline virtual void PRINT() const = 0;

    // prints the value in a formatted manner
    inline virtual void F_PRINT() const = 0;

    // function which is called before moving down the value in Garbage Collector
    inline virtual void PREMOVE() = 0;

    inline virtual const char *TYPE() const = 0;

    // prints the type of the datatype
    inline virtual void TYPE(std::string &) const = 0;

    // returns the type number
    inline virtual const unsigned short int TYPE_NUMBER() const = 0;

    // returns the size of the value in bytes
    inline virtual long long int SIZE_OF() const = 0;

    // returns true if value is a collective type of value like string or list
    inline virtual bool IS_COLLECTIVE() const =0;

    // returns the string form of value
    inline virtual std::string TO_STRING() const {
      throw ThrowException("extracting the 'String' from value of type '"+std::string(this->TYPE()) +"' which is not possible");
    }

    // methods to return object's pointers
    inline virtual ColPtr GET_COLLECTIVE() const
    {
      throw ThrowException("extracting the value of type 'Collective' (parent type for type 'List' and 'String' ) from the value of type '" + std::string(this->TYPE()) + "'", InvalidObjectExtractionException);
    }

    inline virtual long long int GET_INT_ABS() {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Int", this->TYPE());
      return 0;
    }
    inline virtual double GET_DOUBLE_ABS() {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Double", this->TYPE());
      return 0;
    }
    inline virtual char GET_CHAR_ABS() {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Char", this->TYPE());
      return ' ';
    }
    inline virtual bool GET_BOOL_ABS() {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Bool", this->TYPE());
      return false;
    }

    inline virtual VoidPtr GET_VOID() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Void", this->TYPE());
      return nullptr;
    }
    inline virtual IntPtr GET_INT() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Int", this->TYPE());
      return nullptr;
    }
    inline virtual DoublePtr GET_DOUBLE() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Double", this->TYPE());
      return nullptr;
    }
    inline virtual StringPtr GET_STRING() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("String", this->TYPE());
      return nullptr;
    }
    inline virtual CharPtr GET_CHAR() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Char", this->TYPE());
      return nullptr;
    }
    inline virtual BoolPtr GET_BOOL() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Bool", this->TYPE());
      return nullptr;
    }
    inline virtual ListPtr GET_LIST() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("List", this->TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __ADD__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("+", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    inline virtual AnyPtr __SUB__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("-", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    inline virtual AnyPtr __MULT__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("*", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    inline virtual AnyPtr __DIV__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("/", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    inline virtual AnyPtr __MOD__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("%", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    inline virtual AnyPtr __POW__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("^", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __XOR__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("xor", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __BITWISE_AND__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("bitwise-and", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __BITWISE_OR__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("bitwise-or", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __BITWISE_NOT__() const
    {
      MATH_EVALUATION_EXCEPTION("bitwise-not", this->TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __LEFT_SHIFT__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("left-shift", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __RIGHT_SHIFT__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("right-shift", this->TYPE(), __x.TYPE());
      return nullptr;
    }


    inline virtual bool __IS_EQUAL__(Any &__x) const = 0;

    inline virtual bool __NOT_EQUAL__(Any &__x) const = 0;

    inline virtual bool __AND__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("&&", this->TYPE(), __x.TYPE());
      return false;
    }
    inline virtual bool __OR__(Any &__x) const
    {
      MATH_EVALUATION_EXCEPTION("||", this->TYPE(), __x.TYPE());
      return false;
    }
    inline virtual bool __NOT__() const
    {
      MATH_EVALUATION_EXCEPTION("!", this->TYPE());
      return false;
    }
    inline virtual AnyPtr __NEGATE__() const
    {
      MATH_EVALUATION_EXCEPTION("-", this->TYPE());
      return nullptr;
    }


    inline virtual bool __LESS_THAN__(Any &__x) const = 0;

    inline virtual bool __LESS_THAN_EQUAL__(Any &__x) const = 0;

    inline virtual bool __MORE_THAN__(Any &__x) const = 0;

    inline virtual bool __MORE_THAN_EQUAL__(Any &__x) const = 0;

    /*
    Calculate and assign operators overload ....!!
    */

    inline virtual void __ADD_AND_ASSIGN__(Any &__x)
    {
      MATH_EVALUATION_EXCEPTION("+=", this->TYPE(), __x.TYPE());
    }

    inline virtual void __MIN_AND_ASSIGN__(Any &__x)
    {
      MATH_EVALUATION_EXCEPTION("-=", this->TYPE(), __x.TYPE());
    }

    inline virtual void __MULT_AND_ASSIGN__(Any &__x) 
    {
      MATH_EVALUATION_EXCEPTION("*=", this->TYPE(), __x.TYPE());
    }

    inline virtual void __DIV_AND_ASSIGN__(Any &__x)
    {
      MATH_EVALUATION_EXCEPTION("/=", this->TYPE(), __x.TYPE());
    }

    inline virtual void __MOD_AND_ASSIGN__(Any &__x) 
    {
      MATH_EVALUATION_EXCEPTION("%=", this->TYPE(), __x.TYPE());
    }

    inline virtual void __POW_AND_ASSIGN__(Any &__x)
    {
      MATH_EVALUATION_EXCEPTION("^=", this->TYPE(), __x.TYPE());
    }

    virtual ~Any() {}
};

inline static AnyBindPtr operator==(Any &, Any &);
inline static AnyBindPtr operator&&(Any &, Any &);
inline static AnyBindPtr operator||(Any &, Any &);
inline static AnyBindPtr operator!=(Any &, Any &);
inline static AnyBindPtr operator!(Any &);
inline static AnyBindPtr operator-(Any &);

inline static AnyBindPtr operator<(Any &, Any &);
inline static AnyBindPtr operator<=(Any &, Any &);
inline static AnyBindPtr operator>(Any &, Any &);
inline static AnyBindPtr operator>=(Any &, Any &);

inline static AnyBindPtr operator+(Any &, Any &);
inline static AnyBindPtr operator-(Any &, Any &);
inline static AnyBindPtr operator*(Any &, Any &);
inline static AnyBindPtr operator/(Any &, Any &);
inline static AnyBindPtr operator%(Any &, Any &);
inline static AnyBindPtr operator^(Any &, Any &);

inline static void operator+=(Any &, Any &);
inline static void operator-=(Any &, Any &);
inline static void operator*=(Any &, Any &);
inline static void operator/=(Any &, Any &);
inline static void operator%=(Any &, Any &);
inline static void operator^=(Any &, Any &);

class Void final : public Any
{

public:
  // this object is returned by all the user-available in-built functions defined in _user_fnc_.hpp::Sron namespace which returns 'Void' type value.
  static AnyBindPtr void_object;

  inline Void();

  // // inline virtual AnyBind &MOVE() override;
  inline virtual AnyPtr COPY() const override;
  inline virtual void PRINT() const override;
  inline virtual void F_PRINT() const override;
  inline virtual void PREMOVE() override;
  inline virtual long long int SIZE_OF() const override;
  inline virtual std::string TO_STRING() const override;
  inline virtual bool IS_COLLECTIVE() const override;
  inline virtual const char *TYPE() const override;
  inline virtual void TYPE(std::string &str) const override;

  inline virtual const unsigned short int TYPE_NUMBER() const override;

  inline virtual VoidPtr GET_VOID() const override;

  // operative methods .
  inline virtual AnyPtr __ADD__(Any &val) const override;

  inline virtual bool __IS_EQUAL__(Any &val) const override;

  inline virtual bool __NOT_EQUAL__(Any &val) const override;

  inline virtual bool __LESS_THAN__(Any &val) const override;

  inline virtual bool __LESS_THAN_EQUAL__(Any &val) const override;

  inline virtual bool __MORE_THAN__(Any &val) const override;

  inline virtual bool __MORE_THAN_EQUAL__(Any &val) const override;

  inline ~Void() noexcept;
};

AnyBindPtr Void::void_object;

class Collective : public Any
{
public:

  // pure virtual methods ...
  inline virtual void CLEAR() = 0;
  inline virtual void PUSH(AnyPtr ) = 0;
  inline virtual void PUSH_WITHOUT_COPY(AnyPtr ) = 0;
  inline virtual size_t LEN() const = 0;
  inline virtual AnyBindPtr AT(size_t) const = 0;

  // returns the value at a particular index
  inline virtual AnyBindPtr AT(Int &)
  {
    CALLING_NON_DEFINED_FUNCTION("at", this->TYPE());
    return Void::void_object;
  }

  // returns the number of occurence of a value
  inline virtual long long int COUNT(Any &val)
  {
    CALLING_NON_DEFINED_FUNCTION("count", this->TYPE());
    return 0;
  }

  // deletes a value at a particular index.
  inline virtual void DELETE_(Int &)
  {
    CALLING_NON_DEFINED_FUNCTION("delete", this->TYPE());
  }

  // returns the first index of occurence of a value
  inline virtual long long int INDEX(Any &val) const
  {
    CALLING_NON_DEFINED_FUNCTION("index", this->TYPE());
    return 0;
  }

  // inserts the value at a particular index
  inline virtual void INSERT(Int &, AnyPtr &)
  {
    CALLING_NON_DEFINED_FUNCTION("insert", this->TYPE());
  }

  // deletes the values at the top and returns its value
  inline virtual AnyBindPtr POP()
  {
    CALLING_NON_DEFINED_FUNCTION("pop", this->TYPE());

    return Void::void_object;
  }

  // replaces a particular value with another value
  inline virtual void REPLACE(Any &, Any &)
  {
    CALLING_NON_DEFINED_FUNCTION("replace", this->TYPE());
  }

  // reverses the value.
  inline virtual void REVERSE()
  {
    CALLING_NON_DEFINED_FUNCTION("reverse", this->TYPE());
  }

  // returns the first occurence of a value from last
  inline virtual long long int RINDEX(Any &) const
  {
    CALLING_NON_DEFINED_FUNCTION("rindex", this->TYPE());
    return 0;
  }

  // completely overrides this->value with the passed value.
  inline virtual void SET(AnyBind &)
  {
    CALLING_NON_DEFINED_FUNCTION("set", this->TYPE());
  }

  // sorts the values.
  inline virtual void SORT()
  {
    CALLING_NON_DEFINED_FUNCTION("sort", this->TYPE());
  }

  // sorts the values in revese order
  inline virtual void REVERSE_SORT(){
    CALLING_NON_DEFINED_FUNCTION("reverse_sort", this->TYPE());
  }

  // extracts a part of a value within two indexes.
  inline virtual AnyBindPtr SUBPART(Int &, Int &)
  {
    CALLING_NON_DEFINED_FUNCTION("subpart", this->TYPE());
    return Void::void_object;
  }

  // updates/overrides the value at a particular index
  inline virtual void UPDATE(Int &, Any &)
  {
    CALLING_NON_DEFINED_FUNCTION("update", this->TYPE());
  }
};

/*
 * Classes are defined in the following flow :
 * 1. Private values of primitive datatypes in c++.
 * 2. Constructors.
 * 3. Abstract Methods like LEN, PRINT, SIZE_OF, TO_STRING, TYPE etc.
 * 4. object extraction methods
 * 5. operatorive dunder methods
 * 6. dedicated methods only available to that certain class like GET, SET,
 * 7. Destructor.
 */



class Double final : public Any
{
private:
  double value = 0;

public:
  inline Double();
  inline Double(double val);

  inline Double(std::string &val);

  inline Double operator=(double val);
  inline double &operator*();
  inline operator double() const; 

  // // inline virtual AnyBind &MOVE() override;
  inline virtual AnyPtr COPY() const override;

  inline virtual void PRINT() const override;

  inline virtual void F_PRINT() const override;

  inline virtual void PREMOVE() override;

  inline virtual long long int SIZE_OF() const override;

  inline virtual std::string TO_STRING() const override;
  inline virtual bool IS_COLLECTIVE() const override;

  inline virtual const char *TYPE() const override;
  inline virtual void TYPE(std::string &str) const override;

  inline virtual const unsigned short int TYPE_NUMBER() const override;

  inline virtual long long int GET_INT_ABS() override;
  inline virtual double GET_DOUBLE_ABS() override;
  inline virtual bool GET_BOOL_ABS() override;
  
  inline virtual IntPtr GET_INT() const override;
  inline virtual DoublePtr GET_DOUBLE() const override;
  inline virtual BoolPtr GET_BOOL() const override;

  inline void SET(double &value);

  inline virtual AnyPtr __ADD__(Any &val) const override;

  inline virtual AnyPtr __SUB__(Any &val) const override;

  inline virtual AnyPtr __MULT__(Any &val) const override;

  inline virtual AnyPtr __DIV__(Any &val) const override;

  inline virtual AnyPtr __MOD__(Any &val) const override;

  inline virtual AnyPtr __POW__(Any &val) const override;

  inline virtual bool __IS_EQUAL__(Any &val) const override;

  inline virtual bool __NOT_EQUAL__(Any &val) const override;

  inline virtual bool __LESS_THAN__(Any &val) const override;

  inline virtual bool __LESS_THAN_EQUAL__(Any &val) const override;

  inline virtual bool __MORE_THAN__(Any &val) const override;

  inline virtual bool __MORE_THAN_EQUAL__(Any &val) const override;

  inline virtual AnyPtr __NEGATE__() const override;

  inline virtual void __ADD_AND_ASSIGN__(Any&) override;
  inline virtual void __MIN_AND_ASSIGN__(Any&) override;
  inline virtual void __MULT_AND_ASSIGN__(Any&) override;
  inline virtual void __DIV_AND_ASSIGN__(Any&) override;
  inline virtual void __MOD_AND_ASSIGN__(Any&) override;
  inline virtual void __POW_AND_ASSIGN__(Any&) override;

  inline ~Double() noexcept;
};

class Int final : public Any
{
private:
  long long int value = 0;

public:
  inline Int();
  inline Int(const long long int val);
  inline Int(const std::string &val);

  inline Int operator=(long long int &val);
  inline long long int &operator*();

  inline operator long long int() const;

  // inline virtual AnyBind &MOVE() override;
  inline virtual AnyPtr COPY() const override;

  inline virtual void PRINT() const override;

  inline virtual void F_PRINT() const override;

  inline virtual void PREMOVE() override;

  inline virtual long long int SIZE_OF() const override;

  inline virtual const char *TYPE() const override;
  inline virtual void TYPE(std::string &str) const override;

  inline virtual const unsigned short int TYPE_NUMBER() const override;
  inline virtual std::string TO_STRING() const override;
  inline virtual bool IS_COLLECTIVE() const override;

  inline virtual long long int GET_INT_ABS() override;
  inline virtual double GET_DOUBLE_ABS() override;
  inline virtual char GET_CHAR_ABS() override;
  inline virtual bool GET_BOOL_ABS() override;

  inline virtual IntPtr GET_INT() const override;
  inline virtual DoublePtr GET_DOUBLE() const override;
  inline virtual CharPtr GET_CHAR() const override;
  inline virtual BoolPtr GET_BOOL() const override;

  //inline void SET(const long long int value);

  inline virtual AnyPtr __ADD__(Any &val) const override;

  inline virtual AnyPtr __SUB__(Any &val) const override;

  inline virtual AnyPtr __MULT__(Any &val) const override;

  inline virtual AnyPtr __DIV__(Any &val) const override;

  inline virtual AnyPtr __MOD__(Any &val) const override;

  inline virtual AnyPtr __POW__(Any &val) const override;

  inline virtual bool __IS_EQUAL__(Any &val) const override;

  inline virtual bool __NOT_EQUAL__(Any &val) const override;

  inline virtual bool __AND__(Any &val) const override;

  inline virtual bool __OR__(Any &val) const override;

  inline virtual bool __NOT__() const override;

  inline virtual AnyPtr __XOR__(Any &) const override;
  inline virtual AnyPtr __BITWISE_AND__(Any &) const override;
  inline virtual AnyPtr __BITWISE_OR__(Any &) const override;
  inline virtual AnyPtr __BITWISE_NOT__() const override;
  inline virtual AnyPtr __LEFT_SHIFT__(Any &) const override;
  inline virtual AnyPtr __RIGHT_SHIFT__(Any &) const override;

  inline virtual bool __LESS_THAN__(Any &val) const override;

  inline virtual bool __LESS_THAN_EQUAL__(Any &val) const override;

  inline virtual bool __MORE_THAN__(Any &val) const override;

  inline virtual bool __MORE_THAN_EQUAL__(Any &val) const override;

  inline virtual AnyPtr __NEGATE__() const override;

  inline virtual void __ADD_AND_ASSIGN__(Any&) override;
  inline virtual void __MIN_AND_ASSIGN__(Any&) override;
  inline virtual void __MULT_AND_ASSIGN__(Any&) override;
  inline virtual void __DIV_AND_ASSIGN__(Any&) override;
  inline virtual void __MOD_AND_ASSIGN__(Any&) override;
  inline virtual void __POW_AND_ASSIGN__(Any&) override;

  inline ~Int() noexcept;
};

class Char final : public Any
{

private:
  char value = ' ';

public:
  inline Char();
  inline Char(const char &val);

  inline Char operator=(char &val);
  inline char &operator*();
  inline operator char() const;

  // inline virtual AnyBind &MOVE() override;
  inline virtual AnyPtr COPY() const override;
  inline virtual void PRINT() const override;

  inline virtual void F_PRINT() const override;

  inline virtual void PREMOVE() override;

  inline virtual long long int SIZE_OF() const override;
  inline virtual std::string TO_STRING() const override;
  inline virtual bool IS_COLLECTIVE() const override;
  inline virtual const char *TYPE() const override;
  inline virtual void TYPE(std::string &str) const override;
  inline virtual const unsigned short int TYPE_NUMBER() const override;

  inline virtual long long int GET_INT_ABS() override;
  inline virtual char GET_CHAR_ABS() override;

  inline virtual IntPtr GET_INT() const override;
  inline virtual StringPtr GET_STRING() const override;
  inline virtual CharPtr GET_CHAR() const override;

  inline void SET(char &value);

  inline CharPtr TO_LOWERCASE();
  inline CharPtr TO_UPPERCASE();

  inline virtual AnyPtr __ADD__(Any &val) const override;

  inline virtual AnyPtr __SUB__(Any &val) const override;

  inline virtual AnyPtr __MULT__(Any &val) const override;

  inline virtual AnyPtr __DIV__(Any &val) const override;

  inline virtual AnyPtr __MOD__(Any &val) const override;

  inline virtual AnyPtr __POW__(Any &val) const override;

  inline virtual bool __IS_EQUAL__(Any &val) const override;

  inline virtual bool __NOT_EQUAL__(Any &val) const override;

  inline virtual bool __AND__(Any &val) const override;

  inline virtual bool __OR__(Any &val) const override;

  inline virtual bool __NOT__() const override;

  inline virtual bool __LESS_THAN__(Any &val) const override;

  inline virtual bool __LESS_THAN_EQUAL__(Any &val) const override;

  inline virtual bool __MORE_THAN__(Any &val) const override;

  inline virtual bool __MORE_THAN_EQUAL__(Any &val) const override;

  inline virtual void __ADD_AND_ASSIGN__(Any&) override;
  inline virtual void __MIN_AND_ASSIGN__(Any&) override;
  inline virtual void __MULT_AND_ASSIGN__(Any&) override;
  inline virtual void __DIV_AND_ASSIGN__(Any&) override;
  inline virtual void __MOD_AND_ASSIGN__(Any&) override;
  inline virtual void __POW_AND_ASSIGN__(Any&) override;

  inline ~Char() noexcept;
};

class Bool final : public Any
{

private:
  bool value;

public:
  static AnyBindPtr __SronTrue;
  static AnyBindPtr __SronFalse;

  inline Bool();
  inline Bool(bool val);

  inline bool operator*();

  // inline virtual AnyBind &MOVE() override;
  inline virtual AnyPtr COPY() const override;

  inline virtual void PRINT() const override;

  inline virtual void F_PRINT() const override;

  inline virtual void PREMOVE() override;

  inline virtual long long int SIZE_OF() const override;

  inline virtual std::string TO_STRING() const override;
  inline virtual bool IS_COLLECTIVE() const override;

  inline virtual const char *TYPE() const override;

  inline virtual void TYPE(std::string &str) const override;
  inline virtual const unsigned short int TYPE_NUMBER() const override;

  inline virtual long long int GET_INT_ABS() override;
  inline virtual bool GET_BOOL_ABS() override;
  inline virtual double GET_DOUBLE_ABS() override;

  inline virtual IntPtr GET_INT() const override;
  inline virtual BoolPtr GET_BOOL() const override;

  inline bool GET() const noexcept;

  inline virtual bool __IS_EQUAL__(Any &val) const override;

  inline virtual bool __NOT_EQUAL__(Any &val) const override;

  inline virtual bool __AND__(Any &val) const override;

  inline virtual bool __OR__(Any &val) const override;

  inline virtual bool __NOT__() const override;

  inline virtual bool __LESS_THAN__(Any &val) const override;

  inline virtual bool __LESS_THAN_EQUAL__(Any &val) const override;

  inline virtual bool __MORE_THAN__(Any &val) const override;

  inline virtual bool __MORE_THAN_EQUAL__(Any &val) const override;

  inline ~Bool() noexcept;
};

// The both below values will not be registered in GarbageCollector and will be destructed automatically
AnyBindPtr Bool::__SronTrue;
AnyBindPtr Bool::__SronFalse;

class String final : public Collective
{

private:
  std::string value;

public:
  inline String();
  inline String(char ch);
  inline String(const char *const &str);
  inline String(const std::string &str);
  inline String(std::string&&);

  // inline String operator=(std::string &str);

  // inline std::string &operator*();

  // inline virtual AnyBind &MOVE() override;
  inline virtual AnyPtr COPY() const override;

  inline virtual void PRINT() const override;
  inline virtual void F_PRINT() const override;
  inline virtual void PREMOVE() override;
  inline virtual long long int SIZE_OF() const override;
  inline virtual std::string TO_STRING() const override;
  inline virtual bool IS_COLLECTIVE() const override;

  inline virtual const char *TYPE() const override;

  inline virtual void TYPE(std::string &str) const override;
  inline virtual const unsigned short int TYPE_NUMBER() const override;
  inline virtual StringPtr GET_STRING() const override;
  inline virtual ListPtr GET_LIST() const override;
  inline virtual ColPtr GET_COLLECTIVE() const override;

  /* Implementation of methods in Collective... */
  inline virtual AnyBindPtr AT(size_t) const override;
  inline virtual void CLEAR() override;
  inline virtual void PUSH(AnyPtr val) override;
  inline virtual void PUSH_WITHOUT_COPY(AnyPtr) override;
  inline virtual AnyBindPtr AT(Int &index) override;
  inline virtual long long int COUNT(Any &val) override;
  inline virtual void DELETE_(Int &index) override;
  inline virtual long long int INDEX(Any &val) const override;
  inline virtual void INSERT(Int &index, AnyPtr &val) override;
  inline virtual size_t LEN() const override;
  inline virtual AnyBindPtr POP() override;
  inline virtual void REPLACE(Any &replacer, Any &replacement) override;
  inline virtual void REVERSE() override;
  inline virtual long long int RINDEX(Any &) const override;
  inline virtual void SET(AnyBind &val) override;
  inline virtual void SORT() override;
  inline virtual void REVERSE_SORT() override;
  inline virtual AnyBindPtr SUBPART(Int &start_index, Int &end_index) override;
  inline virtual void UPDATE(Int &index, Any &val) override;

  // inline char &AT(const int &);
  // // inline long long int RINDEX(const char&);
  inline void REPLACE(const std::string &replacer, const std::string &replacement);

  inline void TRIM();
  inline ListPtr TO_CHAR_LIST();
  inline ListPtr SPLIT(Char &);
  inline StringPtr TO_LOWERCASE();
  inline StringPtr TO_UPPERCASE();

  inline virtual AnyPtr __ADD__(Any &val) const override;

  inline virtual bool __IS_EQUAL__(Any &val) const override;

  inline virtual bool __NOT_EQUAL__(Any &val) const override;

  inline virtual bool __LESS_THAN__(Any &val) const override;

  inline virtual bool __LESS_THAN_EQUAL__(Any &val) const override;

  inline virtual bool __MORE_THAN__(Any &val) const override;

  inline virtual bool __MORE_THAN_EQUAL__(Any &val) const override;

  inline virtual void __ADD_AND_ASSIGN__(Any&) override;

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
  GcSize_t layer;

  inline void UPDATE_LAYER_OF_ALL_ELEMENTS(){
    for(auto& i : this->value){
      i->layer_ = this->layer;
    }
  }
  

public:

  inline List(GcSize_t) ;

  inline List(const List::SronList_t&);
  inline List(List&);

  inline List(AnyPtr a);

  // inline virtual AnyBind &MOVE() override;
  inline virtual AnyPtr COPY() const override;

  inline virtual void PRINT() const override;

  inline virtual void F_PRINT() const override;

  inline virtual void PREMOVE() override;

  inline virtual const unsigned short int TYPE_NUMBER() const override;

  inline virtual long long int SIZE_OF() const override;

  inline virtual bool IS_COLLECTIVE() const override;

  inline virtual const char *TYPE() const override;
  inline virtual void TYPE(std::string &str) const override;

  inline virtual ListPtr GET_LIST() const override;
  inline virtual ColPtr GET_COLLECTIVE() const override;

  inline virtual AnyBindPtr AT(size_t) const override;
  inline virtual void CLEAR() override;
  inline virtual void PUSH(AnyPtr val) override;
  inline virtual void PUSH_WITHOUT_COPY(AnyPtr) override;
  inline virtual AnyBindPtr AT(Int &index) override;
  inline virtual long long int COUNT(Any &val) override;
  inline virtual void DELETE_(Int &index) override;
  inline virtual long long int INDEX(Any &val) const override;
  inline virtual void INSERT(Int &index, AnyPtr &val) override;
  inline virtual size_t LEN() const override;
  inline virtual AnyBindPtr POP() override;
  inline virtual void REPLACE(Any &replacer, Any &replacement) override;
  inline virtual void REVERSE() override;
  inline virtual long long int RINDEX(Any &) const override;
  inline virtual void SET(AnyBind &val) override;
  inline virtual void SORT() override;
  inline virtual void REVERSE_SORT() override;
  inline virtual AnyBindPtr SUBPART(Int &start_index, Int &end_index) override;
  inline virtual void UPDATE(Int &index, Any &val) override;

  inline virtual AnyPtr __ADD__(Any &val) const override;
  inline virtual bool __IS_EQUAL__(Any &val) const override;

  inline virtual bool __NOT_EQUAL__(Any &val) const override;

  inline virtual bool __LESS_THAN__(Any &val) const override;

  inline virtual bool __LESS_THAN_EQUAL__(Any &val) const override;

  inline virtual bool __MORE_THAN__(Any &val) const override;

  inline virtual bool __MORE_THAN_EQUAL__(Any &val) const override;

  inline virtual void __ADD_AND_ASSIGN__(Any&) override;

  inline auto &operator*();

  inline List &operator=(List &&__other) noexcept;

  inline void APPENDS(List&);

  inline ~List() noexcept;

  inline static bool _ASCENDING_SORT_ROUTINE_METHOD_(Any& __val1, Any& __val2){

    return (__val1.TYPE_NUMBER() == __val2.TYPE_NUMBER())? __val1.__LESS_THAN__(__val2):__val1.TYPE_NUMBER() < __val2.TYPE_NUMBER();

  }

  inline static bool _DESCENDING_SORT_ROUTINE_METHOD_(Any& __val1, Any& __val2){

    return (__val1.TYPE_NUMBER() == __val2.TYPE_NUMBER())? __val1.__MORE_THAN__(__val2):__val1.TYPE_NUMBER() > __val2.TYPE_NUMBER();

  }
};

#endif