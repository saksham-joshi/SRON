#pragma once 

#ifdef _WIN64
    #pragma comment(linker, "/STACK:16777216,16777216")
#endif

#ifndef _SRON_BYTECODE_COMPONENTS_H_
#define _SRON_BYTECODE_COMPONENTS_H_

#include "_cli_colors_.hpp"

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
#define SRON_OFFICIAL_EMAIL                                           "sron.language@gmail.com"
#define SRON_GITHUB_REPO                                              "https://github.com/saksham-joshi/SRON"
#define SRON_ERROR_MESSAGE_FILE_PATH                                  "meta/Errors/"
#define SRON_EXCEPTION_MESSAGE_FILE_PATH                              "meta/Exceptions/"

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

#define GET_SRON_BOOL_STRING(  __val  ) (__val ? TRUE_STRING_PRINT_FORMAT : FALSE_STRING_PRINT_FORMAT )


#define SRON_CMD_OBUFFER_CLEAR              0
#define SRON_CMD_IS_OBUFFER_EMPTY           1
#define SRON_CMD_SIZEOF_OBUFFER             2
#define SRON_CMD_IS_FILE_AVAILABLE          3
#define SRON_CMD_GC_STACK_LEN               4
#define SRON_CMD_IS_BYTECODE_CACHED         5
#define SRON_CMD_NO_OF_BYTECODE_CACHED      6

#define MAX_SRON_INT                        ((SronInt_t)9223372036854775807)
#define MAX_SRON_DOUBLE                     ((SronDouble_t)1.79769e+308)
#define MAX_SRON_CHAR                       ((SronChar_t)255)

#define MIN_SRON_INT                        ((SronInt_t)-9223372036854775808)
#define MIN_SRON_DOUBLE                     ((SronDouble_t)2.22507e-308)
#define MIN_SRON_CHAR                       ((SronChar_t)0)

#ifdef _WIN64
    #define SRON_SIGBREAK_MESSAGE CLI_DESIGN_RESET CLI_COLOR_RED CLI_DESIGN_BOLD "\n" \
            "╭────────────────────────╮\n"  \
            "│  🛑 SIGBREAK DETECTED  │\n"  \
            "│────────────────────────│\n"  \
            "│  Ctrl+Enter Detected   │\n"  \
            "│     Terminating...     │\n"  \
            "╰────────────────────────╯\n" CLI_DESIGN_RESET

    #define SRON_SIGTERM_MESSAGE CLI_DESIGN_RESET CLI_COLOR_RED CLI_DESIGN_BOLD "\n" \
            "╭────────────────────────╮\n"  \
            "│    SIGTERM DETECTED    │\n"  \
            "│────────────────────────│\n"  \
            "│       Gracefully       │\n"  \
            "│     Terminating...     │\n"  \
            "╰────────────────────────╯\n" CLI_DESIGN_RESET
#elifdef __linux__

    #define SRON_SIGKILL_MESSAGE CLI_DESIGN_RESET CLI_COLOR_RED CLI_DESIGN_BOLD "\n" \
            "╭────────────────────────╮\n"  \
            "│    SIGKILL DETECTED    │\n"  \
            "│────────────────────────│\n"  \
            "│       Gracefully       │\n"  \
            "│     Terminating...     │\n"  \
            "╰────────────────────────╯\n" CLI_DESIGN_RESET
#else
    #error "Cannot detect your Operating system"
#endif

#define SRON_SIGINT_MESSAGE CLI_DESIGN_RESET CLI_COLOR_RED CLI_DESIGN_BOLD "\n" \
        "╭────────────────────────╮\n"  \
        "│   🛑 SIGINT DETECTED   │\n"  \
        "│────────────────────────│\n"  \
        "│    Ctrl+C Detected     │\n"  \
        "│     Terminating...     │\n"  \
        "╰────────────────────────╯\n" CLI_DESIGN_RESET

#define SRON_SIGABRT_MESSAGE CLI_DESIGN_RESET CLI_COLOR_RED CLI_DESIGN_BOLD "\n" \
        "╭────────────────────────╮\n"  \
        "│    SIGABRT DETECTED    │\n"  \
        "│────────────────────────│\n"  \
        "│  Found Internal Error  │\n"  \
        "│      Aborting...       │\n"  \
        "╰────────────────────────╯\n" CLI_DESIGN_RESET

#define SRON_SIGSEGV_MESSAGE CLI_DESIGN_RESET CLI_COLOR_RED CLI_DESIGN_BOLD "\n" \
        "╭───────────────────────────────────────╮\n"  \
        "│           SIGSEGV DETECTED            │\n"  \
        "│───────────────────────────────────────│\n"  \
        "│          Segmentation Fault           │\n"  \
        "│                                       │\n"  \
        "│            Report this at             │\n"  \
        "│ " SRON_GITHUB_REPO " │\n"  \
        "│           ────────────────            │\n"  \
        "│           Terminating...              │\n"  \
        "╰───────────────────────────────────────╯\n" CLI_DESIGN_RESET

#define SRON_SIGUNKNOWN_MESSAGE CLI_DESIGN_RESET CLI_COLOR_RED CLI_DESIGN_BOLD "\n" \
        "╭────────────────────────╮\n"  \
        "│     UNKNOWN SIGNAL     │\n"  \
        "│────────────────────────│\n"  \
        "│     Terminating...     │\n"  \
        "╰────────────────────────╯\n" CLI_DESIGN_RESET


#define SRON_VERSION_MESSAGE_PRIMARY_DESIGN               CLI_DESIGN_RESET CLI_COLOR_WHITE CLI_DESIGN_BOLD CLI_BG_RGB(41,44,81)
#define SRON_VERSION_MESSAGE_TEXT_DESIGN(__text)          CLI_DESIGN_RESET CLI_DESIGN_ITALIC CLI_BG_RGB(41,44,81) CLI_COLOR_RGB(2, 214, 214) __text  CLI_DESIGN_RESET SRON_VERSION_MESSAGE_PRIMARY_DESIGN

#define SRON_VERSION_DESIGN                               SRON_VERSION_MESSAGE_TEXT_DESIGN("Version: " SRON_VERSION_STRING)
#define SRON_AUTHOR_NAME_DESIGN                           SRON_VERSION_MESSAGE_TEXT_DESIGN("Developer: SAKSHAM JOSHI")


#define SRON_VERSION_MESSAGE           "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "╔════════════════════════════════════════════╗" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║                                            ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║     ███████ ██████  ████████ ███    ██     ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║     ██      ██   ██ ██    ██ ████   ██     ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║     ██      ██   ██ ██    ██ ████   ██     ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║     ███████ ██████  ██    ██ ██ ██  ██     ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║          ██ ██   ██ ██    ██ ██  ██ ██     ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║          ██ ██   ██ ██    ██ ██  ██ ██     ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║     ███████ ██   ██ ████████ ██   ████     ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║                                            ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║────────────────────────────────────────────║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║                " SRON_VERSION_DESIGN "                ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║        🔰 " SRON_AUTHOR_NAME_DESIGN "         ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║────────────────────────────────────────────║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║                                            ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║  Documentation                             ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║  ╰─" SRON_VERSION_MESSAGE_TEXT_DESIGN(SRON_DOCS_LINK) "                 ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║                                            ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║  Contact                                   ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║  ╰─" SRON_VERSION_MESSAGE_TEXT_DESIGN(SRON_OFFICIAL_EMAIL) "                 ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║                                            ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║  Source Code                               ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║  ╰─" SRON_VERSION_MESSAGE_TEXT_DESIGN(SRON_GITHUB_REPO) "   ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "║                                            ║" CLI_DESIGN_RESET "\n"\
                                       SRON_VERSION_MESSAGE_PRIMARY_DESIGN "╚════════════════════════════════════════════╝" CLI_DESIGN_RESET "\n"

#endif