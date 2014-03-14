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

    g.print();

    while(g.can_move())
    {
        g.action(rand_pos());
        g.print();
    }
    
    std::cout << g.can_move() << std::endl;

    return 0;
}
