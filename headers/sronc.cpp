#include "headers/_bytecode_generator_.hpp"
#include "headers/_exception_.hpp"

int main(int argc, char **argv)
{
    // std::ios_base::sync_with_stdio(false);
    // std::cin.tie(NULL);
    
    try
    {
        clock_t start, end;

        start = clock();

        std::string filename(argv[1]);
        
        // checking if the extension of the file is .sron or not!
        if(!(filename.size() > 5 && Support::TO_LOWER(filename.substr(filename.size()-5)) == ".sron") ){
            std::cout<<"\n =| File Ending with extension .sron can only be compiled |= \n\n";
            exit(1);
        }

        std::ifstream code_file(filename);

        if (code_file.fail())
        {
            if (argc == 1)
            {
                DISPLAY_EXCEPTION("getting the file name.", FileNameNotSpecifiedException, false);
            }
            throw std::exception();
        }

        Logs::filename = filename;

        Logs::SET_DIRECTORY_PATH();

        Logs::mainfile = &code_file;

        ByteCodeGenerator::GENERATE();

        code_file.close();

        end = clock();

        std::cout <<std::setprecision(4)<< "\n\t=---> Time Taken : " << double(end - start) / double(CLOCKS_PER_SEC) << " seconds.\n";

    }
    catch (const std::exception&)
    {
        DISPLAY_EXCEPTION("reading the file from the specified path.", FileNotFoundException, false);
    }
    
    return 0;
}