#include "headers/_boolean_.h"
#include "headers/_char_.h"
#include "headers/_convertor_.h"
#include "headers/_exception_.h"
#include "headers/_execution_engine_.h"
#include "headers/_hashtable_.h"
#include "headers/_input_.h"
#include "headers/_math_.h"
#include "headers/_string_.h"
#include "headers/static_logs.h"
#include "headers/_utility_.h"
#include "headers/_vector_.h"

#include <iostream>
#include <fstream>
#include <map>

int main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    string str;
    try
    {
        ifstream code_file(argv[1]);
        if (code_file.fail())
        {
            DISPLAY_EXCEPTION("getting the file from the specified path.", 1);
        }

        while (getline(code_file, str))
        {

            str = String().STRIP(str);
            if (str.length() == 0)
            {
                continue;
            }
            else if(str == "{" || str == "}" ){
                continue;
            }

            String_and_Int obj = Executor::GET_ATTRIBUTE(str);
            string attribute = obj.str;

            if (Executor::CHECK_IF_ATTRIBUTE_IS_NUMBER(attribute))
            {
                continue;
            }
            else if(attribute == "args"){

            }
            else if (attribute == "comment")
            {
                continue;
            }
            else if (attribute == "condition")
            {
            }  
            else if (attribute == "forloop")
            {

            }
            else if(attribute == "name"){
                
            }
            else if (attribute == "range")
            {

            }
            else if (attribute == "return")
            {

            }
            else if (attribute == "type")
            {

            }
            else if (attribute == "variables")
            {

            }
            else if (attribute == "whileloop")
            {

            }   
            else
            {
                DISPLAY_EXCEPTION("mapping the attribute with the functionality.", 8);
            }
            Logs::INCREMENT_LINE_NUMBER() ;
        }
    }
    catch (const char *excep)
    {
        printf("%s", excep);
        exit(1);
    }
    catch (std::exception)
    {
    }
    return 0;
}
