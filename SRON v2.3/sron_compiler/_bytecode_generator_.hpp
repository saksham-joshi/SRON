
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

    inline static void SHOW_CODE_GLIMPSE(FilePos_t __source_code_index)
    {
        unsigned short int token_count = 20;

        std::printf("\n--------------------------------\n");

        auto start_it = LexicalAnalyzer::fileStart;
        auto end_it = LexicalAnalyzer::fileStart + __source_code_index;

        if ((end_it - token_count) > LexicalAnalyzer::fileStart )
        {
            start_it = end_it - token_count;
        }
        
        while( start_it <= end_it )
        {
            std::printf("%c", *start_it);

            ++start_it;
        }

        // Now printing the characters after the current character position
        while ( token_count-- && (start_it < LexicalAnalyzer::fileEnd))
        {
            std::printf("%c", *start_it);

            ++start_it;
        }
    }

    inline static unsigned int CALCULATE_LINE_NUMBER(FilePos_t __index_of_error)
    {
        auto start = LexicalAnalyzer::fileStart;
        auto target_point = start + __index_of_error;

        unsigned int line_num = 1;

        for(; start != target_point; ++start ) if ( *start == '\n') ++line_num;

        return line_num;
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

        std::printf( CLI_DESIGN_BOLD  CLI_COLOR_BLUE  "\n\n\t +---------------------------------+"
                                                      "\n\t<|| Compilation done successfully ||>"
                                                      "\n\t +---------------------------------+"
                                                      "\n" CLI_DESIGN_RESET);
    }

    inline static void LOAD_IN_BUILT_SET()
    {
        FILE* file = nullptr;

        auto fnlist_file = Logs::executable_path + SRON_FUNCTION_LIB_FILE_PATH;

        SronSupport::safeOpenFile(&file , fnlist_file.c_str() , "rb" );

        if ( ! file )
        {
            auto fnlist_generator = "\"" + Logs::executable_path + "sron-FncList" + "\"";

            if (std::system(fnlist_generator.c_str()) != 0)
            {
                throw ThrowException("loading the in built function set. Cannot find 'sron-FncList' executable which is required for compilation process. Reinstall SRON to fix this!", SronError::SourceCodeChangedError, false);
            }

            SronSupport::safeOpenFile(&file , fnlist_file.c_str() , "rb" );

            if ( ! file ) throw ThrowException("loading the in built function set. Source Code changed", SronError::SourceCodeChangedError);

        }

        struct IndexAndHash obj( 0 ,0 );

        while ( std::fread( &obj , sizeof(obj), 1, file) )
        {
            SemanticAnalyzer::inbuiltFncSet.insert(obj);
        }

        #ifdef SRON_DEBUG_MODE
            std::printf(" \n >>>> InBuilt Fnc Set Load Success!\n");
        #endif
    }
}

#endif