
#pragma once

#ifndef _SRON_STD_HASH_H_
#define _SRON_STD_HASH_H_

#include <string>
#include <string_view>
#include "_bytecode_components_.hpp"
#include "_xxhash_.hpp"

struct SronHasher
{
    private:
        Hash_t hash_value;

        constexpr inline static Hash_t generateHash( const char* __str) noexcept 
        {
            return xxh64::hash( __str, std::string_view(__str).length() ,0);
            //return std::hash<std::string_view>()( __str );
        }

    public:
        constexpr inline SronHasher(const Hash_t __hash_value = 0) : hash_value(__hash_value) {}

        inline SronHasher(const char *const __str = "") : hash_value( SronHasher::generateHash( __str ) ) {  }

        inline SronHasher(const std::string &__str) : hash_value( SronHasher::generateHash(__str.c_str())) {}

        inline bool operator==(const char *const __other) const noexcept
        {
            return this->hash_value == generateHash(__other);
        }

        constexpr inline bool operator==(const SronHasher &__other) const noexcept
        {
            return this->hash_value == __other.hash_value;
        }

        constexpr inline bool operator!=(const SronHasher &__other) const noexcept
        {
            return this->hash_value != __other.hash_value;
        }

        constexpr inline bool operator<(const SronHasher &__other) const noexcept
        {

            return this->hash_value < __other.hash_value;
        }

        constexpr inline bool operator<=(const SronHasher &__other) const noexcept
        {

            return this->hash_value <= __other.hash_value;
        }

        constexpr inline bool operator>(const SronHasher &__other) const noexcept
        {

            return this->hash_value > __other.hash_value;
        }

        constexpr inline bool operator>=(const SronHasher &__other) const noexcept
        {

            return this->hash_value >= __other.hash_value;
        }

        constexpr inline Hash_t GET() const noexcept
        {
            return this->hash_value;
        }

        struct HashFunction
        {

            constexpr inline Hash_t operator()(const SronHasher &__) const noexcept
            {
                return __.hash_value;
            }
        };
};

#endif