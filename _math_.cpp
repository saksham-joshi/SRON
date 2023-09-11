#include<string>
#include<iostream>
#include<cmath>

using namespace std;

/*
In this file, the following Mathematical functions are declared :
    1. Abs
    2. Max
    3. Min
    4. Square root
    5. Cube root
    6. Log10
    7. Log
    8. Log2
    9. Sin
    10. Cos
    11. tan
    12. ceil
    13. floor
*/

//====================|  implementing absolute value
inline double ABSOLUTE(const double i){
    return abs(i);
}
inline int ABSOLUTE(const long long int i){
    return abs(i);
}

//====================|  implementing max value
inline double MAX(const double i,const double j){
    return (i>j)?i:j;
}
inline int MAX(const long long int i ,const long long int j){
    return (i>j)?i:j;
}

//====================|  implementing min value
inline double MIN(const double i,const double j){
    return (i>j)?j:i;
}
inline long long int MIN(const long long int i , const long long int j){
    return (i>j)?j:i;
}

//====================|  implementing Square Root function
inline double SQRT(const double i){
    return sqrt(i);
}
inline double SQRT(const long long int i){
    return sqrt((double)i);
}

//====================|  implementing Cube Root function
inline double CBRT(const double i){
    return cbrt(i);
}
inline double CBRT(const long long int i){
    return cbrt((double)i);
}

//====================|  implementing log base 10 function
inline double LOG10(const double i){
    return log10(i);
}
inline double LOG10(const long long int i){
    return log10((double)i);
}

//====================| implmenting log function
inline double LOG(const double i){
    return log(i);
}
inline double LOG(const long long int i){
    return log((double)i);
}

//====================| implementing log base 2 function
inline double LOG2(const double i){
    return log2(i);
}
inline double LOG2(const long long int i){
    return log2((double)i);
}

/*
===========| implementing trigonometic functions below
    1. Sin
    2. Cos
    3. tan
*/

//=====| SIN |=====//
inline double SIN(const double d){
    return sin(d);
}
inline double SIN(const long long int d){
    return sin((double)d);
}

//=====| COS |=====//
inline double COS(const double d){
    return cos(d);
}
inline double COS(const long long int d){
    return cos((double)d);
}

//=====| TAN |=====//
inline double TAN(const double d){
    return tan(d);
}
inline double TAN(const long long int d){
    return tan((double)d);
}

/*
Now, implementation of floor, ceil and round
    1. floor = returns the largest integer that is smaller than or equal to the value passed as the argument (i.e.: rounds down the nearest integer).
    2. ceil = returns the smallest integer that is greater than or equal to the value passed as the argument (i.e.: rounds up the nearest integer).
    3. round = returns the decimal or integer value rounded to x number of decimal places.
*/
inline long long int CEIL(double d){
    return ((long long int)ceil(d));
}
inline long long int FLOOR(double d){
    return ((long long int)floor(d));
}
inline double ROUND(double d , int places){
    if(places <= 0){
        return (double)((long long int)d);
    }
    //d = (double)((long long int)(d*pow(10,(double)places)));
    std::string str = std::to_string(d);
    std::string fin = "";
    
    for(int i=0;i< str.length() ; i++){
        fin+=str[i];
        if(str[i] == '.'){
            places = ((places+i)>str.length())?str.length():places+i;
            for(int j=i+1;j<=places;j++){
                cout<<fin<<endl;
                fin+=str[j];
            }
            break;
        }
    }
    cout<<">"<< fin<<endl;
    return atof(fin) ;
}


int main(){
    long long int val = -25,i=55;
    double va2 = -25.559545,j=5.5;
    cout<<ROUND(va2,6)<<endl;
    // cout<<ROUND(va2,4)<<endl;
    // cout<<ROUND(va2,6)<<endl;
    //cout<<ROUND(va2,13)<<endl;
}


// implementing eval
// class eval{
// private :
//     string str="";

//     void replacer_checker(){
//         string fin="";
//         for(int i = 0 ; i< str.length() ; i++){
//             try{

//             }
//             catch(exception e){ }
            
//         }
//         str = fin;
//     }
    
// public :
//     eval(const string str){
//         this->str = str;
//         replacer_checker();
//     }
// };