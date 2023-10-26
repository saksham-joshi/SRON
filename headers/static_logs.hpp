#ifndef LOGS_H
#define LOGS_H

class Logs{
    public :
    static int line_number;
    static int GET_LINE_NUMBER();
    static void INCREMENT_LINE_NUMBER();
};

int Logs::line_number=1;

int Logs::GET_LINE_NUMBER(){
    return Logs::line_number;    
}
void Logs::INCREMENT_LINE_NUMBER(){
    ++Logs::line_number;
}

#endif