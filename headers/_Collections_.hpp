#include <variant>
#include <vector>
#include <string>
#include <iostream>
#include "_exception_.hpp"

#ifndef Collection_H
#define Collection_H

using std::get;
using std::string;
using std::variant;
using std::vector;
using std::cout;


typedef variant<long long int, double, char, bool, string, vector<long long int>, vector<double>, vector<char>, vector<bool>, vector<string>> collection;

class Collection_
{

public:
    inline static collection MAKE(collection val)
    {
        return val;
    }
    inline static string TYPE(collection val)
    {
        if (std::holds_alternative<long long int>(val))
        {
            return "Int";
        }
        else if (std::holds_alternative<double>(val))
        {
            return "Double";
        }
        else if (std::holds_alternative<char>(val))
        {
            return "Char";
        }
        else if (std::holds_alternative<bool>(val))
        {
            return "Bool";
        }
        else if (std::holds_alternative<string>(val))
        {
            return "String";
        }
        else if (std::holds_alternative<vector<long long int>>(val))
        {
            return "Int[]";
        }
        else if (std::holds_alternative<vector<double>>(val))
        {
            return "Double[]";
        }
        else if (std::holds_alternative<vector<char>>(val))
        {
            return "Char[]";
        }
        else if (std::holds_alternative<vector<bool>>(val))
        {
            return "Bool[]";
        }
        else if (std::holds_alternative<vector<string>>(val))
        {
            return "String[]";
        }
        return " ";
    }
    template <typename t> inline static void PRINT(vector<t> &vec, char ch)
    {
        if (vec.size() == 0)
        {
            printf("[]");
            return;
        }
        printf("[");
        typename vector<t>::const_iterator it;

        for (it = vec.begin(); it != vec.end() - 1; ++it)
        {
            cout << ch << *it << ch << ", ";
        }
        cout << ch << *it << ch << "]";
    }
    inline static void PRINT(collection val)
    {
        try
        {
            string type = TYPE(val);
            if (type == "Int")
            {
                printf("%lld", get<long long int>(val));
            }
            else if (type == "Int[]")
            {
                PRINT(get<vector<long long int>>(val), ' ');
            }
            else if (type == "Double")
            {
                printf("%0.9lf", get<double>(val));
            }
            else if (type == "Double[]")
            {
                PRINT(get<vector<double>>(val), ' ');
            }
            else if (type == "String")
            {
                printf("\"%s\"", get<string>(val).c_str());
            }
            else if (type == "String[]")
            {
                PRINT(get<vector<string>>(val), '\"');
            }
            else if (type == "Char")
            {
                printf("%c", get<char>(val));
            }
            else if (type == "Bool")
            {
                printf("%s", (get<bool>(val)) ? "true" : "false");
            }
            else if (type == "Char[]")
            {
                PRINT(get<vector<char>>(val), '\'');
            }
            else if (type == "Bool[]")
            {
                auto vec = get<vector<bool>>(val);
                if(vec.size() == 0){
                    printf("[]");return;
                }
                printf("[");
                for(int i=0; i < vec.size()-1; ++i){
                    printf("%s, ", (vec[i])? "true" : "false");
                }
                printf("%s]",(vec[vec.size()-1])?"true":"false");
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("printing the given values.", 3);
        }
    }
    inline static void PRINTLN(collection val){
        PRINT(val);
        printf("\n");
    }

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