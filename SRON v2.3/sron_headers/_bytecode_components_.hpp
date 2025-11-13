#ifdef _WIN64
    #pragma comment(linker, "/STACK:16777216,16777216")
#endif

#ifndef _SRON_BYTECODE_COMPONENTS_H_
#define _SRON_BYTECODE_COMPONENTS_H_

#define MAXOF_UINT32               (4294967295u)

typedef int                        BytecodePos_t;
typedef unsigned int               FilePos_t;
typedef float                      BytecodeVersion_t;
typedef unsigned short int         SronTokenType_t;
typedef unsigned short int         Flag_t;                   // used to store the instruction numbers
typedef unsigned short int         SronInBuiltFncIndex_t;
typedef unsigned short int         BytecodeStringLen_t;      // used to store the length of string to be saved in bytecode
typedef unsigned short int         ArgListLen_t;
typedef unsigned short int         BytecodeCount_t;
typedef unsigned short int         BytecodeVariable_t;
typedef unsigned long long         Hash_t;
typedef unsigned int               TokenCache_t;
typedef long long int              SronInt_t;
typedef double                     SronDouble_t;
typedef char                       SronChar_t;
typedef bool                       SronBool_t;

#define MAX_VARIABLE_IN_ROTATE_ATTRIBUTE       ((BytecodeCount_t)       32    )
#define BYTECODE_STRING_MAX_LEN                ((BytecodeStringLen_t)   4096  )
#define BYTECODE_IDENTIFIER_MAX_LEN            ((unsigned short int)    32    )
#define ARGUMENT_LIST_MAX_LEN                  ((BytecodeCount_t)       32    )
#define SRON_VERSION                           ((BytecodeVersion_t)     2.3   )
#define SRON_VERSION_STRING                                           "2.3"
#define VOID_STRING_PRINT_FORMAT                                      "<#-Void-#>"
#define TRUE_STRING_PRINT_FORMAT                                      "true"
#define FALSE_STRING_PRINT_FORMAT                                     "false"
#define SRON_BYTECODE_FILE_EXTENSION                                  ".srb"
#define SRON_MAIN                                                     "Main"
#define SRON_MAIN_FILE                                                SRON_MAIN SRON_BYTECODE_FILE_EXTENSION
#define SRON_FUNCTION_LIB_FILE_PATH                                   "meta/__function_lib"
#define SRON_DOCS_LINK                                                "https://sron.gitbook.io"
#define SRON_ERROR_MESSAGE_FILE_PATH                                  "meta/Errors/"
#define SRON_EXCEPTION_MESSAGE_FILE_PATH                              "meta/Exceptions/"
#define SRON_VERSION_MESSAGE                                          "\n+----------------------------+"\
                                                                      "\n|      SRON version 2.3      |"\
                                                                      "\n|   @Author: Saksham Joshi   |"\
                                                                      "\n+----------------------------+"


static_assert( sizeof(TokenCache_t) >= sizeof(BytecodeVariable_t)     ,  "size of TokenCache_t must be larger than sizeof BytecodeVariable_t so that TokenCache_t can hold all values of BytecodeVariable_t without overflow");

static_assert( sizeof(TokenCache_t) >= sizeof(SronInBuiltFncIndex_t)  ,  "size of TokenCache_t must be larger than sizeof SronInBuiltFncIndex_t so that TokenCache_t can hold all values of SronInBuiltFncIndex_t without overflow");

static_assert( sizeof(TokenCache_t) >= sizeof(BytecodeCount_t)        ,  "size of TokenCache_t must be larger than size of ByteCount_t so that TokenCache_t can hold all values ofBytecodeCount_t without overflow");

struct SronBytecodeMeta 
{
    BytecodeVersion_t _version;
    Hash_t _safety_hash;

    [[gnu::leaf]] [[gnu::always_inline]] bool matchMeta( const SronBytecodeMeta& __other ) noexcept 
    {
        #ifdef SRON_DEVELOPMENT_PHASE
            printf("\n Version= %lf\t Hash= %llu \n> Version= %lf\t Hash= %llu", this->_version, this->_safety_hash, __other._version, __other._safety_hash);
        #endif
        return ( this->_version == __other._version && this->_safety_hash == __other._safety_hash );
    }
};



struct IndexAndHash
{
    Hash_t _hash;
    SronInBuiltFncIndex_t _index;

    constexpr inline IndexAndHash( Hash_t __hash , SronInBuiltFncIndex_t __index = 0) :
     _hash( __hash ) , _index( __index )  {    } 

    
    constexpr inline bool operator<(const IndexAndHash& __other ) const noexcept 
    {
        return this->_hash < __other._hash;
    }

    constexpr inline bool operator<=(const IndexAndHash& __other ) const noexcept 
    {
        return this->_hash <= __other._hash;
    }

    constexpr inline bool operator>(const IndexAndHash& __other ) const noexcept 
    {
        return this->_hash > __other._hash;
    }

    constexpr inline bool operator>=(const IndexAndHash& __other ) const noexcept 
    {
        return this->_hash >= __other._hash;
    }

    constexpr inline bool operator==(const IndexAndHash& __other ) const noexcept 
    {
        return this->_hash == __other._hash;
    }

    constexpr inline bool operator!=(const IndexAndHash& __other ) const noexcept 
    {
        return this->_hash != __other._hash;
    }
};

#define CREATE_SRON_EXCEPTION( __name )  constexpr static const char*const __name##Exception   =   #__name   "Exception"
#define CREATE_SRON_ERROR(     __name )  constexpr static const char*const __name##Error       =   #__name   "Error"

#define GET_SRON_BOOL_STRING(  __val  ) (__val ? TRUE_STRING_PRINT_FORMAT : FALSE_STRING_PRINT_FORMAT )


#define SRON_CMD_OBUFFER_CLEAR              0
#define SRON_CMD_IS_OBUFFER_EMPTY           1
#define SRON_CMD_SIZEOF_OBUFFER             2
#define SRON_CMD_IS_FILE_AVAILABLE          3
#define SRON_CMD_GC_STACK_LEN               4
#define SRON_CMD_IS_BYTECODE_CACHED         5
#define SRON_CMD_NO_OF_BYTECODE_CACHED      6

#endif