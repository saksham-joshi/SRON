#include "muParser/muParser.h"

int main(){
    mu::Parser parser;
    const mu::string_type str() ;
    //const std::string str = "2*2/2";
    parser.SetExpr(str);
    printf("%lf",parser.Eval());
    
}