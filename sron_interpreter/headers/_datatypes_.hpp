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

#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include "_exception_.hpp"
#include "_flags_.hpp"
#include "_converter_.hpp"


using std::string;
using std::to_string;

#ifndef DATATYPES_H
#define DATATYPES_H

class Any;
class Void;
class Int;
class Double;
class String;
class Char;
class Bool;
class List;

/*
 'Any' datatype is the base class for all other datatypes.
  It is inherited by Void, Int, Double, String, Char, Bool, Vector and List.
*/
class Any
{
public:
    // calls the destructor
    inline virtual void FREE() const = 0;

    inline virtual Any *COPY() const = 0;

    // Returns the length of the datatype
    inline virtual size_t LEN() const = 0;

    // prints the value of the datatype
    inline virtual void PRINT() const = 0;

    // prints the type of the datatype
    inline virtual std::string TYPE() const = 0;

    // returns the type number
    inline virtual unsigned short int TYPE_NUMBER() const = 0;

    // returns the size of the value in bytes
    inline virtual long long int SIZE_OF() const = 0;

    // returns the string form of value
    inline virtual std::string TO_STRING() const = 0;

    // methods to return object's pointers
    inline virtual Void *GET_VOID() const = 0;
    inline virtual Int *GET_INT() const = 0;
    inline virtual Double *GET_DOUBLE() const = 0;
    inline virtual String *GET_STRING() const = 0;
    inline virtual Char *GET_CHAR() const = 0;
    inline virtual Bool *GET_BOOL() const = 0;
    inline virtual List *GET_LIST() const = 0;

    // inline Any &operator=(Any &);

    virtual ~Any() {}
};

/*
 * Classes are defined in the following flow :
 * 1. Private values of primitive datatypes in c++.
 * 2. Constructors.
 * 3. Default Methods like LEN, PRINT, SIZE_OF, TO_STRING, TYPE.
 * 4. Destructor.
 */

/*
  |====================== VOID ===============================|
 'Void' datatype will be used to implement NULL or None values.
  > Syntax in SRON : "Void x"
*/
class Void : public Any
{

public:
    Void() {}

    inline virtual void FREE() const override
    {
        this->~Void();
    }

    inline virtual size_t LEN() const override
    {
        return 0;
    }

    inline virtual Any *COPY() const override
    {
        return const_cast<Void *>(this);
    }

    inline virtual void PRINT() const override
    {
        std::cout << "";
    }
    inline virtual long long int SIZE_OF() const override
    {
        return 0;
    }
    inline virtual std::string TO_STRING() const override
    {
        return "";
    }
    inline virtual std::string TYPE() const override
    {
        return "Void";
    }

    inline virtual unsigned short int TYPE_NUMBER() const override
    {
        return TYPE_VOID;
    }

    inline virtual Void *GET_VOID() const override
    {
        return const_cast<Void *>(this);
    }
    inline virtual Int *GET_INT() const override
    {
        return nullptr;
    }
    inline virtual Double *GET_DOUBLE() const override
    {
        return nullptr;
    }
    inline virtual String *GET_STRING() const override
    {
        return nullptr;
    }
    inline virtual Char *GET_CHAR() const override
    {
        return nullptr;
    }
    inline virtual Bool *GET_BOOL() const override
    {
        return nullptr;
    }
    inline virtual List *GET_LIST() const override
    {
        return nullptr;
    }

    ~Void() {}
};

/*
  |====================== DOUBLE ===============================|
 'Double' datatype use double to store values.
  > long double take 8 bytes.
  > Syntax in SRON : Double x = 1235.123124
*/

class Double : public Any
{
private:
    double value = 0;

public:
    Double() {}
    Double(double val) : value(val) {}
    Double(long long int val) : value((double)val) {}

    Double(std::string &val) : value(Converter::TO_DOUBLE(val)) {}

    inline Double operator=(double val)
    {
        return Double(val);
    }

    inline operator double() const
    {
        return this->value;
    }

    inline virtual void FREE() const override
    {
        this->~Double();
    }

    inline virtual Any *COPY() const override
    {
        return new Double(this->value);
    }

    inline virtual size_t LEN() const override
    {
        return std::to_string(this->value).length();
    }

    inline virtual void PRINT() const override
    {
        std::cout << this->value;
    }

    inline virtual long long int SIZE_OF() const override
    {
        return sizeof(this->value);
    }

    inline virtual std::string TO_STRING() const override
    {
        return std::to_string(this->value);
    }

    inline virtual std::string TYPE() const override
    {
        return "Double";
    }

    inline virtual unsigned short int TYPE_NUMBER() const override
    {
        return TYPE_DOUBLE;
    }

    inline virtual Void *GET_VOID() const override
    {
        return nullptr;
    }
    inline virtual Int *GET_INT() const override
    {
        return nullptr;
    }
    inline virtual Double *GET_DOUBLE() const override
    {
        return const_cast<Double *>(this);
    }
    inline virtual String *GET_STRING() const override
    {
        return nullptr;
    }
    inline virtual Char *GET_CHAR() const override
    {
        return nullptr;
    }
    inline virtual Bool *GET_BOOL() const override
    {
        return nullptr;
    }
    inline virtual List *GET_LIST() const override
    {
        return nullptr;
    }

    inline double &GET()
    {
        return this->value;
    }

    inline void SET(double &value)
    {
        this->value = value;
    }

    ~Double()
    {
        this->value = 0;
    }
};

/*
  |====================== INT ===============================|
 'Int' datatype implements integer type with long long modifier.
 > long long int takes 8 bytes.
 > Syntax in SRON : "Int x = 10" or "Int x"
*/

class Int : public Any
{
private:
    long long int value = 0;

public:
    Int() {}
    Int(long long int val) : value(val) {}
    Int(std::string &val) : value(std::stoll(val)) {}

    inline Int operator=(long long int &val)
    {
        return Int(val);
    }

    inline operator long long int() const
    {
        return this->value;
    }

    inline virtual void FREE() const override
    {
        this->~Int();
    }

    inline virtual Any *COPY() const override
    {
        return new Int(this->value);
    }

    inline virtual size_t LEN() const override
    {
        return floor(log10(this->value) + 1);
    }

    inline virtual void PRINT() const override
    {
        std::cout << this->value;
    }

    inline virtual long long int SIZE_OF() const override
    {
        return sizeof(this->value);
    }

    inline virtual std::string TYPE() const override
    {
        return "Int";
    }

    inline virtual unsigned short int TYPE_NUMBER() const override
    {
        return TYPE_INT;
    }

    inline virtual std::string TO_STRING() const override
    {
        return std::to_string(this->value);
    }

    inline virtual Void *GET_VOID() const override
    {
        return nullptr;
    }
    inline virtual Int *GET_INT() const override
    {
        return const_cast<Int *>(this);
    }
    inline virtual Double *GET_DOUBLE() const override
    {
        return new Double(this->value);
    }
    inline virtual String *GET_STRING() const override
    {
        return nullptr;
    }
    inline virtual Char *GET_CHAR() const override
    {
        return nullptr;
    }
    inline virtual Bool *GET_BOOL() const override
    {
        return nullptr;
    }
    inline virtual List *GET_LIST() const override
    {
        return nullptr;
    }

    // returns the long long int type of value.
    inline long long int &GET()
    {
        return this->value;
    }

    inline void SET(long long int &value)
    {
        this->value = value;
    }

    ~Int()
    {
        this->value = 0;
    }
};

/*
  |====================== CHAR ===============================|
 'Char' datatype uses char to store values.
  > char take 1 byte.
  > Syntax in SRON : Char x = 'S'
*/
class Char : public Any
{

private:
    char value = ' ';

public:
    Char() {}
    Char(char val) : value(val) {}

    inline Char operator=(char &val)
    {
        return Char(val);
    }

    inline operator char() const
    {
        return this->value;
    }

    inline virtual void FREE() const override
    {
        this->~Char();
    }

    inline virtual Any *COPY() const override
    {
        return new Char(this->value);
    }

    inline virtual size_t LEN() const override
    {
        return 1;
    }
    inline virtual void PRINT() const override
    {
        std::cout << this->value;
    }
    inline virtual long long int SIZE_OF() const override
    {
        return sizeof(this->value);
    }
    inline virtual std::string TO_STRING() const override
    {
        return (std::string) "" + this->value;
    }
    inline virtual std::string TYPE() const override
    {
        return "Char";
    }
    inline virtual unsigned short int TYPE_NUMBER() const override
    {
        return TYPE_CHAR;
    }

    inline virtual Void *GET_VOID() const override
    {
        return nullptr;
    }
    inline virtual Int *GET_INT() const override
    {
        return nullptr;
    }
    inline virtual Double *GET_DOUBLE() const override
    {
        return nullptr;
    }
    inline virtual String *GET_STRING() const override
    {
        return nullptr;
    }
    inline virtual Char *GET_CHAR() const override
    {
        return const_cast<Char *>(this);
    }
    inline virtual Bool *GET_BOOL() const override
    {
        return nullptr;
    }
    inline virtual List *GET_LIST() const override
    {
        return nullptr;
    }

    inline char &GET()
    {
        return this->value;
    }

    inline void SET(char &value)
    {
        this->value = value;
    }

    ~Char()
    {
        this->value = ' ';
    }
};

/*
  |====================== BOOL ===============================|
 'Bool' datatype uses bool to store values.
  > bool take 1 bytes.
  > Syntax in SRON : "Bool x = true" or "Bool x"
*/
class Bool : public Any
{

private:
    bool value = false;

public:
    Bool() {}
    Bool(bool val) : value(val) {}

    inline Bool operator=(bool &val)
    {
        return Bool(val);
    }

    inline operator bool() const
    {
        return this->value;
    }

    inline virtual void FREE() const override
    {
        this->~Bool();
    }
    inline virtual Any *COPY() const override
    {
        return new Bool(this->value);
    }

    inline virtual size_t LEN() const override
    {
        return (this->value) ? 4 : 5;
    }

    inline virtual void PRINT() const override
    {
        std::cout << this->TO_STRING();
    }

    inline virtual long long int SIZE_OF() const override
    {
        return sizeof(this);
    }

    inline virtual std::string TO_STRING() const override
    {
        return (this->value) ? "true" : "false";
    }

    inline virtual std::string TYPE() const override
    {
        return "Bool";
    }
    inline virtual unsigned short int TYPE_NUMBER() const override
    {
        return TYPE_BOOL;
    }

    inline virtual Void *GET_VOID() const override
    {
        return nullptr;
    }
    inline virtual Int *GET_INT() const override
    {
        return nullptr;
    }
    inline virtual Double *GET_DOUBLE() const override
    {
        return nullptr;
    }
    inline virtual String *GET_STRING() const override
    {
        return nullptr;
    }
    inline virtual Char *GET_CHAR() const override
    {
        return nullptr;
    }
    inline virtual Bool *GET_BOOL() const override
    {
        return const_cast<Bool *>(this);
    }
    inline virtual List *GET_LIST() const override
    {
        return nullptr;
    }

    inline bool &GET()
    {
        return this->value;
    }

    inline void SET(bool &value)
    {
        this->value = value;
    }

    ~Bool()
    {
        this->value = false;
    }
};

/*
  |====================== String ===============================|
 'String' datatype uses std::string to store values.
  > string are dynamic in size so its size depends on the number of characters it stores.
  > Syntax in SRON : 'String x = "SRON is the Best" ' or "String x"
*/
class String : public Any
{

private:
    std::string value = " ";

public:
    String() {}
    String(std::string str)
    {
        try
        {
            this->value = str;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("creating a variable of type 'String'.", SystemOutofMemoryException);
        }
    }

    inline String operator=(std::string &str)
    {
        return String(str);
    }

    inline operator std::string() const
    {
        return this->value;
    }

    inline virtual void FREE() const override
    {
        this->~String();
    }

    inline virtual Any *COPY() const override
    {
        return new String(this->value);
    }

    inline virtual size_t LEN() const override
    {
        return this->value.length();
    }

    inline virtual void PRINT() const override
    {
        std::cout << this->value;
    }

    inline virtual long long int SIZE_OF() const override
    {
        return sizeof(this->value);
    }

    inline virtual std::string TO_STRING() const override
    {
        return this->value;
    }

    inline virtual std::string TYPE() const override
    {
        return "String";
    }
    inline virtual unsigned short int TYPE_NUMBER() const override
    {
        return TYPE_STRING;
    }

    inline virtual Void *GET_VOID() const override
    {
        return nullptr;
    }
    inline virtual Int *GET_INT() const override
    {
        return nullptr;
    }
    inline virtual Double *GET_DOUBLE() const override
    {
        return nullptr;
    }
    inline virtual String *GET_STRING() const override
    {
        return const_cast<String *>(this);
    }
    inline virtual Char *GET_CHAR() const override
    {
        return nullptr;
    }
    inline virtual Bool *GET_BOOL() const override
    {
        return nullptr;
    }
    inline virtual List *GET_LIST() const override
    {
        return nullptr;
    }

    inline char AT(int index)
    {
        if (index >= 0 && (unsigned)index < this->value.length())
        {
            return this->value[index];
        }
        DISPLAY_EXCEPTION("extracting the elements from the string.", StringIndexException);
        return ' ';
    }

    inline void APPENDS(const std::string str)
    {
        this->value.append(str);
    }

    inline void APPENDS(const char &ch)
    {
        this->value+=ch;
    }

    inline void APPENDS(Any *val)
    {

        if (val == nullptr)
        {
            DISPLAY_EXCEPTION("pushing elements into the 'String'. The passed value is actually 'NULL'.", NoException, false);
        }

        this->value.append(val->TO_STRING());
    }

    inline void CLEAR()
    {
        this->value.clear();
    }

    inline long long int COUNT(String *val)
    {

        std::string &sample = val->GET();

        if (sample.empty() || this->value.length() < sample.length())
        {
            return 0; // If the sample string is empty, return 0
        }

        long long int count = 0;
        size_t pos = 0;

        while ((pos = this->value.find(sample, pos)) != std::string::npos)
        {
            ++count;
            pos += sample.size(); // Move to the next position after the current match
        }

        return count;
    }

    inline long long int COUNT(Char *val)
    {
        return std::count(this->value.begin(), this->value.end(), val->GET());
    }

    inline void DELETE_(long long int index)
    {
        if (index < 0 || (long long unsigned int)index >= this->value.length())
        {
            DISPLAY_EXCEPTION("deleting 'String' type value to type 'String'.", IndexNotWithinRange);
        }

        this->value.erase(this->value.begin() + index);
    }

    inline std::string &GET()
    {
        return this->value;
    }

    // returns the index number if found, otherwise -1
    inline long long int INDEX(Char *val)
    {
        return this->value.find_first_of(val->GET());
    }

    inline long long int INDEX(String *val)
    {
        return this->value.find_first_of(val->GET());
    }

    inline void INSERT(long long int index , Any& val){
        if (index < 0 || (long long unsigned int)index >= this->value.length())
        {
            DISPLAY_EXCEPTION("inserting 'String' type value to type 'String'.", IndexNotWithinRange);
        }
        this->value.insert(index, val.TO_STRING());
    }

    inline char POP_BACK()
    {
        // if the string is empty...
        if(this->value.length() == 0) return ' ';

        char ch = *(this->value.end() - 1);
        this->value.erase(this->value.end() - 1);
        return ch;
    }

    inline void REPLACE(Char *_replacer, Any *replacement)
    {

        char &replacer = _replacer->GET();

        size_t len_of_replacement = replacement->LEN();

        for (size_t i = 0; i < this->value.length(); ++i)
        {
            if (this->value[i] == replacer)
            {
                this->value.erase(i, 1);
                this->value.insert(i, replacement->TO_STRING());
                i += len_of_replacement - 1;
            }
        }
    }

    inline void REVERSE()
    {
        std::reverse(this->value.begin(), this->value.end());
    }

    // returns the index number if found, otherwise -1
    inline long long int RINDEX(Char *val)
    {
        return this->value.find_last_of(val->GET());
    }

    inline long long int RINDEX(String *val)
    {
        return this->value.find_last_of(val->GET());
    }

    inline void SET(std::string &value)
    {
        this->value = value;
    }

    inline void SORT(){
        std::sort(this->value.begin() , this->value.end());
    }

    inline std::string SUBSTRING(long long int first_index, long long int last_index)
    {
        if (first_index < 0 || (size_t)last_index > this->value.length() || first_index > last_index)
        {
            return "";
        }
        return std::string(this->value.begin() + first_index, this->value.begin() + last_index);
    }

    inline std::string TRIM()
    {
        // Find the first non-whitespace character from the left
        auto left = std::find_if_not(this->value.begin(), this->value.end(), [](unsigned char c)
                                     { return std::isspace(c); });

        // Find the first non-whitespace character from the right
        auto right = std::find_if_not(this->value.rbegin(), this->value.rend(), [](unsigned char c)
                                      { return std::isspace(c); })
                         .base();

        // If all characters are whitespace, return an empty string
        if (left == this->value.end() || right == this->value.begin())
            return "";

        return std::string(left, right);
    }

    inline void UPDATE(long long int index, Char *val)
    {
        if (index < 0 || (long long unsigned int)index >= this->value.length())
        {
            DISPLAY_EXCEPTION("updating character at index '" + std::to_string(index) + "' with value '" + val->TO_STRING() + "'.", IndexNotWithinRange);
        }

        this->value.assign(index, val->GET());
    }

    inline List *TO_CHAR_LIST();
    inline List *SPLIT(Char*);

    ~String()
    {
        this->value.~basic_string();
    }
};

/*
  |====================== List ===============================|
 'List' datatype uses std::vector<Any*> to store values.
  > It is dynamic in size as well as in nature so it can store values of different datatype in a single entity. It can store List too but not itself.
  > Syntax in SRON : "List x = [1,123.678, true, false, "Heelo", 'Q ]" or "List x" or "List x = []"
*/
class List : public Any
{
private:
    std::vector<Any *> value;

public:
    List() {}

    List(std::vector<Any *> &val)
    {
        try
        {
            this->value = val;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("creating a variable of type 'List'.", SystemOutofMemoryException);
        }
    }

    List(Any *a)
    {
        try
        {
            this->value.push_back(a);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("creating a variable of type 'List'.", SystemOutofMemoryException);
        }
    }
    List(Any *a, Any *b)
    {
        try
        {
            this->value.push_back(a);
            this->value.push_back(b);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("creating a variable of type 'List'.", SystemOutofMemoryException);
        }
    }
    List(Any *a, Any *b, Any *c)
    {
        try
        {
            this->value.push_back(a);
            this->value.push_back(b);
            this->value.push_back(c);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("creating a variable of type 'List'.", SystemOutofMemoryException);
        }
    }

    inline virtual void FREE() const override
    {
        this->~List();
    }
    inline virtual Any *COPY() const override
    {

        List *lst = new List();

        for (const auto &i : this->value)
        {
            lst->PUSH(i->COPY());
        }
        return lst;
    }

    inline virtual size_t LEN() const override
    {
        return this->value.size();
    }

    inline virtual void PRINT() const override
    {
        try
        {
            if (this->value.size() == 0)
            {
                std::cout << "[]";
                return;
            }

            std::cout << "[";

            std::vector<Any *>::const_iterator it = this->value.begin();
            for (; it != this->value.end() - 1; ++it)
            {
                (*it)->PRINT();
                std::cout << ", ";
            }

            (*it)->PRINT();

            std::cout << "]";
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("displaying the list into the console", UnknownException);
        }
    }
    inline virtual unsigned short int TYPE_NUMBER() const override
    {
        return TYPE_LIST;
    }

    inline virtual long long int SIZE_OF() const override
    {
        long long int size = 0;
        for(const auto& i : this->value){
            size += i->SIZE_OF();
        }
        return size;
    }

    inline virtual std::string TO_STRING() const override
    {
        string fin = "";
        try
        {

            if (this->value.size() == 0)
            {
                return "[]";
            }
            fin = "[";
            std::vector<Any *>::const_iterator it = this->value.begin();
            for (; it != this->value.end() - 1; ++it)
            {
                fin += (*it)->TO_STRING() + ", ";
            }

            fin += (*it)->TO_STRING() + "]";
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("converting the type 'List' to type 'String'.", SystemOutofMemoryException);
        }
        return fin;
    }

    inline virtual std::string TYPE() const override
    {
        return "List";
    }

    inline virtual Void *GET_VOID() const override
    {
        return nullptr;
    }
    inline virtual Int *GET_INT() const override
    {
        return nullptr;
    }
    inline virtual Double *GET_DOUBLE() const override
    {
        return nullptr;
    }
    inline virtual String *GET_STRING() const override
    {
        return nullptr;
    }
    inline virtual Char *GET_CHAR() const override
    {
        return nullptr;
    }
    inline virtual Bool *GET_BOOL() const override
    {
        return nullptr;
    }
    inline virtual List *GET_LIST() const override
    {
        return const_cast<List *>(this);
    }

    inline Any *AT(long long int index)
    {
        try
        {
            if (index < 0 || (long long unsigned int)index >= this->value.size())
            {
                throw std::exception();
            }
            return this->value[index];
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("extracting elements from type 'List'.", IndexNotWithinRange);
        }
        return nullptr;
    }

    inline void CLEAR()
    {
        this->value.clear();
    }

    inline void DELETE_(Int *index)
    {

        long long int _index = index->GET();

        if (_index < 0 || (long long unsigned int)_index >= this->value.size())
        {
            DISPLAY_EXCEPTION("deleting elements from type 'List'.", IndexNotWithinRange, false);
        }

        this->value.erase(this->value.begin() + _index);
    }

    inline std::vector<Any *> &GET()
    {
        return this->GET();
    }

    inline void INSERT(long long int index, Any* val){
        if (index < 0 || (long long unsigned int)index >= this->value.size())
        {
            DISPLAY_EXCEPTION("inserting a value to type 'List'.", IndexNotWithinRange);
        }

        this->value.insert( this->value.begin()+index , val);
    }

    inline Any *POP()
    {
        if (this->value.size() != 0)
        {
            Any *val = this->value.back();
            this->value.pop_back();
            return val;
        }
        return new Void();
    }

    inline void PUSH(Any *val)
    {
        try
        {
            if (this != val)
            {
                this->value.push_back(val);
                return;
            }
            DISPLAY_EXCEPTION("inserting a list inside itself.", InsertionException);
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("appending an element into the type 'List'.", SystemOutofMemoryException);
        }
    }

    inline void REVERSE()
    {
        std::reverse(this->value.begin(), this->value.end());
    }

    inline void SET(std::vector<Any *> value)
    {
        this->value = value;
    }

    inline List *SUBLIST(long long int index1, long long int index2)
    {
        try
        {
            List *lst = new List();

            if (index1 < 0 || (long long unsigned int)index1 >= this->value.size() || (long long unsigned int)index2 > this->value.size())
            {
                DISPLAY_EXCEPTION("extracting the sublist. Both index must be more than zero and less than the size of the list which is " + std::to_string(this->value.size()) + ".", NoException);
            }
            std::vector<Any *>::iterator start = this->value.begin() + index1;
            std::vector<Any *>::const_iterator end = this->value.begin() + index2;

            for (; start < end; ++start)
            {
                lst->PUSH((*start)->COPY());
            }

            return lst;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("creating a sublist.", SystemOutofMemoryException);
        }
        return nullptr;
    }

    inline void UPDATE(long long int index, Any *value)
    {
        try
        {
            if (index < 0 || (long long unsigned int)index >= this->value.size())
            {
                throw std::exception();
            }
            this->value[index] = value;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("updating elements in type 'List'.", IndexNotWithinRange);
        }
    }

    // the below method are dependent on operator overloads therefore they will be defined in the end of the file...
    inline long long int COUNT(Any *);
    inline long long int INDEX(Any *);
    inline long long int RINDEX(Any *);
    inline void SORT();
    inline void REPLACE(Any *, Any *);

    ~List()
    {
        for (auto &i : this->value)
        {
            free(i);
        }
        this->value.~vector();
    }
};



inline List *String::TO_CHAR_LIST()
{
    try
    {
        List *lst = new List();

        for (const auto &i : this->value)
        {
            lst->PUSH(new Char(i));
        }

        return lst;
    }
    catch (const std::exception &e)
    {
        DISPLAY_EXCEPTION("creating a list of type 'Char'.", SystemOutofMemoryException);
    }

    return nullptr;
}

inline List *String::SPLIT(Char* _splitter){
    char& splitter = _splitter->GET();

    List *lst = new List();

    std::string temp = "";

    for(const auto &i : this->value){
        if(i == splitter){
            lst->PUSH(new String(temp));
            temp = "";
        }
        else{
            temp+=i;
        }
    }

    lst->PUSH(new String(temp));

    return lst;
}

inline long long int List::COUNT(Any *val)
{
    long long int count = 0;
    for (auto &i : this->value)
    {
        count += (*i == *val) ? 1 : 0;
    }
    return count;
}
inline long long int List::INDEX(Any *val)
{
    for (auto it = this->value.begin(); it < this->value.end(); ++it)
    {
        if (*val == **it)
        {
            return it - this->value.begin();
        }
    }
    return -1;
}
inline long long int List::RINDEX(Any *val)
{
    for (auto it = this->value.end() - 1; it >= this->value.begin(); --it)
    {
        if (*val == **it)
        {
            return it - this->value.begin();
        }
    }
    return -1;
}
inline void List::SORT()
{
    std::sort(this->value.begin(), this->value.end());
}
inline void List::REPLACE(Any *replacer, Any *replacement)
{
    for (auto &it : this->value)
    {
        if (*it == *replacer)
        {
            it = replacement;
        }
    }
}

#endif