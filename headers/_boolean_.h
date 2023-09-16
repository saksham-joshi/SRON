#include<string>

using namespace std;

//====================| Implementing the logical operators
inline bool OR(const bool val1,const bool val2){
    return val1 || val2;
}
inline bool AND(const bool val1 ,const bool val2){
    return val1 && val2;
}
inline bool NOT(const bool val1){
    return !val1;
}

//====================| Implementing the == operator
inline bool COMPARE(const int val1 , const int val2){
    return val1 == val2;
}
inline bool COMPARE(const string val1 , const string val2){
    return val1 == val2;
}
inline bool COMPARE(const double val1 ,const double val2){
    return val1 == val2;
}
inline bool COMPARE(const char ch1,const char ch2){
    return ch1 == ch2;
}
inline bool COMPARE(const bool b1,const bool b2){
    return b1 == b2;
}


//====================| Implementing < , <= , > , >= for int & double

//      1. > [is greater than]
inline bool ISGREATER(const long long int val1 , const long long int val2){
    return val1>val2;
}
inline bool ISGREATER(const double val1 , const double val2){
    return val1>val2;
}

//     2. < [is less than]
inline bool ISLESS(const long long int val1 , const long long int val2){
    return val1<val2;
}
inline bool ISLESS(const double val1 , const double val2){
    return val1<val2;
}

//      3. >= [is greater than or equal to]
inline bool ISGREATER_EQUAL(const long long int val1 , const long long int val2){
    return val1>=val2;
}
inline bool ISGREATER_EQUAL(const double val1 , const double val2){
    return val1>=val2;
}

//      4. >= [is less than or equal to]
inline bool ISLESS_EQUAL(const long long int val1,const long long int val2){
    return val1<=val2;
}
inline bool ISLESS_EQUAL(const double val1 , const double val2){
    return val1<=val2;
}
