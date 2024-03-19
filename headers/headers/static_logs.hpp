#ifndef LOGS_H
#define LOGS_H

#include <fstream>
#include<iostream>

class Logs
{
public:
    static unsigned short int line_number;

    static std::string filename;

    static unsigned short int GET_LINE_NUMBER();

    static void INCREMENT_LINE_NUMBER();

    static std::ifstream *mainfile;

    // this function contains the path to the file.
    static std::string directory_path;

    // this function just saves the path to the file in Logs::path
    static void SET_DIRECTORY_PATH();
    ~Logs() {}
};

unsigned short int Logs::line_number = 1;

std::string Logs::filename = "terminal";

unsigned short int Logs::GET_LINE_NUMBER()
{
    return Logs::line_number;
}
void Logs::INCREMENT_LINE_NUMBER()
{
    ++Logs::line_number;
}
std::ifstream *Logs::mainfile;

std::string Logs::directory_path = "";

void Logs::SET_DIRECTORY_PATH()
{
    int i = Logs::filename.length() - 1;

    while (i > 0 && !(Logs::filename[i] == '/' || Logs::filename[i] == '\\'))
    {
        --i;
    }
    if(i > 0){
        ++i;
    }
    Logs::directory_path = Logs::filename.substr(0,i);
}
#endif