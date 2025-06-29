
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

    inline static void SHOW_CODE_GLIMPSE(unsigned long __source_code_index){
        
        auto iterator = LexicalAnalyzer::fileStart + __source_code_index;
        
        int __tokenCount = 20;

        std::cerr << "\n--------------------------------\n";

        if ((iterator - __tokenCount) <= LexicalAnalyzer::fileStart)
        {
            
            while (LexicalAnalyzer::fileStart++ <= iterator)
            {
                std::cerr << *LexicalAnalyzer::fileStart;
            }
        }
        else
        {

            auto it = iterator - __tokenCount;

            while (it <= iterator)
            {
                //if(*it == '\n') break;
                std::cerr << *it;
                ++it;
            }
        }

        // Now printing the characters after the current character position
        while (--__tokenCount && (++iterator < LexicalAnalyzer::fileEnd))
        {
            //if(*iterator == '\n') break;
            std::cerr << *iterator;

            ++iterator;
        }
    }

    inline static unsigned long CALCULATE_LINE_NUMBER(unsigned long __index_of_error){

        return std::count(LexicalAnalyzer::fileStart, (LexicalAnalyzer::fileStart + __index_of_error), '\n') + 1;

    }

    // This function will generate the bytecode and uses all the function within this ByteCodeGenerator namespace.
    // To create the bytecode ...

    inline static void GENERATE()
    {
        LexicalAnalyzer::filecode = (std::string((std::istreambuf_iterator<char>(Logs::mainfile)), (std::istreambuf_iterator<char>())));

        Logs::mainfile.close();

        LexicalAnalyzer::iterator = LexicalAnalyzer::fileStart = LexicalAnalyzer::filecode.begin();

        LexicalAnalyzer::fileEnd = LexicalAnalyzer::filecode.end();

        LexicalAnalyzer::MOVE_ITERATOR_TO_WHERE_CODE_STARTS();

        LexicalAnalyzer::temp_string.reserve(64);

        LexicalAnalyzer::tokenVector.reserve(LexicalAnalyzer::filecode.size()/Logs::__ReserveOfTokenVector__);

        LexicalAnalyzer::TOKENIZER();

        std::cout << "\n\n\t +---------------------------------+\n\t<|| Compilation done successfully ||>\n\t +---------------------------------+\n";
    }
}

#endif