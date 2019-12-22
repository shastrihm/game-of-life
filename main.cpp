// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <sfml/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include "Grid.h"

// Constants
static const int WINDOW_HEIGHT = 2000;
static const int WINDOW_WIDTH = 2000;

static const int NUM_ROWS = 50;
static const int NUM_COLS = 50;

const float SQSIZE = sqrt((WINDOW_HEIGHT * WINDOW_WIDTH) / (NUM_ROWS * NUM_COLS));

const sf::Color ONCOLOR = sf::Color::Color(180, 0, 0);
const sf::Color OFFCOLOR = sf::Color::Color(204, 204, 204);
const sf::Color PLAYERCOLOR = sf::Color::Black;

static const int REFRESH_RATE = 100; // in milliseconds
//

// All purpose functions
std::vector<int> xy_to_colrow(int x, int y)
{
	std::vector<int> coords;
	coords.push_back(floor((x / SQSIZE)));
	coords.push_back(floor((y / SQSIZE)));
	return coords;
}

//

int main()
{	
	sf::RenderWindow window(sf::VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH), "Cells", sf::Style::Titlebar | sf::Style::Close);
	sf::Clock clock;
	Grid *grid = new Grid(NUM_COLS, NUM_ROWS, SQSIZE, ONCOLOR, OFFCOLOR);
	Player* player = new Player(10, 10, 2, PLAYERCOLOR);
	bool beginSimul = false;

	while (window.isOpen())
	{
		bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
		bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
		bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
		bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::KeyPressed:
					if (evnt.key.code == sf::Keyboard::R)
					{
						beginSimul = !beginSimul;
					}
					if (evnt.key.code == sf::Keyboard::C)
					{
						grid->clear();
					}
					break;

				case sf::Event::MouseButtonPressed:
					auto x = evnt.mouseButton.x;
					auto y = evnt.mouseButton.y;
					grid->clickAt(xy_to_colrow(x, y));
					break;
			}
		}
		if (up) { 
			grid->deRenderPlayer(player);
			player->move('u', NUM_ROWS, NUM_COLS); }
		if (down) { 
			grid->deRenderPlayer(player);
			player->move('d', NUM_ROWS, NUM_COLS); }
		if (left) { 
			grid->deRenderPlayer(player);
			player->move('l', NUM_ROWS, NUM_COLS); }
		if (right) { 
			grid->deRenderPlayer(player);
			player->move('r', NUM_ROWS, NUM_COLS); }

		if (clock.getElapsedTime().asMilliseconds() > REFRESH_RATE && beginSimul)
		{
			grid->update();
			clock.restart();
		}
		window.clear();
		grid->renderPlayer(player);
		grid->draw(&window);
		window.display();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
