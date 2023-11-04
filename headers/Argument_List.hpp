
#include "_Collections_.hpp"

#ifndef ARGUMENT_LIST_H
#define ARGUMENT_LIST_H

class ArgumentList{

     std::vector<collection> vec;
    public :

    ArgumentList(){ }

    ArgumentList(collection& val){
        vec.push_back(val);
    }
    ArgumentList(collection& val1,collection& val2){
        vec.push_back(val1);
        vec.push_back(val2);
    }
    ArgumentList(collection& val1, collection& val2, collection& val3){
        vec.push_back(val1);
        vec.push_back(val2);
        vec.push_back(val3);
    }

    /*
     * This function returns the argument and it also throws exceptions whenever
     * a wrong value is returned.
    */
    inline long long int GET_INT(int index){ 
        try{
            if(index >= vec.size() || index < 0){
                throw " " ;
            }
            else if(std::holds_alternative<long long int>(vec[index]) ){
                return std::get<long long int>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Int.",23);
            }
        }
        catch(const char *){
            DISPLAY_EXCEPTION("extracting the passes argument of type Int.",23);
        }
        return 0;
    }
    inline double GET_DOUBLE(int index){
        try{
            if(index >= vec.size() || index < 0){
                throw " ";
            }
            else if(std::holds_alternative<double>(vec[index]) ){
                return std::get<double>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Double.",23);
            }
        }
        catch(const char *){
            DISPLAY_EXCEPTION("extracting the passed argument of type Double.",23);
        }
        return 0;
    }
    inline char GET_CHAR(int index){
        try{
            if(index >= vec.size() || index < 0){
                throw " ";
            }
            else if(std::holds_alternative<char>(vec[index]) ){
                return std::get<char>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Char.",23);
            }
        }
        catch(const char *){
            
        }
        return ' ' ;
    }
    inline bool GET_BOOL(int index){
        try{
            if(index >= vec.size() || index < 0){
                throw " ";
            }
            else if(std::holds_alternative<bool>(vec[index]) ){
                return std::get<bool>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type Bool.",23);
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("extracting the passes argument of type Bool.",23);
        }
        return false;
    }
    inline std::string GET_STRING(int index){
        try{
            if(index >= vec.size() || index < 0){
                throw " ";
            }
            else if(std::holds_alternative<std::string>(vec[index]) ){
                return std::get<std::string>(vec[index]);
            }
            else{
                DISPLAY_EXCEPTION("receiving the argument of type String.",23);
            }
        }
        catch(const char*){
            DISPLAY_EXCEPTION("extracting the passes argument of type String.",23);
        }
        return " ";
    }

    inline std::vector<long long int>& GET_INT_VECTOR(int index){
        try{
            if(index >= vec.size() || index < 0){
                throw ThrowException();
            }
            else if(std::holds_alternative<std::vector<long long int>>(vec[index]) ){
                return std::get<std::vector<long long int>>(vec[index]);
            } 
            throw ThrowException();
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("receiving the argument of type Int[].",23);
        }
        exit(0);
    }
    inline std::vector<double>& GET_DOUBLE_VECTOR(int index){
        try{
            if(index >= vec.size() || index < 0){
                throw ThrowException();
            }
            else if(std::holds_alternative<std::vector<double>>(vec[index]) ){
                return std::get<std::vector<double>>(vec[index]);
            }
            throw ThrowException();
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("receiving the argument of type Double[].",23);
        }
        exit(0);
    }
    inline std::vector<char>& GET_CHAR_VECTOR(int index){
        try{
            if(index >= vec.size() || index < 0){
                throw ThrowException() ;
            }
            else if(std::holds_alternative<std::vector<char>>(vec[index]) ){
                return std::get<std::vector<char>>(vec[index]);
            }
            throw ThrowException();
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("receiving the argument of type Char[].",23);
        }
        exit(0);
    }
    inline std::vector<bool>& GET_BOOL_VECTOR(int index){
        try{
            if(index >= vec.size() || index < 0){
                throw ThrowException() ;
            }
            else if(std::holds_alternative<std::vector<bool>>(vec[index]) ){
                return std::get<std::vector<bool>>(vec[index]);
            }
            throw ThrowException();
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("receiving the argument of type Bool[].",23);
        }
        exit(0);
    }
    inline std::vector<std::string>& GET_STRING_VECTOR(int index){
        try{
            if(index >= vec.size() || index < 0){
                throw ThrowException() ;
            }
            else if(std::holds_alternative<std::vector<std::string>>(vec[index]) ){
                return std::get<std::vector<std::string>>(vec[index]);
            }
            throw ThrowException();
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("receiving the argument of type String[].",23);
        }
        exit(0);
    }

    /*
     * This function is used to input the values to the argument list.
     * 
    */
    inline void PUT(collection val){
        try{
            vec.push_back(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("passing the argument to the function.",3);
        }
    }

    // ================================================================| Non-Input-Output operations are defined below from here !
    inline int LEN(){
        return vec.size();
    }

    inline std::vector<collection> GET_VARIANT(){
        return vec;
    }

    // inline static ArgumentList& GET_OBJECT(collection val){
    //     ArgumentList arg;
    //     arg.PUT(val);
    //     return arg;
    // }

    inline std::string GET_TYPE(int index){
        if(index >= vec.size() || index < 0){
            DISPLAY_EXCEPTION("extracting elements from argument list.",22 );
        }
        return Collection_::TYPE(vec[index]);
    }
    ~ArgumentList(){ }
};

#endif