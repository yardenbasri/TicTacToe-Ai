#include "Game.h"

Game::Game()
{
	window = new sf::RenderWindow(sf::VideoMode(SCREENSIZE, SCREENSIZE), "TicTacToe");
    end = 0;
    turn = 1;
    mReleased = 1;
}

void Game::Start()
{
    LoadData();
    LoadBackGround();
    Init();
}

void Game::LoadData()
{
    if (!boardTex.loadFromFile("Assets/background.png"))
    {
        printf("error\n");
    }
    if (!playerOneTex.loadFromFile("Assets/playerOne.png"))
    {
        printf("error\n");
    }
    if (!playerTwoTex.loadFromFile("Assets/playerTwo.png"))
    {
        printf("error\n");
    }
    if (!font.loadFromFile("Assets/arial.ttf"))
    {
        printf("error\n");
    }
   
   

}

void Game::LoadBackGround()
{
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(50, 20);

    board.setTexture(boardTex);
    playerOne.setTexture(playerOneTex);
    playerTwo.setTexture(playerTwoTex);
    board.setPosition(100, 100);
}

void Game::UpdateEvents()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        Update(event);
    }
}

void Game::Print()
{
    window->clear(sf::Color::Black);
    window->draw(board);
    for (int i = 0; i < 9; i++)
    {

        if (played[i] == 1)
        {
            playerOne.setPosition(positions[i].x, positions[i].y);
            window->draw(playerOne);
        }
        if (played[i] == 2)
        {
            playerTwo.setPosition(positions[i].x, positions[i].y);
            window->draw(playerTwo);
        }
    }
    if (end == 1)
    {
        window->draw(line, 2, sf::Lines);
        if (turn)
        {
            text.setString("player two won !\nPress space to start again!");
            window->draw(text);
        }
        else
        {
            text.setString("player one won !\nPress space to start again!");
            window->draw(text);
        }

    }
    if (end == 2)
    {
        text.setString("Draw !\nPress space to start again!");
        window->draw(text);
    }
    window->display();
}

int Game::GameOver()
{
    int check = checkWon(line, played, positions);
    if (check)
    {
        return 1;
    }
    check = 1;
    for (int i = 0; i < 9; i++)
    {
        if (!played[i])
        {
            check = 0;
        }
    }
    if (check)
    {
        check = 2;
    }
    return check;
}

double Game::calculateDistance(Vector2f a, Vector2<int> b)
{
    return sqrt(pow(a.x - b.x, 2) +
        pow(a.y - b.y, 2));
}

void Game::Clear()
{
    for (int i = 0; i < 9; i++)
    {
        played[i] = 0;
    }
    end = 0;
    turn = 1;
    mReleased = 1;
}

int Game::findCell(Vector2f positions[], Vector2<int> mPosition)
{
    int iMin = 0;
    double MinDistance = calculateDistance(positions[0], mPosition);
    double distance;
    for (int i = 1; i < 9; i++)
    {
        distance = calculateDistance(positions[i], mPosition);
        if (distance < MinDistance)
        {
            MinDistance = distance;
            iMin = i;
        }
    }
    return iMin;
}

int Game::checkWon(sf::Vertex line[2], int played[9], Vector2f positions[9]) // return 0 if no one won, 1 if player 1 won, 2 if player 2 won.
{
    for (int i = 1; i <= 2; i++)
    {
        if ((played[0] == i && played[1] == i && played[2] == i))
        {
            line[0] = sf::Vertex(positions[0], sf::Color::Red);
            line[1] = sf::Vertex(positions[2], sf::Color::Red);
            return 1 + i-1;
        }
        if ((played[3] == i && played[4] == i && played[5] == i))
        {
            line[0] = sf::Vertex(positions[3], sf::Color::Red);
            line[1] = sf::Vertex(positions[5], sf::Color::Red);
            return 1 + i - 1;
        }
        if ((played[6] == i && played[7] == i && played[8] == i))
        {
            line[0] = sf::Vertex(positions[6], sf::Color::Red);
            line[1] = sf::Vertex(positions[8], sf::Color::Red);
            return 1 + i - 1;
        }
        if ((played[0] == i && played[3] == i && played[6] == i))
        {
            line[0] = sf::Vertex(positions[0], sf::Color::Red);
            line[1] = sf::Vertex(positions[6], sf::Color::Red);
            return 1 + i - 1;
        }
        if ((played[1] == i && played[4] == i && played[7] == i))
        {
            line[0] = sf::Vertex(positions[1], sf::Color::Red);
            line[1] = sf::Vertex(positions[7], sf::Color::Red);
            return 1 + i - 1;
        }
        if ((played[2] == i && played[5] == i && played[8] == i))
        {
            line[0] = sf::Vertex(positions[2], sf::Color::Red);
            line[1] = sf::Vertex(positions[8], sf::Color::Red);
            return 1 + i - 1;
        }
        if ((played[0] == i && played[4] == i && played[8] == i))
        {
            line[0] = sf::Vertex(positions[0], sf::Color::Red);
            line[1] = sf::Vertex(positions[8], sf::Color::Red);
            return 1 + i - 1;
        }
        if ((played[2] == i && played[4] == i && played[6] == i))
        {
            line[0] = sf::Vertex(positions[2], sf::Color::Red);
            line[1] = sf::Vertex(positions[6], sf::Color::Red);
            return 1 + i - 1;
        }
    }

    return 0;
}
