#include "AiGame.h"

AiGame::AiGame()
{
    end = 0;
}

void AiGame::Init()
{
	while (window->isOpen())
	{
		UpdateEvents();
		Print();
	}
}

void AiGame::Update(Event event)
{
	sf::Mouse mouse;
    sf::Vector2<int> mPosition = mouse.getPosition(*window);
    end = GameOver();
    
    if (event.type == sf::Event::MouseButtonPressed && mReleased && !end)
    {
        if (event.mouseButton.button == mouse.Left)
        {
            int index = findCell(positions, mPosition);
            if (!played[index] && turn)
            {
                played[index] = 1;
                turn = !turn;
            }
        }
        mReleased = 0;
       
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        mReleased = 1;
    }
    end = GameOver();
    
    if (!turn && !end)
    {
        int bestMove = findBestMove();
        played[bestMove] = 2;
        turn = !turn;
    }
    
    if (end)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Clear();
        }
    }
    
}

int AiGame::evaluate()
{
    int check = checkWon(line, played, positions);
    switch (check)
    {
    case 1:
        return -10;
    case 2:
        return +10;
    default:
        return 0;
    }
}

int AiGame::minimax(int depth, int IsMax)
{
    int score = evaluate();
    //check if max won
    if (score == 10)
    {
        return score;
    }
    //check if min won
    if (score == -10)
    {
        return score;
    }
    //check for draws
    if (GameOver() == 2)
    {
        return 0;
    }
    //check if it maximizer move or minimizer move
    if (IsMax)
    {
        int best = -INFINITY;
        for (int i = 0; i < 9; i++)
        {
            if (!played[i])
            {
                played[i] = 2;
                best = max(best, minimax(depth + 1, !IsMax));
                played[i] = 0;// undo the move
            }
        }
        return best;
    }
    else
    {
        int best = INFINITY;
        for (int i = 0; i < 9; i++)
        {
            if (!played[i])
            {
                played[i] = 1;
                best = min(best, minimax(depth + 1, !IsMax));
                played[i] = 0; // undo the move
            }
        }
        return best;
    }


}

int AiGame::findBestMove() // return the index of the cell with the best move
{
    int bestMove = -1;
    int bestScore = -INFINITY;
    for (int i = 0; i < 9; i++)
    {
        if (!played[i])
        {
            played[i] = 2;
            int score = minimax(0, 0);
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
            played[i] = 0;
        }
        
    }
    return bestMove;
}


