#include <iostream>

#include "grid.hpp"

int main()
{
    int largest = 0;

    while(true)
    {
        grid g;
        while(g.can_move())
        {
            bool north = g.action(direction::NORTH);
            bool east = g.action(direction::EAST);

            if(!north && !east)
            {
                bool south = g.action(direction::SOUTH);
                east = g.action(direction::EAST);
                north = g.action(direction::NORTH);

                if(!south && !east && !north)
                {
                    if(g.largest() > largest)
                    {
                        largest = g.largest();
                        std::cout << largest << std::endl;
                    }

                    break;
                }
            }
        }
    }

    return 0;
}
