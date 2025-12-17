
#pragma once

#ifndef _SRON_STD_HASH_H_
#define _SRON_STD_HASH_H_

#include <string>

struct SronHasher
{

private:
    size_t hash_value;

public:
    constexpr inline SronHasher(const size_t __hash_value = 0) : hash_value(__hash_value) {}

    inline SronHasher(const char *const &__str = "") : hash_value(std::hash<std::string>()(__str)) {  }

    inline SronHasher(const std::string &__str) : hash_value(std::hash<std::string>()(__str)) {}

    inline bool operator==(const char *const &__other) const noexcept
    {
        return this->hash_value == std::hash<std::string>()(__other);
    }

    constexpr inline bool operator==(const SronHasher &__other) const noexcept
    {
        return this->hash_value == __other.hash_value;
    }

    constexpr inline bool operator==(const unsigned short int __other) const noexcept
    {
        return this->hash_value == __other;
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

    constexpr inline size_t GET() const noexcept
    {
        return this->hash_value;
    }

    struct HashFunction
    {

        constexpr inline size_t operator()(const SronHasher &__) const noexcept
        {
            return __.hash_value;
        }
    };
};

#endif