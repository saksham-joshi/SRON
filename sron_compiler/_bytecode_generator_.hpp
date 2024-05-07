#ifndef BYTECODE_H
#define BYTECODE_H

#include <queue>
#include "headers/_bytecode_writer_.hpp"

/* This namespace is used to create the bytecode.

 * It has function named as 'GENERATE' which takes a std::ifstream pointer object
 * from Logs::mainfile, extracts the whole file content and starts tokenizing the
 * code and performs the semantic analysis, then creates the Sron Bytecode and
 * saves it in a .srb file.
 */
namespace ByteCodeGenerator
{
    // contains the content from the file.
    std::string filecode;

    // contains the content which is required to temporarily store data.
    std::string temp_string;

    // contains the iterator for the filecode.
    std::string::iterator iterator;

    // contains the record of scopes.
    std::stack<char> scope_stack;

    // contains the tokens
    std::vector<SronToken> token_vector;

    // an iterator to iterate over a vector of SronToken
    std::vector<SronToken>::iterator vecit;

    static bool inside_math_expression = false;

    inline static void CHECK_IF_OPERATOR_IS_INSIDE_MATH_BLOCK();

    inline static void EXTRACT_CHAR();
    inline static void EXTRACT_IDENTIFIER();
    inline static void EXTRACT_STRING();

    inline static bool EXTRACT_NUMBER();

    inline static void GENERATE();

    inline static SronToken *GET_LAST_TOKEN_REFERENCE();

    inline static void HANDLE_SCOPES();

    inline static void JUMP_TO_NEXT_FIRST_OCCURENCE(char);

    inline static void POSTFIX();

    inline static void TOKENIZER();
    inline static void TOKEN_VECTOR_REFINER();


    // This function will generate the bytecode and uses all the function within this ByteCodeGenerator namespace.
    // To create the bytecode..
    // Step 1 : Read the file and store its address to 'Logs::mainfile'.
    // Step 2 : Call ByteCodeGenerator::GENERATE();
    inline static void GENERATE()
    {
        try
        {
            // reading the whole content of the file.
            ByteCodeGenerator::filecode = std::string(std::istreambuf_iterator<char>(*Logs::mainfile), (std::istreambuf_iterator<char>()));

            Logs::mainfile->close();
            Logs::mainfile->~ios_base();

            // assigning the iterator at the beginning of the file
            ByteCodeGenerator::iterator = filecode.begin();

            // Jumping to the first occurrence of the Open braces.
            ByteCodeGenerator::JUMP_TO_NEXT_FIRST_OCCURENCE('{');

            // actual compilation starts from here.
            ByteCodeGenerator::TOKENIZER();

            Logs::line_number = 1;

            // clearing the temp_string
            ByteCodeGenerator::temp_string.~basic_string();

            // clearing the filecode to free up memory.
            ByteCodeGenerator::filecode.~basic_string();

            // removing the comments and unnecessary newlines
            ByteCodeGenerator::TOKEN_VECTOR_REFINER();

            // This function will convert the mathematical expression in the token vector to the postfix expression.
            ByteCodeGenerator::POSTFIX();

            // creating the bytecode using token_vector.
            ByteCodeWriter::WRITE(token_vector);

            ByteCodeGenerator::token_vector.~vector();

            std::cout << "\n\t +---------------------------------+\n\t<|| Compilation done successfully ||>\n\t +---------------------------------+\n";
        }
        catch (const std::exception &)
        {

            DISPLAY_EXCEPTION("creating bytecode and analyzing the source code.", SystemOutofMemoryException);
        }
    }
}
#endif