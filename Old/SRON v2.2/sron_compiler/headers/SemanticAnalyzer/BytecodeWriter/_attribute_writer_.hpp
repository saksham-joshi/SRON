

#include "_utility_.hpp"

inline static void ByteCodeWriter::ATTRIBUTE_ARGS_WRITER()
{
    using ByteCodeWriter::iterator;

    ByteCodeWriter::SAVE_FLAG(Flag_FunctionParamScopeStart);

    iterator += 2;
    // current position of the  iterator -- args : ( <-here

    ByteCodeWriter::seek_tracker.push_back(SeekTracker(0, Flag_FunctionParamScopeEnd));

}

inline static void ByteCodeWriter::ATTRIBUTE_MAPPER()
{
    using ByteCodeWriter::iterator;

    switch (iterator->_flag)
    {

        case Flag_FunctionParamScopeStart: ByteCodeWriter::ATTRIBUTE_ARGS_WRITER(); break;

        case Flag_ConsoleStart: ByteCodeWriter::ATTRIBUTE_CONSOLE_WRITER(); break;

        case Flag_Condition: ++iterator; break; // now the iterator is at condition : <-- here

        case Flag_IfScopeStart:

        case Flag_ElifScopeStart:

        case Flag_ElseScopeStart: ByteCodeWriter::ATTRIBUTE_IF_ELIF_ELSE_WRITER(); break;

        case Flag_ReturnType : iterator += 2; ByteCodeWriter::__returnTypeFlag__ = Support::GET_EQUIVALENT_DATATYPE_EXTRACTOR(iterator->_flag) ; break;

        case Flag_Return: ByteCodeWriter::ATTRIBUTE_RETURN_WRITER(); break;

        case Flag_RotateScopeStart:ByteCodeWriter::ATTRIBUTE_ROTATE_WRITER(); break;

        case Flag_FunctionName: iterator += 2; break;

        case Flag_ForScopeStart: ByteCodeWriter::ATTRIBUTE_FOR_WRITER(); break;

        case Flag_WhileScopeStart: ByteCodeWriter::ATTRIBUTE_WHILE_WRITER(); break;

        case Flag_ForeachScopeStart : ByteCodeWriter::ATTRIBUTE_FOREACH_WRITER(); break;

        default: throw ThrowException("cannot find bytecode generator method for attribute '" + std::string(iterator->_token.c_str()) + "'");
    }

}

/*
    To reduce the memory usage, speed and power usage, this function writes the constant values
    like Int, Double, Bool and String with flag Flag_String_Value then the length of the value
    and then the value itself.

    When it comes to values of type TYPE_CHAR, it puts the Flag Flag_Char_Value and then the
    char itself and for other types of values, it writes the values as per its bytecode format.

    Format:-

    Flag_ConsoleStart
    value type...
    Flag_ConsoleEnd
*/
inline static void ByteCodeWriter::ATTRIBUTE_CONSOLE_WRITER()
{

    using ByteCodeWriter::iterator;
    using ByteCodeWriter::seek_tracker;

    ByteCodeWriter::SAVE_FLAG(Flag_ConsoleStart);

    iterator += 3;    // console : ( data      <- incrementing iterator here...

    // current position of the iterator is the value after '(' ...
    while (iterator < ByteCodeWriter::tokenVectorEnd && iterator->_type != TYPE_CLOSING_BRACKETS)
    {

        if (iterator->_type == TYPE_INT || iterator->_type == TYPE_DOUBLE || iterator->_type == TYPE_BOOL || iterator->_type == TYPE_STRING)
        {
            ByteCodeWriter::SAVE_FLAG(Flag_String_Print);

            ByteCodeWriter::SAVE_DATA<BytecodeStringLen_t>( iterator->_token.length() + 1 ); // + 1 is for '\0'

            ByteCodeWriter::SAVE_CONST_CHAR(iterator->_token.c_str(), iterator->_token.length());

        }
        else if (iterator->_type == TYPE_CHAR)
        {
            ByteCodeWriter::SAVE_FLAG(Flag_Char_Print);

            ByteCodeWriter::SAVE_CHAR(iterator->_token[0]);
        }
        else if( iterator->_flag == Flag_OBuffer )
        {
            ByteCodeWriter::SAVE_FLAG( Flag_OBuffer );
        }
        else
        {
            ByteCodeWriter::TYPE_MAPPER();
        }

        ++iterator;
    }

    ByteCodeWriter::SAVE_FLAG(Flag_ConsoleEnd);
}

/*
 * This function is called when AttributeReturn is found in the code.
 
 * Format:-
   
   Flag_Return 
   Value to be returned
 
 *-----------------------------------------------------------------------
 * After the flag and the value to be returned the ByteCodeWriter::iterator
 * is moved to the end of current scope in order to remove the dead code.
*/
inline static void ByteCodeWriter::ATTRIBUTE_RETURN_WRITER()
{
    using ByteCodeWriter::iterator;

    ByteCodeWriter::SAVE_FLAG(Flag_Return);

    iterator += 2;

    if(ByteCodeWriter::__returnTypeFlag__ != Flag_Any)
    {
        ByteCodeWriter::SAVE_FLAG(ByteCodeWriter::__returnTypeFlag__);
    }
    
    ByteCodeWriter::TYPE_MAPPER();

    ByteCodeWriter::REMOVE_DEAD_CODE();

}

/*
    This function is called when AttributeRotate ('rotate') is found.
    It only writes indexes of the variables, and have no closing flag
    because we store the count of identifiers.

    * Format :
    Flag_RotateScopeStart
    No. of identifiers
    indexes of identifier...

*/
inline static void ByteCodeWriter::ATTRIBUTE_ROTATE_WRITER()
{

    using ByteCodeWriter::iterator;

    ByteCodeWriter::SAVE_FLAG(Flag_RotateScopeStart);

    // the count of identifiers is stored in newline_count by SemanticAnalyzer::FOUND_ROTATE_ATTRIBUTE()
    ByteCodeWriter::SAVE_DATA<BytecodeCount_t>(iterator->_cache_value);

    iterator += 3;

    while (iterator < ByteCodeWriter::tokenVectorEnd && iterator->_type != TYPE_CLOSING_BRACKETS)
    {

        if (iterator->_type == TYPE_IDENTIFIER) ByteCodeWriter::SAVE_VARIABLE( iterator->_cache_value );

        ++iterator;
    }

    // for rotate, no closing flag is required because a closing index is already stored after Flag_RangeScopeStart
}

/*
 * Format:-

   Flag_ForScopeStart
   |      BytecodePos_t (closing index) ------>>>>>>
   |      Flag_iterating_Variable                   |
   |      Starting_value                            |
   |      End_value                                 |
   |      Jump_value ( if any )                     |
   |      Flag_RangeScopeEnd                        |
   |                                                |
   |                                                |
   |            code here.....                      |
   |                                                |
   |      Flag_ForScopeEnd                          |
          <<< next code here <<< -------------------
*/
inline static void ByteCodeWriter::ATTRIBUTE_FOR_WRITER()
{

    using ByteCodeWriter::seek_tracker;
    using ByteCodeWriter::iterator;

    ByteCodeWriter::SAVE_FLAG(Flag_ForScopeStart);

    seek_tracker.push_back(SeekTracker(std::ftell(__ByteCodeFile__), Flag_ForScopeEnd));

    ByteCodeWriter::SAVE_DATA<BytecodePos_t>(0);

    while(++iterator < ByteCodeWriter::tokenVectorEnd && iterator->_flag != Flag_RangeScopeStart);

    // current position of the iterator is at the 'range' 
    iterator += 3;

    /*
        Valid syntaxes of range :

        range : ( Int i = 0, 10, 1)
        range : ( Int i = 0, 10 )

        range : (i = 0, 10 , 1)
        range : (i = 0, 10)

        range : (i, 10, 1)
        range : (i, 10)
    */

    // now the position of the iterator is at the token after '('
    // now the next thing to save into bytecodee is variable_id
    if(iterator->_type == TYPE_DATATYPE)
    {
        // saving the variable_id
        ByteCodeWriter::SAVE_VARIABLE((iterator+1)->_cache_value);

        // writing the starting_value from the current position of the iterator
        // which is at TYPE_DATATYPE
        ByteCodeWriter::TYPE_MAPPER();

        ++iterator;
    }
    else if(iterator->_type == TYPE_IDENTIFIER)
    {
        // saving the variable id        
        ByteCodeWriter::SAVE_VARIABLE( iterator->_cache_value );

        ++iterator;

        // now we have to write the starting value for the loop
        // range : (variable = value, ...
        if(iterator->_flag == Flag_Assign )
        {

            // writing '='
            ByteCodeWriter::SAVE_FLAG(Flag_Assign);

            // then the variable_id
            ByteCodeWriter::SAVE_VARIABLE( (iterator - 1)->_cache_value );

            // currently the iterator is at '='
            ++iterator;

            // current position is the value after '=' ...
            ByteCodeWriter::TYPE_MAPPER();

            ++iterator;
        }
        // range : (variable, )
        else{

            ByteCodeWriter::SAVE_FLAG(Flag_Identifier_Variable);
            
            ByteCodeWriter::SAVE_VARIABLE( (iterator-1)->_cache_value );
        }
    }
    else
    {
        throw ThrowException("generating the bytecode. Found an invalid token '" + std::string(iterator->_token.c_str())+ "'. Expected a datatype or variable [Compiler-Issue]", iterator->_file_index);
    }

    // till here, we have written starting_value
    iterator += ((iterator->_type == TYPE_COMMA) ? 1 : 0);

    // writing the end-value now
    ByteCodeWriter::TYPE_MAPPER();

    ++iterator;

    // if the token is not closing bracket, then it must be comma,
    // and if it is comma then the next token is the step/jump value
    if(iterator->_type != TYPE_CLOSING_BRACKETS)
    {
        ++iterator;
        // writing the step-value
        ByteCodeWriter::TYPE_MAPPER();

        ++iterator;
    }

    ByteCodeWriter::SAVE_FLAG(Flag_RangeScopeEnd);
}

/*
 * Format:-
  
          Flag_IfScopeStart / Flag_ElifScopeStart / Flag_ElseScopeStart
  ending flag index 
  |       value type for condition
  |       code inside the scope of if / elif / else
  |      Flag_IfScopeEnd / Flag_ElifScopeEnd / Flag_ElseScopeEnd
  |-> next flags...
*/

inline static void ByteCodeWriter::ATTRIBUTE_IF_ELIF_ELSE_WRITER()
{

    using ByteCodeWriter::iterator;

    ByteCodeWriter::SAVE_FLAG(iterator->_flag);

    Flag_t ending_flag = Support::GET_RESPECTIVE_ENDING_FLAG(iterator->_flag);

    ByteCodeWriter::seek_tracker.push_back(SeekTracker(std::ftell(ByteCodeWriter::__ByteCodeFile__), ending_flag));

    ByteCodeWriter::SAVE_DATA<BytecodePos_t>(0);

    //ByteCodeWriter::scope_handler.push(ending_flag);

    // current position of iterator is if/elif/else,
    // jumping +2 to move to the position of '{'
    iterator += 2;
}

// inline static void ByteCodeWriter::ATTRIBUTE_IF_ELIF_ELSE_END_WRIER()
// {
//     /*
//         Flag_IfScopeEnd, Flag_ElifScopeEnd or Flag_ElseScopeEnd, any one of the mentioned
//         flag can be there at the top of ByteCodeWriter::scope_handler stack
//     */
//     Flag_t top_flag = ByteCodeWriter::scope_handler.top();

//     ByteCodeWriter::SAVE_FLAG(top_flag);

//     /*
//         After writing the ending flag, it is needed to store the current index


//         if : {
//         }
//         println("SRON")

//         OR

//         if : {
//         }
//         elif : {
//         }
//         else : {
//         }
//     */
//     auto cur_index = std::ftell(ByteCodeWriter::__ByteCodeFile__);

//     auto& it = ByteCodeWriter::seek_tracker.back();

//     // moving the seek back to where if attribute is written ....
//     std::fseek(ByteCodeWriter::__ByteCodeFile__, it._position, SEEK_SET);

//     ByteCodeWriter::SAVE_LONG(cur_index);

//     // getting back to the end position from where we left
//     std::fseek(ByteCodeWriter::__ByteCodeFile__, cur_index, SEEK_SET);

//     // erasing the element which stored it....
//     ByteCodeWriter::seek_tracker.pop_back();
// }
/*


  |->  Flag_WhileScopeStart
  |      <---closing-index--->------>---
  |      <- flag-condition-value->     |
  |      code ...                      |
  ^      ...                           | 
  |      ...                           |
  |      ...                           |
  |    Flag_WhileScopeEnd              |
      next code...  <------------------|                        

*/
inline static void ByteCodeWriter::ATTRIBUTE_WHILE_WRITER()
{

    ByteCodeWriter::SAVE_FLAG(Flag_WhileScopeStart);

    ByteCodeWriter::seek_tracker.push_back(SeekTracker(std::ftell(ByteCodeWriter::__ByteCodeFile__), Flag_WhileScopeEnd));

    // saving the closing index ...
    ByteCodeWriter::SAVE_DATA<BytecodePos_t>(0);

    iterator += 2;
}


/*
 Flag_ForeachScopeStart
 closing_index

 Flag_ForeachScopeEnd
*/

inline static void ByteCodeWriter::ATTRIBUTE_FOREACH_WRITER()
{
    using ByteCodeWriter::iterator;

    ByteCodeWriter::SAVE_FLAG(Flag_ForeachScopeStart);

    ByteCodeWriter::seek_tracker.push_back(SeekTracker(std::ftell(ByteCodeWriter::__ByteCodeFile__), Flag_ForeachScopeEnd));

    ByteCodeWriter::SAVE_DATA<BytecodePos_t>(0);

    while(++iterator < ByteCodeWriter::tokenVectorEnd && iterator->_flag != Flag_ForeachOn);

    iterator+=3;

    // current position of the iterator is at--- on : (identifier / datatype <---here
    iterator += (iterator->_type == TYPE_DATATYPE) ? 1 : 0;

    ByteCodeWriter::SAVE_VARIABLE(iterator->_cache_value);

    iterator += 2;
    //current position of the iterator is at- on : (variable , value <----here

    ByteCodeWriter::TYPE_MAPPER();

    ++iterator;
}