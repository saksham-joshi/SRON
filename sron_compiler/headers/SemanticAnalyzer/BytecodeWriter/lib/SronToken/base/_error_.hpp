#pragma once

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "_logs_.hpp"

#define CREATE_SRON_ERROR(     __name )  constexpr static const char*const __name##Error       =   #__name   "Error"

namespace SronError 
{
// used to display no reason and solution to the occured exception.

    CREATE_SRON_ERROR(  Default                           );
    CREATE_SRON_ERROR(  ByteCodeCannotbeSaved             );
    CREATE_SRON_ERROR(  BytecodeMetaNotValid              );
    CREATE_SRON_ERROR(  Compiler                          );
    CREATE_SRON_ERROR(  DatatypeConversion                );
    CREATE_SRON_ERROR(  DoubleOverflow                    );
    CREATE_SRON_ERROR(  DivisionByZero                    );
    CREATE_SRON_ERROR(  EmptyAttributeCode                );
    CREATE_SRON_ERROR(  FileNotFound                      );
    CREATE_SRON_ERROR(  FileNameNotSpecified              );
    CREATE_SRON_ERROR(  FunctionNotFound                  );
    CREATE_SRON_ERROR(  IntegerOverflow                   );
    CREATE_SRON_ERROR(  InvalidFunctionName               );
    CREATE_SRON_ERROR(  InvalidFunctionCallSyntax         );
    CREATE_SRON_ERROR(  InvalidForLoopSyntax              );
    CREATE_SRON_ERROR(  InvalidOBufferSyntax              );
    CREATE_SRON_ERROR(  InvalidRangeSyntax                );
    CREATE_SRON_ERROR(  InvalidVariableName               );
    CREATE_SRON_ERROR(  InvalidAttribute                  );
    CREATE_SRON_ERROR(  InvalidToken                      );
    CREATE_SRON_ERROR(  InvalidVariableSyntax             );
    CREATE_SRON_ERROR(  InvalidType                       );
    CREATE_SRON_ERROR(  InvalidScope                      );
    CREATE_SRON_ERROR(  InvalidArgsSyntax                 );
    CREATE_SRON_ERROR(  InvalidAttributeSyntax            );
    CREATE_SRON_ERROR(  MathBlockSyntax                   );
    CREATE_SRON_ERROR(  SourceCodeChanged                 );
    CREATE_SRON_ERROR(  ScopeBased                        );
    CREATE_SRON_ERROR(  TooLargeString                    );
    CREATE_SRON_ERROR(  TooLargeNumber                    );
    CREATE_SRON_ERROR(  TooMuchArgumentsInFunctionCall    );
    CREATE_SRON_ERROR(  TooMuchParametersInFunction       );
    CREATE_SRON_ERROR(  TypeConversion                    );
    CREATE_SRON_ERROR(  VariableExistAlready              );
    CREATE_SRON_ERROR(  VariableNotFound                  );
    CREATE_SRON_ERROR(  WrongSyntax                       );
    CREATE_SRON_ERROR(  IncorrectOsAttribute              );


    struct SourceCodeFileNotFound : public std::exception
    {
        inline virtual const char* what() const noexcept override
        {
            return "reading the file from specified path";
        }

    };

    struct FileNameNotProvidedToCompiler : public std::exception
    {
        inline virtual const char* what() const noexcept override
        {
            return "getting the file name";
        }
    };

    inline static void DISPLAY_ERROR(const char*const __during, const char*const __code, FilePos_t __line_number = MAXOF_UINT32)
    {
        #ifdef SRON_DEVELOPMENT_PHASE
            if ( __during == nullptr || __code == nullptr )
            {
                std::printf("\n ||> Received exception parameters are null pointers\n <||");
                return;
            }
        #endif
        
        std::printf(CLI_COLOR_BRIGHT_RED "\n--------------------------------\nError: %s\nIn '%s'", __code , Logs::filename.data());

        if (__line_number != MAXOF_UINT32)  std::printf(":\nAt Line %u:", __line_number);

        std::printf( "\n=>> While %s.\n    " CLI_DESIGN_RESET CLI_COLOR_CYAN, __during);

        if (std::strcmp(__code, SronError::DefaultError) != 0)
        {

            FILE* error_message_file = nullptr;

            SronSupport::safeOpenFile( &error_message_file , ( Logs::executable_path + SRON_ERROR_MESSAGE_FILE_PATH + __code + ".txt").c_str() , "r");

            if ( error_message_file )
            {
                char ch;

                FilePos_t count = 0;

                while ( count++ < 10000 && ( ch = std::fgetc( error_message_file )) != EOF ) std::putchar(ch);

                std::fclose(error_message_file);
            }

            else  std::printf ("\n+------------------------------------+\n"
                                 "|  Exception message file not found  |\n"
                                 "+------------------------------------+\n"
                  );
        
        }

        std::printf(CLI_DESIGN_RESET "\n\n    [|#| Read Documentations at " SRON_DOCS_LINK " |#|]\n");
    }

}

#endif