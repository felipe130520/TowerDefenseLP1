#include "Game.h"
#include <time.h>

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Game game;

    game.run();
    //End
    return 0;
}