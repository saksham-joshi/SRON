#include "headers/_bytecode_generator_.hpp"
#include "headers/_exception_.hpp"

int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    try
    {
        clock_t start, end;

        start = clock();

        std::ifstream code_file(argv[1]);

        if (code_file.fail())
        {
            if (argc == 1)
            {
                DISPLAY_EXCEPTION("getting the file name.", FileNameNotSpecifiedException);
            }
            throw std::exception();
        }

        Logs::filename = argv[1];

        Logs::mainfile = &code_file;

        ByteCodeGenerator::GENERATE();

        code_file.close();

        end = clock();

        std::cout <<std::setprecision(4)<< "\n\t=---> Time Taken : " << double(end - start) / double(CLOCKS_PER_SEC) << " seconds.\n";
    }
    catch (const std::exception&)
    {
        DISPLAY_EXCEPTION("reading the file from the specified path.", FileNotFoundException);
    }
    return 0;
}