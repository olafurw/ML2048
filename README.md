ML2048
======

This project impliments a C++ console version of the game 2048.

To build

```
mkdir build;
cd build;
cmake ..;
make;
```

Then you can run ./game to play a console game version of 2048, ./ga to run the genetic algorithm version, or ./speed to run for valgrind tests.

Here is a usage example of the grid class.

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

Author: Olafur Waage / @olafurw / olafurw@gmail.com
