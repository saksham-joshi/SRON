#include "_support_.hpp"
#include "_user_fnc_.hpp"
#include <stack>
#include "_flags_.hpp"

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

    // contains the tokens
    std::vector<std::string> token_vector;

    inline static void EXTRACT_CHAR();
    inline static void EXTRACT_IDENTIFIER();
    inline static void EXTRACT_STRING();
    inline static void EXTRACT_NUMBER();

    inline static void FILE_WRITE();
    inline static void GENERATE(std::ifstream *);

    inline static void HANDLE_SCOPES();

    inline static void JUMP_SPACE_AND_NEWLINE();
    inline static void JUMP_TILL_CHAR_REPEATS(char);
    inline static void JUMP_TO_NEXT_FIRST_OCCURENCE(char);

    inline static void TOKENIZER();

    /*
     * Implementation of above forward declared functions starts from here !
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
        try
        {
            std::string temp = std::string(Logs::filename);
            temp = temp.substr(0, temp.find_last_of('.')) + ".srb";
            std::ofstream outfile(temp);
    
            if (outfile.is_open())
            {
                outfile.write(filecode.c_str(), filecode.size());
                outfile.close();
            }
            else
            {
                DISPLAY_EXCEPTION("saving the bytecode to '" + temp + "'.", ByteCodeCannotbeSavedException);
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("saving the bytecode.", SystemOutofMemoryException);
        }
    }

    /*
     * This function is used to handle scopes.
     * NOTE : the if statement written within the case of ']' works like this :
     * the ascii of '[' is 91, ']' is 93, '{' is 123 and '}' is 125.
     * So, that statement converts the charcter to int and then subtract it by 2.
     * In case of '()', the ascii of '(' is 40 and ')' is 41.
     * Therefore, it is made in a different case. 
    */
    inline static void HANDLE_SCOPES()
    {
        try
        {
            switch (*iterator)
            {

            case '{':
            case '[':
            case '(':
                scope_stack.push(*iterator); 
                break;
            case '}':
            case ']':
                if (!scope_stack.empty() && (scope_stack.top() == (char)(((int)*iterator) - 2)))
                {
                    scope_stack.pop();
                }
                else
                {
                    throw std::exception();
                }
                break;
            case ')':
                if (!scope_stack.empty() && scope_stack.top() == '(')
                {
                    scope_stack.pop();
                }
                else
                {
                    throw std::exception();
                }
                break;
            default :
            DISPLAY_EXCEPTION("generating bytecode and handling scopes.",NoException);
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("generating bytecode and handling scopes.", InvalidScopeException);
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

            for(const auto& i : token_vector){
                printf("%s | ", i.c_str());
            }

            // Saving bytecode to the .srb file !
            //ByteCodeGenerator::FILE_WRITE();

            printf("\n\t +---------------------------------+\n\t<|| Compilation done successfully ||>\n\t +---------------------------------+\n\n");
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("creating bytecode and analyzing the source code.", SystemOutofMemoryException);
        }
    }

    inline static void TOKENIZER()
    {

        for (; iterator < filecode.end(); ++iterator)
        {
            if (*iterator == ' ')
            {
                continue;
            }
            else if (*iterator == '"')
            {
                ByteCodeGenerator::EXTRACT_STRING();
            }
            else if (*iterator == '\'')
            {
                ByteCodeGenerator::EXTRACT_CHAR();
            }
            else if (Support::is_alphabet(*iterator) || *iterator == '_')
            {
                ByteCodeGenerator::EXTRACT_IDENTIFIER();
                --iterator;
            }
            else if (Support::is_number(*iterator) || *iterator == '-' || *iterator == '.')
            {
                ByteCodeGenerator::EXTRACT_NUMBER();
                --iterator;
            }
            else if (*iterator == '{' || *iterator == '}' || *iterator == '[' || *iterator == ']' || *iterator == '(' || *iterator == ')' )
            {
                
                ByteCodeGenerator::HANDLE_SCOPES();
                temp_string+=*iterator;
            }
            else if (Support::IS_OPERATOR(*iterator) || *iterator == '\n')
            {
                temp_string += *iterator;

            }
            else
            {
                DISPLAY_EXCEPTION("tokenizing the code. Found this Token '" + *iterator + (std::string) "'.", InvalidTokenException);
            }
            token_vector.push_back(temp_string);
            temp_string = "";
        }

        if(!scope_stack.empty()){
            DISPLAY_EXCEPTION("tokenizing the code.",InvalidScopeException);
        }

        
    }
}
#endif