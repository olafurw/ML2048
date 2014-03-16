#include <iostream>

#include "grid.hpp"

int main()
{
    grid g;

    for(unsigned int i = 0; i < 1000; ++i)
    {
        while(g.can_move())
        {
            g.action(rand_action());
        }
    }    

    return 0;
}
