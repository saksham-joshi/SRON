#include "headers/_bytecode_generator_.hpp"

int main(int argc, char **argv){

    try{
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

        ByteCodeGenerator::GENERATE(&code_file);

        code_file.close();
    }
    catch(const std::exception&){
        DISPLAY_EXCEPTION("reading the file from the specified path.",FileNotFoundException);
    }
}