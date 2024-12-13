/*
 * Copyright (c) 2025 SAKSHAM JOSHI
 * All rights reserved.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 * @author- SAKSHAM JOSHI
 * @Linkedin- @sakshamjoshi27
 * @Twitter- @sakshamjoshi27
 * @email- social.sakshamjoshi@gmail.com
 */

#include "sron_compiler/_bytecode_generator_.hpp"

int main(int argc, char **argv)
{
    try
    {
        if (Support::HANDLE_CMD_ARGUMENTS(argc, argv)) return 0;

        Logs::SET_DIRECTORY_PATH();

        Logs::SET_EXECUTABLE_PATH();

        SemanticAnalyzer::LOAD_IN_BUILT_SET();

        #ifndef SRON_DEVELOPMENT_PHASE
            std::ios_base::sync_with_stdio(false);
            std::cout.tie(NULL);
        #endif

        ByteCodeGenerator::GENERATE();

        std::cout << "\n    =---> Time Taken : " << std::fixed << std::setprecision(5) << double(clock()) / double(CLOCKS_PER_SEC) << " seconds.\n";
    }
    catch (const ThrowException &excep)
    {
        unsigned long line_num = ULONG_MAX;

        if(excep._file_index != ULONG_MAX)
        {

            ByteCodeGenerator::SHOW_CODE_GLIMPSE(excep._file_index);

            line_num = ByteCodeGenerator::CALCULATE_LINE_NUMBER(excep._file_index);
        }
        
        DISPLAY_ERROR(excep._message.GET(), excep._excode, line_num);
    }
    catch(const FileNameNotProvidedToCompiler &excep)
    {
        DISPLAY_ERROR(excep.what(), FileNameNotSpecifiedException);
    }
    catch(const SourceCodeFileNotFound &excep)
    {
        DISPLAY_ERROR(excep.what(), FileNotFoundException);
    }
    catch (const std::bad_alloc &excep)
    {

        std::cerr<<"\n+================================+\n"
                     "|     System Out of Memory       |\n"
                     "+================================+\n";
    }
    catch (const std::exception &excep)
    {
        std::cerr << "\n | Error: " << excep.what() << '\n';

        DISPLAY_ERROR("compiling the source code. An Unexpected Error showed up. Mail the error on 'sron.language@gmail.com' with source code and above mentioned error", NoException);
    }

    return 0;
}