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
            bool south = g.action(direction::SOUTH);
            bool west = g.action(direction::WEST);
            bool south2 = g.action(direction::SOUTH);

            if(!east && !south && !west && !south2)
            {
                if(g.largest() > largest)
                {
                    largest = g.largest();
                    std::cout << largest << std::endl;
                    g.print();
                }

                break;
            }
        }

        ++count;

        if(count % 1000 == 0)
        {
            std::cout << "game: " << count << std::endl;
        }
    }

    return 0;
}
