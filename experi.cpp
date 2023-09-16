#include <iostream>
#include <cstring>
#include<map>
#include<vector>

using namespace std;

int main()
{
    vector<map<string,int>> mp;
    mp["val"] = 10;
    cout<<mp.at("val") ;
}