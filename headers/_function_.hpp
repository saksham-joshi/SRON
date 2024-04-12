#include "_argument_list_.hpp"
#include "_variable_manager_.hpp"
#include <stack>

struct SronFunction
{
    // this variable contains the variables
    VariableManager _Vmanager;

    // this variable contains the current code in which the bytecode is there.
    std::string _codeline;

    // this variable contains the name of the function
    std::string _function_name;

    // this contains each line of the vector
    std::vector<std::string> _codevector;

    // this iterator is used to iterator over the _codevector
    std::vector<std::string>::iterator _iterator;

    // this stack is used to handle scopes
    std::stack<std::vector<std::string>::iterator> _scopestack;

    // Argument_List containing the values passed to the function
    Argument_List *_arglist;

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

            // reading the whole file and saving the lines into the _codevector
            while (std::getline(codefile, this->_codeline))
            {
                this->_codevector.push_back(this->_codeline);
            }

            // putting empty into the codeline
            this->_codeline = "";

            this->_iterator = this->_codevector.begin();

            this->_Vmanager = VariableManager();

            this->_arglist = args;
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing function.", SystemOutofMemoryException);
        }
    }

    ~SronFunction()
    {
        //std::cout<<"destroying function"<<this->_function_name;
        this->_function_name.~basic_string();

        this->_Vmanager.~VariableManager();

        this->_arglist->~Argument_List();

        this->_codevector.~vector();

        this->_codeline.~basic_string();
        //std::cout<<"destruction end function"<<this->_function_name;
    }
};