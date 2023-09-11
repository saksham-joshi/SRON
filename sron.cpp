#include <iostream>
#include <fstream>
#include<stack>
using namespace std;

// print function code



// function to validate variable names

int main(int argc, char **argv)
{
    string str;
    try
    {
        ifstream code_file(argv[1]);
        
        while(getline(code_file , str)){
            cout<<str<<endl;
        }

    }
    catch (exception e)
    {
        cout << "File_Not_Found_Exception : " << *argv << " not found !";
    }
    // getchar();

    
}