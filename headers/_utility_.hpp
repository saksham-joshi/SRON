#include<cstdlib>
#include "Argument_List.hpp"

#ifndef UTILITY_H
#define UTILITY_H

class Utility{
public :

    inline static collection EXIT(ArgumentList args){
        exit(args.GET_INT(0));
    }
    inline static void EXIT(const long long int status){
        exit(status);
    }

    inline static collection SIZEOF(ArgumentList args){
        return SIZEOF(args.GET_COLLECTION(0));
    }
    template<typename t> inline static long long int SIZEOF(const t obj){
        return sizeof(obj);
    }

    inline static void SWAP(ArgumentList& args){
        collection val = args.GET_COLLECTION(0);
        args.PUT(args.GET_COLLECTION(1),0);
        args.PUT(val,1);
    }
    template<typename t> inline static void SWAP(t &i, t &j){
        t temp = i;
        i = j;
        j = temp;
    }
    ~Utility(){}
};

#endif