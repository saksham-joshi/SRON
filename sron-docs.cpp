#include <cstdlib>
#include <cstdio>
int main()
{
    if (system("start https://sron.gitbook.io/docs") != 0)
    {
        printf("\n Cannot find link to the documentation. Can you reinstall SRON to refresh?");
    }
    return 0;
}