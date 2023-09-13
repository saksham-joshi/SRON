#include<cstdlib>
#include<iostream>

class Utility{
public :

    inline static void EXIT(long long int status){
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
