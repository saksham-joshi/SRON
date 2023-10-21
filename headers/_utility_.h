#include<cstdlib>
#include<iostream>

#ifndef UTILITY_H
#define UTILITY_H

class Utility{
public :

    inline static void EXIT(const long long int status){
        exit(status);
    }
    template<typename t> inline static long long int SIZEOF(const t obj){
        return sizeof(obj);
    }
    template<typename t> inline static void SWAP(t &i, t &j){
        t temp = i;
        i = j;
        j = temp;
    }
};

#endif