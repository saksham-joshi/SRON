#ifndef EXCEPTION_H
#define EXCEPTION_H

#pragma once

#include "logs/_logs_.hpp"

#define CREATE_SRON_EXCEPTION( __name )  constexpr static const char*const __name##Exception   =   #__name   "Exception"

namespace SronException 
{
    // The exception below which be used to extract files from the Exception directory and display
    CREATE_SRON_EXCEPTION(   Default                   );
    CREATE_SRON_EXCEPTION(   Argument                  );
    CREATE_SRON_EXCEPTION(   BytecodeNotFound          );
    CREATE_SRON_EXCEPTION(   DatatypeConversion        );
    CREATE_SRON_EXCEPTION(   DivisionByZero            );
    CREATE_SRON_EXCEPTION(   FileNotFound              );
    CREATE_SRON_EXCEPTION(   FileReader                );
    CREATE_SRON_EXCEPTION(   FileWriter                );
    CREATE_SRON_EXCEPTION(   FunctionNotFound          );
    CREATE_SRON_EXCEPTION(   ImplicitConversion        );
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
    CREATE_SRON_EXCEPTION(   CallStackOverflow         );
    CREATE_SRON_EXCEPTION(   TypeConversion            );
    CREATE_SRON_EXCEPTION(   Unknown                   );
    CREATE_SRON_EXCEPTION(   VariableNotFound          );



    struct NullPointerException : public std::exception
    {
        inline virtual const char* what() const noexcept
        {
            return "accessing the non-ownable memory. [Issue of Compiler & Interpreter]";
        }
    };

    struct UserWantsExit
    {
        int _exit_code;

        inline UserWantsExit(int __exit_code) : _exit_code(__exit_code) { }
    };


    inline static void loadFileAndPrint(const char*const& __code)
    {
        std::printf(CLI_COLOR_CYAN);
        
        // now adding the directory path with with the path to exception....
        FILE* error_message_file = nullptr;

        SronSupport::safeOpenFile(&error_message_file , (SronSupport::getExecutablePath() + SRON_EXCEPTION_MESSAGE_FILE_PATH + __code + ".txt").c_str() , "r" );

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

        else  std::printf(
            "\n"
            "+------------------------------------+\n"
            "|  Exception message file not found  |\n"
            "+------------------------------------+\n"
        );

        std::printf(CLI_DESIGN_RESET);
    }

    inline static void displayException(const char *const __during, const char *const __code , const char*const __filename )
    {
        std::printf(CLI_COLOR_BRIGHT_RED);

        std::printf("\n--------------------------------\nIn '%s'\n", __filename );

        if(! SronSupport::compareString(__code, SronException::DefaultException) )
        {
            std::printf("%s caught:\n", __code);
        }

        std::printf("||>> While %s.\n    " CLI_DESIGN_RESET, __during );

        if (SronSupport::compareString(__code, SronException::DefaultException))
            return;

        loadFileAndPrint(__code);

        std::printf("\n\n   [|#| Read Documentations at " SRON_DOCS_LINK " |#|]\n");
    }

    struct ExceptionThrowByUser 
    {
        private :
            std::string _excep;

        public :
            inline ExceptionThrowByUser(const std::string& __excep) : _excep(__excep) { }

            inline void print() const
            {
                std::printf("%s caught:\n    ", this->_excep.c_str());

                SronException::loadFileAndPrint(this->_excep.c_str());
            }
    };
}


#endif