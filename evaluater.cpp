#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

class eval{

    unordered_map<char,int> umap;

    public :

    eval(string str){

        umap['^'] = 3;

        umap['/'] = 2;
        umap['*'] = 2;

        umap['+'] = 1;
        umap['-'] = 1;
    }



    private :
    static string extract_number_till_operator(string str, int index){
        string fin = ""+str[index++];
        try{
            for(int i = index ; i < str.length() ; i++){
                if(is_number(str[i])){
                    fin += string(1,str[i]);
                    continue;
                }
                break;
            }
        }
        catch(exception e){
            cout<<"Exception Caught :"<<e.what()<<endl;
        }
    }
    static bool is_operator(char ch){
        if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' ){
            return true;
        }
        return false;
    }
    static bool is_number(char ch){
        if (ch == '0' || ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '.') {
            return true;
        }
        return false;
    }
    ~eval(){ }
};