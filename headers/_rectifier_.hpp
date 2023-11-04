#include "_Collections_.hpp"

#ifndef RECTIFIER_H
#define RECTIFIER_H

//typedef std::variant<void, long long int, double, char, bool, std::string, std::vector<long long int>, std::vector<double>, std::vector<char>, std::vector<bool>, std::vector<std::string>> collection;

/*
 * This class implements the rectifier which converts a variant value(after typedef its called collection) to other type like long long int, double, char, bool, std::string and their vectors forms also.
 * It contains method which may throw RectifyingException which eventually exits the whole program, so we have to use it carefully.
*/


class Rectifier{
    public :
    inline static long long int TO_INT(collection val){
        try{
            return std::get<long long int>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the Int value.",25);
        }
        return 0;
    }

    inline static double TO_DOUBLE(collection val){
        try{
            return std::get<double>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the Double value.",25);
        }
        return 0;
    }

    inline static char TO_CHAR(collection val){
        try{
            return std::get<char>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the Char value.",25);
        }
        return ' ';
    }

    inline static bool TO_BOOL(collection val){
        try{
            return std::get<bool>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the Bool value.",25);
        }
        return false;
    }

    inline static std::string TO_STRING(collection val){
        try{
            return std::get<std::string>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the String value.",25);
        }
        return " ";
    }

    inline static std::vector<long long int> TO_INT_VECTOR(collection val){
        try{
            return std::get<std::vector<long long int>>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the Int[] value.",25);
        }
        exit(1);
    }

    inline static std::vector<double> TO_DOUBLE_VECTOR(collection val){
        try{
            return std::get<std::vector<double>>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the Double[] value.",25);
        }
        exit(1);
    }

    inline static std::vector<char> TO_CHAR_VECTOR(collection val){
        try{
            return std::get<std::vector<char>>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the Char[] value.",25);
        }
        exit(1);
    }

    inline static std::vector<bool> TO_BOOL_VECTOR(collection val){
        try{
            return std::get<std::vector<bool>>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the Bool[] value.",25);
        }
        exit(1);
    }

    inline static std::vector<std::string> TO_STRING_VECTOR(collection val){
        try{
            return std::get<std::vector<std::string>>(val);
        }
        catch(const std::exception&){
            DISPLAY_EXCEPTION("rectifying the String[] value.",25);
        }
        exit(1);
    }
};

#endif