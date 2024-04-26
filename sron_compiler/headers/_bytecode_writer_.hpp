#include "_support_.hpp"
#include "_sron_token_.hpp"
#include "_converter_.hpp"

#include <algorithm>
#include <unordered_map>
#include <stack>
#include <vector>

inline namespace ByteCodeWriter
{

    // contains the full bytecode to be saved on .srb file
    std::vector<std::string> bytecode;

    // the vector of string containing the tokenized code
    std::vector<SronToken> token_vector;

    // this iterator can be used to extract the current location of the token_vector
    std::vector<SronToken>::iterator vecit;

    // stack to keep track of scopes
    std::stack<std::string> scope_stack;

    // stack to keep track of scope iteartor, used to rewriting the next ending flag position
    //std::stack<std::vector<std::string>> iterator_stack;

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
        {"return", Flag_Return},
        {"break", Flag_Break},
        {"continue", Flag_Continue}};

    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &);
    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &, const std::string &);

    inline static void CREATE_BYTECODE();
    inline static void CONVERT_CHAR_TO_RAW_STRING();

    inline static void FILE_WRITE();

    //inline static void JUMP_TO_FIRST_OCCURRENCE(std::string str);

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
    // this function will add new element to the bytecode and also appends a newline at the end
    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &str)
    {
        // ByteCodeWriter::bytecode.append(str);
        // ByteCodeWriter::bytecode.push_back('\n');
        ByteCodeWriter::bytecode.push_back(str);
        ByteCodeWriter::bytecode.push_back("\n");
    }
    inline static void ADD_ELEMENT_TO_BYTECODE(const std::string &str1, const std::string &str2)
    {
        ByteCodeWriter::bytecode.push_back(str1);
        ByteCodeWriter::bytecode.push_back("\n");
        ByteCodeWriter::bytecode.push_back(str2);
        ByteCodeWriter::bytecode.push_back("\n");
        // ByteCodeWriter::bytecode.append(str1);
        // ByteCodeWriter::bytecode.push_back('\n');
        // ByteCodeWriter::bytecode.append(str2);
        // ByteCodeWriter::bytecode.push_back('\n');
    }

    // This function will iterate the token vector and create the bytecode
    inline static void CREATE_BYTECODE()
    {
        try
        {
            bool inside_eval_flag = false;

            for (; vecit < token_vector.end(); ++vecit)
            {
                const auto &_token_ = vecit->_token;
                if (_token_ == "," || _token_ == ":" || _token_ == "\n")
                {
                    continue;
                }
                else if (_token_ == "{")
                {
                    scope_stack.push(Flag_ScopeEnd);
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_ScopeStart);
                }
                else if (_token_ == "(")
                {
                    scope_stack.push(Flag_Args_End);
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Args_Start);
                }
                else if (_token_ == "[")
                {
                    scope_stack.push(Flag_ListEnd);
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_ListStart);
                }
                else if (_token_ == "}" || _token_ == ")" || _token_ == "]")
                {
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(scope_stack.top());
                    scope_stack.pop();

                    if (scope_stack.empty())
                    {
                        ByteCodeWriter::FILE_WRITE();
                    }
                }
                else if (vecit->_type == TYPE_OPERATOR)
                {
                    //std::cout<<"\n=======>"<<vecit->_token<<"\n";
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(vecit->_token);
                }
                else if (_token_ == "~")
                {
                    inside_eval_flag = !inside_eval_flag;
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE((inside_eval_flag) ? Flag_EvalStart : Flag_EvalEnd);
                }
                else if (vecit->_type == TYPE_ATTRIBUTE)
                {

                    if (_token_ == AttributeName)
                    {
                        vecit += 2;
                        ByteCodeWriter::fnc_name = vecit->_token;
                    }
                    else if(_token_ == AttributeVariables){
                        ++vecit;
                    }
                    else if (_token_ == AttributeArgs)
                    {
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_FunctionArgsScopeStart);
                        ByteCodeWriter::scope_stack.push(Flag_FunctionArgsScopeEnd);
                        vecit += 2;
                    }
                    else if (_token_ == AttributeReturn)
                    {
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Return);
                    }
                    else if (_token_ == AttributeCondition)
                    {
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_ConditionScopeStart);
                        ByteCodeWriter::scope_stack.push(Flag_ConditionScopeEnd);
                        vecit += 2;
                    }
                    else if (_token_ == AttributeRange)
                    {
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_RangeScopeStart);
                        ByteCodeWriter::scope_stack.push(Flag_RangeScopeEnd);
                        vecit += 2;
                    }
                    else if (_token_ == AttributeIf)
                    {
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_IfScopeStart);
                        ByteCodeWriter::scope_stack.push(Flag_IfScopeEnd);
                        vecit += 2;
                    }
                    else if (_token_ == AttributeElif)
                    {
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_ElifScopeStart);
                        ByteCodeWriter::scope_stack.push(Flag_ElifScopeEnd);
                        vecit += 2;
                    }
                    else if (_token_ == AttributeElse)
                    {
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_ElseScopeStart);
                        ByteCodeWriter::scope_stack.push(Flag_ElseScopeEnd);
                        vecit += 2;
                    }
                    else if (_token_ == AttributeFor)
                    {
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_ForScopeStart);
                        ByteCodeWriter::scope_stack.push(Flag_ForScopeEnd);
                        vecit += 2;
                    }
                    else if (_token_ == AttributeWhile)
                    {
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_WhileScopeStart);
                        ByteCodeWriter::scope_stack.push(Flag_WhileScopeEnd);
                        vecit += 2;
                    }
                    else if (Support::IS_UNSIGNED_INTEGER(vecit->_token) && vecit->_type == TYPE_ATTRIBUTE)
                    {
                        // if a numeric attribute arrives, then we just increment the iterator so that
                        // it can come to the place of colon(:) and the forloop will further increment it
                        // to the next token.
                        ++vecit;
                    }
                }
                else if(vecit->_type == TYPE_INT){
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Int_Value, vecit->_token);
                }
                else if(vecit->_type == TYPE_DOUBLE){
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Double_Value , vecit->_token);
                }
                else if(vecit->_type == TYPE_CHAR){
                    //ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Char_Value , vecit->_token);
                    ByteCodeWriter::CONVERT_CHAR_TO_RAW_STRING();
                }
                else if(vecit->_type == TYPE_BOOL){
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Bool_Value, vecit->_token);
                }
                else if(vecit->_type == TYPE_STRING){

                    // removing the initial apostrophe from starting and end of the string...
                    vecit->_token.erase(vecit->_token.begin());
                    vecit->_token.erase(vecit->_token.end()-1);

                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_StringScopeStart, std::to_string(std::count(vecit->_token.begin(), vecit->_token.end(), '\n')+2));
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(vecit->_token ,Flag_StringScopeEnd);
                }
                else if(vecit->_type == TYPE_IDENTIFIER){
                    if((vecit-1)->_type == TYPE_DATATYPE){
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Variable, vecit->_token);
                    }
                    else{
                        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Identifier_Variable, vecit->_token);
                    }
                }
                else if(vecit->_type == TYPE_DATATYPE || vecit->_type == TYPE_KEYWORD){
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(ByteCodeWriter::token_to_flag_map.at(vecit->_token));
                }
                else if(vecit->_type == TYPE_FUNCTION_CALL){
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_FunctionCall, vecit->_token);
                }
                else if(vecit->_token == "="){
                    ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Assign);
                }
                else{

                    std::cout<<"\n==============> you are missing '"<<vecit->_token<<"' saksham joshi\n";
                }
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("generating the bytecode.", SystemOutofMemoryException);
        }
    }

    // This function will write the character in the std::string bytecode to a file.
    inline static void FILE_WRITE()
    {
        try
        {
            ByteCodeWriter::fnc_name = Logs::directory_path + ByteCodeWriter::fnc_name + ".srb";

            std::ofstream outfile(ByteCodeWriter::fnc_name);

            if (outfile.is_open())
            {
                //finally writing the bytecode into the .srb file.
                //outfile.write(bytecode.data(), bytecode.size() - 1);

                for(const auto& i : ByteCodeWriter::bytecode){
                    outfile.write(i.data(), i.size());
                }

                outfile.close();

                std::cout << "\n=|> Succesfully saved SRON's Bytecode to '" << fnc_name << "'.\n";

                ByteCodeWriter::bytecode.clear();
                ByteCodeWriter::fnc_name = "";
            }
            else
            {
                DISPLAY_EXCEPTION("saving the bytecode to '" + fnc_name + "'.", ByteCodeCannotbeSavedException);
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("saving the bytecode.", SystemOutofMemoryException);
        }
    }

    // this function will convert the char type values in the ByteCodeWriter::token_vector
    // which are in the format like this '\n' or '\t' or 'A' etc. then appends to ByteCodeWriter::bytecode
    inline static void CONVERT_CHAR_TO_RAW_STRING()
    {
        char ch = (vecit->_token)[1];
        std::string temp = "";
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
        ByteCodeWriter::ADD_ELEMENT_TO_BYTECODE(Flag_Char_Value, temp);
    }
}