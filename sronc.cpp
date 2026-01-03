// #define SRON_DEVELOPMENT_PHASE

#include "sron_compiler/_bytecode_generator_.hpp"

int EXIT_CODE__ = 0;

int main(int argc, char **argv)
{
    try
    {
        #ifdef _WIN64 
            SetConsoleOutputCP(CP_UTF8);
            SetConsoleCP(CP_UTF8);
        #endif

        Logs::SET_DIRECTORY_PATH();

        Logs::executable_path = SronSupport::getExecutablePath();

        if (Support::HANDLE_CMD_ARGUMENTS(argc, argv)) return 0;

        ByteCodeGenerator::LOAD_IN_BUILT_SET();

        ByteCodeGenerator::GENERATE();

        std::printf("\n    =---> Time Taken : %llu ms.\n", SronSupport::getExecTime(SronSupport::getCurTime(), SronSupport::CODE_START_TIME));
    }
    catch (const ThrowException &excep)
    {
        auto line_num = ThrowException::_DEFAULT_FILE_INDEX;

        if(excep._file_index != line_num)
        {

            ByteCodeGenerator::SHOW_CODE_GLIMPSE(excep._file_index);

            line_num = ByteCodeGenerator::CALCULATE_LINE_NUMBER(excep._file_index);
        }
        
        SronError::DISPLAY_ERROR(excep._message.c_str(), excep._excode, line_num);

        EXIT_CODE__ = 1;
    }
    catch(const SronError::FileNameNotProvidedToCompiler& excep)
    {
        SronError::DISPLAY_ERROR(excep.what(), SronError::FileNameNotSpecifiedError);

        EXIT_CODE__ = 1;
    }
    catch(const SronError::SourceCodeFileNotFound& excep)
    {
        SronError::DISPLAY_ERROR(excep.what(), SronError::FileNotFoundError);

        EXIT_CODE__ = 1;
    }
    catch (const std::bad_alloc &excep)
    {
        std::printf  ( CLI_COLOR_RED CLI_DESIGN_BOLD
                   "\n+================================+\n"
                     "|     System Out of Memory       |\n"
                     "+================================+\n" CLI_DESIGN_RESET
                  );

        EXIT_CODE__ = 1;
    }
    catch (const std::exception &excep)
    {
        std::printf( "\n | Error: %s\n", excep.what());

        SronError::DISPLAY_ERROR("compiling the source code. An Unexpected Error showed up. Report this error on '" SRON_GITHUB_REPO "' with source code and above mentioned error", SronError::DefaultError);
        
        EXIT_CODE__ = 1;
    }

    #ifdef __linux__
        putchar('\n');  // linux terminal doesn't put newline in the end of the program
    #endif

    return EXIT_CODE__;
}