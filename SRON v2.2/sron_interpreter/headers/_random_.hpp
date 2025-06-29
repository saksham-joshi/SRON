#ifndef RANDOM_H
#define RANDOM_H

#include <random>

namespace SronRandom
{
    inline static std::mt19937_64& GET_GENERATOR()
    {
        static std::random_device rd;
        static std::mt19937_64 gen(rd());
        return gen;
    }

    // Function to generate long long int type random number
    inline static long long int GENERATE_RANDOM_INT()
    {

        static std::uniform_int_distribution<long long int> dis;

        return dis(GET_GENERATOR());
    }

    // Function to generate a double type random number
    inline static double GENERATE_RANDOM_DOUBLE()
    {
        static std::uniform_real_distribution<double> dis;

        return dis(GET_GENERATOR());
    }

    // Function to generate a random number of long long int type between two given numbers
    inline static long long GENERATE_RANDOM_INT_RANGE(long long int lower, long long int upper)
    {
        static std::uniform_int_distribution<long long int> dis(lower, upper);

        return dis(GET_GENERATOR());
    }

    // Function to generate a random number of double type between two given numbers
    inline static double GENERATE_RANDOM_DOUBLE_RANGE(double lower, double upper)
    {
        static std::uniform_real_distribution<double> dis(lower, upper);

        return dis(GET_GENERATOR());
    }
}

#endif