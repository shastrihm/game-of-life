#include "GridCell.h"

GridCell::GridCell(sf::Vector2f position, sf::Vector2f size, int column, int row, sf::Color onColor, sf::Color offColor)
{
	// set data members
	this->_column = column;
	this->_row = row;
	this->_active = false;
	this->_onColor = onColor;
	this->_offColor = offColor;
	this->_cell = sf::RectangleShape(size);

	this->_cell.setPosition(position);
	this->_cell.setFillColor(this->_offColor);
	this->_cell.setOutlineColor(sf::Color::Black);
	this->_cell.setOutlineThickness(2);
};

GridCell::~GridCell()
{
}

void GridCell::draw(sf::RenderWindow *window)
{
	window->draw(this->_cell);
}

int GridCell::getCol()
{
	return this->_column;
}

int GridCell::getRow()
{
	return this->_row;
}

void GridCell::setColor(sf::Color color)
{
	this->_cell.setFillColor(color);
}

sf::Color GridCell::getColor()
{
	return this->_cell.getFillColor();
}

void GridCell::activate()
{
	this->_active = true;
	this->_cell.setFillColor(this->_onColor);
}

void GridCell::deactivate()
{
	this->_active = false;
	this->_cell.setFillColor(this->_offColor);
}

void GridCell::flipState()
{
	if(this->_active){
		this->deactivate();
	}
	else {
		this->activate();
	}
}

bool GridCell::isActive()
{
	return this->_active;
}

