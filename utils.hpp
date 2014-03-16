#ifndef __2048_UTILS__
#define __2048_UTILS__

#include <random>
#include <algorithm>

// How large to make the grid
static const int grid_size = 4;

// What value to set the first tile as
static const int initial_value = 2;

// How many tiles should have values at the start
static const int initial_slot_count = 2;

// How many empty slots get a value after every turn
static const int round_slot_count = 1;

// Fixed values, probably shouldn't change.
enum class direction
{
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
    CHEAT,
    GODCHEAT
};

static const int action_count = 4;

// Mersenne twister random generator
std::mt19937& rand_gen();

// Gives a random position from [0, grid_size)
int rand_pos();

// Gives a random action from [0, action_count)
direction rand_action();

#endif
