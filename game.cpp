#include <iostream>

#include "grid.hpp"

direction get_action()
{
    char action;
    std::cin >> action;

    if(action == 'w')
    {
        return direction::NORTH;
    }

    if(action == 's')
    {
        return direction::SOUTH;
    }

    if(action == 'a')
    {
        return direction::WEST;
    }

    if(action == 'd')
    {
        return direction::EAST;
    }

    if(action == 'x')
    {
        return direction::CHEAT;
    }
    if(action == 'g')
    {
        return direction::GODCHEAT;
    }

    return direction::NORTH;
}

int main()
{
    std::cout << "w = north, s = south, a = west, d = east" << std::endl;

    grid g;

    g.print();

    while(g.can_move())
    {
        g.action(get_action());
        g.print();
        std::cout << "Score: " << g.score() << std::endl;
    }

    return 0;
}
