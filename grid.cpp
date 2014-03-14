#include "grid.hpp"

#include <iostream>
#include <algorithm>

// Clear the board and add 2 numbers
grid::grid()
{
    reset();
    init(initial_slot_count);
}

// Sets all values to 0
void grid::reset()
{
    for(short x = 0; x < grid_size; ++x)
    {
        for(short y = 0; y < grid_size; ++y)
        {
            m_grid[y][x] = 0;
        }
    }
}

// Sets count values of 2 onto the board in an empty slot
void grid::init(short count)
{
    for(short i = 0; i < count; ++i)
    {
        short x = -1;
        short y = -1;

        random_empty_pos(x, y);

        if(x == -1 && y == -1)
        {
            return;
        }

        m_grid[y][x] = initial_value;
    }
}

void grid::print()
{
    for(short y = 0; y < grid_size; ++y)
    {
        for(short x = 0; x < grid_size; ++x)
        {
            std::cout << m_grid[y][x] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Returns true if the value is outside
inline bool grid::is_outside(const short& x, const short& y) const
{
    return (x < 0 || x >= grid_size || y < 0 || y >= grid_size);
}

// An action is a move, merge and then move the merged pieces and then add an new piece
void grid::action(short dir)
{
    bool a = move(dir);
    bool b = merge(dir);
    bool c = move(dir);

    if(a || b || c)
    {
        init(round_slot_count);
    }

    m_actions.push_back(dir);
}

// Returns true if there is an available move
bool grid::can_move() const
{
    for(short x = 0; x < grid_size; ++x)
    {
        for(short y = 0; y < grid_size; ++y)
        {
            // Only need 1 empty space to move
            if(m_grid[y][x] == 0)
            {
                return true;
            }

            // Neighbor check
            short value = m_grid[y][x];

            short north = get(x, y - 1);
            if(value == north)
            {
                return true;
            }

            short south = get(x, y + 1);
            if(value == south)
            {
                return true;
            }

            short east = get(x - 1, y);
            if(value == east)
            {
                return true;
            }

            short west = get(x + 1, y);
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
int grid::has_empty() const
{
    for(short x = 0; x < grid_size; ++x)
    {
        for(short y = 0; y < grid_size; ++y)
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
inline short grid::get(const short& x, const short& y) const
{
    if(is_outside(x, y))
    {
        return -1;
    }

    return m_grid[y][x];
}

// Sum the score
int grid::score() const
{
    int total = 0;
    for(short x = 0; x < grid_size; ++x)
    {
        for(short y = 0; y < grid_size; ++y)
        {
            total += m_grid[y][x];
        }
    }

    return total;
}

// Find the largest
short grid::largest() const
{
    short num = 0;
    for(short x = 0; x < grid_size; ++x)
    {
        for(short y = 0; y < grid_size; ++y)
        {
            short value = m_grid[y][x];
            if(value > num)
            {
                num = value;
            }
        }
    }

    return num;
}

std::vector<short> grid::actions() const
{
    return m_actions;
}

// Moves the tiles in the direction
// TODO: Refactor, works for now
bool grid::move(short dir)
{
    bool movement = false;

    if(dir == SOUTH)
    {
        for(short x = 0; x < grid_size; ++x)
        {
            for(short y = grid_size - 1; y >= 0; --y)
            {
                // Empty slots dont move
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                short newY = y;
                short nextY = y + 1;

                while(m_grid[nextY][x] == 0 && !is_outside(x, nextY))
                {
                    newY = nextY;

                    ++nextY;
                }

                if(newY != y)
                {
                    movement = true;
                }

                short value = m_grid[y][x];

                m_grid[y][x] = 0;
                m_grid[newY][x] = value;
            }
        }
    }
    if(dir == NORTH)
    {
        for(short x = 0; x < grid_size; ++x)
        {
            for(short y = 0; y < grid_size; ++y)
            {
                // Empty slots dont move
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                short newY = y;
                short nextY = y - 1;

                while(m_grid[nextY][x] == 0 && !is_outside(x, nextY))
                {
                    newY = nextY;

                    --nextY;
                }

                if(newY != y)
                {
                    movement = true;
                }

                short value = m_grid[y][x];

                m_grid[y][x] = 0;
                m_grid[newY][x] = value;
            }
        }
    }
    if(dir == WEST)
    {
        for(short x = 0; x < grid_size; ++x)
        {
            for(short y = 0; y < grid_size; ++y)
            {
                // Empty slots dont move
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                short newX = x;
                short nextX = x - 1;

                while(m_grid[y][nextX] == 0 && !is_outside(nextX, y))
                {
                    newX = nextX;

                    --nextX;
                }

                if(newX != x)
                {
                    movement = true;
                }

                short value = m_grid[y][x];

                m_grid[y][x] = 0;
                m_grid[y][newX] = value;
            }
        }
    }
    if(dir == EAST)
    {
        for(short x = grid_size - 1; x >= 0; --x)
        {
            for(short y = 0; y < grid_size; ++y)
            {
                // Empty slots dont move
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                short newX = x;
                short nextX = x + 1;

                while(m_grid[y][nextX] == 0 && !is_outside(nextX, y))
                {
                    newX = nextX;

                    ++nextX;
                }

                if(newX != x)
                {
                    movement = true;
                }

                short value = m_grid[y][x];

                m_grid[y][x] = 0;
                m_grid[y][newX] = value;
            }
        }
    }

    return movement;
}

// Goes through and merges in that direction
bool grid::merge(short dir)
{
    bool merging = false;

    if(dir == SOUTH)
    {
        for(short x = 0; x < grid_size; ++x)
        {
            for(short y = grid_size - 1; y >= 0; --y)
            {
                // Empty slots dont merge
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                short nextY = y + 1;
                short value = m_grid[y][x];
                short merge_value = get(x, nextY);

                if(value == merge_value)
                {
                    m_grid[y][x] = 0;
                    m_grid[nextY][x] = value + value;

                    merging = true;
                }
            }
        }

        return merging;
    }
    if(dir == NORTH)
    {
        for(short x = 0; x < grid_size; ++x)
        {
            for(short y = 0; y < grid_size; ++y)
            {
                // Empty slots dont merge
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                short nextY = y - 1;
                short value = m_grid[y][x];
                short merge_value = get(x, nextY);

                if(value == merge_value)
                {
                    m_grid[y][x] = 0;
                    m_grid[nextY][x] = value + value;

                    merging = true;
                }
            }
        }

        return merging;
    }
    if(dir == WEST)
    {
        for(short x = 0; x < grid_size; ++x)
        {
            for(short y = 0; y < grid_size; ++y)
            {
                // Empty slots dont merge
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                short nextX = x - 1;
                short value = m_grid[y][x];
                short merge_value = get(nextX, y);

                if(value == merge_value)
                {
                    m_grid[y][x] = 0;
                    m_grid[y][nextX] = value + value;

                    merging = true;
                }
            }
        }

        return merging;
    }
    if(dir == EAST)
    {
        for(short x = grid_size - 1; x >= 0; --x)
        {
            for(short y = 0; y < grid_size; ++y)
            {
                // Empty slots dont merge
                if(m_grid[y][x] == 0)
                {
                    continue;
                }

                short nextX = x + 1;
                short value = m_grid[y][x];
                short merge_value = get(nextX, y);

                if(value == merge_value)
                {
                    m_grid[y][x] = 0;
                    m_grid[y][nextX] = value + value;

                    merging = true;
                }
            }
        }

        return merging;
    }

    return merging;
}

// Sets the x and y with a random empty position
void grid::random_empty_pos(short& x, short& y)
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
