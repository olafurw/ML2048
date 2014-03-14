#ifndef __2048_UTILS__
#define __2048_UTILS__

#include <random>

static const short grid_size = 2;
static const short initial_value = 2;
static const short initial_slot_count = 2;
static const short round_slot_count = 1;

static const short NORTH = 0;
static const short SOUTH = 1;
static const short EAST = 2;
static const short WEST = 3;
static const short action_count = 4;

std::mt19937& rand_gen();
short rand_pos();
short rand_action();

#endif
