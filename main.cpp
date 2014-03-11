#include <iostream>
#include <random>
#include <algorithm>
#include <chrono>

static const int grid_size = 4;

enum class direction
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

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
    grid()
    {
        reset();
        init();
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

    // Sets two values of 2 onto the board
    void init()
    {
        for(int i = 0; i < 6; ++i)
        {
            int x = 0;
            int y = 0;

            random_empty_pos(x, y);

            set(x, y, i + 1);
        }
    }

    void print()
    {
        for(int y = 0; y < grid_size; ++y)
        {
            for(int x = 0; x < grid_size; ++x)
            {
                std::cout << get(x, y) << " ";
            }
            std::cout << std::endl;
        }
    }

    // Returns true if a space is empty
    inline bool is_empty(const int& x, const int& y) const
    {
        return get(x, y) == 0;
    }

    inline bool is_outside(const int& x, const int& y) const
    {
        return (x < 0 || x >= grid_size || y < 0 || y >= grid_size);
    }

    inline bool is_edge(const int& x, const int& y) const
    {
        return x == 0 || x == (grid_size - 1) || y == 0 || y == (grid_size - 1);
    }

    void move(direction dir)
    {
        if(dir == direction::SOUTH)
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

                    int value = get(x, y);

                    set(x, y, 0);
                    set(x, newY, value);
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
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int newY = y;

                    while(is_empty(x, newY - 1) && !is_outside(x, newY - 1))
                    {
                        newY--;
                    }

                    int value = get(x, y);

                    set(x, y, 0);
                    set(x, newY, value);
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
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int newX = x;

                    while(is_empty(newX, y) && !is_outside(newX, y))
                    {
                        newX--;
                    }

                    int value = get(x, y);

                    set(x, y, 0);
                    set(newX, y, value);
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
                    if(is_empty(x, y))
                    {
                        continue;
                    }

                    int newX = x;

                    while(is_empty(newX, y) && !is_outside(newX, y))
                    {
                        newX++;
                    }

                    int value = get(x, y);

                    set(x, y, 0);
                    set(newX, y, value);
                }
            }
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

    int get(const int& x, const int& y) const
    {
        if(is_outside(x, y))
        {
            return -1;
        }

        return m_grid[y][x];
    }

    void set(const int& x, const int& y, const int value)
    {
        if(is_outside(x, y))
        {
            return;
        }

        m_grid[y][x] = value;
    }

private:
    // Sets the x and y with a random empty position
    void random_empty_pos(int& x, int& y)
    {
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
    grid g;

    g.print();

    g.move(direction::SOUTH);

    std::cout << std::endl;

    g.print();

    g.move(direction::NORTH);

    std::cout << std::endl;

    g.print();

    g.move(direction::EAST);

    std::cout << std::endl;

    g.print();

    g.move(direction::WEST);

    std::cout << std::endl;

    g.print();

    return 0;
}
