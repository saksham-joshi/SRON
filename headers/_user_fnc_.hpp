#include "_argument_list_.hpp"

namespace Sron
{

    inline Any* LEN(Argument_List &args){
        return Int::MAKE(args[0]->LEN());
    }

    inline Any* SIZE_OF(Argument_List &args){
        return Int::MAKE(args[0]->SIZE_OF());
    }

    inline Any* PRINT(Argument_List &args){
        for(size_t i=0; i < args.LEN() ; ++i){
            args[i]->PRINT();
        }
        return Void::MAKE();
    }

    inline Any* PRINTLN(Argument_List &args){
        PRINT(args);
        printf("\n");
        return Void::MAKE();
    }
    inline Any* AT(Argument_List &args){
        try{
            if(args[0]->TYPE() == "List"){
                return args[0]->GET_LIST()->AT( args[1]->GET_INT()->GET());
            }
            return Char::MAKE(args[0]->GET_STRING()->AT(args[1]->GET_INT()->GET()));
        }
        catch(std::exception&){
            DISPLAY_EXCEPTION("executing the AT function and extracting elements from it.",ArgumentException);
        }
        return nullptr;
    }
}
