
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define C_COMPILER   "clang"

#define CPP_COMPILER "clang++"

#define CPP_VERSION  " -std=c++23"

#define SRON_MAX_OPTIMIZATION_FLAGS " -Wall -Wextra -Wpedantic -O3 -flto -fuse-ld=lld -fvectorize -ftree-vectorize -fomit-frame-pointer -fstrict-aliasing -fstrict-vtable-pointers -fno-rtti -finline-functions -ffast-math -funroll-loops -march=native -mavx2 -mfma -m64"

#define SRON_COMPILER              CPP_COMPILER " sronc.cpp -o sronc.exe"              SRON_MAX_OPTIMIZATION_FLAGS       CPP_VERSION

#define SRON_INTERPRETER           CPP_COMPILER " sron.cpp -o sron.exe"                SRON_MAX_OPTIMIZATION_FLAGS       CPP_VERSION

#define SRON_DOCS                  C_COMPILER   " sron-docs.cpp -o sron-docs.exe -O3"

#define SRON_FNC_LIST              CPP_COMPILER " sron-FncList.cpp -o sron-FncList.exe -O3"                              CPP_VERSION

#define SRON_FNC_LIST_GENERATE     ".\\sron-FncList"

#define ArLen(__array) (sizeof(__array) / sizeof(__array[0]))


// This function returns 1, if the build is not successful otherwise 0
inline static _Bool build( const char *const __component, const char*const __command )
{
    if ( system( __command ) == 0 )
    {
        printf(
            "\n                       +-----------------------------------+"
            "\n                       ||         BUILD SUCCESSFUL        ||"
            "\n                       +-----------------------------------+"
            "\n                   Succesfully builded '%s'.\n"

            ,
            __component );
    }

    else
    {
        printf(
            "\n                       =========================="
            "\n                       <!!!!! Build Failed !!!!!>"
            "\n                       =========================="
            "\n                   Failed to build '%s'"

            ,
            __component );
        
        errno = 1;

        return 1;
    }

    return 0;
}

int main(int argc, char **argv)
{

    if (argc == 2)
    {
        if (strcmp(argv[1], "clean") == 0) system("del *.exp,*.pdb,*.lib");

        else if (strcmp(argv[1], "compiler") == 0)    build( "Sron Compiler"     , SRON_COMPILER    );

        else if (strcmp(argv[1], "interpreter") == 0) build( "Sron Interpreter"  , SRON_INTERPRETER );

        else if (strcmp(argv[1] , "fnlist") == 0)     build( "Sron-FncList"      , SRON_FNC_LIST    );

        else printf_s("\n | Invalid command: '%s'", argv[1]);
    }

    else
    {
        const char *const PROJECT_COMPILATION_STRING[][2] = {

            {   "Sron Compiler"             , SRON_COMPILER             },
            {   "Sron Interpreter"          , SRON_INTERPRETER          },
            {   "Sron Docs"                 , SRON_DOCS                 },
            {   "Sron FncList"              , SRON_FNC_LIST             },
            {   "Fnc-List file"             , SRON_FNC_LIST_GENERATE    }
        };

        for (unsigned char i = 0; i < ArLen(PROJECT_COMPILATION_STRING); ++i)
        {
            if ( build ( PROJECT_COMPILATION_STRING[i][0] , PROJECT_COMPILATION_STRING[i][1] ) ) return 0;
        }

        printf("\n"
               "           ++====================================++\n"
               "           ||                                    ||\n"
               "           ||    PROJECT-SRON BUILD COMPLETED    ||\n"
               "           ||           in %.3lf sec            ||\n"
               "           ||         CONGRATULATIONS!           ||\n"
               "           ||                                    ||\n"
               "           ++====================================++\n"
               ,
               (double)clock() / (double)CLOCKS_PER_SEC);
    }
}