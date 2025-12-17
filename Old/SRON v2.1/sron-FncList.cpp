
#include "sron_interpreter/headers/_user_fnc_.hpp"

int main(){

    std::ofstream file("meta/__function__lib", std::ios::binary);

    if(file.fail()){

        std::cout<<"\n=| Failed to generate file |= \n";

        return 1;
    }

    for(const auto& i : Sron::Fmap){

        size_t temp = i.first.GET();

        file.write (reinterpret_cast<const char*>(&temp), sizeof(temp) );
        
    }

    file.close();

    std::cout<<"\n =| Succesfully generated the Function List |= \n ";

    return 0;
}