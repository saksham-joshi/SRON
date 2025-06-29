
#pragma once

#ifndef BYTECODE_H
#define BYTECODE_H

#include "headers/_lexical_analyzer_.hpp"


/* This namespace is used to create the bytecode.

 * It has function named as 'GENERATE' which takes a std::ifstream object
 * from Logs::mainfile, extracts the whole file content and starts tokenizing the
 * code and performs the semantic analysis, then creates the Sron Bytecode and
 * saves it in a .srb file.
 */
namespace ByteCodeGenerator
{

    inline static void SHOW_CODE_GLIMPSE(unsigned long __source_code_index)
    {
        unsigned short int token_count = 20;

        printf_s("\n--------------------------------\n");

        auto start_it = LexicalAnalyzer::fileStart;
        auto end_it = LexicalAnalyzer::fileStart + __source_code_index;

        if ((end_it - token_count) > LexicalAnalyzer::fileStart )
        {
            start_it = end_it - token_count;
        }
        
        while( start_it <= end_it )
        {
            printf_s("%c", *start_it);

            ++start_it;
        }

        // Now printing the characters after the current character position
        while ( token_count-- && (start_it < LexicalAnalyzer::fileEnd))
        {
            printf_s("%c", *start_it);

            ++start_it;
        }
    }

    inline static unsigned long CALCULATE_LINE_NUMBER(unsigned long __index_of_error)
    {
        return std::count(LexicalAnalyzer::fileStart, (LexicalAnalyzer::fileStart + __index_of_error), '\n') + 1;
    }

    // This function will generate the bytecode and uses all the function within this ByteCodeGenerator namespace.
    // To create the bytecode ...

    inline static void GENERATE()
    {
        LexicalAnalyzer::filecode = (std::string((std::istreambuf_iterator<char>(*Logs::mainfile)), (std::istreambuf_iterator<char>())));

        Logs::mainfile->close();

        delete Logs::mainfile;

        LexicalAnalyzer::iterator = LexicalAnalyzer::fileStart = LexicalAnalyzer::filecode.begin();

        LexicalAnalyzer::fileEnd = LexicalAnalyzer::filecode.end();

        LexicalAnalyzer::MOVE_ITERATOR_TO_WHERE_CODE_STARTS();

        LexicalAnalyzer::temp_string.reserve(64);

        LexicalAnalyzer::tokenVector.reserve(LexicalAnalyzer::filecode.size()/Logs::__ReserveOfTokenVector__);

        LexicalAnalyzer::TOKENIZER();

        printf_s("\n\n\t +---------------------------------+"
                   "\n\t<|| Compilation done successfully ||>"
                   "\n\t +---------------------------------+"
                   "\n");
    }

    inline static void LOAD_IN_BUILT_SET()
    {
        FILE* file = nullptr;

        fopen_s(&file , (Logs::executable_path + SRON_FUNCTION_LIB_FILE_PATH).c_str() , "rb" );

        if ( ! file )
        {
            if ( std::system( "start sron-FncList" ) != 0 )
            {
                throw ThrowException("loading the in built function set. Cannot find 'sron-FncList' executable which is required for compilation process. Reinstall SRON to fix this!", SronError::SourceCodeChangedError, false);
            }

            fopen_s(&file , (Logs::executable_path + SRON_FUNCTION_LIB_FILE_PATH).c_str() , "rb" );

            if ( ! file ) throw ThrowException("loading the in built function set. Source Code changed", SronError::SourceCodeChangedError);

        }

        struct IndexAndHash obj( 0 ,0 );

        while ( fread_s( &obj , sizeof(obj), sizeof(obj), 1, file) )
        {
            SemanticAnalyzer::inbuiltFncSet.insert(obj);
        }

        #ifdef SRON_DEBUG_MODE
            printf_s(" \n >>>> InBuilt Fnc Set Load Success!\n");
        #endif
    }
}

#endif