#ifndef BYTECODE_H
#define BYTECODE_H

#include <queue>
#include "_bytecode_writer_.hpp"

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
    std::vector<std::string> token_vector;

    // an iterator to iterate over a vector of string
    std::vector<std::string>::iterator vecit;

    inline static void ANALYZER();

    inline static void EXTRACT_CHAR();
    inline static void EXTRACT_IDENTIFIER();
    inline static void EXTRACT_STRING();
    inline static void EXTRACT_NUMBER();

    inline static void GENERATE();

    inline static void HANDLE_SCOPES();

    inline static void JUMP_SPACE_AND_NEWLINE();
    // inline static void JUMP_TILL_CHAR_REPEATS(char);
    inline static void JUMP_TO_NEXT_FIRST_OCCURENCE(char);

    inline static void POSTFIX();

    inline static void TOKENIZER();
    inline static void TOKEN_VECTOR_REFINER();

    inline static void POSTFIX()
    {
        try
        {
            std::stack<std::string> stk;
            std::vector<std::string> exp;
            for (vecit = token_vector.begin(); vecit < token_vector.end(); ++vecit)
            {
                if (*vecit == "~")
                {
                    ++vecit;
                    auto start = vecit;
                    while (vecit < token_vector.end() && *vecit != "~")
                    {
                        const auto temp = Support::IDENTIFY_TYPE_FROM_STRING(*vecit);

                        // checking if the std::string is a number or a variable
                        if (temp == TYPE_DOUBLE || temp == TYPE_INT || temp == TYPE_CHAR || temp == TYPE_BOOL || temp == TYPE_STRING || Support::IS_IDENTIFIER(*vecit))
                        {
                            exp.push_back(*vecit);
                        }
                        else if (*vecit == "(")
                        {
                            stk.push((*vecit));
                        }
                        else if (*vecit == ")")
                        {
                            while (!stk.empty() && stk.top() != "(")
                            {
                                exp.push_back(stk.top());
                                stk.pop();
                            }

                            if (!stk.empty())
                            {
                                stk.pop();
                            }
                        }
                        else if (Support::IS_OPERATOR((*vecit)))
                        {
                            while (!stk.empty() && Support::PRECEDENCE(*vecit) <= Support::PRECEDENCE(stk.top()))
                            {
                                exp.push_back(*vecit);
                                stk.pop();
                            }
                            stk.push((*vecit));
                        }
                        else
                        {
                            DISPLAY_EXCEPTION("parsing and optimizing a mathematical expression. Found this token '" + (*vecit) + "'.", MathEvaluationException, false);
                        }
                        ++vecit; // incrementing the iterator
                    }

                    // transferring all the element in the stack to the vector
                    while (!stk.empty())
                    {
                        exp.push_back(stk.top());
                        stk.pop();
                    }

                    // deleting the expression from the the element next to the
                    token_vector.erase(start, vecit);

                    token_vector.insert(start, exp.begin(), exp.end());

                    // clearing the std::vector<std::string> exp .
                    exp.clear();
                }
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("parsing and optimizing the mathematical expression.", SystemOutofMemoryException);
        }
    }

    /*
     * Implementation of above forward declared functions starts from here !
     */

    // This function will find the string in the vector
    // If the string is not found, it will push it into the vector
    // otherwise will throw an exception
    inline static void FIND_AND_PUSH(std::vector<std::string> *vec, std::string &str)
    {
        for (auto &i : *vec)
        {
            if (i == str)
            {
                DISPLAY_EXCEPTION("analyzing the code. You are redeclaring identifier(function or variable name).", NoException);
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
            std::vector<std::string> function_vector;   // it contains the name of the function

            auto iterator = token_vector.begin();

            // lambda function
            auto INLINE_ITERATE_AND_DELETE = [](std::vector<std::string>::iterator iterator)
            {
                auto temp = iterator;
                iterator += 2;
                while (iterator++ < ByteCodeGenerator::token_vector.end() && !Support::IS_VALID_END(*iterator))
                {
                }
                ByteCodeGenerator::token_vector.erase(temp, iterator);
            };

            for (; iterator < token_vector.end(); ++iterator)
            {
                if (Support::IS_CURLY_BRACES(*iterator))
                {
                    continue;
                }
                else if (Support::IS_INBUILT_ATTRIBUTE(*iterator))
                {
                    //  name : function
                    if (*iterator == AttributeName && *(iterator + 1) == ":" && Support::CHECK_VALID_IDENTIFIER_NAME(*(iterator + 2)) && Support::IS_VALID_END(*(iterator + 4)))
                    {
                        FIND_AND_PUSH(&function_vector, *(iterator + 2));
                        iterator += 4;
                        continue;
                    }
                    // comment : this is how you comment in SRON
                    else if (*iterator == AttributeComment && *(iterator + 1) == ":")
                    {
                        INLINE_ITERATE_AND_DELETE(iterator);
                        // deleting the comment statement
                    }
                    // type : Int
                    else if (*iterator == AttributeType && *(iterator + 1) == ":" && Support::IS_DATATYPE(*(iterator + 2)) && Support::IS_VALID_END(*(iterator + 3)))
                    {
                        INLINE_ITERATE_AND_DELETE(iterator);
                        // deleting the type statement
                    }
                    // if : {       // for : {
                    else if ((*iterator == AttributeIf || *iterator == AttributeElif || *iterator == AttributeElse) && *(iterator + 1) == ":" && (*(iterator + 2) == "\n" || *(iterator + 2) == "{"))
                    {
                        iterator += 2;
                        continue;
                    }
                    else if (*iterator == AttributeArgs && *(iterator + 1) == ":" && !Support::IS_VALID_END(*(iterator + 2)))
                    {
                        iterator += 2;
                        while (iterator < token_vector.end() && !Support::IS_VALID_END(*iterator))
                        {
                            if (!(Support::IS_DATATYPE(*iterator) && Support::CHECK_VALID_IDENTIFIER_NAME(*(iterator + 1))))
                            {
                                DISPLAY_EXCEPTION("analyzing the code and checking the 'args' attribute.", InvalidArgsSyntaxException);
                            }
                            FIND_AND_PUSH(&identifier_vector, *(iterator + 1));
                            iterator += 2;
                            if (*iterator == ",")
                            {
                                ++iterator;
                            }
                        }
                    }
                }
                else if (Support::IS_NUMBER(*iterator))
                {
                }
            }
        }
        catch (const std::exception &)
        {

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
            // if user is trying to enter a empty character like this :
            // Char ch = ''
            else if (*iterator == '\'')
            {
                temp_string = " ";
                return;
            }
            else
            {
                if (*iterator == '\n')
                {
                    Logs::INCREMENT_LINE_NUMBER();
                }
                temp_string += *iterator;
                ++iterator;
            }
            if ((*iterator) != '\'')
            {
                DISPLAY_EXCEPTION("extracting the value of 'Char' type.", InvalidValueException);
            }
        }
        catch (const std::exception &)
        {

            exit(-1);
        }
    }

    // This function will extract the identifier means any word staring from an alphabet or an underscore
    inline static void EXTRACT_IDENTIFIER()
    {
        temp_string += *iterator;
        while (iterator++ < filecode.end() && (Support::is_alpha_number(*iterator) || *iterator == '_'))
        {
            temp_string += *iterator;
        }
    }

    // This function will extract the numeric values
    inline static void EXTRACT_NUMBER()
    {
        temp_string += *iterator;
        while (iterator++ < filecode.end() && (is_number(*iterator) || *iterator == '.'))
        {
            temp_string += *iterator;
        }
    }

    // This function will extract the string values string from an quote until an another quote arrives
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
                else if (*iterator == '\n')
                {
                    Logs::INCREMENT_LINE_NUMBER();
                }
                temp_string += *iterator;
                ++iterator;
            }
        }
        catch (const std::exception &)
        {

            exit(-1);
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
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION(std::string("generating bytecode and handling scopes.\n Current Value = '") + *iterator + "'.", InvalidScopeException);
        }
    }

    // This function will jump spaces and newline in the token_vector using vecit iteratior
    inline static void JUMP_SPACE_AND_NEWLINE()
    {
        while ((*vecit == " " || *vecit == "\n") && vecit++ < token_vector.end())
        {
        }
    }

    // moves the std::string::iterator iterator which is iterating over the
    // ByteCodeGenerator::filecode, to the next first occurrence of the passed character.
    inline static void JUMP_TO_NEXT_FIRST_OCCURENCE(char ch)
    {
        if (*iterator == '\n')
        {
            Logs::INCREMENT_LINE_NUMBER();
        }
        while (*iterator != ch && iterator++ < filecode.end())
        {
            if (*iterator == '\n')
            {
                Logs::INCREMENT_LINE_NUMBER();
            }
        }
    }

    // This function will tokenize the code means that it will split the code into different tokens like
    // strings, numbers, operators, identifiers etc. and saves it to ByteCodeGenerator::token_vector.
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
                else if (*iterator == '\n')
                {
                    Logs::INCREMENT_LINE_NUMBER();
                    if (token_vector.size() > 0 && *(token_vector.end() - 1) == "\n")
                    {
                        continue;
                    }
                    temp_string += '\n';
                }
                else if (*iterator == '~')
                {
                    if (*(token_vector.end() - 1) == "~")
                    {
                        DISPLAY_EXCEPTION("tokenizing the code and going through a mathematical block.", MathematicalBlockSyntaxException);
                    }
                    ++wave_count;
                    temp_string = "~";
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
                    if (*iterator == '}' && scope_stack.empty())
                    {
                        ByteCodeGenerator::JUMP_TO_NEXT_FIRST_OCCURENCE('{');
                        --iterator;
                    }
                }
                else if (*iterator == '!' && iterator < filecode.end() - 1 && *(iterator + 1) == '=')
                {
                    temp_string += "!=";
                    ++iterator;
                }
                else if ((*iterator == '&' || *iterator == '|' || *iterator == '=') && (*iterator == *(iterator + 1)))
                {
                    temp_string += ((std::string) "" + *iterator) + *(iterator + 1);
                    ++iterator;
                }
                else if ((*iterator == '<' || *iterator == '>'))
                {
                    // checking if <= or >= is appearing...
                    if (iterator < filecode.end() - 1 && *(iterator + 1) == '=')
                    {
                        temp_string = (temp_string + (*iterator)) + "=";
                        ++iterator;
                    }
                    else{
                        temp_string = temp_string + (*iterator);
                    }
                }
                else if (Support::IS_OPERATOR(*iterator))
                {
                    temp_string += *iterator;
                }
                else
                {
                    DISPLAY_EXCEPTION((std::string) "tokenizing the code. Found this Token '" + *iterator + "'.", InvalidTokenException);
                }
                token_vector.push_back(temp_string);
                temp_string = "";
            }
            if (!scope_stack.empty())
            {
                DISPLAY_EXCEPTION("tokenizing the code.", InvalidScopeException);
            }

            if (wave_count % 2 != 0)
            {
                DISPLAY_EXCEPTION("tokenizing the code.", WaveCountIsNotEvenException);
            }
        }
        catch (const std::exception &)
        {

            DISPLAY_EXCEPTION("tokenizing the code.", NoException);
        }
    }

    inline static void TOKEN_VECTOR_REFINER()
    {
        ByteCodeGenerator::vecit = token_vector.begin();
        try
        {
            for (; vecit < ByteCodeGenerator::token_vector.end(); ++vecit)
            {
                if (*vecit == "\n")
                {
                    auto temp = *(vecit + 1);
                    if (temp == "}" || temp == "{")
                    {
                        ByteCodeGenerator::token_vector.erase(vecit);
                        --vecit;
                    }
                    else if (temp == "\n")
                    {
                        auto first = vecit + 1;

                        // jumping till the newline is occuring
                        while (vecit < token_vector.end() && *vecit == "\n")
                        {
                            ++vecit;
                        }

                        ByteCodeGenerator::token_vector.erase(first, vecit);

                        vecit = first - 1;
                    }
                }
                else if (*vecit == "{" && *(vecit + 1) == "\n")
                {
                    ByteCodeGenerator::token_vector.erase(vecit + 1);
                    --vecit;
                }
                else if (*vecit == AttributeComment) // removing comments from the code
                {
                    if ((*(vecit + 1)) == ":")
                    {
                        auto first = vecit;
                        vecit += 2;

                        while (vecit < token_vector.end() && (!Support::IS_VALID_END(*vecit)))
                        {
                            ++vecit;
                        }
                        ++vecit;

                        ByteCodeGenerator::token_vector.erase(first, vecit);
                        vecit = first - 2;
                    }
                    else
                    {
                        DISPLAY_EXCEPTION("refining the code and removing comments.", InvalidCommentSyntaxException, false);
                    }
                }
                else if (*vecit == AttributeType)
                {
                    if (vecit < token_vector.end() - 1 && *(vecit + 1) == ":")
                    {
                        auto first = vecit;
                        vecit += 2;

                        // jumping to the next first occurence of newline(\n)
                        while (vecit < token_vector.end() && (!Support::IS_VALID_END(*vecit)))
                        {
                            ++vecit;
                        }
                        ++vecit;

                        // deleting from the starting of AttributeType to the first occurence of newline
                        // including the newline.
                        ByteCodeGenerator::token_vector.erase(first, vecit);
                        --vecit;
                    }
                    else
                    {
                        DISPLAY_EXCEPTION("refining the code and analyzing the attribute 'type'.", InvalidAttributeException, false);
                    }
                }
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("refining the code.", SystemOutofMemoryException);
        }
    }

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

            // assigning the iterator at the beginning of the file
            ByteCodeGenerator::iterator = filecode.begin();

            // Jumping to the first occurrence of the Open braces.
            ByteCodeGenerator::JUMP_TO_NEXT_FIRST_OCCURENCE('{');

            // actual compilation starts from here.
            ByteCodeGenerator::TOKENIZER();

            // for (auto &i : token_vector)
            // {
            //     std::cout << i << " | ";
            // }
            
            std::cout<<"\n\n";
            // clearing the temp_string
            ByteCodeGenerator::temp_string.~basic_string();

            // clearing the filecode to free up memory.
            ByteCodeGenerator::filecode.~basic_string();

            // removing the comments and unnecessary newlines
            ByteCodeGenerator::TOKEN_VECTOR_REFINER();

            // analyzing the code
            // ByteCodeGenerator::ANALYZER();

            // This function will convert the mathematical expression in the token vector to the postfix expression.
            ByteCodeGenerator::POSTFIX();

            // for (auto &i : token_vector)
            // {
            //     std::cout << i << " | ";
            // }

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