#include <iostream>

#include "grid.hpp"

int main()
{
    for(unsigned int i = 0; i < 5000; ++i)
    {
        grid g;

        while(g.can_move())
        {
            g.action(rand_action());
        }
    }    

    return 0;
}
