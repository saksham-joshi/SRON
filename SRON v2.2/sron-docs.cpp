#include <cstdlib>
#include <cstdio>
int main()
{
    if (system("start https://sron.gitbook.io") != 0)
    {
        printf("\n =| Cannot find link to the documentation. Reinstall SRON to fix this?");
        
    }
    return 0;
}