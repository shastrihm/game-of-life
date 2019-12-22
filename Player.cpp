#include "Player.h"


Player::Player(int col, int row, int dim, sf::Color color)
{
	this->_column = col;
	this->_row = row;
	this->_color = color;
	this->_dim = dim;
}

Player::~Player()
{
}

int Player::getCol()
{
	return this->_column;
}

int Player::getRow()
{
	return this->_row;
}

int Player::getDim()
{
	return this->_dim;
}
sf::Color Player::getColor()
{
	return this->_color;
}


void Player::move(char dir, int maxRow, int maxCol)
{

	switch (dir)
	{
		case 'd':
			this->_row++;
			if (this->_row + this->_dim  > maxRow)
			{
				this->_row--;
			}
			break;
		case 'u':
			this->_row--;
			if (this->_row < 0)
			{
				this->_row++;
			}
			break;
		case 'l':
			this->_column--;
			if (this->_column < 0)
			{
				this->_column++;
			}
			break;
		case 'r':
			this->_column++;
			if (this->_column + this->_dim > maxCol)
			{
				this->_column--;
			}
			break;
	}
	
}



