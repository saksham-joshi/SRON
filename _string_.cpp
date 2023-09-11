#include<cstring>
#include<cstdio>
#include<ctype.h>
#include<iostream>
#include<vector>

using namespace std;

inline string STRIP(const string str){
    string fin = "";
    int string_end_index = 0;
    for(int i = str.length()-1 ; i>= 0 ; i--){
        if(str[i] != ' '){
            break;
        }
        string_end_index++;
    }
    for(int i = 0 ; i< strlen(str.c_str()) ; i++){
        if (str[i] != ' '){
            for (int j = i; j < str.length() - string_end_index ; j++){
                fin += str[j];
            }
            break;
        }
    }
    return fin;
}

inline string CONCAT(string str1, const string str2){
    return str1.append(str2);
}
inline string CONCAT(string str,char ch){
    return str+ch;
}
inline string CONCAT(string str,double d){
    return str+to_string(d);
}
inline string CONCAT(string str,long long int x){
    return str+to_string(x);
}

inline string CAPITALIZE(string str){
    try{ str[0] = toupper(str[0]); }
    catch(exception e){ }
    return str ;
}

inline string SUBSTRING(const string str,int start,int end){
    string fin="";
    end = (end>str.length())?str.length():end;
    start = (start<0)?0:start;
    try{
        for(int i=start;i<end;i++){
            fin+=str[i];
        }
    }
    catch(exception e){}
    return fin;
}

inline int LEN(const string str){
    return str.length();
}
inline void CLEAR(string &str){
    str="";
}
inline string COPY(const string str){
    string fin="";
    for(int i=0;i<str.length();i++){
        fin+=str[i];
    }
    return fin;
}
inline string REVERSE(const string str){
    string fin="";
    for(int i = str.length()-1 ; i>=0;i--){
        fin+=str[i];
    }
    return fin;
}

inline int COUNT(const string str,const char ch){
    int count=0;
    for(int i=0;i<str.length();i++){
        if(ch == str[i]){
            count++;
        }
    }
    return count;
}
// inline int COUNT(const string str,const string counter){

// }

inline string REPLACE(const string str , const char from, const char with){
    string fin="";
    for(int i=0;i<str.length();i++){
        if(str[i] == from){
            fin+=with;
            continue;
        }
        fin+=str[i];

    }
    return fin;
}

// inline string REPLACE(const string str , const string from , const string with){

// }

inline vector<string> SPLIT(const string str , const char splitter){
    vector<string> vec;
    string temp="";
    for(int i=0;i<str.length();i++){
        if(str[i] == splitter){
            vec.push_back(temp);
            temp="";
            continue;
        }
        temp+=str[i];
    }
    vec.push_back(temp);
    return vec;
}
// inline vector<string> SPLIT(const string str , const string splitter){

// }


int main(){
    string fin = "123-456-789";
    char ch;
    cin>>ch;
    vector<string> vec = SPLIT(fin,ch);
    for(vector<string>::iterator it = vec.begin() ; it != vec.end() ; it++){
        cout<<*it<<"<"<<endl;
    }
}