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

#include <vector>
#include <iomanip>
#include <cmath>
#include "_exception_.hpp"
#include "_flags_.hpp"
#include "_converter_.hpp"

using std::exception;
using std::string;
using std::to_string;
using std::vector;

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
    inline virtual string TYPE() const = 0;

    // returns the type number
    inline virtual unsigned short int TYPE_NUMBER() const = 0;

    // returns the size of the value in bytes
    inline virtual long long int SIZE_OF() const = 0;

    // returns the string form of value
    inline virtual string TO_STRING() const = 0;

    // methods to return object's pointers
    inline virtual Void *GET_VOID() const = 0;
    inline virtual Int *GET_INT() const = 0;
    inline virtual Double *GET_DOUBLE() const = 0;
    inline virtual String *GET_STRING() const = 0;
    inline virtual Char *GET_CHAR() const = 0;
    inline virtual Bool *GET_BOOL() const = 0;
    inline virtual List *GET_LIST() const = 0;

    inline Any &operator=(Any &);

    virtual ~Any() {}
};

/*
 * Classes are defined in the following flow :
 * 1. Private values of primitive datatypes in c++.
 * 2. Constructors.
 * 3. Default Methods like LEN, PRINT, SIZE_OF, TO_STRING, TYPE.
 * 4. Static Methods like MAKE.
 * 5. Destructor.
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
    inline virtual string TO_STRING() const override
    {
        return "";
    }
    inline virtual string TYPE() const override
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

    inline static Any *MAKE()
    {
        return new Void();
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

    inline virtual string TO_STRING() const override
    {
        return std::to_string(this->value);
    }

    inline virtual string TYPE() const override
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

    inline static Double *MAKE()
    {
        return new Double();
    }

    inline static Double *MAKE(double val)
    {
        return new Double(val);
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

    inline virtual string TYPE() const override
    {
        return "Int";
    }

    inline virtual unsigned short int TYPE_NUMBER() const override
    {
        return TYPE_INT;
    }

    inline virtual string TO_STRING() const override
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

    inline static Int *MAKE()
    {
        return new Int();
    }

    inline static Int *MAKE(long long int val)
    {
        return new Int(val);
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
    inline virtual string TO_STRING() const override
    {
        return (std::string) "" + this->value;
    }
    inline virtual string TYPE() const override
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

    inline static Char *MAKE()
    {
        return new Char();
    }

    inline static Char *MAKE(char val)
    {
        return new Char(val);
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

    inline virtual string TO_STRING() const override
    {
        return (this->value) ? "true" : "false";
    }

    inline virtual string TYPE() const override
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

    inline static Bool *MAKE()
    {
        return new Bool();
    }

    inline static Bool *MAKE(bool val)
    {
        return new Bool(val);
    }
    inline static Bool *MAKE(string str)
    {
        if (str == "true")
        {
            return new Bool(true);
        }
        else if (str == "false")
        {
            return new Bool(false);
        }
        DISPLAY_EXCEPTION("creating a variable of type 'Bool' from '" + str + "' value.", InvalidValueException);
        return new Bool();
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

    inline virtual string TO_STRING() const override
    {
        return this->value;
    }

    inline virtual string TYPE() const override
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

    inline void APPENDS(std::string str)
    {
        this->value.append(str);
    }

    inline void POP_BACK()
    {
        this->value.erase(this->value.end() - 1);
    }

    inline std::string &GET()
    {
        return this->value;
    }

    inline void SET(std::string &value)
    {
        this->value = value;
    }

    inline void CLEAR()
    {
        this->value.clear();
    }
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
        return sizeof(this->value);
    }

    inline virtual string TO_STRING() const override
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

    inline virtual string TYPE() const override
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

    inline void CLEAR()
    {
        this->value.clear();
    }
    inline std::vector<Any *> &GET()
    {
        return this->GET();
    }

    inline void SET(std::vector<Any *> value)
    {
        this->value = value;
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

    inline Any *AT(int index)
    {
        try
        {
            return this->value[index];
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("extracting elements from type 'List'.", IndexNotWithinRange);
        }
        return nullptr;
    }

    inline void UPDATE(size_t index, Any *value)
    {
        try
        {
            if (index >= this->value.size())
            {
                DISPLAY_EXCEPTION("updating elements in type 'List'.", IndexNotWithinRange);
            }
            this->value[index] = value;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("updating elements in type 'List'.", SystemOutofMemoryException);
        }
    }

    inline static List *MAKE()
    {
        return new List();
    }

    inline static List *MAKE(Any *val)
    {
        return new List(val);
    }

    inline static Any *MAKE(List *val)
    {
        return val;
    }

    ~List()
    {
        for (auto &i : this->value)
        {
            // i->FREE();
            // i = nullptr;
            free(i);
        }
        this->value.~vector();
    }
};

/*
  |====================== Vector ===============================|
 'Vector' datatype uses std::vector to store values.
  > It is dynamic in size but not dynamic in nature because it can store only similar datatypes within itself.
  > Syntax in SRON : "Vector x = [1,2,3,3,4,6,7,8,9,0]" or "Vector x" or "Vector x =[]"

  NOTE: It's implementation is causing troubles with the speed and efficieny so it will be implemented further.
*/

inline static bool operator==(Any &val1, Any &val2)
{
    try
    {
        switch (val1.TYPE_NUMBER())
        {

        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_INT()->GET() == val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_INT()->GET() == val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;

        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_DOUBLE()->GET() == val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_DOUBLE()->GET() == val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;

        case TYPE_CHAR:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_CHAR:
                return val1.GET_CHAR()->GET() == val2.GET_CHAR()->GET();
            case TYPE_STRING:
                return val2.GET_STRING()->LEN() == 1 && (val2.GET_STRING()->AT(0) == val1.GET_CHAR()->GET());
            default:
                throw std::exception();
            }
        }
        break;

        case TYPE_BOOL:
        {
            switch (val2.TYPE_NUMBER())
            {

            case TYPE_BOOL:
                return val1.GET_BOOL()->GET() == val2.GET_BOOL()->GET();
            default:
                throw std::exception();
            }
        }
        break;

        case TYPE_STRING:
        {
            switch (val2.TYPE_NUMBER())
            {

            case TYPE_STRING:
                return val1.GET_STRING()->GET() == val2.GET_STRING()->GET();
            case TYPE_CHAR:
                return val1.GET_STRING()->LEN() == 1 && (val1.GET_STRING()->AT(0) == val2.GET_CHAR()->GET());
            default:
                throw std::exception();
            }
        }
        break;

        case TYPE_LIST:
        {
            if (val2.TYPE_NUMBER() == TYPE_LIST)
            {
                size_t len = val1.GET_LIST()->LEN();
                if (len != val2.GET_LIST()->LEN())
                {
                    return false;
                }
                List *list1 = val1.GET_LIST();
                List *list2 = val2.GET_LIST();

                for (size_t i = 0; i < len; ++i)
                {
                    if (list1->AT(i) != list2->AT(i))
                    {
                        return false;
                    }
                }
                return true;
            }
            throw std::exception();
        }
        break;

        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("comparing values of type '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return false;
}

inline static bool operator&&(Any &val1, Any &val2)
{
    if (val1.TYPE_NUMBER() == TYPE_BOOL && val2.TYPE_NUMBER() == TYPE_BOOL)
    {
        return val1.GET_BOOL()->GET() && val2.GET_BOOL()->GET();
    }
    DISPLAY_EXCEPTION("performing 'and' operation on values of type '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    return false;
}

inline static bool operator||(Any &val1, Any &val2)
{
    if (val1.TYPE_NUMBER() == TYPE_BOOL && val2.TYPE_NUMBER() == TYPE_BOOL)
    {
        return val1.GET_BOOL()->GET() || val2.GET_BOOL()->GET();
    }
    DISPLAY_EXCEPTION("performing 'or' operation on values of type '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    return false;
}

inline static bool operator!=(Any &val1, Any &val2)
{
    return !(val1 == val2);
}

inline static bool operator!(Any &val1)
{
    if (val1.TYPE_NUMBER() == TYPE_BOOL)
    {
        return !val1.GET_BOOL()->GET();
    }
    DISPLAY_EXCEPTION("performing 'not' operation on value of type '" + val1.TYPE() + "'.", MathEvaluationException);
    return false;
}

inline static bool operator<(Any &val1, Any &val2)
{
    try
    {
        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_INT()->GET() < val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_INT()->GET() < val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_DOUBLE()->GET() < val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_DOUBLE()->GET() < val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_CHAR:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_CHAR:
                return val1.GET_CHAR()->GET() < val2.GET_CHAR()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_STRING:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_STRING:
                return val1.GET_STRING()->GET() < val2.GET_STRING()->GET();
            default:
                throw std::exception();
            }
        }
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("performing '<' operation between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return false;
}

inline static bool operator<=(Any &val1, Any &val2)
{
    try
    {

        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_INT()->GET() <= val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_INT()->GET() <= val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_DOUBLE()->GET() <= val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_DOUBLE()->GET() <= val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_CHAR:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_CHAR:
                return val1.GET_CHAR()->GET() <= val2.GET_CHAR()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_STRING:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_STRING:
                return val1.GET_STRING()->GET() <= val2.GET_STRING()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("performing '<=' operation between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return false;
}

inline static bool operator>(Any &val1, Any &val2)
{
    try
    {

        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_INT()->GET() > val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_INT()->GET() > val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_DOUBLE()->GET() > val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_DOUBLE()->GET() > val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_CHAR:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_CHAR:
                return val1.GET_CHAR()->GET() > val2.GET_CHAR()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_STRING:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_STRING:
                return val1.GET_STRING()->GET() > val2.GET_STRING()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("performing '>' operation between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return false;
}

inline static bool operator>=(Any &val1, Any &val2)
{
    try
    {

        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_INT()->GET() >= val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_INT()->GET() >= val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return val1.GET_DOUBLE()->GET() >= val2.GET_INT()->GET();
            case TYPE_DOUBLE:
                return val1.GET_DOUBLE()->GET() >= val2.GET_DOUBLE()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_CHAR:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_CHAR:
                return val1.GET_CHAR()->GET() >= val2.GET_CHAR()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_STRING:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_STRING:
                return val1.GET_STRING()->GET() >= val2.GET_STRING()->GET();
            default:
                throw std::exception();
            }
        }
        break;
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("performing '>=' operation between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return false;
}
inline static Any *operator+(Any &val1, Any &val2)
{
    try
    {
        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Int(val1.GET_INT()->GET() + val2.GET_INT()->GET());
            case TYPE_DOUBLE:
                return new Double(val1.GET_INT()->GET() + val2.GET_DOUBLE()->GET());
            case TYPE_STRING:
                return new String(val1.TO_STRING() + val2.TO_STRING());
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Double(val1.GET_DOUBLE()->GET() + val2.GET_INT()->GET());
            case TYPE_DOUBLE:
                return new Double(val1.GET_DOUBLE()->GET() + val2.GET_DOUBLE()->GET());
            case TYPE_STRING:
                return new String(val1.TO_STRING() + val2.TO_STRING());
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_CHAR:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_CHAR:
            case TYPE_STRING:
                return new String(val1.TO_STRING() + val2.TO_STRING());
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_STRING:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
            case TYPE_DOUBLE:
            case TYPE_CHAR:
            case TYPE_BOOL:
            case TYPE_STRING:
                return new String(val1.TO_STRING() + val2.TO_STRING());
            default:
                throw std::exception();
            }
        }
        break;
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("performing '' operation between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return new Void();
}

inline static Any *operator-(Any &val1, Any &val2)
{
    try
    {
        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Int(val1.GET_INT()->GET() - val2.GET_INT()->GET());
            case TYPE_DOUBLE:
                return new Double(val1.GET_INT()->GET() - val2.GET_DOUBLE()->GET());
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Double(val1.GET_DOUBLE()->GET() - val2.GET_INT()->GET());
            case TYPE_DOUBLE:
                return new Double(val1.GET_DOUBLE()->GET() - val2.GET_DOUBLE()->GET());
            default:
                throw std::exception();
            }
        }
        break;
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("performing subtraction between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return new Void();
}
inline static Any *operator*(Any &val1, Any &val2)
{
    try
    {
        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Int(val1.GET_INT()->GET() * val2.GET_INT()->GET());
            case TYPE_DOUBLE:
                return new Double(val1.GET_INT()->GET() * val2.GET_DOUBLE()->GET());
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Double(val1.GET_DOUBLE()->GET() * val2.GET_INT()->GET());
            case TYPE_DOUBLE:
                return new Double(val1.GET_DOUBLE()->GET() * val2.GET_DOUBLE()->GET());
            default:
                throw std::exception();
            }
        }
        break;
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("performing multiplication between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return new Void();
}

// this function takes care of if the second value is a zero or not and returns a long long int value
inline static long long int __DIVIDE(long long int val1, long long int val2)
{
    if (val2 == 0)
    {
        DISPLAY_EXCEPTION("performing the division operation.", DivisionByZeroException);
    }
    return val1 / val2;
}
inline static long long int __MODULUS(long long int val1, long long int val2)
{
    if (val2 == 0)
    {
        DISPLAY_EXCEPTION("performing the modulus operation.", DivisionByZeroException);
    }
    return val1 % val2;
}

inline static Any *operator/(Any &val1, Any &val2)
{
    try
    {
        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Int(__DIVIDE(val1.GET_INT()->GET(), val2.GET_INT()->GET()));
            case TYPE_DOUBLE:
                return new Double(__DIVIDE(val1.GET_INT()->GET(), val2.GET_DOUBLE()->GET()));
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Double(__DIVIDE(val1.GET_DOUBLE()->GET(), val2.GET_INT()->GET()));
            case TYPE_DOUBLE:
                return new Double(__DIVIDE(val1.GET_DOUBLE()->GET(), val2.GET_DOUBLE()->GET()));
            default:
                throw std::exception();
            }
        }
        break;
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("performing division between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return new Void();
}

inline static Any *operator%(Any &val1, Any &val2)
{
    try
    {
        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:

                return new Int(__MODULUS(val1.GET_INT()->GET(), val2.GET_INT()->GET()));

            case TYPE_DOUBLE:

                return new Double(__MODULUS(val1.GET_INT()->GET(), val2.GET_DOUBLE()->GET()));
                
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:

                return new Double(__MODULUS(val1.GET_DOUBLE()->GET(), val2.GET_INT()->GET()));

            case TYPE_DOUBLE:

                return new Double(__MODULUS(val1.GET_DOUBLE()->GET(), val2.GET_DOUBLE()->GET()));

            default:
                throw std::exception();
            }
        }
        break;
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("performing modulus between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return new Void();
}

inline static Any *operator^(Any &val1, Any &val2)
{
    try
    {
        switch (val1.TYPE_NUMBER())
        {
        case TYPE_INT:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Int(std::pow(val1.GET_INT()->GET(), val2.GET_INT()->GET()));
            case TYPE_DOUBLE:
                return new Double(std::pow(val1.GET_INT()->GET(), val2.GET_DOUBLE()->GET()));
            default:
                throw std::exception();
            }
        }
        break;
        case TYPE_DOUBLE:
        {
            switch (val2.TYPE_NUMBER())
            {
            case TYPE_INT:
                return new Double(std::pow(val1.GET_DOUBLE()->GET(), val2.GET_INT()->GET()));
            case TYPE_DOUBLE:
                return new Double(std::pow(val1.GET_DOUBLE()->GET(), val2.GET_DOUBLE()->GET()));
            default:
                throw std::exception();
            }
        }
        break;
        default:
            throw std::exception();
        }
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("finding power of values between type of '" + val1.TYPE() + "' and '" + val2.TYPE() + "'.", MathEvaluationException);
    }
    return new Void();
}

inline Any &Any::operator=(Any &val)
{
    if (this->TYPE_NUMBER() != val.TYPE_NUMBER())
    {
        return val;
    }

    switch (this->TYPE_NUMBER())
    {

    case TYPE_INT:
        this->GET_INT()->SET(val.GET_INT()->GET());
        break;

    case TYPE_DOUBLE:
        this->GET_DOUBLE()->SET(val.GET_DOUBLE()->GET());
        break;

    case TYPE_CHAR:
        this->GET_CHAR()->SET(val.GET_CHAR()->GET());
        break;

    case TYPE_STRING:
        this->GET_STRING()->SET(val.GET_STRING()->GET());
        break;

    case TYPE_BOOL:
        this->GET_BOOL()->SET(val.GET_BOOL()->GET());
        break;

    case TYPE_LIST:
        this->GET_LIST()->SET(val.GET_LIST()->GET());
        break;

    default:
        DISPLAY_EXCEPTION("assigning value of type '" + val.TYPE() + "' to value of type '" + this->TYPE() + "'.", InterpretationException);
    }
    return val;
}

#endif