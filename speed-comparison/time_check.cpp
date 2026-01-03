#include<iostream>
#include<string>
#include<ctime>

int main()
{
    auto start_time = clock();

    std::string str;

    for(unsigned i = 0 ; i < 100000; ++i)
    {
        str += std::to_string(i);
        str.push_back('\n');
    }

    puts(str.c_str());
    std::cout << "Time taken= " << clock() - start_time << "ms";
}