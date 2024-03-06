#include "_support_.hpp"
#include "unordered_map"
#include "_user_fnc_.hpp"
#include <stack>
#include <vector>

inline namespace ByteCodeWriter
{

    // contains the full bytecode to be saved on .srb file
    std::string bytecode;

    // the vector of string containing the tokenized code
    std::vector<std::string> token_vector;

    // this iterator can be used to extract the current location of the token_vector
    std::vector<std::string>::iterator vecit;

    // stack to keep track of scopes
    std::stack<std::string> scope_stack;

    std::unordered_map<std::string, std::string> token_to_flag_map{
        {"{", Flag_ScopeStart},
        {"}", Flag_ScopeEnd},
        {"(", Flag_Args_Start},
        {")", Flag_Args_End},
        {"[", Flag_ListStart},
        {"]", Flag_ListEnd},
        {"~", Flag_MathEvalStart},
        {",", Flag_Comma},
        {"=", Flag_Assign},
        {"\n", Flag_LineEnd},
        {"Int", Flag_Int},
        {"Double", Flag_Double},
        {"Char", Flag_Char},
        {"Bool", Flag_Bool},
        {"String", Flag_String},
        {"List", Flag_List},
        {"return", Flag_Return},
        {"args", Flag_FunctionArgsScopeStart}};

    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &);
    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &, const std::string &);

    inline static void CREATE_BYTECODE();
    inline static void CONVERT_CHAR_TO_RAW_STRING();

    inline static void FILE_WRITE(std::string &);

    // this function will start converting the token_vector to bytecode
    // it calls the CREATE_BYTECODE function.
    inline static void WRITE(std::vector<std::string> &_vector)
    {

        ByteCodeWriter::token_vector = _vector;

        ByteCodeWriter::vecit = token_vector.begin();

        ByteCodeWriter::CREATE_BYTECODE();
    }

    // this function will add new element to the bytecode and also appends a newline at the end
    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &str)
    {
        ByteCodeWriter::bytecode.append(str);
        ByteCodeWriter::bytecode.push_back('\n');
    }
    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &str1, const std::string &str2)
    {
        ByteCodeWriter::bytecode.append(str1);
        ByteCodeWriter::bytecode.push_back('\n');
        ByteCodeWriter::bytecode.append(str2);
        ByteCodeWriter::bytecode.push_back('\n');
    }

    // this function will identify the identifier either it is a variable or a function
    // then calls the ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE function
    inline static void IDENTIFY_IDENTIFIER_AND_ADD()
    {

        // if a identifier is in *vecit and if the value is *(vecit-1) is a datatype
        // then there must be the variable declaration
        if (vecit > token_vector.begin() && Support::IS_DATATYPE(*(vecit - 1)))
        {
            ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Variable, *vecit);
        }
        // if after a identifier there is a opening bracket '(' , then there
        // is a function call therefore adding a function call flag
        else if (vecit < token_vector.end() - 1 && *(vecit + 1) == "(")
        {
            ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_FunctionCall, Flag_FunctionArgsScopeStart);
            scope_stack.push(Flag_FunctionArgsScopeEnd);
            ++vecit;
        }
    }

    // This function will iterate the token vector and create the bytecode
    inline static void CREATE_BYTECODE()
    {

        std::string fnc_name = "";

        for (; vecit < token_vector.end(); ++vecit)
        {
            // first handling scopes
            if (*vecit == "{")
            {
                scope_stack.push(Flag_ScopeEnd);
            }
            else if (*vecit == "}" || *vecit == ")" || *vecit == "]")
            {
                ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(scope_stack.top());
                scope_stack.pop();

                if (scope_stack.empty())
                {
                    ByteCodeWriter::FILE_WRITE(fnc_name);
                }
                continue;
            }
            else if (*vecit == ":")
            {
                continue;
            }
            else if (*vecit == AttributeName)
            {
                fnc_name = *(vecit + 2);
                vecit += 2;
            }

            auto byte = ByteCodeWriter::token_to_flag_map.find(*vecit);
            if (byte != token_to_flag_map.end())
            {
                ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(byte->second);
                continue;
            }

            unsigned short int temp = Support::IDENTIFY_TYPE_FROM_STRING(*vecit);

            switch (temp)
            {

            case TYPE_OPERATOR:
                ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(*vecit);
            case TYPE_INT:
                ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Int, *vecit);
                break;
            case TYPE_DOUBLE:
                ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Double, *vecit);
                break;
            case TYPE_CHAR:
                ByteCodeWriter::CONVERT_CHAR_TO_RAW_STRING();
                break;
            case TYPE_BOOL:
                ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Bool, *vecit);
                break;
            case TYPE_LIST:
                ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_List, *vecit);
                ByteCodeWriter::scope_stack.push(Flag_ListEnd);
                break;
            case TYPE_STRING:
                ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_String, Flag_StringScopeStart);

                // removing the initial and ending apostrophe (")
                (*vecit).erase(vecit->begin());
                (*vecit).erase(vecit->end() - 1);

                // writing to the bytecode
                ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(*vecit, Flag_StringScopeEnd);
                break;

            case IDENTIFIER:
                ByteCodeWriter::IDENTIFY_IDENTIFIER_AND_ADD();
                break;
            }
        }
    }

    // This function will write the character in the std::string bytecode to a file.
    inline static void FILE_WRITE(std::string &fnc_name)
    {
        try
        {
            // if the name of the function is MAIN, then the function's bytecode
            // will be saved as the name of the file which is being compiled by the user.

            if (fnc_name == "MAIN")
            {
                fnc_name = std::string(Logs::filename);
                fnc_name = fnc_name.substr(0, fnc_name.find_last_of('.')) + ".srb";
            }
            else
            {
                // if the function name is not main, then the file name will be same
                // as the function name adding .srb extension at the end.
                fnc_name += ".srb";
            }

            std::ofstream outfile(fnc_name);

            if (outfile.is_open())
            {
                // finally writing the bytecode into the .srb file.
                outfile.write(bytecode.data(), bytecode.size() - 1);

                outfile.close();

                std::cout << "\n\n =|> Succesfully saved SRON's Bytecode to " << fnc_name << ".\n";

                bytecode.clear();
            }
            else
            {
                DISPLAY_EXCEPTION("saving the bytecode to '" + fnc_name + "'.", ByteCodeCannotbeSavedException);
            }
        }
        catch (const std::exception &ex)
        {
            std::cout << "\nError : " << ex.what();
            DISPLAY_EXCEPTION("saving the bytecode.", SystemOutofMemoryException);
        }
    }

    // this function will convert the char type values in the ByteCodeWriter::token_vector
    // which are in the format like this '\n' or '\t' or 'A' etc. then appends to ByteCodeWriter::bytecode
    inline static void CONVERT_CHAR_TO_RAW_STRING()
    {
        char ch = (*vecit)[1];
        string temp = "";
        switch (ch)
        {

        case '\\':
            temp = "\\";
            break;
        case '\n':
            temp = "\\n";
            break;
        case '\t':
            temp = "\\t";
            break;
        case '\"':
            temp = "\"";
            break;
        case '\'':
            temp = "\'";
            break;
        default:
            temp = (std::string) "" + ch;
        }
        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(temp);
    }
}