#include "_argument_list_.hpp"
#include "_variable_manager_.hpp"
#include <stack>

struct SronFunction
{
    Any* _return_value;

    // this variable contains the variables
    VariableManager _Vmanager;

    // this variable contains the name of the function
    std::string _function_name;

    // this contains each line of the vector
    std::vector<std::string> _codevector;

    // this iterator is used to iterator over the _codevector
    std::vector<std::string>::iterator _iterator;

    // and ending to the end of the the _codevector
    std::vector<std::string>::iterator _end;

    // this stack is used to handle scopes
    std::stack<std::vector<std::string>::iterator> _scopestack;

    // Argument_List containing the values passed to the function
    Argument_List _arglist;

    SronFunction(std::string function_name, Argument_List *args)
    {
        try
        {
            this->_function_name = function_name;

            auto codefile = std::ifstream(function_name + ".srb");

            if (codefile.fail())
            {
                if (function_name == "MAIN")
                {
                    DISPLAY_EXCEPTION("searching for MAIN.srb file.", MainFunctionNotFoundException, false);
                }
                DISPLAY_EXCEPTION("calling the function '" + function_name + "'.", FunctionNotFoundException);
            }

            std::string codeline;
            
            // reading the whole file and saving the lines into the _codevector
            while (std::getline(codefile, codeline))
            {
                // if there is a multiline string, then it is converted to single line at loading time...
                if(codeline == Flag_StringScopeStart){
                    
                    std::getline(codefile, codeline);

                    int loop_count = std::stoi(codeline);

                    std::string temp_string;

                    for(; loop_count != 1 ; --loop_count){
                        std::getline(codefile, codeline);
                        temp_string.append(codeline+'\n');
                    }

                    // removing the last added new line
                    temp_string.pop_back();

                    // pushing a new flag Flag_String_Value with already combined value.
                    this->_codevector.push_back(Flag_String_Value);
                    this->_codevector.push_back(temp_string);

                    // reading file again to jump the Flag_StringScopeEnd
                    std::getline(codefile, codeline);
                    
                    continue;
                }
                else if(codeline == Flag_String_Value){ 
                // line written after Flag_String_Value may contain Flag_StringScopeStart which is 
                // one of the scenario that may occur some errors

                    this->_codevector.push_back(codeline);

                    std::getline(codefile,codeline);
                }
                this->_codevector.push_back(codeline);
            }

            this->_end = this->_codevector.end();

            this->_return_value = nullptr;

            this->_iterator = this->_codevector.begin();

            this->_Vmanager = VariableManager();

            this->_arglist = *args;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing function.", SystemOutofMemoryException);
        }
    }

    ~SronFunction()
    {
        
    }
};