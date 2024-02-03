#include "headers/_bytecode_generator_.hpp"

int main(int argc, char **argv){

    try{
        std::ifstream code_file(argv[1]);
        clock_t start,end;
        start = clock();
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

        printf("\n\t=---> Time Taken: %lf .\n",double(end-start)/double(CLOCKS_PER_SEC));
    }
    catch(const std::exception&){
        DISPLAY_EXCEPTION("reading the file from the specified path.",FileNotFoundException);
    }
}