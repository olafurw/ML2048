// A very rough C++ version for the 2048 game
//
// Author: Olafur Waage / @olafurw
// olafurw@gmail.com
//
// Under the Apache License
// If you have any fun with this, please let me know, I would love to hear from you.

#include <iostream>

#include "utils.hpp"
#include "grid.hpp"

int main()
{
    grid g;

    while(g.can_move())
    {
        g.action(rand_action());
    }

    for(auto& action : g.actions())
    {
        std::cout << action << std::endl;
    }

    g.print();
    std::cout << g.score() << std::endl;

    return 0;
}
