

#include "_utility_.hpp"

inline static void ByteCodeWriter::ATTRIBUTE_ARGS_WRITER()
{
   
}

inline static void ByteCodeWriter::ATTRIBUTE_MAPPER()
{

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

}

/*
    This function is called when AttributeRotate ('rotate') is found.
    It only writes hashes of the identifiers, and have no closing flag
    because we store the count of identifiers.

    * Format :
    Flag_RotateScopeStart
    No. of identifiers
    Hashes of identifier...

*/
inline static void ByteCodeWriter::ATTRIBUTE_ROTATE_WRITER()
{

}

/*
 * Format:-

   Flag_ForScopeStart
   |      >>> unsigned long (closing index) ------>>>
   |
   |            code here.....         
   |                                                |
   |      Flag_ForScopeEnd                          |
          <<< next code here <<< -------------------
*/
inline static void ByteCodeWriter::ATTRIBUTE_FOR_WRITER()
{

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

}

/*


  |->  Flag_WhileScopeStart
  |      <---closing-index--->------>---
  |      <- flag-condition-value->     |
  |      code ...                      |
  ^      ...                           | 
  |      ...                           |
  |      ...                           |
  |    Flag_WhileScopeEnd              |
  |-<---get-back-index-<<              |
      next code...  <------------------|                        

*/
inline static void ByteCodeWriter::ATTRIBUTE_WHILE_WRITER()
{

}

inline static void ByteCodeWriter::ATTRIBUTE_FOREACH_WRITER()
{

}