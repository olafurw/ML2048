#ifndef __2048_UTILS__
#define __2048_UTILS__

#include <random>
#include <algorithm>

// How large to make the grid
static const short grid_size = 4;

// What value to set the first tile as
static const short initial_value = 2;

// How many tiles should have values at the start
static const short initial_slot_count = 2;

// How many empty slots get a value after every turn
static const short round_slot_count = 1;

// Fixed values, probably shouldn't change.
static const short NORTH = 0;
static const short SOUTH = 1;
static const short EAST = 2;
static const short WEST = 3;
static const short action_count = 4;

// Mersenne twister random generator
std::mt19937& rand_gen();

// Gives a random position from [0, grid_size)
short rand_pos();

// Gives a random action from [0, action_count)
short rand_action();

#endif
