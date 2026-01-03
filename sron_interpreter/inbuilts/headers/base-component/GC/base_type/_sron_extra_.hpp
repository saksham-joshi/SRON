#ifndef _EXTRA_H_
#define _EXTRA_H_

#include "_datatypes_.hpp"

namespace SronExtra
{
    inline static bool doesFileExists( const std::string_view& __path )
    {
        return std::filesystem::exists( __path );
    }

    inline static const char* typenumToString( SronTypeNum __type ) noexcept
    {
        switch( __type )
        {
            case SronTypeNum::TYPE_VOID : return "Void";

            case SronTypeNum::TYPE_INT : return "Int";

            case SronTypeNum::TYPE_DOUBLE : return "Double";

            case SronTypeNum::TYPE_CHAR : return "Char";

            case SronTypeNum::TYPE_BOOL : return "Bool";

            case SronTypeNum::TYPE_STRING : return "String";

            case SronTypeNum::TYPE_LIST : return "List";

            case SronTypeNum::TYPE_FILE_READER : return "FileReader";

            case SronTypeNum::TYPE_FILE_WRITER : return "FileWriter";

            case SronTypeNum::TYPE_LITERAL_STR : return "LiteralString";

            case SronTypeNum::INVALID_TYPE : return "Invalid-Type";
        }
    }

    [[nodiscard]] [[using gnu:always_inline,hot]] inline static std::string_view duplicateString(const std::string_view& __filename)
    {
        const auto len = __filename.length();

        char* duplicate_str = new char[len + 1];

        SronSupport::copyMemory(duplicate_str, __filename.data(), len);

        duplicate_str[len] = '\0';

        return std::string_view(duplicate_str, len);
    }

    inline static long long countSubString(const std::string_view& __str, const std::string_view& __search)
    {
        if(__str.length() < __search.length() || __str.length() == 0 || __search.length() == 0) return 0;

        else if(__search.length() == 1) return std::count(__str.begin(), __str.end(), __search[0]);

        long long count = 0;

        auto start = __str.begin();
        const auto end = __str.end() - __search.length() + 1;

        auto search_it = __search.begin();
        const auto search_end = __search.end();

        while(start < end)
        {
            if(*start == *search_it)
            {
                // Searching inside the substring
                auto it = search_it + 1;
                auto jt = start + 1;
                
                while(it < search_end && jt != __str.end() && *it == *jt)
                {
                    ++it;
                    ++jt;
                }
                
                // If we matched the entire search string
                if(it == search_end)
                {
                    ++count;
                }
            }

            ++start;
        }
        
        return count;
    }

    constexpr const char*const TERMINAL_RESET_STRING = "\033[0m" 

    #ifdef _WIN64
        "";
    #else
        "\n";
    #endif
}
#endif