

#include "_data_savers_.hpp"


/*
 
 This function is called when type of Datatype is found ...!!



 Source Code:
     Int a
 Bytecode :
     Flag_Int       index_of_a



 Source Code :
 
    Int a = 10
 ByteCode :
    Flag_Assign       index_of_a      Flag_Int_Extractor        10
*/
inline static void ByteCodeWriter::DATATYPE_WRITER()
{

    using ByteCodeWriter::iterator;

    if ((iterator + 2)->_type == TYPE_ASSIGN)
    {
        // current position of the iterator is at datatype
        Flag_t extractor_flag = Support::GET_EQUIVALENT_DATATYPE_EXTRACTOR(iterator->_flag);

        ByteCodeWriter::SAVE_FLAG (Flag_Assign);

        ++iterator ;

        //current position of the iterator is the variable name after datatype
        ByteCodeWriter::SAVE_VARIABLE(iterator->_cache_value);

        iterator+=2;

        //current position of the iterator is the value type after assign (=)
        if(extractor_flag != Flag_Any)
        {
            ByteCodeWriter::SAVE_FLAG (extractor_flag);
        }

        ByteCodeWriter::TYPE_MAPPER();

        return;
    }

    ByteCodeWriter::SAVE_FLAG (iterator->_flag);

    ++iterator;

    ByteCodeWriter::SAVE_VARIABLE(iterator->_cache_value);

}

/*
 * This function is called when a function call is found!
 * Format:-

   Hash of In-Built function or String form of User-defined function
   arguments (if any)
   Flag_Args_End

*/
inline static void ByteCodeWriter::FUNCTION_CALL_WRITER()
{
    using ByteCodeWriter::iterator;

    // the flag with either Flag_InbuiltFunctionCall or Flag_UserDefinedFunctionCall
    ByteCodeWriter::SAVE_FLAG (iterator->_flag);

    bool is_halt_function__ = false;

    if (iterator->_flag == Flag_InBuiltFunctionCall)
    {
        #ifdef SRON_DEVELOPEMENT_PHASE
            printf_s("\n In-built Function call : %hu (%s)", iterator->_cache_value, iterator->_token.c_str());
        #endif

        ByteCodeWriter::SAVE_DATA<SronInBuiltFncIndex_t> (iterator->_cache_value);

        is_halt_function__ = Support::IS_HALT_TYPE_FUNCTION(iterator->_token);
    }
    else
    {
        #ifdef SRON_DEVELOPMENT_PHASE
            printf_s("\n User-defined Function call : '%s.srb'", iterator->_token.c_str());
        #endif

        // replacing '.' with '\\'
        auto last_index_of_backslash = Support::REPLACE_CHAR_IN_CHAR_STR(iterator->_token.data() , '.' , '\\');

        last_index_of_backslash += ( last_index_of_backslash == 0 ? 0 : 1); // jumping next to '.' 

        // writing the length of the bytecode file name along with its extension .srb's length 4
        // and '\0' with length 1
        ByteCodeWriter::SAVE_DATA<BytecodeStringLen_t>( iterator->_token.length() + 5 );

        // writing the function name to the file
        ByteCodeWriter::SAVE_CONST_CHAR(iterator->_token.c_str(), iterator->_token.length(), false);

        // writing the extension with '\0'
        ByteCodeWriter::SAVE_CONST_CHAR( SRON_BYTECODE_FILE_EXTENSION, sizeof(SRON_BYTECODE_FILE_EXTENSION) - 1 );

        // storing the index from where the function name starts excluding directory path
        // not storing hash to bytecode so that if someone made changes to the bytecode 
        // then this change can't be caught (it creates a vulnerability).
        ByteCodeWriter::SAVE_DATA<BytecodeStringLen_t>( last_index_of_backslash );
    }

    // current position of iterator = 'function_name' and the open round bracket is not going to be written on bytecode because
    // it is usual that if there is a function call, then must be arguments after that...!
    iterator += 2;

    for(; iterator < ByteCodeWriter::tokenVectorEnd && iterator->_flag != Flag_Args_End ; ++iterator) ByteCodeWriter::TYPE_MAPPER();

    ByteCodeWriter::SAVE_FLAG (Flag_Args_End);

    if(is_halt_function__)  ByteCodeWriter::REMOVE_DEAD_CODE();
    
}


/*
 * This function is called when an identifier is found..

 * If the token next to the identifier is an assignment operator like
 * '=' or '+=', '-=', '*=' etc., then it writes the the flag of the
 * assignment operator, then writes the hash of the identifier
 * and then the value
 

 * If the next token is not an assignment operator, then write the 
 * Flag_Identifier_Variable and then the hash of the identifier.
   
*/
inline static void ByteCodeWriter::IDENTIFIER_WRITER()
{

    using ByteCodeWriter::iterator;

    if ((iterator + 1)->_type == TYPE_ASSIGN || (iterator + 1)->_type == TYPE_CALC_ASSIGN)
    {
        ByteCodeWriter::SAVE_FLAG ((iterator + 1)->_flag);

        ByteCodeWriter::SAVE_VARIABLE( iterator->_cache_value );
        
        ++iterator;
    }
    else
    {
        ByteCodeWriter::SAVE_FLAG (Flag_Identifier_Variable);

        ByteCodeWriter::SAVE_VARIABLE( iterator->_cache_value );
    }
}

inline static void ByteCodeWriter::LIST_WRITER()
{
    using ByteCodeWriter::iterator;

    ByteCodeWriter::SAVE_FLAG (Flag_ListStart);

    ++iterator;

    for(;iterator < ByteCodeWriter::tokenVectorEnd && iterator->_flag != Flag_ListEnd ; ++iterator)
    {
        ByteCodeWriter::TYPE_MAPPER();
    }

    ByteCodeWriter::SAVE_FLAG (Flag_ListEnd);
}

inline static void ByteCodeWriter::MATH_BLOCK_WRITER()
{
    ByteCodeWriter::SAVE_FLAG (Flag_EvalStart);

    PostFixGenerator postfix(iterator, tokenVectorEnd);

    auto temp_start = postfix.POSTFIX();
    auto temp_end = ByteCodeWriter::tokenVectorEnd;

    ByteCodeWriter::iterator = postfix.expression.begin();

    ByteCodeWriter::tokenVectorEnd = postfix.expression.end();

    for (; iterator < tokenVectorEnd; ++iterator)
    {
        ByteCodeWriter::TYPE_MAPPER();
    }

    ByteCodeWriter::iterator = temp_start;
    ByteCodeWriter::tokenVectorEnd = temp_end;

    ByteCodeWriter::SAVE_FLAG (Flag_EvalEnd);

}

inline static void ByteCodeWriter::KEYWORD_WRITER()
{
    using ByteCodeWriter::iterator;

    ByteCodeWriter::SAVE_FLAG (iterator->_flag);

    switch(iterator->_flag)
    {
        case Flag_Break : ByteCodeWriter::REMOVE_DEAD_CODE(); break;

        case Flag_OBuffer : iterator += 2; ByteCodeWriter::TYPE_MAPPER(); break;
    }
}