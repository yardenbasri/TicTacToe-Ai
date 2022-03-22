#include "UserGame.h"

UserGame::UserGame()
{
    end = 0;
    turn = 1;
    mReleased = 1;
}



void UserGame::Init()
{
    while (window->isOpen())
    {
        UpdateEvents();
        Print();
    }
   
}

void UserGame::Update(Event event)
{
    sf::Mouse mouse;
    sf::Vector2<int> mPosition = mouse.getPosition(*window);
    end = GameOver();
    if (event.type == sf::Event::MouseButtonPressed && mReleased && !end)
    {
        if (event.mouseButton.button == mouse.Left)
        {
            printf("(%d , %d)\n", mPosition.x, mPosition.y);
            int index = findCell(positions, mPosition);
            if (!played[index])
            {
                if (turn)
                {
                    played[index] = 1;
                    turn = !turn;
                }
                else
                {
                    played[index] = 2;
                    turn = !turn;
                }
                
            }
        }
        mReleased = 0;
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        mReleased = 1;
    }
    if (end)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Clear();
        }
    }
    
   
}


