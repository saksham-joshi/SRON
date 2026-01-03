
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define C_COMPILER   "clang"

#define CPP_COMPILER "clang++"

#define CPP_VERSION  " -std=c++23"

#ifdef _WIN64
    #define LINKER_NAME      "lld"
    #define CLEAN_CMD        "del *.srb,experi.exe,experi,sronc.exe,sron.exe,sron-docs.exe,sron-FncList.exe,testcase\\*.srb"
    #define EXEC_EXTENSION   ".exe"
    #define PRE_COMMAND      ".\\"
    #define LINKER_STACK_CMD " -Xlinker /STACK:16777216,16777216"
#elif defined(__linux__)
    #define LINKER_NAME      "ld"
    #define CLEAN_CMD        "rm *.srb experi sron sronc sron-docs sron-FncList testcase/*.srb"
    #define EXEC_EXTENSION   ""
    #define PRE_COMMAND      "./"
    #define LINKER_STACK_CMD " -Wl,-z,stack-size=16777216"
    #define PACK_GENERATE    "tar -czf Installer/SRON-v2.3-linux-x64.tar.gz meta/Errors meta/Exceptions sronc sron sron-docs sron-FncList Installer/uninstall_sron.sh"
#else
    #error "SRON's codebase is only maintained for Windows x64 and Linux x64"
#endif

#define SRON_MAX_OPTIMIZATION_FLAGS " -static -Wall -Wextra -Wpedantic -O2 -flto -fuse-ld=" LINKER_NAME " -fvectorize -ftree-vectorize -fomit-frame-pointer -fstrict-aliasing -fstrict-vtable-pointers -fno-rtti -finline-functions -ffast-math -funroll-loops -march=native -m64"

#define SRON_COMPILER              CPP_COMPILER " sronc.cpp -o sronc"                     EXEC_EXTENSION      SRON_MAX_OPTIMIZATION_FLAGS       CPP_VERSION       LINKER_STACK_CMD

#define SRON_INTERPRETER           CPP_COMPILER " sron.cpp -o sron"                       EXEC_EXTENSION      SRON_MAX_OPTIMIZATION_FLAGS       CPP_VERSION       LINKER_STACK_CMD

#define SRON_DOCS                  C_COMPILER   " sron-docs.c -o sron-docs"               EXEC_EXTENSION                     " -static"

#define SRON_FNC_LIST              CPP_COMPILER " sron-FncList.cpp -O3 -o sron-FncList"   EXEC_EXTENSION      CPP_VERSION    " -static"

#define SRON_FNC_LIST_GENERATE     PRE_COMMAND "sron-FncList"

#define SRON_TESTCASE              C_COMPILER   " sron-test.c -o sron-test"               EXEC_EXTENSION      " -Wall -Wextra -std=c23"    

#define ArLen(__array) (sizeof(__array) / sizeof(__array[0]))

inline static double getTimeTaken( void ) // returns time taken in seconds
{
    #if defined(_WIN64)
        return (double)clock() / (double) CLOCKS_PER_SEC;
    #elif defined(__linux__)
        #include "/usr/include/time.h"

        struct timespec ts;

        clock_gettime(CLOCK_MONOTONIC, &ts);

        return ((unsigned long long)ts.tv_sec * 1000ULL + ts.tv_nsec / 1000000ULL) / 1000;
    #else
        #error To display the time taken to compile the project, it uses OS-specific headers. Please Implement!
    #endif
}


// This function returns 1, if the build is not successful otherwise 0
inline static _Bool build( const char *const __component, const char*const __command )
{
    if ( system( __command ) == 0 )
    {
        printf( "\033[32m" "\033[1m"
            "\n                       +-----------------------------------+"
            "\n                       ||         BUILD SUCCESSFUL        ||"
            "\n                       +-----------------------------------+"
            "\n                   Succesfully builded '%s'\n" "\033[0m"

            ,
            __component );
    }

    else
    {
        printf( "\033[31m" "\033[1m"
            "\n                       =========================="
            "\n                       <!!!!! Build Failed !!!!!>"
            "\n                       =========================="
            "\n                   Failed to build '%s'\n" "\033[0m"

            ,
            __component );
        
        errno = 1;

        return 1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    double start_time = getTimeTaken();

    if (argc == 2)
    {
        if (strcmp(argv[1], "clean") == 0) system( CLEAN_CMD );

        else if (strcmp(argv[1], "compiler") == 0)    build( "Sron Compiler"     , SRON_COMPILER    );

        else if (strcmp(argv[1], "interpreter") == 0) build( "Sron Interpreter"  , SRON_INTERPRETER );

        else if (strcmp(argv[1] , "fnlist") == 0)     build( "Sron-FncList"      , SRON_FNC_LIST    );

        #ifdef __linux__
            else if (strcmp(argv[1], "pack") == 0)    build(  "Sron Linux Pack"  , PACK_GENERATE    );
        #endif

        else if (strcmp(argv[1], "test") == 0)        build( "Sron-Test"         , SRON_TESTCASE    );

        else printf("\n | Invalid command: '%s'", argv[1]);
    }

    else
    {
        const char *const PROJECT_COMPILATION_STRING[][2] = {

            {   "Sron Compiler"             , SRON_COMPILER             },
            {   "Sron Interpreter"          , SRON_INTERPRETER          },
            {   "Sron Docs"                 , SRON_DOCS                 },
            {   "Sron FncList"              , SRON_FNC_LIST             },
            {   "Fnc-List file"             , SRON_FNC_LIST_GENERATE    },
            {   "Sron-Test"                 , SRON_TESTCASE             }
        };

        for (unsigned char i = 0; i < ArLen(PROJECT_COMPILATION_STRING); ++i)
        {
            if ( build ( PROJECT_COMPILATION_STRING[i][0] , PROJECT_COMPILATION_STRING[i][1] ) ) return 0;
        }

        printf("\n" "\033[34m" "\033[1m"
               "           ++====================================++\n"
               "           ||                                    ||\n"
               "           ||    PROJECT-SRON BUILD COMPLETED    ||\n"
               "           ||           in %.3lf sec            ||\n"
               "           ||         CONGRATULATIONS!           ||\n"
               "           ||                                    ||\n"
               "           ++====================================++\n" "\033[0m"
               ,
               (getTimeTaken() - start_time)

        );
               
    }
}