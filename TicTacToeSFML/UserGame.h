#pragma once
#include "Game.h"
class UserGame :
    public Game
{
public:
    UserGame();
    void Init();
    void Update(Event event);

};

