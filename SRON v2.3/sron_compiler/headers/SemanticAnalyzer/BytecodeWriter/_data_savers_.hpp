
#include "_attribute_writer_.hpp"

template <typename Tp> inline static void ByteCodeWriter::SAVE_DATA( Tp __value )
{
}

inline static void ByteCodeWriter::SAVE_CONST_CHAR (const char* __value, unsigned short int __len, bool __put_terminator)
{
}

inline static void ByteCodeWriter::SAVE_FLAG (BytecodeFlags __flag)
{

}

inline static void ByteCodeWriter::SAVE_INT64 ( SronInt_t __value)
{

}

inline static void ByteCodeWriter::SAVE_DOUBLE ( SronDouble_t __value)
{

}

inline static void ByteCodeWriter::SAVE_CHAR ( SronChar_t value)
{

}

inline static void ByteCodeWriter::SAVE_HASH ( Hash_t __value )
{

}

inline static void ByteCodeWriter::SAVE_STRING ( const SronToken::TokenElement_t& __str )
{

}

// saves constant string to the bytecode with Flag_String_Value and without the null terminator
inline static void ByteCodeWriter::SAVE_SRON_STRING( const SronToken::TokenElement_t& __str )
{

}

inline static void ByteCodeWriter::SAVE_VARIABLE ( BytecodeVariable_t __variable )
{

}