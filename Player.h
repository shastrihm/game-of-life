#pragma once
#include <SFML/Graphics.hpp>

class Player
{
	public:
		Player(int col, int row, int dim, sf::Color color);
		~Player();
		int getCol();
		int getRow();
		int getDim();
		sf::Color getColor();
		void move(char dir, int maxRow, int maxCol);


	private:
		int _column;
		int _row;
		int _dim;
		sf::Color _color;


};

