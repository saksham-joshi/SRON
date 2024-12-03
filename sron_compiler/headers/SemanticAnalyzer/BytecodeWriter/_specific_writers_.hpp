

#include "_data_savers_.hpp"


/*
 
 This function is called when type of Datatype is found ...!!



 Source Code:
     Int a
 Bytecode :
     Flag_Int       hash_of_a



 Source Code :
 
    Int a = 10
 ByteCode :
    Flag_Assign       hash_of_a      Flag_Int_Extractor        10
*/
inline static void ByteCodeWriter::DATATYPE_WRITER()
{
    // This code is not open sourced for security reasons
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
    // This code is not open sourced for security reasons
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
    // This code is not open sourced for security reasons
}

inline static void ByteCodeWriter::LIST_WRITER()
{
    // This code is not open sourced for security reasons
}

inline static void ByteCodeWriter::MATH_BLOCK_WRITER()
{
    // This code is not open sourced for security reasons

}

inline static void ByteCodeWriter::KEYWORD_WRITER()
{
    // This code is not open sourced for security reasons
}