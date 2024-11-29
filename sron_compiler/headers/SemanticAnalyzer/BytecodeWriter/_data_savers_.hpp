
#include "_attribute_writer_.hpp"

inline static void ByteCodeWriter::SAVE_CONST_CHAR_TO_FILE(const char* __value, unsigned short int __len)
{

    #ifdef SRON_DEVELOPMENT_PHASE
        std::cout << "\n >>>>> String : '" << __value << "'\n     >>>>> Len: "<< __len ;
    #endif

}

inline static void ByteCodeWriter::SAVE_FLAG_TO_FILE(flag_t __flag)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        std::cout << "\n >>>>> Flag : " << __flag << "    " << Support::FLAG_TO_STRING(__flag);
    #endif

}

inline static void ByteCodeWriter::SAVE_INT64_TO_FILE(long long int value)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        std::cout << "\n >>>>> Int value :" << value;
    #endif

}

inline static void ByteCodeWriter::SAVE_DOUBLE_TO_FILE(double value)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        std::cout << "\n >>>>> Double value :" << value;
    #endif

}

inline static void ByteCodeWriter::SAVE_CHAR_TO_FILE(char value)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        std::cout << "\n >>>>> Char value :" << value;
    #endif

}

inline static void ByteCodeWriter::SAVE_LONG_TO_FILE(long value)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        std::cout<<"\n >>>>> Closing Index :"<< value;
    #endif

}

inline static void ByteCodeWriter::SAVE_U_INT16_TO_FILE(unsigned short int __value)
{
    #ifdef SRON_DEVELOPMENT_PHASE
        std::cout << "\n >>>>> USInt8 Value: "<< __value;
    #endif
}

// saving the user defined string to file ...
inline static void ByteCodeWriter::SAVE_STRING_TO_FILE(SronTokenString &value)
{
    // This code is not open sourced for security reasons
}

inline static size_t ByteCodeWriter::SAVE_UNSIGNED_INT64_TO_FILE(size_t __hash){


    #ifdef SRON_DEVELOPMENT_PHASE
        std::cout << "\n >>>>> Hash = " << __hash;
    #endif

    return __hash;
}

inline static size_t ByteCodeWriter::SAVE_UNSIGNED_INT64_TO_FILE(SronTokenString &__str)
{

    return ByteCodeWriter::SAVE_UNSIGNED_INT64_TO_FILE(SronHasher(__str.GET()).GET());

}