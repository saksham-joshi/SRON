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

    inline static void ANALYZER();

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

    // This function will find the string in the vector
    // If the string is not found, it will push it into the vector
    // otherwise will throw an exception 
    inline static void FIND_AND_PUSH(std::vector<std::string> *vec, std::string& str){
        for(auto& i : *vec){
            if(i == str){
                DISPLAY_EXCEPTION("analyzing the code. You are redeclaring identifier(function or variable name).",NoException);
            }
        }
        vec->push_back(str);
    }
    /*
     * This function will analyze the code and find the syntax errors
     * This function will be called after tokenization.
     */
    inline static void ANALYZER()
    {
        try
        {
            std::vector<std::string> identifier_vector; // it contains the identifiers in a current function
            std::vector<std::string> function_vector; // it contains the name of the function
            
            auto iterator = token_vector.begin();

            auto INLINE_ITERATE_AND_DELETE =[] (std::vector<std::string>::iterator iterator){
                auto temp = iterator;
                        iterator+=2;
                        while(iterator++ < ByteCodeGenerator::token_vector.end() && !Support::IS_VALID_END(*iterator) ){
                        }
                        ByteCodeGenerator::token_vector.erase(temp,iterator);
            };

            
            for (; iterator < token_vector.end(); ++iterator)
            {
                if(Support::IS_CURLY_BRACES(*iterator)){
                    continue;
                }
                else if(Support::IS_INBUILT_ATTRIBUTE(*iterator)){
                    //  name : function
                    if(*iterator == AttributeName && *(iterator+1) == ":" && Support::CHECK_VALID_IDENTIFIER_NAME(*(iterator+2)) && Support::IS_VALID_END(*(iterator+4) ) ){
                        FIND_AND_PUSH(&function_vector,*(iterator+2));
                        iterator+=4;
                        continue;
                    }
                    else if(*iterator == AttributeComment && *(iterator+1) == ":"){
                        INLINE_ITERATE_AND_DELETE(iterator);
                         // deleting the comment statement
                    }
                    else if(*iterator == AttributeType && *(iterator+1) == ":" && Support::IS_DATATYPE(*(iterator+2)) && Support::IS_VALID_END(*(iterator+3))){
                        INLINE_ITERATE_AND_DELETE(iterator); 
                        // deleting the type statement
                    }
                    else if((*iterator == AttributeIf || *iterator == AttributeElif || *iterator == AttributeElse) && *(iterator+1) == ":" && (*(iterator+2) == "\n" || *(iterator+2) == "{")){
                        iterator+=2;
                        continue;
                    }
                    else if(*iterator == AttributeArgs && *(iterator+1) == ":" && !Support::IS_VALID_END(*(iterator+2)) ){
                        iterator+=2;
                        while(iterator < token_vector.end() && !Support::IS_VALID_END (*iterator)){
                            if(!(Support::IS_DATATYPE(*iterator) && Support::CHECK_VALID_IDENTIFIER_NAME(*(iterator+1)) )){
                                DISPLAY_EXCEPTION("analyzing the code and checking the 'args' attribute.",InvalidArgsSyntaxException);
                            }
                            FIND_AND_PUSH(&identifier_vector,*(iterator+1));
                            iterator+=2;
                            if(*iterator == ","){
                                ++iterator;
                            }
                        }
                    }
                }
                else if(Support::IS_NUMBER(*iterator)){

                }
                
            }
        }
        catch (const std::exception &ex)
        {
            printf("\nError : %s.\n",ex.what());
            DISPLAY_EXCEPTION("analyzing the code syntax and format.", SystemOutofMemoryException);
        }
    }

    inline static void EXTRACT_CHAR()
    {
        try
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
        catch (const std::exception &ex)
        {
            printf("Error : %s", ex.what());
            exit(-1);
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
        try
        {

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
        catch (const std::exception &ex)
        {
            printf("\nError : %s.", ex.what());
            exit(-1);
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
                printf("\n\n =|> Succesfully saved SRON's Bytecode to %s.\n", temp.c_str());
            }
            else
            {
                DISPLAY_EXCEPTION("saving the bytecode to '" + temp + "'.", ByteCodeCannotbeSavedException);
            }
        }
        catch (const std::exception &ex)
        {
            printf("Error : %s.\n", ex.what());
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
            default:
                DISPLAY_EXCEPTION("generating bytecode and handling scopes.", NoException);
            }
        }
        catch (const std::exception &ex)
        {
            printf("Error : %s.\n", ex.what());
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

    inline static void GENERATE()
    {
        try
        {
            // reading the whole content of the file.
            ByteCodeGenerator::filecode = std::string(std::istreambuf_iterator<char>(*Logs::mainfile), (std::istreambuf_iterator<char>()));

            // assigning the iterator at the beginning of the file
            ByteCodeGenerator::iterator = filecode.begin();

            // Jumping to the first occurrence of the Open braces.
            ByteCodeGenerator::JUMP_TO_NEXT_FIRST_OCCURENCE('{');

            // actual compilation starts from here.
            ByteCodeGenerator::TOKENIZER();

            // analyzing the code
            ByteCodeGenerator::ANALYZER();

            // Saving bytecode to the .srb file !
            // ByteCodeGenerator::FILE_WRITE();

            printf("\n\t +---------------------------------+\n\t<|| Compilation done successfully ||>\n\t +---------------------------------+\n");
        }
        catch (const std::exception &ex)
        {
            printf("Error : %s.\n", ex.what());
            DISPLAY_EXCEPTION("creating bytecode and analyzing the source code.", SystemOutofMemoryException);
        }
    }

    inline static void TOKENIZER()
    {
        try
        {
            unsigned short int wave_count = 0;
            for (; iterator < filecode.end(); ++iterator)
            {
                if (*iterator == ' ')
                {
                    continue;
                }
                else if(*iterator == '~'){
                    ++wave_count;
                }
                else if (*iterator == '"')
                {
                    ByteCodeGenerator::EXTRACT_STRING();
                    temp_string = '"' + temp_string + '"';
                }
                else if (*iterator == '\'')
                {
                    ByteCodeGenerator::EXTRACT_CHAR();
                    temp_string = "'" + temp_string + "'";
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
                else if (*iterator == '{' || *iterator == '}' || *iterator == '[' || *iterator == ']' || *iterator == '(' || *iterator == ')')
                {
                    ByteCodeGenerator::HANDLE_SCOPES();
                    temp_string += *iterator;
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

            if (!scope_stack.empty())
            {
                DISPLAY_EXCEPTION("tokenizing the code.", InvalidScopeException);
            }
            
            if(wave_count%2 != 0){
                DISPLAY_EXCEPTION("tokenizing the code.",WaveCountIsNotEvenException);
            }
        }
        catch (const std::exception &ex)
        {
            printf("Error : %s.\n", ex.what());
            DISPLAY_EXCEPTION("tokenizing the code.", NoException);
        }
    }
}
#endif