#include <iostream>

#include "grid.hpp"

void do_action(grid& g)
{
    char action;
    std::cin >> action;

    if(action == 'w')
    {
        g.action(direction::NORTH);

        return;
    }

    if(action == 's')
    {
        g.action(direction::SOUTH);

        return;
    }

    if(action == 'a')
    {
        g.action(direction::WEST);

        return;
    }

    if(action == 'd')
    {
        g.action(direction::EAST);

        return;
    }

    if(action == 'g')
    {
        std::cout << "Cheater!" << std::endl;
        g.set(0, 0, 2048);        
    }
}

int main()
{
    std::cout << "w = north, s = south, a = west, d = east" << std::endl;

    grid g;

    g.print();

    while(g.can_move())
    {
        do_action(g);
        g.print();
        std::cout << "Score: " << g.score() << std::endl;

        if(g.largest() == 2048)
        {
            std::cout << "Win" << std::endl;
            break;
        }
    }

    return 0;
}
