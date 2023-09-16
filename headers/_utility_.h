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
private : 
    inline static string GET_ATTRIBUTE(string str){
        int i=0;
        string attribute = "";
        while(str[i] != ':'){
            if(str[i] == ' '){
                ++i;
                continue;
            }
            attribute+=str[i++];
        }
    }
    friend int main(int argc, char **argv);
};
