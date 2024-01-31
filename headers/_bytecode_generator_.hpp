#include "_support_.hpp"
#include "_user_fnc_.hpp"
#include <stack>

#ifndef BYTECODE_H
#define BYTECODE_H

/* This namespace is used to create the bytecode.
 * It has function named as 'GENERATE' which takes a character array 'filename' as parameter,
 * read the file and save its content to a .srb file.
 */
namespace ByteCodeGenerator
{
    // contains the full bytecode to be saved on .srb file
    std::string bytecode;

    // contains the content from the file.
    std::string filecode;

    // contains the content which is required to temporarily store data.
    std::string temp_string;

    // contains the iterator for the filecode.
    std::string::iterator iterator;

    // contains the record of scopes.
    std::stack<char> scope_stack;

    inline static void EXTRACT_CHAR();
    inline static void EXTRACT_IDENTIFIER();
    inline static void EXTRACT_LIST();
    inline static void EXTRACT_STRING();
    inline static void EXTRACT_NUMBER();

    inline static void FILE_WRITE();
    inline static void GENERATE(std::ifstream*);

    inline static void HANDLE_SCOPES();

    inline static void JUMP_SPACE_AND_NEWLINE();
    inline static void JUMP_TILL_CHAR_REPEATS(char);
    inline static void JUMP_TO_NEXT_FIRST_OCCURENCE(char);

    inline static void TOKENIZER();

    /*
     * Implementation of above functions starts from here !
     */

    inline static void EXTRACT_CHAR()
    {
        ++iterator;

        if (*iterator == '\\')
        {
            switch (*(iterator + 1))
            {
            case '\\':
                temp_string += '\\';
                break;
            case 'n':
                temp_string += '\n';
                break;
            case 't':
                temp_string += '\t';
                break;
            case '\'':
                temp_string += '\'';
                break;
            case '"':
                temp_string += '"';
                break;
            default:
                DISPLAY_EXCEPTION("extracting the value of 'Char' type.", InvalidValueException);
            }
            iterator += 2;
        }
        else
        {
            temp_string += *iterator;
            ++iterator;
        }
        if (*iterator != '\'')
        {
            DISPLAY_EXCEPTION("extracting the value of 'Char' type.", InvalidValueException);
        }
    }

    inline static void EXTRACT_IDENTIFIER()
    {
        temp_string += *iterator;
        while (iterator++ < filecode.end() && (is_alpha_number(*iterator)))
        {
            temp_string += *iterator;
        }
    }

    inline static void EXTRACT_NUMBER()
    {
        temp_string += *iterator;
        while (iterator++ < filecode.end() && (is_number(*iterator) || *iterator == '.'))
        {
            temp_string += *iterator;
        }
    }

    inline static void EXTRACT_STRING()
    {
        ++iterator;
        while (iterator < filecode.end() && *iterator != '"')
        {
            if (*iterator == '\\')
            {
                switch (*(iterator + 1))
                {
                case 'n':
                    temp_string += '\n';
                    break;
                case 't':
                    temp_string += '\t';
                    break;
                case '"':
                    temp_string += '"';
                    break;
                default:
                    temp_string += '\\';
                    break;
                }
                iterator += 2;
                continue;
            }
            temp_string += *iterator;
            ++iterator;
        }
    }

    inline static void FILE_WRITE()
    {
        try{
        std::string temp = std::string(Logs::filename);
        //std::ofstream outfile(temp.substr(0, temp.find_last_of('.')) + ".srb");
        std::ofstream outfile("SampleCodes/factorial.srb");

        outfile.write(filecode.c_str(), filecode.size());

        outfile.close();
        }
        catch(const std::exception&){
            printf("\n\n\t|> Something going wrong !");
        }
    }
    inline static void JUMP_SPACE_AND_NEWLINE()
    {
        while ((*iterator == ' ' || *iterator == '\n') && iterator++ < filecode.end())
        {
        }
    }
    inline static void JUMP_TILL_CHAR_REPEATS(char ch)
    {
        while (*iterator == ch && iterator++ < filecode.end())
        {
        }
    }

    inline static void JUMP_TO_NEXT_FIRST_OCCURENCE(char ch)
    {
        while (*iterator != ch && iterator++ < filecode.end())
        {
        }
    }

    inline static void GENERATE(std::ifstream *inputfile)
    {
        try
        {
            // reading the whole content of the file.
            ByteCodeGenerator::filecode = std::string(std::istreambuf_iterator<char>(*inputfile), (std::istreambuf_iterator<char>()));

            // assigning the iterator at the beginning of the file
            ByteCodeGenerator::iterator = filecode.begin();

            // Jumping to the first occurrence of the Open braces.
            ByteCodeGenerator::JUMP_TO_NEXT_FIRST_OCCURENCE('{');

            // actual compilation starts from here.
            ByteCodeGenerator::TOKENIZER();
            
            // Saving bytecode to the .srb file !
            ByteCodeGenerator::FILE_WRITE();

            printf("\n\t +---------------------------------+\n\t<|| Compilation done successfully ||>\n\t +---------------------------------+\n\n");
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("creating bytecode and analyzing the source code.", SystemOutofMemoryException);
        }
    }

    inline static void TOKENIZER(){

        for(; iterator < filecode.end() ; ++iterator){
            if(*iterator == ' '){
                continue;
            }
            else if(*iterator == '"'){
                ByteCodeGenerator::EXTRACT_STRING();
            }
            else if(*iterator == '\''){
                ByteCodeGenerator::EXTRACT_CHAR();
            }
            else if(*iterator == '['){
                ByteCodeGenerator::EXTRACT_LIST();
            }
            else if(Support::is_alphabet(*iterator) || *iterator =='_' ){
                ByteCodeGenerator::EXTRACT_IDENTIFIER();
            }
            else if(Support::is_number(*iterator) || *iterator == '-' || *iterator == '.'){
                ByteCodeGenerator::EXTRACT_NUMBER();
            }
            else if(*iterator == '{' || *iterator == '}'){
                ByteCodeGenerator::HANDLE_SCOPES();
            }
            else if(Support::IS_OPERATOR(*iterator)){
                temp_string+=*iterator;
            }
            else{
                DISPLAY_EXCEPTION("tokenizing and analyzing the code. Found this Token '"+*iterator+(std::string)"'." ,InvalidTokenException);
            }
        }
    }
}
#endif