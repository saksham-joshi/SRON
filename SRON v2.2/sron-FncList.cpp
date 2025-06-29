
#include "sron_interpreter/headers/_user_fnc_.hpp"

int main()
{
    FILE* file = nullptr;

    fopen_s(&file , (Logs::GET_EXECUTABLE_PATH() + SRON_FUNCTION_LIB_FILE_PATH ).c_str(), "wb" );

    if ( file )
    {
        SronInBuiltFncIndex_t index = 0;

        for(const auto& i : Sron::Fmap)
        {
            IndexAndHash temp( SronHasher(i._fnc_name).GET() , index++);

            std::fwrite(&temp, sizeof(temp), 1, file);  
        }

        std::fclose( file );

        printf_s("\n =| Succesfully generated the Function List |= \n ");
    }

    else {

        printf_s("\n=| Failed to generate file |= \n");

        return 1;
    }

    return 0;
}