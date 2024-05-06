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

    inline static void POSTFIX()
    {
        try
        {
            std::stack<SronToken> stk;
            std::vector<SronToken> exp;
            for (vecit = token_vector.begin(); vecit < token_vector.end(); ++vecit)
            {
                if (vecit->_token == "~")
                {
                    ++vecit;
                    auto start = vecit;
                    while (vecit < token_vector.end() && vecit->_token != "~")
                    {

                        const auto temp = vecit->_type;

                        // checking if the std::string is a number or a variable
                        if (temp == TYPE_DOUBLE || temp == TYPE_INT || temp == TYPE_CHAR || temp == TYPE_BOOL || temp == TYPE_STRING || temp == TYPE_IDENTIFIER)
                        {
                            exp.push_back(*vecit);
                        }
                        else if (temp == TYPE_FUNCTION_CALL)
                        {
                            unsigned short int bracket_count = 1;
                            exp.push_back(*vecit);
                            ++vecit;
                            exp.push_back(*vecit);
                            ++vecit;

                            while (vecit < token_vector.end() && (vecit->_type != TYPE_MATH_BLOCK && bracket_count != 0))
                            {

                                bracket_count += (vecit->_type == TYPE_OPENING_BRACKETS) ? 1 : 0;
                                bracket_count -= (vecit->_type == TYPE_CLOSING_BRACKETS) ? 1 : 0;
                                exp.push_back(*vecit);
                                ++vecit;
                            }

                            continue;
                        }
                        else if (temp == TYPE_OPENING_BRACKETS)
                        {
                            stk.push(*vecit);
                        }
                        else if (temp == TYPE_CLOSING_BRACKETS)
                        {
                            while (!stk.empty() && stk.top()._type != TYPE_OPENING_BRACKETS)
                            {
                                exp.push_back(stk.top());
                                stk.pop();
                            }

                            // if the stack is made empty, then there will be nothing but if there is a round bracket
                            // then removing that round bracket.
                            if (!stk.empty())
                            {
                                stk.pop();
                            }
                        }
                        else if (Support::IS_OPERATOR(vecit->_token))
                        {
                            // std::cout<<"\n1----->"<<vecit->_token<<"<\n";
                            while ((!stk.empty()) && (Support::PRECEDENCE(vecit->_token) <= Support::PRECEDENCE(stk.top()._token)))
                            {

                                exp.push_back(stk.top());
                                stk.pop();
                            }

                            stk.push(*vecit);
                        }
                        else
                        {
                            DISPLAY_EXCEPTION("parsing and optimizing a mathematical expression. Found this token '" + (vecit->_token) + "' of type '" + (Support::TYPE_FLAG_TO_STRING(vecit->_type)) + "'.", MathematicalBlockSyntaxException, false);
                        }
                        ++vecit; // incrementing the iterator
                    }

                    // transferring all the element in the stack to the vector
                    while (!stk.empty())
                    {
                        exp.push_back(stk.top());
                        stk.pop();
                    }

                    // deleting the expression from the the element next to the Math block (~) ...
                    token_vector.erase(start, vecit);

                    token_vector.insert(start, exp.begin(), exp.end());

                    // clearing the std::vector<SronToken> exp .
                    exp.clear();
                }
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("parsing and optimizing the mathematical expression.", SystemOutofMemoryException);
        }
    }

    // if the ByteCodeGenerator::inside_math_expression is false, then this function will throw the error.
    inline static void CHECK_IF_OPERATOR_IS_INSIDE_MATH_BLOCK()
    {
        if (!ByteCodeGenerator::inside_math_expression)
        {
            DISPLAY_EXCEPTION("tokenizing the code. Found : '" + temp_string + "' outside the Mathematical block.\n     You can use mathematical and logical operators only inside the mathematical block.", NoException);
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
                    ++Logs::line_number;
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

    // This function will extract the numeric values. It returns true if the final value is a Double type value and returns false otherwise.
    inline static bool EXTRACT_NUMBER()
    {
        temp_string += *iterator;
        bool double_type_value = false;

        while (iterator++ < filecode.end() && (is_number(*iterator) || *iterator == '.'))
        {
            if (*iterator == '.')
            {

                // if '.' is coming again it means the passed value is an invalid number
                if (double_type_value)
                {
                    DISPLAY_EXCEPTION("tokenizing the code. Found : " + (temp_string + *iterator) + ". Not a valid decimal number with more than one decimal points.", NoException);
                }
                double_type_value = true;
            }

            temp_string += *iterator;
        }

        return double_type_value;
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
                    ++Logs::line_number;
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

    inline static SronToken *GET_LAST_TOKEN_REFERENCE()
    {

        return &(*(token_vector.end() - 1));
    }

    /*
     * This function is used to handle scopes.
     * NOTE : the 'if' statement written within the case of ']' works like this :
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
            case '~':
                if ((!scope_stack.empty()) && scope_stack.top() == '~')
                {
                    scope_stack.pop();
                }
                else if (inside_math_expression)
                {
                    scope_stack.push(*iterator);
                }
                else
                {
                    throw std::exception();
                }
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

    // moves the std::string::iterator iterator which is iterating over the
    // ByteCodeGenerator::filecode, to the next first occurrence of the passed character.
    inline static void JUMP_TO_NEXT_FIRST_OCCURENCE(char ch)
    {
        if (*iterator == '\n')
        {
            ++Logs::line_number;
        }
        while (*iterator != ch && iterator++ < filecode.end())
        {
            if (*iterator == '\n')
            {
                ++Logs::line_number;
            }
        }
    }

    // This function will tokenize the code means that it will split the code into different tokens like
    // strings, numbers, operators, identifiers etc. and saves it to ByteCodeGenerator::token_vector.
    inline static void TOKENIZER()
    {
        try
        {
            SronToken token_object;

            unsigned short int wave_count = 0;

            for (; iterator < filecode.end(); ++iterator)
            {
                if (*iterator == ' ')
                {
                    continue;
                }
                else if (*iterator == '\n')
                {
                    std::string &last_token = GET_LAST_TOKEN_REFERENCE()->_token;
                    if (Support::IS_CURLY_BRACES(last_token) || last_token == "\n")
                    {
                        ++Logs::line_number;
                        continue;
                    }
                    else if (last_token == ":")
                    { // checking if the attribue is left empty
                        DISPLAY_EXCEPTION("tokenizing the code. You left an attribute empty.", EmptyAttributeCode);
                    }
                    else
                    {
                        ++Logs::line_number;

                        if (inside_math_expression)
                        {
                            DISPLAY_EXCEPTION("tokenizing the code. You cannot start a new line inside the mathematical block. ", NoException);
                        }
                        if (token_vector.size() > 0 && (*(token_vector.end() - 1))._token == "\n")
                        {
                            continue;
                        }

                        temp_string += '\n';
                        token_object._type = TYPE_NEWLINE;
                    }
                }
                else if (*iterator == '~')
                {
                    if (ByteCodeGenerator::GET_LAST_TOKEN_REFERENCE()->_token == "~")
                    {
                        DISPLAY_EXCEPTION("tokenizing the code and going through a mathematical block.", MathematicalBlockSyntaxException);
                    }

                    ByteCodeGenerator::inside_math_expression = !ByteCodeGenerator::inside_math_expression;

                    ByteCodeGenerator::HANDLE_SCOPES();

                    token_object._type = TYPE_MATH_BLOCK;

                    
                    ++wave_count;
                    temp_string = "~";
                }
                else if (*iterator == '"')
                {
                    token_object._type = TYPE_STRING;

                    ByteCodeGenerator::EXTRACT_STRING();

                    temp_string = '"' + temp_string + '"';
                }
                else if (*iterator == '\'')
                {
                    token_object._type = TYPE_CHAR;

                    ByteCodeGenerator::EXTRACT_CHAR();

                    temp_string = "'" + temp_string + "'";
                }
                else if (Support::is_alphabet(*iterator) || *iterator == '_')
                {
                    ByteCodeGenerator::EXTRACT_IDENTIFIER();

                    // jump the comment...
                    if (temp_string == AttributeComment)
                    {
                        ByteCodeGenerator::JUMP_TO_NEXT_FIRST_OCCURENCE('\n');
                        temp_string = "";
                        continue;
                    }
                    else if (Support::IS_ATTRIBUTE(temp_string))
                    {
                        token_object._type = TYPE_ATTRIBUTE;
                    }
                    else if (Support::IS_DATATYPE(temp_string))
                    {
                        token_object._type = TYPE_DATATYPE;
                    }
                    else if (temp_string == "true" || temp_string == "false")
                    {
                        token_object._type = TYPE_BOOL;
                    }
                    else if (Support::IS_KEYWORD(temp_string))
                    {
                        token_object._type = TYPE_KEYWORD;
                    }
                    else if (temp_string == "PI")
                    {
                        temp_string = PI_VALUE;
                        token_object._type = TYPE_DOUBLE;
                    }
                    else
                    {
                        token_object._type = TYPE_IDENTIFIER;
                    }

                    --iterator;
                }
                else if (*iterator == '-')
                {

                    unsigned short int previous_token_type = (*(token_vector.end() - 1))._type;

                    // if previous_token is of type other than Int and Double then user is trying to put a minus sign
                    if ((previous_token_type == TYPE_INT) || (previous_token_type == TYPE_DOUBLE) || (previous_token_type == TYPE_IDENTIFIER) || (previous_token_type == TYPE_CLOSING_BRACKETS))
                    {

                        CHECK_IF_OPERATOR_IS_INSIDE_MATH_BLOCK();
                        temp_string += *iterator;
                        token_object._type = TYPE_OPERATOR;
                    }
                    else
                    {
                        token_object._type = (ByteCodeGenerator::EXTRACT_NUMBER()) ? TYPE_DOUBLE : TYPE_INT;
                        --iterator;
                    }
                }
                else if (Support::is_number(*iterator) || *iterator == '.')
                {
                    token_object._type = (ByteCodeGenerator::EXTRACT_NUMBER()) ? TYPE_DOUBLE : TYPE_INT;

                    // checking if the number is 0 and the token before it is either / or %.
                    std::string &last_token = GET_LAST_TOKEN_REFERENCE()->_token;
                    if (Converter::TO_DOUBLE(temp_string) == 0 && (last_token == "/" || last_token == "%"))
                    {
                        DISPLAY_EXCEPTION("tokenizing the code. You are trying to divide or mod a value by zero.", DivisionByZeroException);
                    }
                    --iterator;
                }
                else if (*iterator == '(')
                {

                    // if the previous token is a valid identifier and now the open bracket is coming it means
                    // user is trying to call the function.
                    if ((*(token_vector.end() - 1))._type == TYPE_IDENTIFIER)
                    {
                        (*(token_vector.end() - 1))._type = TYPE_FUNCTION_CALL;
                    }

                    ByteCodeGenerator::HANDLE_SCOPES();

                    temp_string += *iterator;

                    token_object._type = TYPE_OPENING_BRACKETS;
                }
                else if (*iterator == ')')
                {
                    temp_string += *iterator;
                    ByteCodeGenerator::HANDLE_SCOPES();

                    token_object._type = TYPE_CLOSING_BRACKETS;
                }
                else if (*iterator == '{')
                {

                    temp_string += *iterator;

                    ByteCodeGenerator::HANDLE_SCOPES();

                    token_object._type = TYPE_FUNCTION_SCOPE_START;
                }
                else if (*iterator == '[')
                {
                    temp_string += *iterator;

                    ByteCodeGenerator::HANDLE_SCOPES();

                    token_object._type = TYPE_LIST_OPEN;
                }
                else if (*iterator == ']')
                {
                    temp_string += *iterator;

                    ByteCodeGenerator::HANDLE_SCOPES();

                    token_object._type = TYPE_LIST_CLOSE;
                }
                else if (*iterator == '}')
                {
                    ByteCodeGenerator::HANDLE_SCOPES();
                    temp_string += *iterator;

                    if (*iterator == '}' && scope_stack.empty())
                    {
                        ByteCodeGenerator::JUMP_TO_NEXT_FIRST_OCCURENCE('{');
                        --iterator;
                    }

                    token_object._type = TYPE_FUNCTION_SCOPE_CLOSE;
                }
                else if (*iterator == '!' && iterator < filecode.end() - 1 && *(iterator + 1) == '=')
                {

                    temp_string += "!=";

                    ByteCodeGenerator::CHECK_IF_OPERATOR_IS_INSIDE_MATH_BLOCK();

                    token_object._type = TYPE_OPERATOR;

                    ++iterator;
                }
                else if ((*iterator == '&' || *iterator == '|' || *iterator == '=') && (*iterator == *(iterator + 1)))
                {
                    temp_string += ((std::string) "" + *iterator) + *(iterator + 1);

                    ByteCodeGenerator::CHECK_IF_OPERATOR_IS_INSIDE_MATH_BLOCK();

                    token_object._type = TYPE_OPERATOR;

                    ++iterator;
                }
                else if (*iterator == '=')
                {
                    if (ByteCodeGenerator::GET_LAST_TOKEN_REFERENCE()->_type != TYPE_IDENTIFIER)
                    {
                        DISPLAY_EXCEPTION("tokenizing the code. You are trying to assign some value to '" + GET_LAST_TOKEN_REFERENCE()->_token + "' which is not an identifier but is of type '" + std::string(Support::TYPE_FLAG_TO_STRING(ByteCodeGenerator::GET_LAST_TOKEN_REFERENCE()->_type)) + "'.", NoException);
                    }

                    temp_string += *iterator;
                    token_object._type = TYPE_ASSIGN;
                }
                else if ((*iterator == '<' || *iterator == '>'))
                {

                    // checking if <= or >= is appearing...
                    if (iterator < filecode.end() - 1 && *(iterator + 1) == '=')
                    {
                        temp_string = (temp_string + (*iterator)) + "=";
                        ++iterator;
                    }
                    else
                    {
                        temp_string += (*iterator);
                    }

                    ByteCodeGenerator::CHECK_IF_OPERATOR_IS_INSIDE_MATH_BLOCK();

                    token_object._type = TYPE_OPERATOR;
                }
                else if (*iterator == ':')
                {

                    // checking if previous token is a valid Attribute or not...
                    if (!Support::IS_ATTRIBUTE(GET_LAST_TOKEN_REFERENCE()->_token))
                    {
                        DISPLAY_EXCEPTION("tokenizing the code. Found an invalid attribute : '" + GET_LAST_TOKEN_REFERENCE()->_token + "'.", NoException);
                    }

                    // because the last token is a valid attribute, so we will convert its type to
                    ByteCodeGenerator::GET_LAST_TOKEN_REFERENCE()->_type = TYPE_ATTRIBUTE;

                    temp_string += *iterator;

                    token_object._type = TYPE_COLON;
                }
                else if (*iterator == ',')
                {
                    temp_string += *iterator;

                    token_object._type = TYPE_COMMA;
                }
                else if (Support::IS_OPERATOR(*iterator))
                {
                    temp_string += *iterator;

                    ByteCodeGenerator::CHECK_IF_OPERATOR_IS_INSIDE_MATH_BLOCK();

                    token_object._type = TYPE_OPERATOR;
                }
                else
                {
                    DISPLAY_EXCEPTION((std::string) "tokenizing the code. Found this Token '" + *iterator + "'.", InvalidTokenException);
                }

                token_object._token = temp_string;

                token_vector.push_back(token_object);

                temp_string = "";
                token_object._type = -1;
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
            if ((vecit + 1)->_token != AttributeName)
            {
                // checking if the function's name is declared first or not ...!!
                DISPLAY_EXCEPTION("refining and analyzing the code. The first attribute after starting a function is attribute 'name' which defines the function's name.", NoException);
            }
            for (; vecit < ByteCodeGenerator::token_vector.end(); ++vecit)
            {
                if (vecit->_type == TYPE_NEWLINE)
                {
                    ++Logs::line_number;

                    //const auto& next_type = (vecit+1)->_type;

                    // if(next_type != TYPE_ATTRIBUTE || next_type != TYPE_FUNCTION_SCOPE_CLOSE || next_type != TYPE_NEWLINE){
                    //     DISPLAY_EXCEPTION("refining and analyzing the code. Maybe you are writing a code without specifying the attribute.", NoException);
                    // }
                }
                else if (vecit->_type == TYPE_DATATYPE && ((vecit + 1)->_type != TYPE_IDENTIFIER))
                {
                    // if the variable declared is not a valid identifier name
                    DISPLAY_EXCEPTION("refining and analyzing the code. Found : '" + (vecit + 1)->_token + "' which is not a valid identifier.", NoException);
                }
                else if (vecit->_type == TYPE_ASSIGN && (!Support::IS_VALID_TYPE_AFTER_ASSIGN((vecit + 1)->_type)))
                {
                    // checking if the value after the assignment is a valid value or not.
                    DISPLAY_EXCEPTION("refining and analyzing the code. Found invalid value after assignment : '" + (vecit + 1)->_token + "'.", NoException);
                }
                else if (vecit->_token == AttributeName && (!IS_VALID_FUNCTION_NAME((vecit + 2)->_token)))
                {
                    // if the function name is not a valid.
                    DISPLAY_EXCEPTION("refining and analyzing the code. Found invalid function name '" + ((vecit + 2)->_token) + "'.", InvalidFunctionName);
                }
                else if (vecit->_type == TYPE_FUNCTION_CALL && (Support::TO_LOWER(vecit->_token) == "main"))
                {
                    // if user is trying to call main function...
                    DISPLAY_EXCEPTION("refining and analyzing the code. You cannot call 'MAIN' function, it is called automatically by SRON Interpreter.", NoException);
                }
                else if (Support::IS_VALID_ATTRIBUTE_WITH_ROUND_BRACKETS(vecit->_token) && (vecit + 2)->_type != TYPE_OPENING_BRACKETS)
                {

                    // if the attribute is 'args' , 'range' or 'condition' then
                    DISPLAY_EXCEPTION("refining and analyzing the code. When the attribute is '" + vecit->_token + "' , then it is required to put round bracket '()' around the statement. for example- " + vecit->_token + " : (  ) \n.", NoException);
                }
                else if (Support::IS_INNER_SCOPE_ATTRIBUTE(vecit->_token) && (vecit + 2)->_type != TYPE_FUNCTION_SCOPE_START)
                {

                    // if the attribute is for / while / if / elif / else ...
                    DISPLAY_EXCEPTION("refining and analyzing the code. Found this attribute '" + vecit->_token + "'.\n     Attribute like for / while / if / elif / else , should start a scope within its statement using '{' after the colon.", NoException);
                }
                else if (vecit->_token == AttributeFor && (vecit + 3)->_token != AttributeRange)
                {

                    // checking if the first attribute within the forloop is 'range' or not.
                    DISPLAY_EXCEPTION("refining and analyzing the code. The first attribute within for-loop must be 'range' instead '" + (vecit + 3)->_token + "' is found.", NoException);
                }
                else if ((vecit->_token == AttributeIf || vecit->_token == AttributeElif || vecit->_token == AttributeWhile) && (vecit + 3)->_token != AttributeCondition)
                {

                    // checking if the first attribute after if / elif / while is 'condition' or not
                    DISPLAY_EXCEPTION("refining and analyzing the code. The first attribute after 'if', 'elif' and 'while' attribute must be 'condition' but '" + (vecit + 3)->_token + "' is found.", NoException);
                }
                else if (vecit->_type == TYPE_ATTRIBUTE && !((vecit - 1)->_type == TYPE_NEWLINE || ((vecit - 1)->_type == TYPE_FUNCTION_SCOPE_START) || (vecit - 1)->_type == TYPE_FUNCTION_SCOPE_CLOSE))
                {

                    DISPLAY_EXCEPTION("refining and analyzing the code. You should start any attribute in a new line '" + vecit->_token + "' .", NoException);
                }
                else if (vecit->_token == AttributeComment)
                {
                    auto temp_iterator = vecit;

                    while (vecit++ < token_vector.end() && vecit->_type != TYPE_NEWLINE)
                    {
                    }

                    token_vector.erase(temp_iterator, vecit);
                }
                
            }
        }
        catch (const std::exception &)
        {
            DISPLAY_EXCEPTION("refining and analyzing the code.", SystemOutofMemoryException);
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