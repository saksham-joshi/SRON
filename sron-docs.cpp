#include<cstdlib>
#include<cstdio>
int main(){
    if(system("docs.html") != 0){
        printf("\n Cannot find link to the documentation. Can you reinstall SRON to refresh?");
        getchar();
    }
    return 0;
}