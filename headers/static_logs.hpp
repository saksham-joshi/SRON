#ifndef LOGS_H
#define LOGS_H


#include<fstream>

class Logs{
    public :
    static unsigned short int line_number;
    static std::string filename ;
    static unsigned short int GET_LINE_NUMBER();
    static void INCREMENT_LINE_NUMBER();
    static std::ifstream *mainfile;
    ~Logs(){}
};

unsigned short int Logs::line_number=1;

std::string Logs::filename = "terminal" ;

unsigned short int Logs::GET_LINE_NUMBER(){
    return Logs::line_number;    
}
void Logs::INCREMENT_LINE_NUMBER(){
    ++Logs::line_number;
}
std::ifstream *Logs::mainfile;

#endif