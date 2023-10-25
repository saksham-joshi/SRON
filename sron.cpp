#include "headers/_boolean_.h"
#include "headers/_char_.h"
#include "headers/_converter_.h"
#include "headers/_exception_.h"
#include "headers/_execution_engine_.h"
#include "headers/_hashtable_.h"
#include "headers/_input_.h"
#include "headers/lexical_analyst.h"
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
            if(argc == 1){
                DISPLAY_EXCEPTION("getting the file name.",16);
            }
            DISPLAY_EXCEPTION("getting the file from the specified path.", 1);
        }

        HashTable H;
        Executor executor(H);

        while (getline(code_file, str))
        {
            std::vector<std::string> lexcode = LEX(str);
            
            if(lexcode.size() == 0){
                Logs::INCREMENT_LINE_NUMBER();
                continue;
            }
            string attribute = lexcode[0];
            std::cout<<"\n"<<attribute<<" --> "<<lexcode;

            if (attribute == "{" || attribute == "}" ){

            }
            else if (CHECK_IF_ATTRIBUTE_IS_NUMBER(attribute))
            {
                //continue;
            }
            else if (attribute == "args"){

            }
            else if (attribute == "condition")
            {
            } 
            else if (attribute == "else"){

            }
            else if (attribute == "for")
            {

            }
            else if (attribute == "if"){

            }
            else if (attribute == "name"){
                
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
                executor.VARIABLES(lexcode);
            }
            else if (attribute == "while")
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
        DISPLAY_EXCEPTION("interpreting the written code.",3);
    }
    return 0;
}
