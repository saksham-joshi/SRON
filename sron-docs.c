#include<stdio.h>
#include<stdlib.h>

#ifdef _WIN64 
    #define CMD "start"
    #define EXTRA ""
#elif defined(__linux__)
    #define CMD "xdg-open"
    #define EXTRA " 2> /dev/null"
#else
    #error Cannot detect the current operating system
#endif

int main ( void )
{
    if (system(CMD " https://sron.gitbook.io" EXTRA) != 0)
    {
        printf("\n =| Cannot find link to the documentation. Reinstall SRON to fix this?\n");
        
    }
    return 0;
}