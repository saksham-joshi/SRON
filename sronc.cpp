#include "sron_compiler/_bytecode_generator_.hpp"

int main(int argc, char **argv)
{
    try
    {
        std::string filename;

        Logs::SET_EXECUTABLE_PATH();

        if (argc > 1)
        {

            // checking if the terminal is passed with --version parameter: sronc --version
            if (argv[1] == Logs::version_string)
            {
                Support::DISPLAY_VERSION();
                return 0;
            }

            filename = std::string(argv[1]);
        }
        else
        {
            throw std::exception();
        }

        // checking if the extension of the file is .sron or not!
        if (!(filename.size() > 5 && Support::TO_LOWER(filename.substr(filename.size() - 5)) == ".sron"))
        {
            std::cout << "\n =| Only files with extension '.sron'  can be compiled!! |= \n\n";
            exit(1);
        }

        std::ifstream code_file(filename);

        if (code_file.fail())
        {

            if (argc == 1)
            {
                throw std::exception();
            }
            DISPLAY_EXCEPTION("reading the file from the specified path.", FileNotFoundException, false);
        }

        Logs::filename = filename;

        Logs::SET_DIRECTORY_PATH();

        Logs::mainfile = &code_file;

        ByteCodeGenerator::GENERATE();

        std::cout << "\n\t=---> Time Taken : " << double(clock()) / double(CLOCKS_PER_SEC) << " seconds.\n";
    }
    catch (const std::exception &)
    {
        DISPLAY_EXCEPTION("getting the file name.", FileNameNotSpecifiedException, false);
    }

    return 0;
}