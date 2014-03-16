#include "utils.hpp"

std::mt19937& rand_gen()
{
    static std::mt19937 gen(seed);
    return gen;
}

int rand_pos()
{
    static std::uniform_int_distribution<> dis(0, grid_size - 1);

    return dis(rand_gen());
}

direction rand_action()
{
    static std::uniform_int_distribution<> dis(0, action_count - 1);

    return static_cast<direction>(dis(rand_gen()));
}
