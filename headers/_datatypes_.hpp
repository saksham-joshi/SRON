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
  9. Vector.
*/

#include<string>
#include<vector>
#include<cmath>
#include "_exception_.hpp"

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
  It is implemented by Void, Int, Double, String, Char, Bool, Vector and List.
*/
class Any{
    public:
        // Returns the length of the datatype 
        inline virtual long long int LEN() const = 0;

        // prints the value of the datatype
        inline virtual void PRINT() const = 0;

        // prints the type of the datatype
        inline virtual string TYPE() const = 0;

        // returns the size of the value in bytes
        inline virtual long long int SIZE_OF() const = 0;

        // returns the string form of value
        inline virtual string TO_STRING() const = 0;

        // methods to return object's pointers
        inline virtual Void* GET_VOID() const = 0;
        inline virtual Int* GET_INT() const = 0;
        inline virtual Double* GET_DOUBLE() const = 0;
        inline virtual String* GET_STRING() const = 0;
        inline virtual Char* GET_CHAR() const = 0;
        inline virtual Bool* GET_BOOL() const = 0;
        inline virtual List* GET_LIST() const = 0;

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
class Void : public Any{

    public :
        Void(){}

        inline virtual long long int LEN() const override{
            return 0;
        }

        inline virtual void PRINT() const override{
            printf("");
        }
        inline virtual long long int SIZE_OF() const override{
            return 0;
        }
        inline virtual string TO_STRING() const override{
            return "";
        }
        inline virtual string TYPE() const override{
            return "Void";
        }

        inline virtual Void* GET_VOID() const override{
            return const_cast<Void*>(this);
        }
        inline virtual Int* GET_INT() const override{
            return nullptr;
        }
        inline virtual Double* GET_DOUBLE() const override{
            return nullptr;
        }
        inline virtual String* GET_STRING() const override{
            return nullptr;
        }
        inline virtual Char* GET_CHAR() const override{
            return nullptr;
        }
        inline virtual Bool* GET_BOOL() const override{
            return nullptr;
        }
        inline virtual List* GET_LIST() const override{
            return nullptr;
        }

        inline static Any* MAKE() {
            return new Void();
        }

        ~Void() {}
};

/*
  |====================== INT ===============================|
 'Int' datatype implements integer type with long long modifier.
 > long long int takes 8 bytes.
 > Syntax in SRON : "Int x = 10" or "Int x" 
*/

class Int: public Any {
    private:
        long long int value=0;

    public :

        Int(){}
        Int(long long int val) : value(val){}

        inline virtual long long int LEN() const override{
            return floor(log10(value)+1 );
        }

        inline virtual void PRINT() const override{
            printf("%lld",value);
        }

        inline virtual long long int SIZE_OF() const override{
            return sizeof(value);
        }

        inline virtual string TYPE() const override{
            return "Int";
        }

        inline virtual string TO_STRING() const override{
            return std::to_string(value);
        }

        inline virtual Void* GET_VOID() const override{
            return nullptr;
        }
        inline virtual Int* GET_INT() const override{
            return const_cast<Int*>(this);
        }
        inline virtual Double* GET_DOUBLE() const override{
            return nullptr;
        }
        inline virtual String* GET_STRING() const override{
            return nullptr;
        }
        inline virtual Char* GET_CHAR() const override{
            return nullptr;
        }
        inline virtual Bool* GET_BOOL() const override{
            return nullptr;
        }
        inline virtual List* GET_LIST() const override{
            return nullptr;
        }

        inline long long int GET(){
            return value;
        }

        inline static Int* MAKE(){
            return new Int();
        }

        inline static Int* MAKE(long long int val){
            return new Int(val) ;
        }

        ~Int(){}
};

/*
  |====================== DOUBLE ===============================|
 'Double' datatype uses long double to store values.
  > long double take 16 bytes.
  > Syntax in SRON : Double x = 1235.123124
*/

class Double : public Any{
    private :
        long double value=0;

    public :
        Double(){}
        Double(long double val) : value(val){}

        inline virtual long long int LEN() const override{
            return std::to_string(value).length();
        }
        
        inline virtual void PRINT() const override{
            printf("%0.8Lf",value);
        }

        inline virtual long long int SIZE_OF() const override{
            return sizeof(value);
        }

        inline virtual string TO_STRING() const override{
            return std::to_string(value);
        }

        inline virtual string TYPE() const override{
            return "Double";
        }

        inline virtual Void* GET_VOID() const override{
            return nullptr;
        }
        inline virtual Int* GET_INT() const override{
            return nullptr;
        }
        inline virtual Double* GET_DOUBLE() const override{
            return const_cast<Double*>(this);
        }
        inline virtual String* GET_STRING() const override{
            return nullptr;
        }
        inline virtual Char* GET_CHAR() const override{
            return nullptr;
        }
        inline virtual Bool* GET_BOOL() const override{
            return nullptr;
        }
        inline virtual List* GET_LIST() const override{
            return nullptr;
        }
        

        inline long double GET(){
            return value;
        }

        inline static Double* MAKE(){
            return new Double();
        }

        inline static Double* MAKE(long double val){
            return new Double(val);
        }

        ~Double(){}
};

/*
  |====================== CHAR ===============================|
 'Char' datatype uses char to store values.
  > char take 1 byte.
  > Syntax in SRON : Char x = 'S'
*/
class Char : public Any{

    private :
        char value=' ';
    public :
        Char(){ }
        Char(char val): value(val){}

        inline virtual long long int LEN() const override{
            return 1;
        }
        inline virtual void PRINT() const override{
            printf("%c",value);
        }
        inline virtual long long int SIZE_OF() const override{
            return sizeof(value);
        }
        inline virtual string TO_STRING() const override{
            return (string)""+value;
        }
        inline virtual string TYPE() const override{
            return "Char";
        }

        inline virtual Void* GET_VOID() const override{
            return nullptr;
        }
        inline virtual Int* GET_INT() const override{
            return nullptr;
        }
        inline virtual Double* GET_DOUBLE() const override{
            return nullptr;
        }
        inline virtual String* GET_STRING() const override{
            return nullptr;
        }
        inline virtual Char* GET_CHAR() const override{
            return const_cast<Char*>(this);
        }
        inline virtual Bool* GET_BOOL() const override{
            return nullptr;
        }
        inline virtual List* GET_LIST() const override{
            return nullptr;
        }

        inline char GET(){
            return value;
        }

        inline static Char* MAKE(){
            return new Char();
        }

        inline static Char* MAKE(char val){
            return new Char(val);
        }
        ~Char(){}
};

/*
  |====================== BOOL ===============================|
 'Bool' datatype uses bool to store values.
  > bool take 1 bytes.
  > Syntax in SRON : "Bool x = true" or "Bool x"
*/
class Bool : public Any{

    private :
        bool value = false;
    public :
        Bool(){}
        Bool(bool val) : value(val){}

        inline virtual long long int LEN() const override{
            return (value)?4:5;
        }
        
        inline virtual void PRINT() const override{
            printf("%s",this->TO_STRING().c_str());
        }

        inline virtual long long int SIZE_OF() const override{
            return sizeof(value);
        }

        inline virtual string TO_STRING() const override{
            return (value)?"true":"false";
        }

        inline virtual string TYPE() const override{
            return "Bool";
        }

        inline virtual Void* GET_VOID() const override{
            return nullptr;
        }
        inline virtual Int* GET_INT() const override{
            return nullptr;
        }
        inline virtual Double* GET_DOUBLE() const override{
            return nullptr;
        }
        inline virtual String* GET_STRING() const override{
            return nullptr;
        }
        inline virtual Char* GET_CHAR() const override{
            return nullptr;
        }
        inline virtual Bool* GET_BOOL() const override{
            return const_cast<Bool*>(this);
        }
        inline virtual List* GET_LIST() const override{
            return nullptr;
        }

        inline bool GET(){
            return value;
        }

        inline static Bool* MAKE(){
            return new Bool();
        }

        inline static Bool* MAKE(bool val){
            return new Bool(val);
        }
        ~Bool(){}
};

/*
  |====================== String ===============================|
 'String' datatype uses std::string to store values.
  > string are dynamic in size so its size depends on the number of characters it stores.
  > Syntax in SRON : 'String x = "SRON is the Best" ' or "String x"
*/
class String : public Any{
    
    private :
        string value = " ";
    public :
        String(){}
        String(string str){
            try{
                this->value = str;
            }catch(const std::exception&){
                DISPLAY_EXCEPTION("creating a variable of type 'String'.",SystemOutofMemoryException);
            }
        }

        inline virtual long long int LEN() const override{
            return value.length();
        }

        inline virtual void PRINT() const override{
            printf("%s",value.c_str());
        }

        inline virtual long long int SIZE_OF() const override{
            return sizeof(value);
        }

        inline virtual string TO_STRING() const override{
            return value;
        }

        inline virtual string TYPE() const override{
            return "String";
        }

        inline virtual Void* GET_VOID() const override{
            return nullptr;
        }
        inline virtual Int* GET_INT() const override{
            return nullptr;
        }
        inline virtual Double* GET_DOUBLE() const override{
            return nullptr;
        }
        inline virtual String* GET_STRING() const override{
            return const_cast<String*>(this);
        }
        inline virtual Char* GET_CHAR() const override{
            return nullptr;
        }
        inline virtual Bool* GET_BOOL() const override{
            return nullptr;
        }
        inline virtual List* GET_LIST() const override{
            return nullptr;
        }

        inline char AT(int index){
            if(index >= 0 && index < value.length()){
                return value[index];
            }
            DISPLAY_EXCEPTION("extracting the elements from the string.",StringIndexException );
        }

        inline string GET(){
            return value;
        }

        inline static String* MAKE(){
            return new String();
        }

        inline static String* MAKE(string val){
            return new String(val);
        }
        ~String(){}
};

/*
  |====================== List ===============================|
 'List' datatype uses std::vector<Any*> to store values.
  > It is dynamic in size as well as in nature so it can store values of different datatype in a single entity. It can store List too but not itself.
  > Syntax in SRON : "List x = [1,123.678, true, false, "Heelo", 'Q ]" or "List x" or "List x = []"
*/
class List : public Any{
    private :
        std::vector<Any*> value;
    public :

        List(){}

        List(std::vector<Any*> &val){
            try{
                value = val;
            }catch(const std::exception&){
                DISPLAY_EXCEPTION("creating a variable of type 'List'.",SystemOutofMemoryException);
            }
        }

        List(Any* a){
            try{
                value.push_back(a);
            }catch(const std::exception&){
                DISPLAY_EXCEPTION("creating a variable of type 'List'.",SystemOutofMemoryException);
            }
        }
        List(Any* a, Any* b){
            try{
                value.push_back(a);
                value.push_back(b);
            }catch(const std::exception&){
                DISPLAY_EXCEPTION("creating a variable of type 'List'.",SystemOutofMemoryException);
            }
        }
        List(Any* a, Any* b, Any* c){
            try{
                value.push_back(a);
                value.push_back(b);
                value.push_back(c);
            }catch(const std::exception&){
                DISPLAY_EXCEPTION("creating a variable of type 'List'.",SystemOutofMemoryException);
            }
        }

        inline virtual long long int LEN() const override{
            return value.size();
        }

        inline virtual void PRINT() const override{
            try{
                if(value.size() == 0){
                    printf("[]");
                    return;
                }

                printf("[");
            
                std::vector<Any*>::const_iterator it = value.begin();
                for(; it != value.end()-1; ++it){
                    (*it)->PRINT();
                    printf(", ");
                }

                (*it)->PRINT();

                printf("]");
            }
            catch(const std::exception&){
                DISPLAY_EXCEPTION("displaying the list into the console",UnknownException);
            }
            
        }

        inline virtual long long int SIZE_OF() const override{
            return sizeof(value);
        }

        inline virtual string TO_STRING() const override{
            string fin = "";
            try{
                
                if(value.size() == 0){
                    return "[]";
                }
                fin="[";
                std::vector<Any*>::const_iterator it = value.begin();
                for(; it != value.end()-1; ++it){
                    fin+= (*it)->TO_STRING()+", ";
                }

                fin+=(*it)->TO_STRING()+"]";

            }catch(const std::exception&){
                DISPLAY_EXCEPTION("converting the type 'List' to type 'String'.",SystemOutofMemoryException);
            }
            return fin;
        }

        inline virtual string TYPE() const override{
            return "List";
        }

        inline virtual Void* GET_VOID() const override{
            return nullptr;
        }
        inline virtual Int* GET_INT() const override{
            return nullptr;
        }
        inline virtual Double* GET_DOUBLE() const override{
            return nullptr;
        }
        inline virtual String* GET_STRING() const override{
            return nullptr;
        }
        inline virtual Char* GET_CHAR() const override{
            return nullptr;
        }
        inline virtual Bool* GET_BOOL() const override{
            return nullptr;
        }
        inline virtual List* GET_LIST() const override{
            return const_cast<List*>(this);
        }

        inline void PUSH(Any* val){
            try{
                if(this != val){
                    value.push_back(val);
                    return;
                }
                DISPLAY_EXCEPTION("inserting a list inside itself.",InsertionException);
            }catch(const std::exception&){
                DISPLAY_EXCEPTION("appending an element into the type 'List'.",SystemOutofMemoryException);
            }
        }

        inline Any* AT(int index){
            try{
                return value[index];
            }
            catch(const std::exception&){
                DISPLAY_EXCEPTION("extracting elements from type 'List'.",IndexNotWithinRange);
            }
            return nullptr;
        }

        inline static List* MAKE(){
            return new List();
        }

        inline static List* MAKE(Any* val){
           return new List(val) ;
            
        }

        inline static Any* MAKE(List* val){
            return val;
        }

        ~List(){}
};

/*
  |====================== Vector ===============================|
 'Vector' datatype uses std::vector to store values.
  > It is dynamic in size but not dynamic in nature because it can store only similar datatypes within itself.
  > Syntax in SRON : "Vector x = [1,2,3,3,4,6,7,8,9,0]" or "Vector x" or "Vector x =[]"

  NOTE: It's implementation is causing troubles with the speed and efficieny so it will be implemented further.
*/
// template<typename T>class Vector : public Any{

//     private:
//         vector<T> value;
//     public :
//         Vector(){ }
//         Vector(vector<T>& val) : value(val){ }
        
//         inline virtual long long int LEN() const override{
//             return value.size();
//         }

//         inline virtual void PRINT() const override{
//             if(value.size() == 0){
//                 printf("[]");
//                 return;
//             }
//             printf("[");
//             typename const std::vector<T>::const_iterator it = value.begin();
//             for(; it != value.end() - 1; ++it){
                
//             }

//         }
// };

#endif