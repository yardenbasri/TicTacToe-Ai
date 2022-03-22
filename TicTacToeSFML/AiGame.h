#pragma once
#include "Game.h"
class AiGame :
    public Game
{
public:
    AiGame();
    void Init();
    void Update(Event event);
    int evaluate();
    int minimax(int depth, int IsMax);
    int findBestMove();

};

