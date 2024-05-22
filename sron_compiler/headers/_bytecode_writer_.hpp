#include "_support_.hpp"
#include "_sron_token_.hpp"
#include "_converter_.hpp"

#include <algorithm>
#include <unordered_map>
#include <stack>
#include <vector>
#include <list>

inline namespace ByteCodeWriter
{
    const char* __CLOSING_INDEX_REPLACER__ = "_";
    // contains the full bytecode to be saved on .srb file
    // std::vector<std::string> bytecode;
    std::vector<std::string> bytecode;

    // the vector of string containing the tokenized code
    std::vector<SronToken> token_vector;

    // this iterator can be used to extract the current location of the token_vector
    std::vector<SronToken>::iterator vecit;

    // stack to keep track of scopes
    std::stack<std::string> scope_stack;

    // stack to keep track of scope iteartor, used to rewriting the next ending flag position
    std::stack<std::vector<std::string>::iterator> iterator_stack;

    // contains the name of the function which is being converted to the bytecode
    std::string fnc_name;

    std::unordered_map<std::string, std::string> token_to_flag_map{
        {"=", Flag_Assign},
        {"Any", Flag_Any},
        {"Int", Flag_Int},
        {"Double", Flag_Double},
        {"Char", Flag_Char},
        {"Bool", Flag_Bool},
        {"String", Flag_String},
        {"List", Flag_List},
        {"Void", Flag_Void},
        {"return", Flag_Return},
        {"break", Flag_Break},
        {"continue", Flag_Continue}};

    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &);
    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &, const std::string &);

    inline static int ADD_ENDING_FLAG_POSITION(const char *ending_flag, std::vector<std::string>::iterator it);

    inline static void CREATE_BYTECODE();
    inline static void CONVERT_CHAR_TO_RAW_STRING();

    inline static void FILE_WRITE();

    // this function will start converting the token_vector to bytecode
    // it calls the CREATE_BYTECODE function.
    inline static void WRITE(std::vector<SronToken> &_vector)
    {

        // assigning the ByteCodeWriter::token_vector ...
        ByteCodeWriter::token_vector = _vector;

        // assigning the ByteCodeWriter::vecit at the starting of the token_vector
        ByteCodeWriter::vecit = token_vector.begin();

        // now creating the bytecode
        ByteCodeWriter::CREATE_BYTECODE();

        // clearing all the variables
        ByteCodeWriter::bytecode.clear();

        ByteCodeWriter::token_vector.clear();

        ByteCodeWriter::fnc_name.clear();

        ByteCodeWriter::token_to_flag_map.clear();
    }
}