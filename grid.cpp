#include "grid.hpp"

#include <iostream>
#include <algorithm>

// Clear the board and add 2 numbers
grid::grid()
{
    m_score = 0;

    reset();
    init(initial_slot_count);
}

// Sets all values to 0
void grid::reset()
{
    for(int x = 0; x < grid_size; ++x)
    {
        for(int y = 0; y < grid_size; ++y)
        {
            m_grid[y][x] = 0;
        }
    }
}

// Sets count values of 2 onto the board in an empty slot
void grid::init(int count)
{
    for(int i = 0; i < count; ++i)
    {
        int x = -1;
        int y = -1;

        random_empty_pos(x, y);

        if(x == -1 && y == -1)
        {
            return;
        }

        bool dbl = double_initial_value();

        m_grid[y][x] = (dbl ? (initial_value * initial_value) : initial_value);
    }
}

// Applies the actions to the grid
void grid::add_actions(std::vector<direction>& actions)
{
    for(direction a : actions)
    {
        action(a);
    }
}

void grid::print()
{
    for(int y = 0; y < grid_size; ++y)
    {
        for(int x = 0; x < grid_size; ++x)
        {
            std::cout << m_grid[y][x] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Returns true if the value is outside
inline bool grid::is_outside(const int x, const int y) const
{
    return (x < 0 || x >= grid_size || y < 0 || y >= grid_size);
}

// An action is a move, merge and then move the merged pieces and then add an new piece
bool grid::action(direction dir)
{
    bool a = move(dir);
    bool b = merge(dir);
    bool c = move(dir);

    if(a || b || c)
    {
        init(round_slot_count);
    }

    m_actions.push_back(dir);

    return a || b || c;
}

// Returns true if there is an available move
bool grid::can_move() const
{
    for(int x = 0; x < grid_size; ++x)
    {
        for(int y = 0; y < grid_size; ++y)
        {
            // Only need 1 empty space to move
            if(m_grid[y][x] == 0)
            {
                return true;
            }

            // Neighbor check
            int value = m_grid[y][x];

            int north = get(x, y - 1);
            if(value == north)
            {
                return true;
            }

            int south = get(x, y + 1);
            if(value == south)
            {
                return true;
            }

            int east = get(x - 1, y);
            if(value == east)
            {
                return true;
            }

            int west = get(x + 1, y);
            if(value == west)
            {
                return true;
            }
        }
    }

    // If we made it through, there are no empty slots or
    // slots with equal values next to it
    return false;
}

// Returns true if there is an empty slots anywhere
bool grid::has_empty() const
{
    for(int x = 0; x < grid_size; ++x)
    {
        for(int y = 0; y < grid_size; ++y)
        {
            if(m_grid[y][x] == 0)
            {
                return true;
            }
        }
    }

    return false;
}

// Get the value from x,y
inline int grid::get(const int& x, const int& y) const
{
    if(is_outside(x, y))
    {
        return -1;
    }

    return m_grid[y][x];
}

// Get the value from x,y
void grid::set(const int& x, const int& y, const int value)
{
    if(is_outside(x, y))
    {
        return;
    }

    m_grid[y][x] = value;
}

// Sum the score
unsigned int grid::score() const
{
    return m_score;
}

// Find the largest
int grid::largest() const
{
    int num = 0;
    for(int x = 0; x < grid_size; ++x)
    {
        for(int y = 0; y < grid_size; ++y)
        {
            int value = m_grid[y][x];
            if(value > num)
            {
                num = value;
            }
        }
    }

    return num;
}

int grid::size()
{
    return grid_size;
}

std::vector<direction> grid::actions() const
{
    return m_actions;
}

// Moves the tiles in the direction
// TODO: Refactor, works for now
bool grid::move(direction dir)
{
    bool movement = false;

    if(dir == direction::SOUTH)
    {
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = grid_size - 1; y >= 0; --y)
            {
                // Empty slots dont move
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                int newY = y;
                int nextY = y + 1;

                while(m_grid[nextY][x] == 0 && !is_outside(x, nextY))
                {
                    newY = nextY;

                    ++nextY;
                }

                if(newY != y)
                {
                    movement = true;
                }

                int value = m_grid[y][x];

                m_grid[y][x] = 0;
                m_grid[newY][x] = value;
            }
        }
    }
    if(dir == direction::NORTH)
    {
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                // Empty slots dont move
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                int newY = y;
                int nextY = y - 1;

                while(m_grid[nextY][x] == 0 && !is_outside(x, nextY))
                {
                    newY = nextY;

                    --nextY;
                }

                if(newY != y)
                {
                    movement = true;
                }

                int value = m_grid[y][x];

                m_grid[y][x] = 0;
                m_grid[newY][x] = value;
            }
        }
    }
    if(dir == direction::WEST)
    {
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                // Empty slots dont move
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                int newX = x;
                int nextX = x - 1;

                while(m_grid[y][nextX] == 0 && !is_outside(nextX, y))
                {
                    newX = nextX;

                    --nextX;
                }

                if(newX != x)
                {
                    movement = true;
                }

                int value = m_grid[y][x];

                m_grid[y][x] = 0;
                m_grid[y][newX] = value;
            }
        }
    }
    if(dir == direction::EAST)
    {
        for(int x = grid_size - 1; x >= 0; --x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                // Empty slots dont move
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                int newX = x;
                int nextX = x + 1;

                while(m_grid[y][nextX] == 0 && !is_outside(nextX, y))
                {
                    newX = nextX;

                    ++nextX;
                }

                if(newX != x)
                {
                    movement = true;
                }

                int value = m_grid[y][x];

                m_grid[y][x] = 0;
                m_grid[y][newX] = value;
            }
        }
    }

    return movement;
}

// Goes through and merges in that direction
bool grid::merge(direction dir)
{
    bool merging = false;

    if(dir == direction::SOUTH)
    {
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = grid_size - 1; y >= 0; --y)
            {
                // Empty slots dont merge
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                int nextY = y + 1;
                int value = m_grid[y][x];
                int merge_value = get(x, nextY);

                if(value == merge_value)
                {
                    int new_value = value + value;

                    m_grid[y][x] = 0;
                    m_grid[nextY][x] = new_value;

                    merging = true;

                    m_score += new_value;
                }
            }
        }

        return merging;
    }
    if(dir == direction::NORTH)
    {
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                // Empty slots dont merge
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                int nextY = y - 1;
                int value = m_grid[y][x];
                int merge_value = get(x, nextY);

                if(value == merge_value)
                {
                    int new_value = value + value;

                    m_grid[y][x] = 0;
                    m_grid[nextY][x] = new_value;

                    merging = true;

                    m_score += new_value;
                }
            }
        }

        return merging;
    }
    if(dir == direction::WEST)
    {
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                // Empty slots dont merge
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                int nextX = x - 1;
                int value = m_grid[y][x];
                int merge_value = get(nextX, y);

                if(value == merge_value)
                {
                    int new_value = value + value;

                    m_grid[y][x] = 0;
                    m_grid[y][nextX] = new_value;

                    merging = true;

                    m_score += new_value;
                }
            }
        }

        return merging;
    }
    if(dir == direction::EAST)
    {
        for(int x = grid_size - 1; x >= 0; --x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                // Empty slots dont merge
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                int nextX = x + 1;
                int value = m_grid[y][x];
                int merge_value = get(nextX, y);

                if(value == merge_value)
                {
                    int new_value = value + value;

                    m_grid[y][x] = 0;
                    m_grid[y][nextX] = new_value;

                    merging = true;

                    m_score += new_value;
                }
            }
        }

        return merging;
    }

    return merging;
}

// Sets the x and y with a random empty position
void grid::random_empty_pos(int& x, int& y)
{
    if(!has_empty())
    {
        return;
    }

    do
    {
        x = rand_pos();
        y = rand_pos();
    }
    while(!m_grid[y][x] == 0);
}
