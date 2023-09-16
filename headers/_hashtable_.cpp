/*
 * This HashTable implementation will be used to declare and store variables .
 * Also allow developers to free up memory at runtime which eventually increase the speed of the program at whole another level.
 */

#include<vector>
#include<map>
#include<iostream>
#include<algorithm>

using namespace std;

#define VariableExistAlreadyException "Exception Caught :\n\t> Reason: Specified Variable already exist !\n\t> Solution: Enter a different & valid variable name."
#define VariableNotFoundException "Exception Caught :\n\t> Reason: Specified Variable not found !\n\t> Solution: Enter a valid variable name."


class HashTable{
    private :
    std::map<std::string,long long int> IntMap;
    std::map<std::string,double> DoubleMap;
    std::map<std::string,char> CharMap;
    std::map<std::string,std::string> StringMap;
    std::map<std::string,bool> BoolMap;
    std::map<std::string,std::vector<std::string>> VectorStringMap;
    std::map<std::string,std::vector<long long int>> VectorIntMap;
    std::map<std::string,std::vector<double>> VectorDoubleMap;
    std::map<std::string,std::vector<char>> VectorCharMap;
    std::map<std::string,std::vector<bool>> VectorBoolMap;
    
    //std::vector<std::string> variable_list;
    std::map<std::string , std::string> variable_map;

    bool CHECK_IF_ELEMENT_EXIST(string str){
        // if(variable_list.end() == std::find(variable_list.begin() , variable_list.end() , str) ){
        //     return false;
        // }
        if(variable_map.find(
            
        ))
        return true;
    }
    
    //==========| insertion of variables |==========//
    void INSERT(std::string str , long long int val){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        IntMap[str] = val;
    }
    void INSERT(std::string str , double val){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        DoubleMap[str] = val;
    }
    void INSERT(std::string str , char val){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        CharMap[str] = val;
    }
    void INSERT(std::string str , std::string val){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        StringMap[str] = val;
    }
    void INSERT(std::string str , bool val){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        BoolMap[str] = val;
    }
    void INSERT(std::string str,std::vector<std::string> vec){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        VectorStringMap[str] = vec;
    }
    void INSERT(std::string str,std::vector<long long int> vec){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        VectorIntMap[str] = vec;
    }
    void INSERT(std::string str , std::vector<double> vec){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        VectorDoubleMap[str] = vec;
    }
    void INSERT(std::string str , std::vector<char> vec){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        VectorCharMap[str] = vec;
    }
    void INSERT(std::string str , std::vector<bool> vec){
        if(CHECK_IF_ELEMENT_EXIST(str)){
            printf("%s",VariableExistAlreadyException);
            exit(1);
        }
        VectorBoolMap[str] = vec;
    }

    /*
     * 
     * 
     * 
     */

    public :
    /*
     *                  Free function Implementation
     * This functionality will allow developers of clear up memory at runtime
     */
    void Free(string str){
        // for(std::vector<std::string>::iterator it = variable_list.begin() ; it < variable_list.end() ; ++it)
        std::vector<std::string>::iterator it = std::find(variable_list.begin() , variable_list.end() , str);
        if(it != variable_list.end()){
            
        }
        printf("%s",VariableNotFoundException);
    }
    ~HashTable(){ }

    friend int main();
    //friend int main(int argc , char **argv);
};
// class HashTable{

//     private :


//     public :
//         HashTable(){

//         }
// };

int main(){
    
}
