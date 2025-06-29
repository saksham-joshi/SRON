//#define SRON_DEVELOPMENT_PHASE

#include "sron_compiler/_bytecode_generator_.hpp"

int main(int argc, char **argv)
{
    try
    {
        Logs::SET_DIRECTORY_PATH();

        Logs::SET_EXECUTABLE_PATH();

        if (Support::HANDLE_CMD_ARGUMENTS(argc, argv)) return 0;

        ByteCodeGenerator::LOAD_IN_BUILT_SET();

        ByteCodeGenerator::GENERATE();

        printf_s("\n    =---> Time Taken : %.5lf seconds.\n", double(clock()) / double(CLOCKS_PER_SEC) );
    }
    catch (const ThrowException &excep)
    {
        unsigned long line_num = ULONG_MAX;

        if(excep._file_index != ULONG_MAX)
        {

            ByteCodeGenerator::SHOW_CODE_GLIMPSE(excep._file_index);

            line_num = ByteCodeGenerator::CALCULATE_LINE_NUMBER(excep._file_index);
        }
        
        SronError::DISPLAY_ERROR(excep._message.c_str(), excep._excode, line_num);

        return 1;
    }
    catch(const SronError::FileNameNotProvidedToCompiler& excep)
    {
        SronError::DISPLAY_ERROR(excep.what(), SronError::FileNameNotSpecifiedError);

        return 1;
    }
    catch(const SronError::SourceCodeFileNotFound& excep)
    {
        SronError::DISPLAY_ERROR(excep.what(), SronError::FileNotFoundError);

        return 1;
    }
    catch (const std::bad_alloc &excep)
    {
        printf_s  (
                   "\n+================================+\n"
                     "|     System Out of Memory       |\n"
                     "+================================+\n"
                  );

        return 1;
    }
    catch (const std::exception &excep)
    {
        printf_s( "\n | Error: %s\n", excep.what());

        SronError::DISPLAY_ERROR("compiling the source code. An Unexpected Error showed up. Mail the error on 'sron.language@gmail.com' with source code and above mentioned error", SronError::DefaultError);
        
        return 1;
    }

    return 0;
}