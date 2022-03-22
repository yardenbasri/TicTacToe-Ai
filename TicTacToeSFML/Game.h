#pragma once
#include <SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include <stdio.h>
#include <algorithm>
#include "constants.h"

using namespace sf;
using namespace std;
class Game
{
public:
	Game();
	void Start();
	void LoadData();
	void LoadBackGround();
	void UpdateEvents();
	void Print();
	int GameOver();
	double calculateDistance(Vector2f a, Vector2<int> b);
	void Clear();
	int findCell(Vector2f positions[], Vector2<int> mPosition);
	int checkWon(sf::Vertex line[2], int played[9], Vector2f positions[9]);
	virtual void Init() = 0;
	virtual void Update(Event event) = 0;

	
protected:
	sf::RenderWindow* window;
	sf::Texture boardTex;
	sf::Texture playerOneTex;
	sf::Texture playerTwoTex;
	sf::Vector2f positions[9] = { {150,150}, {285, 150}, {420, 150}, {150, 285}, {285, 285}, {420, 285},{150,420},{285, 420}, {420, 420} };
	sf::Vertex line[2];
	sf::Font font;
	sf::Text text;
	sf::Sprite board;
	sf::Sprite playerOne;
	sf::Sprite playerTwo;
	int played[9] = { 0 };
	int end;
	int turn;
	int mReleased;
	
	
};

