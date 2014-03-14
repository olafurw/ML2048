#include "utils.hpp"

#include <chrono>

std::mt19937& rand_gen()
{
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    return gen;
}

int rand_pos()
{
    return static_cast<int>(rand_gen()() % grid_size);
}

int rand_action()
{
    return static_cast<int>(rand_gen()() % action_count);
}
