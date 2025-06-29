
#include "_attribute_writer_.hpp"

template <typename Tp> inline static void ByteCodeWriter::SAVE_DATA( Tp __value )
{
    std::fwrite(&__value , sizeof(__value), 1, ByteCodeWriter::__ByteCodeFile__);
}

inline static void ByteCodeWriter::SAVE_CONST_CHAR (const char* __value, unsigned short int __len, bool __put_terminator)
{

    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s( "\n >>>>> String : '%s'\n     >>>>> Len: %hu", __value , __len);
    #endif

    std::fwrite(__value , sizeof(*__value), __len , ByteCodeWriter::__ByteCodeFile__);

    if ( __put_terminator ) std::fputc('\0', ByteCodeWriter::__ByteCodeFile__);
}

inline static void ByteCodeWriter::SAVE_FLAG (Flag_t __flag)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s( "\n >>>>> Flag : %hu \t %s", __flag , Support::FLAG_TO_STRING(__flag));
    #endif

    ByteCodeWriter::SAVE_DATA<Flag_t>( __flag );
}

inline static void ByteCodeWriter::SAVE_INT64 ( SronInt_t __value)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s("\n >>>>>> Int value : %lld", __value);
    #endif

    ByteCodeWriter::SAVE_DATA<SronInt_t>( __value );
}

inline static void ByteCodeWriter::SAVE_DOUBLE ( SronDouble_t __value)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s("\n >>>>> Double value : %lf", __value);
    #endif

    ByteCodeWriter::SAVE_DATA<SronDouble_t>( __value );
}

inline static void ByteCodeWriter::SAVE_CHAR ( SronChar_t value)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s("\n >>>>> Char value : '%c'", value);
    #endif

    std::fputc(value, ByteCodeWriter::__ByteCodeFile__);
}

inline static void ByteCodeWriter::SAVE_LONG (long __value)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s("\n >>>>> Closing Index : %ld", __value);
    #endif

    ByteCodeWriter::SAVE_DATA<long>( __value );
}

inline static void ByteCodeWriter::SAVE_HASH ( Hash_t __value )
{
    #ifdef SRON_DEVELOPMENT_PHASE 
        printf_s("\n >>>>> Hash : %zu" , __value );
    #endif

    ByteCodeWriter::SAVE_DATA<Hash_t> ( __value );
}

inline static void ByteCodeWriter::SAVE_STRING ( const SronToken::TokenElement_t& __str )
{
    ByteCodeWriter::SAVE_DATA<BytecodeStringLen_t> ( __str.length() + 1 );  // + 1 is for '\0'

    ByteCodeWriter::SAVE_CONST_CHAR( __str.c_str() , __str.length() );
}

// saves constant string to the bytecode with Flag_String_Value and without the null terminator
inline static void ByteCodeWriter::SAVE_SRON_STRING( const SronToken::TokenElement_t& __str )
{
    ByteCodeWriter::SAVE_FLAG( Flag_String_Value );

    ByteCodeWriter::SAVE_DATA<BytecodeStringLen_t>( __str.length() );

    ByteCodeWriter::SAVE_CONST_CHAR( __str.c_str() , __str.length() , false);
}

inline static void ByteCodeWriter::SAVE_VARIABLE ( BytecodeVariable_t __variable )
{
    #ifdef SRON_DEVELOPMENT_PHASE
        printf_s("\n >>>>>> Variable : %hu", __variable);
    #endif

    ByteCodeWriter::SAVE_DATA<BytecodeVariable_t>( __variable );
}


// // saving the user defined string to file ...
// inline static void ByteCodeWriter::SAVE_STRING (SronToken::TokenElement_t &value)
// {
//     using ByteCodeWriter::__ByteCodeFile__;

//     ByteCodeWriter::SAVE_FLAG (Flag_String_Value);

//     // limiting the len before the end quote " but adding one more for ending '\0' terminator
//     BytecodeStringLen_t str_len = value.length() - 2 + 1;

//     // writing the length of the file to the bytecode
//     ByteCodeWriter::SAVE_DATA<BytecodeStringLen_t>(str_len);
//     //std::fwrite(&str_len, sizeof(str_len), 1, __ByteCodeFile__);

//     const char* ch = value.c_str()+1;    // jumping first single quote of the string

//     #ifdef SRON_DEVELOPMENT_PHASE
//          printf_s("\n >>>>> String Length : %hu \t \"%s", str_len , ch );
//     #endif

//     ByteCodeWriter::SAVE_CONST_CHAR (ch, str_len - 1 ); // decrementing the str_len so the ending quote doesn't get saved to bytecode
// }

// inline static size_t ByteCodeWriter::SAVE_UNSIGNED_INT64 (const SronHasher& __hash)
// {

//     #ifdef SRON_DEVELOPMENT_PHASE
//         printf_s("\n >>>>> Hash = %zu", __hash.GET());
//     #endif

//     ByteCodeWriter::SAVE_DATA<Hash_t>( __hash );

//     return __hash;
// }

// inline static size_t ByteCodeWriter::SAVE_UNSIGNED_INT64 (SronToken::TokenElement_t &__str)
// {
//     return ByteCodeWriter::SAVE_UNSIGNED_INT64 (SronHasher(__str.c_str()).GET());
// }