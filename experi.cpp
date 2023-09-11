#include<iostream>
// #include<string>
#include<stdarg.h>
using namespace std;

//inline long long int ADD(long long int a , long long int b){ return a+b ;}

// inline std::string MINUS(std::string str1 , std::string str2){
//     if (str1.length() < str2.length() || str2.length() == 0){
//         return str1;
//     }
//     for(int i=0;i<str1.length();i++){
//         if(str1[i] == str2[0]){
//             for(int j=i++;j<str2.length();j++){
//                 if(){
//                     break;
//                 }
//             }
//         }
//     }
//     std::string fin="";
//     return fin;
// }

// inline long long int SUM(long long int n_args , ...){
//     va_list vl;
//     va_start(vl,n_args);
//     long long int sum = va_arg(vl,long long int);
//     for(int i=1;i<n_args;i++) sum+=va_arg(vl,long long int);
//     va_end(vl);
//     return sum;
// }

// template<class... Args>
// inline long long int SUM(Args... args){
//     for_each(args,)
// }

inline std::string ToUPPERCASE(std::string str){
        for(int i=0;i<str.length();i++){
            str[i] = toupper(str[i]);
        }
        return str;
    }


int main(){
    cout<<ToUPPERCASE("efqw123@#afasfsdf");
}