#include<string>

using namespace std;

//====================| Implementing the logical operators
inline bool OR(bool val1,bool val2){
    return val1 || val2;
}
inline bool AND(bool val1 , bool val2){
    return val1 && val2;
}
inline bool NOT(bool val1){
    return !val1;
}

//====================| Implementing the == operator
inline bool COMPARE(int val1 , int val2){
    return val1 == val2;
}
inline bool COMPARE(string val1 , string val2){
    return val1 == val2;
}
inline bool COMPARE(double val1 , double val2){
    return val1 == val2;
}

//====================| Implementing < , <= , > , >= for int & double

//      1. > [is greater than]
inline bool ISGREATER(long long int val1 , long long int val2){
    return val1>val2;
}
inline bool ISGREATER(double val1 , double val2){
    return val1>val2;
}

//     2. < [is less than]
inline bool ISLESS(long long int val1 , long long int val2){
    return val1<val2;
}
inline bool ISLESS(double val1 , double val2){
    return val1<val2;
}

//      3. >= [is greater than or equal to]
inline bool ISGREATER_EQUAL(long long int val1 , long long int val2){
    return val1>=val2;
}
inline bool ISGREATER_EQUAL(double val1 , double val2){
    return val1>=val2;
}

//      4. >= [is less than or equal to]
inline bool ISLESS_EQUAL(long long int val1,long long int val2){
    return val1<=val2;
}
inline bool ISLESS_EQUAL(double val1 , double val2){
    return val1<=val2;
}
