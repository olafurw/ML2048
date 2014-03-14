#ifndef __2048_GRID__
#define __2048_GRID__

// A very rough C++ version for the 2048 game
//
// Author: Olafur Waage / @olafurw
// olafurw@gmail.com
//
// Under the Apache License
// If you have any fun with this, please let me know, I would love to hear from you.

#include "utils.hpp"
#include <vector>

class grid
{
public:
    // Clear the board and add 2 numbers
    grid();

    // Sets all values to 0
    void reset();

    // Applies the actions to the grid
    void add_actions(std::vector<direction>& actions);

    void print();

    // An action is a move, merge and then move the merged pieces and then add an new piece
    void action(direction dir);

    // Returns true if there is an available move
    bool can_move() const;

    // Returns true if there is an empty slots anywhere
    bool has_empty() const;

    // Get the value from x,y
    inline int get(const int& x, const int& y) const;

    // Sum the score
    int score() const;

    // Find the largest
    int largest() const;

    // Returns the actions the grid has performed
    std::vector<direction> actions() const;

    // Returns the size of the grid
    static int size();

private:
    // Sets count values of 2 onto the board in an empty slot
    void init(int count);

    // Moves the tiles in the direction
    // TODO: Refactor, works for now
    bool move(direction dir);

    // Goes through and merges in that direction
    bool merge(direction dir);
    
    // Returns true if the value is outside
    inline bool is_outside(const int x, const int y) const;

    // Sets the x and y with a random empty position
    void random_empty_pos(int& x, int& y);

    int m_grid[grid_size][grid_size];

    std::vector<direction> m_actions;
};

#endif
