#include "_argument_list_.hpp"
#include "_variable_manager_.hpp"
#include <stack>

struct SronFunction
{
    Any *_return_value;

    // this variable contains the variables
    VariableManager _Vmanager;

    // this iterator is used to iterator over the _codevector
    std::vector<std::string>::iterator _iterator;

    // and ending to the end of the the _codevector
    std::vector<std::string>::iterator _end;

    // this stack is used to handle scopes
    std::stack<std::vector<std::string>::iterator> _scopestack;

    // Argument_List containing the values passed to the function
    Argument_List& _arglist;

    SronFunction(std::string function_name, Argument_List &args) : _arglist(args) {
        try
        {
            std::vector<std::string>::iterator ar[2];

            Support::GET_FUNCTION_VECTOR(function_name, ar);

            this->_iterator = ar[0];

            this->_end = ar[1];

            this->_return_value = nullptr;

        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("executing function.", SystemOutofMemoryException);
        }
    }

    ~SronFunction()
    {
        delete this->_return_value;
    }
};