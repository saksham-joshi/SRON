#ifndef _BYTECODE_FILE_MNG_H_
#define _BYTECODE_FILE_MNG_H_

#include "_argument_list_.hpp"
#include "_variable_manager_.hpp"

struct SronByteCodeFileManip
{

private:
    _iobuf *file__ = nullptr;

public:

    // stores true if code is executing and if set false, code will end
    bool executing__ = true;
    
    inline SronByteCodeFileManip(const char *const &);

    inline void CLOSE() noexcept;

    inline void DECREMENT_SEEK_BY(long);

    inline long GET_CUR_SEEK_POS() const noexcept;

    inline void MOVE_SEEK(long) noexcept;

    inline void PRINT(unsigned short int) const noexcept;

    inline bool READ_BOOL() const;
    inline char READ_CHAR() const;
    inline double READ_DOUBLE() const;
    inline flag_t READ_FLAG();
    inline int READ_INT32() const;
    inline long long int READ_INT64() const;
    inline long READ_LONG() const;

    inline void READ_STRING(unsigned short int, char*);
    inline std::string &READ_STRING(std::string &);
    inline void READ_STRING(SronTokenString&);

    inline size_t READ_UNSIGNED_INT64() const;
    inline unsigned short int READ_U_INT16() const noexcept;

    inline void SET_SEEK_TO_END() noexcept;
    inline void SET_SEEK_AT(long) noexcept;
    inline ~SronByteCodeFileManip() noexcept;
};

inline SronByteCodeFileManip::SronByteCodeFileManip(const char *const &__filename)
{   
    fopen_s(&this->file__, __filename, "rb");

    if (!this->file__)
    {
        throw ThrowException("loading the bytecode. Cannot find the bytecode file '" + (std::string(__filename)) + "'", FileNotFoundException);
    }

    // checking if the version of the bytecode is same as the version of the interpreter
    double version__ = this->READ_DOUBLE();
    if (Logs::__SronVersion__ != version__)
    {
        throw ThrowException("loading the bytecode. The bytecode's version doesn't match with interpreter's version. Bytecode is compiled in version '" + std::to_string(version__) + "' of SRON's compiler whereas the current SRON's version is '" + std::string(Logs::__SronVersionString__) + "'", InvalidByteCodeException);
    }
}

/*
 closes the stream and destructs the file
*/
inline void SronByteCodeFileManip::CLOSE() noexcept
{
    if (this->file__ != nullptr)
    {
        std::fclose(this->file__);

        this->file__ = nullptr;
    }
}

inline void SronByteCodeFileManip::DECREMENT_SEEK_BY(long __jump)
{
    std::fseek(this->file__, std::ftell(this->file__) - __jump, SEEK_SET);
}

/*
 */
inline long SronByteCodeFileManip::GET_CUR_SEEK_POS() const noexcept
{
    return std::ftell(this->file__);
}

/*
sets the position of the seek to the index position add to the current position of the seek
 */
inline void SronByteCodeFileManip::MOVE_SEEK(long __position) noexcept
{
    std::fseek(this->file__, __position, SEEK_CUR);
}

inline void SronByteCodeFileManip::PRINT(unsigned short int __count) const noexcept
{
    static char array[1024];

    std::fread(array, sizeof(char), __count, this->file__);

    array[__count] = '\0';

    std::cout<<array;

}

inline bool SronByteCodeFileManip::READ_BOOL() const
{
    static bool value;

    std::fread(&value, sizeof(bool), 1, this->file__);

    return value;
}

/*

*/
inline char SronByteCodeFileManip::READ_CHAR() const
{

    return std::fgetc(this->file__);
}

/*

*/
inline double SronByteCodeFileManip::READ_DOUBLE() const
{
    static double value;

    std::fread(&value, sizeof(value), 1, this->file__);

    return value;
}

/*

*/
inline flag_t SronByteCodeFileManip::READ_FLAG()
{
    static flag_t value;

    std::fread(&value, sizeof(value), 1, this->file__);

    return value;
}

/*

*/
inline int SronByteCodeFileManip::READ_INT32() const
{
    static int value;

    std::fread(&value, sizeof(value), 1, this->file__);

    return value;
}

inline long long int SronByteCodeFileManip::READ_INT64() const
{

    static long long int value;

    std::fread(&value, sizeof(value), 1, this->file__);

    return value;
}

inline long SronByteCodeFileManip::READ_LONG() const {

    static long value;

    std::fread(&value, sizeof(value), 1, this->file__);

    return value;
}



inline void SronByteCodeFileManip::READ_STRING(unsigned short int __len, char* __value)
{
    std::fread(__value , sizeof(char), __len, this->file__);
    __value[__len] = '\0';
}


/*

*/
inline std::string &SronByteCodeFileManip::READ_STRING(std::string &__str)
{
    const int len = this->READ_INT32();

    for (int i = 0; i < len; ++i)  __str.push_back(std::fgetc(this->file__));

    return __str;
}

inline void SronByteCodeFileManip::READ_STRING(SronTokenString& __str){
    
    int len = this->READ_INT32();

    char* cstr = new char[len+1];

    std::fread(cstr, sizeof(char), len, this->file__ );

    cstr[len] = '\0';

    __str = SronTokenString(cstr, len);

    cstr = nullptr;
}

/*

*/
inline size_t SronByteCodeFileManip::READ_UNSIGNED_INT64() const
{
    static size_t value;

    std::fread(&value, sizeof(value), 1, this->file__);

    return value;
}

inline unsigned short int SronByteCodeFileManip::READ_U_INT16() const noexcept{

    static unsigned short int value;

    std::fread(&value, sizeof(value), 1, this->file__);

    return value;
}

/*
sets the seek to the end of the file
*/
inline void SronByteCodeFileManip::SET_SEEK_TO_END() noexcept
{
    this->executing__ = false;
}

inline void SronByteCodeFileManip::SET_SEEK_AT(long __position) noexcept
{
    std::fseek(this->file__, __position, SEEK_SET);
}

/*
    Calls the this->CLOSE() method, so no need to close the file explicitly
*/
inline SronByteCodeFileManip::~SronByteCodeFileManip() noexcept
{
    this->CLOSE();
}

#endif