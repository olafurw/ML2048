#ifndef __2048_UTILS__
#define __2048_UTILS__

#include <random>
#include <algorithm>
#include <chrono>

// How large to make the grid
static const int grid_size = 4;

// Seed
static const auto seed = std::chrono::system_clock::now().time_since_epoch().count();

// What value to set the first tile as
static const int initial_value = 2;

// How many tiles should have values at the start
static const int initial_slot_count = 2;

// The % that an initial value will be double
static const int initial_double_value_percent = 10;

// How many empty slots get a value after every turn
static const int round_slot_count = 1;

// Fixed values, probably shouldn't change.
enum class direction
{
    NORTH = 0,
    SOUTH,
    EAST,
    WEST
};

static const int action_count = 4;

// Mersenne twister random generator
std::mt19937& rand_gen();

// Gives a random position from [0, grid_size)
int rand_pos();

// Returns true if you should double the initial value
bool double_initial_value();

// Gives a random action from [0, action_count)
direction rand_action();

#endif
