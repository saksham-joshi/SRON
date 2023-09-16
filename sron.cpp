#include "headers/_boolean_.h"
#include "headers/_char_.h"
#include "headers/_convertor_.h"
#include "headers/_exception_.h"
#include "headers/_input_.h"
#include "headers/_math_.h"
#include "headers/_string_.h"
#include "headers/_utility_.h"
#include "headers/_vector_.h"

#include <iostream>
#include <fstream>
#include<map>


// function to validate variable names

int main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string str;
    try
    {
        ifstream code_file(argv[1]);
        if(code_file.fail()){
            throw FileNotFoundException;
        }
        while(getline(code_file , str)){
            str = String().STRIP(str);
            if(str.length() == 0){
                continue;
            }
            string attribute = Utility().GET_ATTRIBUTE(str);
            if(attribute == "Comment"){
                continue;
            }

        }
        
        
    }
    catch (const char* excep )
    {
        printf("%s",excep);
        exit(1);
    }
    return 0;
}