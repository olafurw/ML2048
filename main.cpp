// A very rough C++ version for the 2048 game
//
// Author: Olafur Waage / @olafurw
// olafurw@gmail.com
//
// Under the Apache License
// If you have any fun with this, please let me know, I would love to hear from you.

#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

static const int grid_size = 4;

// Use int so i can ask for random directions
static const int NORTH = 0;
static const int SOUTH = 1;
static const int EAST = 2;
static const int WEST = 3;

std::mt19937& rand_gen()
{
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    return gen;
}

int rand_pos()
{
    return static_cast<int>(rand_gen()() % 4);
}

class grid
{
public:
    // Clear the board and add 2 numbers
    grid()
    {
        reset();
        init(2);
    }

    // Sets all values to 0
    void reset()
    {
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                set(x, y, 0);
            }
        }
    }

    // Sets count values of 2 onto the board in an empty slot
    void init(int count)
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

            set(x, y, 2);
        }
    }

    void print()
    {
        for(int y = 0; y < grid_size; ++y)
        {
            for(int x = 0; x < grid_size; ++x)
            {
                std::cout << get(x, y) << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Returns true if a space is empty
    inline bool is_empty(const int& x, const int& y) const
    {
        return get(x, y) == 0;
    }

    // Returns true if the value is outside
    inline bool is_outside(const int& x, const int& y) const
    {
        return (x < 0 || x >= grid_size || y < 0 || y >= grid_size);
    }

    // Returns true if the value is on the edge
    inline bool is_edge(const int& x, const int& y) const
    {
        return x == 0 || x == (grid_size - 1) || y == 0 || y == (grid_size - 1);
    }

    // An action is a move, merge and then move the merged pieces and then add an new piece
    void action(int dir)
    {
        bool a = move(dir);
        bool b = merge(dir);
        bool c = move(dir);

        if(a || b || c)
        {
            init(1);
        }
    }

    // Returns true if there is an available move
    bool can_move() const
    {
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                // Only need 1 empty space to move
                if(is_empty(x, y))
                {
                    return true;
                }

                // Neighbor check
                int value = get(x, y);

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
    int has_empty() const
    {
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                if(is_empty(x, y))
                {
                    return true;
                }
            }
        }

        return false;
    }

    // Get the value from x,y
    int get(const int& x, const int& y) const
    {
        if(is_outside(x, y))
        {
            return -1;
        }

        return m_grid[y][x];
    }

    // Set the value to x,y
    void set(const int& x, const int& y, const int value)
    {
        if(is_outside(x, y))
        {
            return;
        }

        m_grid[y][x] = value;
    }

    // Sum the score
    int score() const
    {
        int total = 0;
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                total += get(x, y);
            }
        }

        return total;
    }

    // Find the largest
    int largest() const
    {
        int num = 0;
        for(int x = 0; x < grid_size; ++x)
        {
            for(int y = 0; y < grid_size; ++y)
            {
                int value = get(x, y);
                if(value > num)
                {
                    num = value;
                }
            }
        }

        return num;
    }

private:
    // Moves the tiles in the direction
    // TODO: Refactor, works for now
    bool move(int dir)
    {
        bool movement = false;

        if(dir == SOUTH)
        {
            for(int x = 0; x < grid_size; ++x)
            {
                for(int y = grid_size - 1; y >= 0; --y)
                {
                    // Empty slots dont move
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int newY = y;

                    while(is_empty(x, newY + 1) && !is_outside(x, newY + 1))
                    {
                        newY++;
                    }

                    movement = newY != y;

                    int value = get(x, y);

                    set(x, y, 0);
                    set(x, newY, value);
                }
            }
        }
        if(dir == NORTH)
        {
            for(int x = 0; x < grid_size; ++x)
            {
                for(int y = 0; y < grid_size; ++y)
                {
                    // Empty slots dont move
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int newY = y;

                    while(is_empty(x, newY - 1) && !is_outside(x, newY - 1))
                    {
                        newY--;
                    }

                    movement = newY != y;

                    int value = get(x, y);

                    set(x, y, 0);
                    set(x, newY, value);
                }
            }
        }
        if(dir == WEST)
        {
            for(int x = 0; x < grid_size; ++x)
            {
                for(int y = 0; y < grid_size; ++y)
                {
                    // Empty slots dont move
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int newX = x;

                    while(is_empty(newX - 1, y) && !is_outside(newX - 1, y))
                    {
                        newX--;
                    }

                    movement = newX != x;

                    int value = get(x, y);

                    set(x, y, 0);
                    set(newX, y, value);
                }
            }
        }
        if(dir == EAST)
        {
            for(int x = grid_size - 1; x >= 0; --x)
            {
                for(int y = 0; y < grid_size; ++y)
                {
                    // Empty slots dont move
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int newX = x;

                    while(is_empty(newX + 1, y) && !is_outside(newX + 1, y))
                    {
                        newX++;
                    }

                    movement = newX != x;

                    int value = get(x, y);

                    set(x, y, 0);
                    set(newX, y, value);
                }
            }
        }

        return movement;
    }

    // Goes through and merges in that direction
    bool merge(int dir)
    {
        bool merging = false;

        if(dir == SOUTH)
        {
            for(int x = 0; x < grid_size; ++x)
            {
                for(int y = grid_size - 1; y >= 0; --y)
                {
                    // Empty slots dont merge
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int value = get(x, y);
                    int merge_value = get(x, y + 1);

                    if(value == merge_value)
                    {
                        set(x, y, 0);
                        set(x, y + 1, value + value);

                        merging = true;
                    }
                }
            }

            return merging;
        }
        if(dir == NORTH)
        {
            for(int x = 0; x < grid_size; ++x)
            {
                for(int y = 0; y < grid_size; ++y)
                {
                    // Empty slots dont merge
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int value = get(x, y);
                    int merge_value = get(x, y - 1);

                    if(value == merge_value)
                    {
                        set(x, y, 0);
                        set(x, y - 1, value + value);

                        merging = true;
                    }
                }
            }

            return merging;
        }
        if(dir == WEST)
        {
            for(int x = 0; x < grid_size; ++x)
            {
                for(int y = 0; y < grid_size; ++y)
                {
                    // Empty slots dont merge
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int value = get(x, y);
                    int merge_value = get(x - 1, y);

                    if(value == merge_value)
                    {
                        set(x, y, 0);
                        set(x - 1, y, value + value);

                        merging = true;
                    }
                }
            }

            return merging;
        }
        if(dir == EAST)
        {
            for(int x = grid_size - 1; x >= 0; --x)
            {
                for(int y = 0; y < grid_size; ++y)
                {
                    // Empty slots dont merge
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int value = get(x, y);
                    int merge_value = get(x + 1, y);

                    if(value == merge_value)
                    {
                        set(x, y, 0);
                        set(x + 1, y, value + value);

                        merging = true;
                    }
                }
            }

            return merging;
        }

        return merging;
    }

    // Sets the x and y with a random empty position
    void random_empty_pos(int& x, int& y)
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
        while(!is_empty(x, y));
    }

    int m_grid[grid_size][grid_size];
};

int main()
{
    // Init grid
    int largest = 0;

    while(true)
    {
        grid g;

        while(g.can_move())
        {
            g.action(rand_pos());
        }

        int large = g.largest();

        if(large > largest)
        {
            std::cout << large << std::endl;
            largest = large;
        }

        if(large >= 2048)
        {
            g.print();
            break;
        }
    }

    return 0;
}
