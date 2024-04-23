#include <string>
#include <algorithm>
#include "_exception_.hpp"

#ifndef STRING_H
#define STRING_H

/*
 * String Class - this class includes static function which can help you easily work on string and perfomr manipulations.

 * It includes these functions :

 * 1. STRIP
 * 2. CONCAT
 * 3. AT
 * 4. CAPITALIZE
 * 5. SUBSTRING
 * 6. LEN
 * 7. CLEAR
 * 8. COPY
 * 9. REVERSE
 * 10. COUNT
 * 11. REPLACE
 * 12. SPLIT
 * 13. TO_LOWERCASE
 * 14. TO_UPPERCASE
*/

inline namespace SronString
{

    inline static long long int COUNT(const std::string &, const std::string &);
    inline static long long int COUNT(const std::string &, char &);

    inline static std::string CAPITALIZE(std::string);

    //inline static std::string REPLACE(const std::string &, const std::string &, const std::string &);
    inline static std::string REVERSE(std::string);

    inline static std::string STRIP(std::string);
    inline static std::string SUBSTRING(const std::string &, long long int &, long long int &);

    inline static std::string TO_LOWERCASE(std::string);
    inline static std::string TO_UPPERCASE(std::string);

    /*
    =========================================================================
                    Implementation start from here
    */

    inline static std::string STRIP(std::string str)
    {
        // Find the first non-whitespace character from the left
        auto left = std::find_if_not(str.begin(), str.end(), [](unsigned char c)
                                     { return std::isspace(c); });

        // Find the first non-whitespace character from the right
        auto right = std::find_if_not(str.rbegin(), str.rend(), [](unsigned char c)
                                      { return std::isspace(c); })
                         .base();

        // If all characters are whitespace, return an empty string
        if (left == str.end() || right == str.begin())
            return "";

        return std::string(left, right);
    }

    // this function will capitalize the std::string
    inline static std::string CAPITALIZE(std::string str)
    {
        std::string::iterator c = str.begin();

        if (str.length() > 0)
        {
            *c = std::toupper(*c);
        }

        ++c;

        // Iterate over each character in the string
        for (; c < str.end(); ++c)
        {
            *c = std::tolower(*c);
        }
        return str;
    }

    inline static std::string SUBSTRING(const std::string &str, long long int &start, long long int &end)
    {
        if (start > end)
        {
            DISPLAY_EXCEPTION("extracting the substring. The exception is thrown because second argument is of type 'Int' and is larger than third argument.", NoException);
        }
        return std::string(str.begin() + start, str.begin() + end);
    }

    inline static std::string REVERSE(std::string str)
    {
        std::reverse(str.begin(), str.end());
        return str;
    }

    // function to search and count the numnber of occurrences of a string in another string
    inline static long long int COUNT(const std::string &str, const std::string &sample)
    {
        if (sample.empty() || str.length() < sample.length())
        {
            return 0; // If the sample string is empty, return 0
        }

        long long int count = 0;
        size_t pos = 0;

        while ((pos = str.find(sample, pos)) != std::string::npos)
        {
            ++count;
            pos += sample.size(); // Move to the next position after the current match
        }

        return count;
    }

    inline static long long int COUNT(const std::string &str, char &sample)
    {
        long long int count = 0;

        for (const char &c : str)
        {
            count += (c == sample) ? 1 : 0;
        }

        return count;
    }

    // inline static std::string REPLACE(std::string str, const std::string &str_to_be_replaced, const std::string &str_replacement)
    // {
    //     std::string result = str;

    //     if (str_to_be_replaced.empty())
    //     {
    //         return result;
    //     }

    //     size_t pos = 0;

    //     // Find and replace all occurrences of the substring
    //     while ((pos = result.find(str_to_be_replaced, pos)) != std::string::npos)
    //     {
    //         result.replace(pos, str_to_be_replaced.length(), str_replacement); // Replace the occurrence
    //         pos += str_replacement.length();                                   // Move the position to after the replacement
    //     }

    //     return result;
    // }

    inline static std::string TO_LOWERCASE(std::string str)
    {
        for (auto &i : str)
        {
            i = std::tolower(i);
        }
        return str;
    }

    inline static std::string TO_UPPERCASE(std::string str)
    {
        for (auto &i : str)
        {
            i = std::toupper(i);
        }
        return str;
    }
}

#endif