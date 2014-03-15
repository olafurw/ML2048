ML2048
======

This project impliments a C++ console version of the game 2048.

```C++
#include "grid.hpp"

grid g;

// You can also feed it actions via a vector
// g.add_actions(some_vector_of_shorts);

// While there are moves to be made
while(g.can_move())
{
    g.action(direction::NORTH);
}

// Prints the board
g.print();

// Print the sum of the tiles
std::cout << g.score() << std::endl;

// Print the largest tile
std::cout << g.largest() << std::endl;

// Get the actions that were performed
std::vector<short> a = g.actions();
```

You can increase the size of the grid and change a few other parameters in the utils.hpp file

It also contains a Genetic Algorithm structure to try to solve the game but it is in very early stages.

If you want to try some methods yourself, please check it out, the class "grid" has all the interfaces for you to use to play the game.

Author: Olafur Waage / @olafurw / olafurw@gmail.com
