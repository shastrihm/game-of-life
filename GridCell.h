#pragma once
#include <SFML/Graphics.hpp>


class GridCell
{
	public:
		GridCell(sf::Vector2f position, sf::Vector2f size, int column, int row, sf::Color onColor, sf::Color offColor);
		~GridCell();

		void draw(sf::RenderWindow *window);
		int getCol();
		int getRow();
		void setColor(sf::Color color);
		sf::Color getColor();

		void activate();
		void deactivate();
		void flipState();
		bool isActive();





	private:
		int _column = 0;
		int _row = 0;
		bool _active = false;
		sf::Color _onColor;
		sf::Color _offColor;
		sf::RectangleShape _cell;

};

