/*
 * Copyright (c) 2024 SAKSHAM JOSHI
 * All rights reserved.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * You can freely redistribute it but cannot modify the source code without the permission from the author.
 */
#ifndef EXCEPTION_H
#define EXCEPTION_H

#pragma once

#include "logs/_logs_.hpp"

namespace SronException 
{
    // The exception below which be used to extract files from the Exception directory and display
    CREATE_SRON_EXCEPTION(   Default                   );
    CREATE_SRON_EXCEPTION(   Argument                  );
    CREATE_SRON_EXCEPTION(   BytecodeNotFound          );
    CREATE_SRON_EXCEPTION(   DatatypeConversion        );
    CREATE_SRON_EXCEPTION(   DivisionByZero            );
    CREATE_SRON_EXCEPTION(   FileNotFound              );
    CREATE_SRON_EXCEPTION(   FunctionNotFound          );
    CREATE_SRON_EXCEPTION(   IndexNotWithinRange       );
    CREATE_SRON_EXCEPTION(   InputType                 );
    CREATE_SRON_EXCEPTION(   Insertion                 );
    CREATE_SRON_EXCEPTION(   InvalidByteCode           );
    CREATE_SRON_EXCEPTION(   InvalidFlag               );
    CREATE_SRON_EXCEPTION(   InvalidObjectExtraction   );
    CREATE_SRON_EXCEPTION(   InvalidType               );
    CREATE_SRON_EXCEPTION(   MathEvaluation            );
    CREATE_SRON_EXCEPTION(   NullAccessing             );
    CREATE_SRON_EXCEPTION(   SourceCodeChanged         );
    CREATE_SRON_EXCEPTION(   TypeConversion            );
    CREATE_SRON_EXCEPTION(   Unknown                   );
    CREATE_SRON_EXCEPTION(   VariableNotFound          );



    struct NullPointerException : public std::exception
    {
        
        inline virtual const char* what() const noexcept{
            return "accessing the non-ownable memory. [Issue of Compiler & Interpreter]";
        }
    };


    inline static void LOAD_FILE_AND_PRINT(const char*const& __code)
    {
        // now adding the directory path with with the path to exception....
        FILE* error_message_file = nullptr;

        fopen_s(&error_message_file , (Logs::GET_EXECUTABLE_PATH() + SRON_EXCEPTION_MESSAGE_FILE_PATH + __code + ".txt").c_str() , "r" );

        if ( error_message_file ) [[likely]]
        {
            /* 
            * Not using buffer because it may bring a vulnerability that if 
            * someone rewrote the message file with a lot of data then std::bad_allloc
            * will be caught by main function and if the memory is available
            * then it will take a lot of time to print that much content.
            */
            char ch;

            unsigned int count = 0;

            while( count++ < 10000 && (ch = fgetc(error_message_file) ) != EOF ) std::putchar(ch);

            std::fclose(error_message_file);
        }

        else  printf_s(
            "\n"
            "+------------------------------------+\n"
            "|  Exception message file not found  |\n"
            "+------------------------------------+\n"
        );
    }

    inline static void DISPLAY_EXCEPTION(const char *const __during, const char *const __code , const char*const __filename )
    {
        printf_s("\n--------------------------------\nIn '%s'\n", __filename );

        if(std::strcmp(__code, SronException::DefaultException) != 0)
        {
            printf_s("%s caught:\n", __code);
        }

        printf_s( "||>> While %s.\n    ", __during );

        if (std::strcmp(__code, SronException::DefaultException) == 0)
            return;

        LOAD_FILE_AND_PRINT(__code);

        printf_s("\n\n   [|#| Read Documentations at " SRON_DOCS_LINK " |#|]");
    }
}


#endif