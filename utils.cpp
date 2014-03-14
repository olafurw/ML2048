#include "utils.hpp"

#include <chrono>

std::mt19937& rand_gen()
{
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    return gen;
}

short rand_pos()
{
    return static_cast<short>(rand_gen()() % grid_size);
}
