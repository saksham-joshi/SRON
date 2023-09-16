#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

class Vector{
public :
    template<typename t> inline static void INSERT(vector<t> &vec,t val){
        try{
            vec.push_back(val);
        }
        catch(exception e){
            printf("\nException Caught :\n > While pushing element in vector.\n\t> Reason 1: You inserted the wrong character.\n\t> Reason 2: System is out of memory.\n\t> Solution 1: Insert the valid elements in the vector.\n\t>Solution 2: Remove the background applications running in our system.");
            exit(1);
        }
    }

    template<typename t> inline static std::vector<t> COPY(vector<t> vec){
        try{
            std::vector<t> copy;
            for(typename std::vector<t>::iterator it = vec.begin() ; it != vec.end() ; ++it ){
                copy.push_back(*it);
            }
            return copy;
        }
        catch(std::exception e){
            printf("\nException Caught :\n > While creating vector of type int .\n\t> Reason : Your System is out of Memory .\n\t> Solution : Remove some background applications and free up RAM .\n");
            exit(1);
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
            printf("\nException Caught :\n > While creating vector of type int .\n\t> Reason : Your System is out of Memory .\n\t> Solution : Remove some background applications and free up RAM .\n");
            exit(1);
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
        catch(exception e){
            printf("\nException Caught :\n > While creating vector of type double .\n\t> Reason : Your System is out of Memory .\n\t> Solution : Remove some background applications and free up RAM .\n");
            exit(1);
        }  
    }
    template<typename t> inline static long long int LEN(const std::vector<t> vec){
        return (long long int)vec.size();
    }
    template<typename t> inline static t AT(const std::vector<t> vec,long long int index){
        if(index < 0 && index>=vec.size()){
            printf("\nException Caught :\n > While extracting a element of Vector type.\n\t> Reason 1: Index is more than or equal to the length of Vector.\n\t> Reason 2: Index is less than 0.\n\t> Solution : Store elements in vector and insert index more than 0 and less than the length of the Vector .\n");
            exit(1);
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
        for(std::vector<string>::iterator it = vec.begin() ; it != vec.end() ; ++it){
            sum+=*it;
        }
        return sum;
    }
    inline static string SUM(std::vector<char> vec){
        try{
            string sum = "";
            for(std::vector<char>::iterator it = vec.begin() ; it != vec.end() ; ++it){
                sum+=*it;
            }
            return sum;
        }
        catch(std::exception e){
            printf("\nException Caught :\n > While adding string.\n\t> Reason : Your System is out of Memory .\n\t> Solution : Remove some background applications and free up RAM .\n");
            exit(1);
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
            printf("\nException Caught :\n > While deleting an element of Vector type.\n\t> Reason 1: Index is more than or equal to the length of Vector.\n\t> Reason 2: Index is less than 0.\n\t> Solution : Store elements in vector and insert index more than 0 and less than the length of the Vector .\n");
            exit(1);
        }
        vec.erase(vec.begin()+index);
    }
    template<typename t> inline static void CLEAR(std::vector<t> &vec){
        vec.clear();
    }
    template<typename t> inline static void ASSIGN(std::vector<t> &vec , long long int index, t val){
        if(index < 0 || index >= vec.size()){
            printf("\nException Caught :\n > While assigning an element to a Vector.\n\t> Reason 1: Index is more than or equal to the length of Vector.\n\t> Reason 2: Index is less than 0.\n\t> Solution : Store elements in vector and insert index more than 0 and less than the length of the Vector .\n");
            exit(1);
        }
        vec[index] = val;
    }
    template<typename t> inline static std::vector<t> SUBVECTOR(std::vector<t> vec,long long int start , long long int end){
        if(start < 0 || end>= vec.size()){
            printf("\nException Caught :\n > While creating a subvector.\n\t> Reason 1: Index is more than or equal to the length of Vector.\n\t> Reason 2: Index is less than 0.\n\t> Solution : Store elements in vector and insert index more than 0 and less than the length of the Vector .\n");
            exit(1);
        }
        try{
            std::vector<t> temp;
            for(typename std::vector<t>::const_iterator it = vec.begin()+start ; it <vec.begin()+end ; ++it){
                temp.push_back(*it);
            }
            return temp;
        }
        catch(std::exception e){
            printf("\nException Caught :\n > While creating a Vector from another Vector.\n\t> Reason : Your System is out of Memory .\n\t> Solution : Remove some background applications and free up RAM .\n");
            exit(1);
        }
    }
    ~Vector(){ } 
};

// template<typename t>
// ostream& operator<<(ostream& COUT, vector<t> &vec){
//     for(typename std::vector<t>::const_iterator it = vec.begin() ; it != vec.end() ; ++it){
//         cout<<*it<<" ";
//     }
//     return COUT;
// }

// int main(){
    
//     // vector<double> vec1 = ;
//     long long int i = 1;
//     long long int j = 71;
//     vector<long long int> vec2 = {9,8,7,65,5324,46,9};
//     cout<<vec2<<endl;
//     Vector().ASSIGN(vec2,j,i);
//     cout<<vec2;
    
// }