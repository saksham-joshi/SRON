#include<fstream>
#ifndef LOGS_H
#define LOGS_H

class Logs{
    public :
    static unsigned short int line_number;
    static const char * filename;
    static unsigned short int GET_LINE_NUMBER();
    static void INCREMENT_LINE_NUMBER();
    static std::ifstream *mainfile;
    ~Logs(){}
};

unsigned short int Logs::line_number=1;

const char *Logs::filename;

unsigned short int Logs::GET_LINE_NUMBER(){
    return Logs::line_number;    
}
void Logs::INCREMENT_LINE_NUMBER(){
    ++Logs::line_number;
}
std::ifstream *Logs::mainfile;

#endif