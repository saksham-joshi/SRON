/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 */

#pragma once

#ifndef EXCEPTION_H
#define EXCEPTION_H


#include "_logs_.hpp"

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

    inline static void DISPLAY_ERROR(const char*const __during, const char*const __code, unsigned long __line_number = ULONG_MAX)
    {
        #ifdef SRON_DEVELOPMENT_PHASE
            if ( __during == nullptr || __code == nullptr )
            {
                printf_s("\n ||> Received exception parameters are null pointers\n <||");
                return;
            }
        #endif
        
        printf_s("\n--------------------------------\nError: %s\nIn '%s'", __code , Logs::filename.data());

        if (__line_number != ULONG_MAX)  printf_s(":\nAt Line %u:", __line_number);

        printf_s( "\n=>> While %s.\n    ", __during);

        if (std::strcmp(__code, SronError::DefaultError) != 0)
        {

            FILE* error_message_file = nullptr;

            fopen_s( &error_message_file , ( Logs::executable_path + SRON_ERROR_MESSAGE_FILE_PATH + __code + ".txt").c_str() , "r");

            if ( error_message_file )
            {
                char ch;

                unsigned short int count = 0;

                while ( count++ < 10000 && ( ch = std::fgetc( error_message_file )) != EOF ) std::putchar(ch);

                std::fclose(error_message_file);
            }

            else  printf_s ("\n+------------------------------------+\n"
                              "|  Exception message file not found  |\n"
                              "+------------------------------------+\n"
                  );
        
        }

        printf_s("\n\n    [|#| Read Documentations at " SRON_DOCS_LINK " |#|]");
    }

}

#endif