#include<vector>
#include<iostream>
#include<algorithm>
#include "_exception_.h"

#ifndef VECTOR_H
#define VECTOR_H

class Vector{
public :
    template<typename t> inline static void INSERT(std::vector<t> &vec,t val){
        try{
            vec.push_back(val);
        }
        catch(exception e){
            DISPLAY_EXCEPTION("pushing element in vector.",5);
            
        }
    }

    template<typename t> inline static std::vector<t> COPY(std::vector<t> vec){
        try{
            std::vector<t> copy;
            for(typename std::vector<t>::iterator it = vec.begin() ; it != vec.end() ; ++it ){
                copy.push_back(*it);
            }
            return copy;
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("creating vector.",3);
            
        }
    }

    inline static std::vector<long long int> RANGE(long long int start,long long int end,long long int step=1){
        std::vector<long long int> vec;
        try{
            if(start > end){
                if(step == 1){
                    step = -1;
                }
                for(long long int i = start; i>end ; i+=step){
                    vec.push_back(i);
                }
                return vec;
            }
            for(long long int i = start; i<end ; i+=step){
                vec.push_back(i);
            }
            return vec;
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("creating vector of type Int.",3);
            
        }
    }

    inline static std::vector<double> RANGE(double start,double end,double step=1){
        try{
            std::vector<double> vec;
                if(start > end){
                    if(step == 1){
                        step = -1;
                    }
                for(double i = start; i>end ; i+=step){
                    vec.push_back(i);
                }
                return vec;
            }
            for(double i = start; i<end ; i+=step){
                vec.push_back(i);
            }
            return vec;
        }
        catch(std::exception e){
            DISPLAY_EXCEPTION("creating vector of type Double.",3);
            
        }  
    }
    template<typename t> inline static long long int LEN(const std::vector<t> vec){
        return (long long int)vec.size();
    }
    template<typename t> inline static t AT(const std::vector<t> vec,long long int index){
        if(index < 0 && index>=vec.size()){
            DISPLAY_EXCEPTION("extracting an element of Vector type.",7);
            
        }
        return vec[index];
    }
    inline static long long int SUM(std::vector<long long int> vec){
        long long int sum = 0;
        for(std::vector<long long int>::iterator it = vec.begin() ; it != vec.end() ; ++it){
            sum+=*it;
        }
        return sum;
    }
    inline static double SUM(std::vector<double> vec){
        double sum = 0;
        for(std::vector<double>::iterator it = vec.begin() ; it != vec.end() ; ++it){
            sum+=*it;
        }
        return sum;
    }
    inline static std::string SUM(std::vector<std::string> vec){
        std::string sum = "";
        for(std::vector<std::string>::iterator it = vec.begin() ; it != vec.end() ; ++it){
            sum+=*it;
        }
        return sum;
    }
    inline static std::string SUM(std::vector<char> vec){
        try{
            std::string sum = "";
            for(std::vector<char>::iterator it = vec.begin() ; it != vec.end() ; ++it){
                sum+=*it;
            }
            return sum;
        }
        catch(std::exception e){
            
            DISPLAY_EXCEPTION("adding strings.",4);
        }
        
    }
    template<typename t> inline static void SORT(std::vector<t> &vec){
        sort(vec.begin(),vec.end());
    }
    template<typename t> inline static std::vector<t> SORTED(std::vector<t> vec){
        std::vector<t> copy = Vector().COPY(vec);
        sort(copy.begin(),copy.end());
        return copy;
    }
    template<typename t> inline static bool DELETE(std::vector<t> &vec,t val){
        for(typename std::vector<t>::const_iterator it= vec.begin() ; it != vec.end() ; ++it){
            if(*it == val){
                vec.erase(it);
                return true;
            }
        }
        return false;
    }
    template<typename t> inline static long long int DELETE_ALL(std::vector<t> &vec,t val){
        long long int count=0;
        for(typename std::vector<t>::const_iterator it= vec.begin() ; it < vec.end() ; ++it ){
            if(*it == val){
                vec.erase(it);
                ++count;
            }
        }
        return count;
    }
    template<typename t> inline static void DELETE_INDEX(std::vector<t> &vec , long long int index){
        if(index < 0 || index >= vec.size()){
            DISPLAY_EXCEPTION("deleting an element of Vector type.",7);
            
        }
        vec.erase(vec.begin()+index);
    }
    template<typename t> inline static void CLEAR(std::vector<t> &vec){
        vec.clear();
    }
    template<typename t> inline static void ASSIGN(std::vector<t> &vec , long long int index, t val){
        if(index < 0 || index >= vec.size()){
            
            DISPLAY_EXCEPTION("assigning an element to a Vector.",7);
        }
        vec[index] = val;
    }
    template<typename t> inline static std::vector<t> SUBVECTOR(std::vector<t> vec,long long int start , long long int end){
        if(start < 0 || end>= vec.size()){
            
            DISPLAY_EXCEPTION("creating a SubVector.",7);
        }
        try{
            std::vector<t> temp;
            for(typename std::vector<t>::const_iterator it = vec.begin()+start ; it <vec.begin()+end ; ++it){
                temp.push_back(*it);
            }
            return temp;
        }
        catch(std::exception e){
            
            DISPLAY_EXCEPTION("creating a Vector from another vector",3);
        }
    }
    ~Vector(){ } 
};

#endif