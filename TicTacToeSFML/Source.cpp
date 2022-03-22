#include <SFML/Graphics.hpp>
#include "Game.h"
#include "UserGame.h"
#include "AiGame.h"

#include<iostream>
#include<vector>



int main()
{
    Game* game = new AiGame();
    game->Start();
}
