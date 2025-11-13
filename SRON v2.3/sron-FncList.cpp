
#include "./sron_interpreter/headers/_user_fnc_.hpp"

int main()
{
    std::printf("\n -- Generating Fnc List --");

    FILE* file = nullptr;

    auto fnlist_exec = SronSupport::getExecutablePath() + SRON_FUNCTION_LIB_FILE_PATH;

    SronSupport::safeOpenFile(&file , fnlist_exec.c_str(), "wb" );

    if ( file )
    {
        SronInBuiltFncIndex_t index = 0;

        for(const auto& i : Sron::Fmap)
        {
            IndexAndHash temp( SronHasher(i._fnc_name).GET() , index++);

            std::fwrite(&temp, sizeof(temp), 1, file);  
        }

        std::fclose( file );

        std::printf("\n =| Succesfully generated the Function List |= \n ");
    }

    else {

        std::printf("\n=| Failed to generate file |= \n");

        return 1;
    }

    return 0;
}