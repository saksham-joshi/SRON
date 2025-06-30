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
    [[gnu::always_inline]] [[gnu::hot]] [[nodiscard]] inline virtual AnyPtr COPY() const = 0;

    // prints the value of the datatype
    [[gnu::always_inline]] [[gnu::hot]] inline virtual void PRINT() const = 0;

    // prints the value in a formatted manner
    [[gnu::always_inline]] [[gnu::hot]] inline virtual void F_PRINT() const = 0;

    // function which is called before moving down the value in Garbage Collector
    [[gnu::always_inline]] [[gnu::hot]] inline virtual void PREMOVE() = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void FILL_OBUFFER( SronOBuffer&) const = 0;

    inline virtual const char *TYPE() const = 0;

    // prints the type of the datatype
    inline virtual void TYPE(std::string &) const = 0;

    // returns the type number
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronTypeNum TYPE_NUMBER() const = 0;

    // returns the size of the value in bytes
    inline virtual long long int SIZE_OF() const = 0;

    // returns true if value is a collective type of value like string or list
    [[gnu::always_inline]] [[gnu::hot]] inline virtual bool IS_COLLECTIVE() const =0;

    // returns the string form of value
    inline virtual std::string TO_STRING() const {
      throw ThrowException("extracting the 'String' from value of type '"+std::string(this->TYPE()) +"' which is not possible");
    }

    // methods to return object's pointers
    [[gnu::always_inline]] [[gnu::hot]] inline virtual ColPtr GET_COLLECTIVE() const
    {
      throw ThrowException("extracting the value of type 'Collective' (parent type for type 'List' and 'String' ) from the value of type '" + std::string(this->TYPE()) + "'", SronException::InvalidObjectExtractionException);
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronInt_t GET_INT_ABS() {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Int", this->TYPE());
      return 0;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronDouble_t GET_DOUBLE_ABS() {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Double", this->TYPE());
      return 0;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronChar_t GET_CHAR_ABS() {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Char", this->TYPE());
      return ' ';
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t GET_BOOL_ABS() {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Bool", this->TYPE());
      return false;
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual VoidPtr GET_VOID() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Void", this->TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual IntPtr GET_INT() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Int", this->TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual DoublePtr GET_DOUBLE() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Double", this->TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual StringPtr GET_STRING() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("String", this->TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual CharPtr GET_CHAR() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Char", this->TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual BoolPtr GET_BOOL() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("Bool", this->TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual ListPtr GET_LIST() const
    {
      THROW_INVALID_OBJECT_EXTRACTION_EXCEPTION("List", this->TYPE());
      return nullptr;
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __ADD__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("+", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __SUB__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("-", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __MULT__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("*", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __DIV__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("/", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __MOD__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("%", this->TYPE(), __x.TYPE());
      return nullptr;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __POW__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("^", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __XOR__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("xor", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __BITWISE_AND__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("bitwise-and", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __BITWISE_OR__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("bitwise-or", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __BITWISE_NOT__() const
    {
      MATH_EVALUATION_EXCEPTION("bitwise-not", this->TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __LEFT_SHIFT__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("left-shift", this->TYPE(), __x.TYPE());
      return nullptr;
    }

    inline virtual AnyPtr __RIGHT_SHIFT__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("right-shift", this->TYPE(), __x.TYPE());
      return nullptr;
    }


    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __IS_EQUAL__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __NOT_EQUAL__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __AND__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("&&", this->TYPE(), __x.TYPE());
      return false;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __OR__(Any &__x , SronTypeNum) const
    {
      MATH_EVALUATION_EXCEPTION("||", this->TYPE(), __x.TYPE());
      return false;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __NOT__() const
    {
      MATH_EVALUATION_EXCEPTION("!", this->TYPE());
      return false;
    }
    [[gnu::always_inline]] [[gnu::hot]] inline virtual AnyPtr __NEGATE__() const
    {
      MATH_EVALUATION_EXCEPTION("-", this->TYPE());
      return nullptr;
    }


    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __LESS_THAN__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __LESS_THAN_EQUAL__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __MORE_THAN__(Any &__x , SronTypeNum) const = 0;

    [[gnu::always_inline]] [[gnu::hot]] inline virtual SronBool_t __MORE_THAN_EQUAL__(Any &__x , SronTypeNum) const = 0;

    /*
    Calculate and assign operators overload ....!!
    */

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __ADD_AND_ASSIGN__(Any &__x , SronTypeNum)
    {
      MATH_EVALUATION_EXCEPTION("+=", this->TYPE(), __x.TYPE());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __MIN_AND_ASSIGN__(Any &__x , SronTypeNum)
    {
      MATH_EVALUATION_EXCEPTION("-=", this->TYPE(), __x.TYPE());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __MULT_AND_ASSIGN__(Any &__x , SronTypeNum) 
    {
      MATH_EVALUATION_EXCEPTION("*=", this->TYPE(), __x.TYPE());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __DIV_AND_ASSIGN__(Any &__x , SronTypeNum)
    {
      MATH_EVALUATION_EXCEPTION("/=", this->TYPE(), __x.TYPE());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __MOD_AND_ASSIGN__(Any &__x , SronTypeNum) 
    {
      MATH_EVALUATION_EXCEPTION("%=", this->TYPE(), __x.TYPE());
    }

    [[gnu::always_inline]] [[gnu::hot]] inline virtual void __POW_AND_ASSIGN__(Any &__x , SronTypeNum)
    {
      MATH_EVALUATION_EXCEPTION("^=", this->TYPE(), __x.TYPE());
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

  inline virtual AnyPtr COPY() const final override;
  inline virtual void PRINT() const final override;
  inline virtual void F_PRINT() const final override;
  inline virtual void PREMOVE() final override;
  inline virtual void FILL_OBUFFER(SronOBuffer&) const final override;
  inline virtual long long int SIZE_OF() const final override;
  inline virtual std::string TO_STRING() const final override;
  inline virtual bool IS_COLLECTIVE() const final override;
  inline virtual const char *TYPE() const final override;
  inline virtual void TYPE(std::string &str) const final override;

  inline virtual SronTypeNum TYPE_NUMBER() const final override;

  inline virtual VoidPtr GET_VOID() const final override;

  inline virtual SronBool_t __IS_EQUAL__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __NOT_EQUAL__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN_EQUAL__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN_EQUAL__(Any &, SronTypeNum) const final override;

  inline ~Void() noexcept;
};

AnyBindPtr Void::void_object;

class Collective : public Any
{
public:

  // pure virtual methods ...
  inline virtual void CLEAR() = 0;
  inline virtual void PUSH(AnyPtr ) = 0;
  inline virtual void PUSH_WITHOUT_COPY(AnyPtr , SronTypeNum ) = 0;
  inline virtual size_t LEN() const = 0;
  inline virtual AnyBindPtr AT(size_t) const = 0;

  // returns the value at a particular index
  inline virtual AnyBindPtr AT(Int &)
  {
    CALLING_NON_DEFINED_FUNCTION("at", this->TYPE());
    return Void::void_object;
  }

  // returns the number of occurence of a value
  inline virtual long long int COUNT(Any &)
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
  inline virtual long long int INDEX(Any &) const
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
  // inline virtual void SET(AnyBind &)
  // {
  //   CALLING_NON_DEFINED_FUNCTION("set", this->TYPE());
  // }

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
      case 1 : printf_s("%.1lf", __value); break;

      case 2 : printf_s("%.2lf", __value); break;

      case 4 : printf_s("%.4lf", __value); break;

      case 5 : printf_s("%.5lf", __value); break;

      case 6 : printf_s("%.6lf", __value); break;

      case 7 : printf_s("%.7lf", __value); break;

      case 8 : printf_s("%.8lf" , __value); break;

      default : printf_s("%.3lf", __value); break;
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

  inline virtual AnyPtr COPY() const final override;

  inline virtual void PRINT() const final override;

  inline virtual void F_PRINT() const final override;

  inline virtual void PREMOVE() final override;

  inline virtual void FILL_OBUFFER(SronOBuffer&) const final override;

  inline virtual long long int SIZE_OF() const final override;

  inline virtual std::string TO_STRING() const final override;
  inline virtual bool IS_COLLECTIVE() const final override;

  inline virtual const char *TYPE() const final override;
  inline virtual void TYPE(std::string &str) const final override;

  inline virtual SronTypeNum TYPE_NUMBER() const final override;

  inline virtual SronInt_t GET_INT_ABS() final override;
  inline virtual SronDouble_t GET_DOUBLE_ABS() final override;
  inline virtual SronBool_t GET_BOOL_ABS() final override;
  
  inline virtual IntPtr GET_INT() const final override;
  inline virtual DoublePtr GET_DOUBLE() const final override;
  inline virtual BoolPtr GET_BOOL() const final override;

  inline virtual AnyPtr __ADD__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __SUB__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __MULT__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __DIV__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __MOD__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __POW__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __IS_EQUAL__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __NOT_EQUAL__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN_EQUAL__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN__(Any &, SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN_EQUAL__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __NEGATE__() const final override;

  inline virtual SronBool_t __NOT__() const final override;

  inline virtual void __ADD_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __MIN_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __MULT_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __DIV_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __MOD_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __POW_AND_ASSIGN__(Any& , SronTypeNum) final override;

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

  inline virtual AnyPtr COPY() const final override;

  inline virtual void PRINT() const final override;

  inline virtual void F_PRINT() const final override;

  inline virtual void PREMOVE() final override;

  inline virtual void FILL_OBUFFER(SronOBuffer&) const final override;

  inline virtual long long int SIZE_OF() const final override;

  inline virtual const char *TYPE() const final override;
  inline virtual void TYPE(std::string &str) const final override;

  inline virtual SronTypeNum TYPE_NUMBER() const final override;
  inline virtual std::string TO_STRING() const final override;
  inline virtual bool IS_COLLECTIVE() const final override;

  inline virtual SronInt_t GET_INT_ABS() final override;
  inline virtual SronDouble_t GET_DOUBLE_ABS() final override;
  inline virtual SronChar_t GET_CHAR_ABS() final override;
  inline virtual SronBool_t GET_BOOL_ABS() final override;

  inline virtual IntPtr GET_INT() const final override;
  inline virtual DoublePtr GET_DOUBLE() const final override;
  inline virtual CharPtr GET_CHAR() const final override;
  inline virtual BoolPtr GET_BOOL() const final override;


  inline virtual AnyPtr __ADD__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __SUB__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __MULT__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __DIV__(Any &, SronTypeNum) const final override;

  inline virtual AnyPtr __MOD__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __POW__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __IS_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __NOT_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __AND__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __OR__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __NOT__() const final override;

  inline virtual AnyPtr __XOR__(Any & , SronTypeNum) const final override;
  inline virtual AnyPtr __BITWISE_AND__(Any & , SronTypeNum) const final override;
  inline virtual AnyPtr __BITWISE_OR__(Any & , SronTypeNum) const final override;
  inline virtual AnyPtr __BITWISE_NOT__() const final override;
  inline virtual AnyPtr __LEFT_SHIFT__(Any & , SronTypeNum) const final override;
  inline virtual AnyPtr __RIGHT_SHIFT__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __NEGATE__() const final override;

  inline virtual void __ADD_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __MIN_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __MULT_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __DIV_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __MOD_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __POW_AND_ASSIGN__(Any& , SronTypeNum) final override;

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

  inline virtual AnyPtr COPY() const final override;
  inline virtual void PRINT() const final override;

  inline virtual void F_PRINT() const final override;

  inline virtual void PREMOVE() final override;

  inline virtual void FILL_OBUFFER(SronOBuffer&) const final override;

  inline virtual long long int SIZE_OF() const final override;
  inline virtual std::string TO_STRING() const final override;
  inline virtual bool IS_COLLECTIVE() const final override;
  inline virtual const char *TYPE() const final override;
  inline virtual void TYPE(std::string &str) const final override;
  inline virtual SronTypeNum TYPE_NUMBER() const final override;

  inline virtual SronInt_t GET_INT_ABS() final override;
  inline virtual SronChar_t GET_CHAR_ABS() final override;

  inline virtual IntPtr GET_INT() const final override;
  inline virtual StringPtr GET_STRING() const final override;
  inline virtual CharPtr GET_CHAR() const final override;

  inline CharPtr TO_LOWERCASE();
  inline CharPtr TO_UPPERCASE();

  inline virtual AnyPtr __ADD__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __SUB__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __MULT__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __DIV__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __MOD__(Any & , SronTypeNum) const final override;

  inline virtual AnyPtr __POW__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __IS_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __NOT_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __AND__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __OR__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __NOT__() const final override;

  inline virtual SronBool_t __LESS_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual void __ADD_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __MIN_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __MULT_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __DIV_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __MOD_AND_ASSIGN__(Any& , SronTypeNum) final override;
  inline virtual void __POW_AND_ASSIGN__(Any& , SronTypeNum) final override;

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

  inline virtual AnyPtr COPY() const final override;

  inline virtual void PRINT() const final override;

  inline virtual void F_PRINT() const final override;

  inline virtual void PREMOVE() final override;

  inline virtual void FILL_OBUFFER(SronOBuffer&) const final override;

  inline virtual long long int SIZE_OF() const final override;

  inline virtual std::string TO_STRING() const final override;
  inline virtual bool IS_COLLECTIVE() const final override;

  inline virtual const char *TYPE() const final override;

  inline virtual void TYPE(std::string &str) const final override;
  inline virtual SronTypeNum TYPE_NUMBER() const final override;

  inline virtual SronInt_t GET_INT_ABS() final override;
  inline virtual SronBool_t GET_BOOL_ABS() final override;
  inline virtual SronDouble_t GET_DOUBLE_ABS() final override;

  inline virtual IntPtr GET_INT() const final override;
  inline virtual BoolPtr GET_BOOL() const final override;

  inline SronBool_t GET() const noexcept;

  inline virtual SronBool_t __IS_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __NOT_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __AND__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __OR__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __NOT__() const final override;

  inline virtual SronBool_t __LESS_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN_EQUAL__(Any & , SronTypeNum) const final override;

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

  inline virtual AnyPtr COPY() const final override;

  inline virtual void PRINT() const final override;
  inline virtual void F_PRINT() const final override;
  inline virtual void PREMOVE() final override;
  inline virtual void FILL_OBUFFER(SronOBuffer&) const final override;
  inline virtual long long int SIZE_OF() const final override;
  inline virtual std::string TO_STRING() const final override;
  inline virtual bool IS_COLLECTIVE() const final override;

  inline virtual const char *TYPE() const final override;

  inline virtual void TYPE(std::string &str) const final override;
  inline virtual SronTypeNum TYPE_NUMBER() const final override;
  inline virtual StringPtr GET_STRING() const final override;
  inline virtual ListPtr GET_LIST() const final override;
  inline virtual ColPtr GET_COLLECTIVE() const final override;

  /* Implementation of methods in Collective... */
  inline virtual AnyBindPtr AT(size_t) const final override;
  inline virtual void CLEAR() final override;
  inline virtual void PUSH(AnyPtr val) final override;
  inline virtual void PUSH_WITHOUT_COPY(AnyPtr , SronTypeNum) final override;
  inline virtual AnyBindPtr AT(Int &index) final override;
  inline virtual long long int COUNT(Any &) final override;
  inline virtual void DELETE_(Int &index) final override;
  inline virtual long long int INDEX(Any &val) const final override;
  inline virtual void INSERT(Int &index, AnyPtr &val) final override;
  inline virtual size_t LEN() const final override;
  inline virtual AnyBindPtr POP() final override;
  inline virtual void REPLACE(Any &replacer, Any &replacement) final override;
  inline virtual void REVERSE() final override;
  inline virtual long long int RINDEX(Any &) const final override;
  inline virtual void SORT() final override;
  inline virtual void REVERSE_SORT() final override;
  inline virtual AnyBindPtr SUBPART(Int &start_index, Int &end_index) final override;
  inline virtual void UPDATE(Int &index, Any &val) final override;

  inline void REPLACE(const std::string &replacer, const std::string &replacement);

  inline void TRIM();
  inline ListPtr TO_CHAR_LIST();
  inline ListPtr SPLIT(Char &);
  inline StringPtr TO_LOWERCASE();
  inline StringPtr TO_UPPERCASE();

  inline virtual AnyPtr __ADD__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __IS_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __NOT_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual void __ADD_AND_ASSIGN__(Any& , SronTypeNum) final override;

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

  inline void UPDATE_LAYER_OF_ALL_ELEMENTS() noexcept
  {
      for(auto& i : this->value) i->setLayer( this->layer );
  }
  

public:

  inline List(GarbageCollector::GcSize_t __layer = GarbageCollector::__gcStackTopLoc) : layer(__layer) { }

  inline List(const List::SronList_t&);
  inline List(List&);
  inline List(List&&);

  inline List(AnyPtr a);

  inline virtual AnyPtr COPY() const final override;

  inline virtual void PRINT() const final override;

  inline virtual void F_PRINT() const final override;

  inline virtual void PREMOVE() final override;

  inline virtual void FILL_OBUFFER(SronOBuffer&) const final override;

  inline virtual SronTypeNum TYPE_NUMBER() const final override;

  inline virtual long long int SIZE_OF() const final override;

  inline virtual bool IS_COLLECTIVE() const final override;

  inline virtual const char *TYPE() const final override;
  inline virtual void TYPE(std::string &str) const final override;

  inline virtual ListPtr GET_LIST() const final override;
  inline virtual ColPtr GET_COLLECTIVE() const final override;

  inline virtual AnyBindPtr AT(size_t) const final override;
  inline virtual void CLEAR() final override;
  inline virtual void PUSH(AnyPtr val) final override;
  inline virtual void PUSH_WITHOUT_COPY(AnyPtr , SronTypeNum) final override;
  inline virtual AnyBindPtr AT(Int &index) final override;
  inline virtual long long int COUNT(Any &val) final override;
  inline virtual void DELETE_(Int &index) final override;
  inline virtual long long int INDEX(Any &val) const final override;
  inline virtual void INSERT(Int &index, AnyPtr &val) final override;
  inline virtual size_t LEN() const final override;
  inline virtual AnyBindPtr POP() final override;
  inline virtual void REPLACE(Any &replacer, Any &replacement) final override;
  inline virtual void REVERSE() final override;
  inline virtual long long int RINDEX(Any &) const final override;
  inline virtual void SORT() final override;
  inline virtual void REVERSE_SORT() final override;
  inline virtual AnyBindPtr SUBPART(Int &start_index, Int &end_index) final override;
  inline virtual void UPDATE(Int &index, Any &val) final override;

  inline virtual AnyPtr __ADD__(Any & , SronTypeNum) const final override;
  inline virtual SronBool_t __IS_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __NOT_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __LESS_THAN_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN__(Any & , SronTypeNum) const final override;

  inline virtual SronBool_t __MORE_THAN_EQUAL__(Any & , SronTypeNum) const final override;

  inline virtual void __ADD_AND_ASSIGN__(Any& , SronTypeNum) final override;

  inline auto &operator*();

  inline List &operator=(List &&__other) noexcept;

  inline void APPENDS(List&);

  inline void PUSH( AnyPtr , SronTypeNum);

  inline ~List() noexcept;
};

#define colCast(    __ptr )   (reinterpret_cast<ColPtr>    ( __ptr ))
#define voidCast(   __ptr )   (reinterpret_cast<VoidPtr>   ( __ptr ))
#define intCast(    __ptr )   (reinterpret_cast<IntPtr>    ( __ptr ))
#define doubleCast( __ptr )   (reinterpret_cast<DoublePtr> ( __ptr ))
#define charCast(   __ptr )   (reinterpret_cast<CharPtr>   ( __ptr ))
#define boolCast(   __ptr )   (reinterpret_cast<BoolPtr>   ( __ptr ))
#define stringCast( __ptr )   (reinterpret_cast<StringPtr> ( __ptr ))
#define listCast(   __ptr )   (reinterpret_cast<ListPtr>   ( __ptr ))



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