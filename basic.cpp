#include <iostream>

#include "grid.hpp"

int main()
{
    int largest = 0;
    int count = 0;

    while(true)
    {
        grid g;
        while(g.can_move())
        {
            bool east = g.action(direction::EAST);
            east |= g.action(direction::EAST);
            east |= g.action(direction::EAST);

            bool south = g.action(direction::SOUTH);

            bool west = g.action(direction::WEST);
            west |= g.action(direction::WEST);
            west |= g.action(direction::WEST);

            if(!east && !south && !west)
            {
                g.action(direction::NORTH);
            }
        }

        if(g.largest() > largest)
        {
            largest = g.largest();
            std::cout << largest << std::endl;
            g.print();
        }

        ++count;

        if(count % 1000 == 0)
        {
            std::cout << "game: " << count << std::endl;
        }
    }

    return 0;
}
