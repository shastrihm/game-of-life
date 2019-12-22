#pragma once
#include "GridCell.h"
#include "Player.h"
#include <vector>

class Grid
{
	public:
		Grid(int numCols, int numRows, float sqsize, sf::Color onColor, sf::Color offColor);
		~Grid();

		void clickAt(std::vector<int> coords);
		void draw(sf::RenderWindow *window);
		void renderPlayer(Player* player);
		void deRenderPlayer(Player* player);
		void update();
		void clear();
		sf::Color onColor;
		sf::Color offColor;

	private:
		int _numCols = 0;
		int _numRows = 0;
		std::vector<GridCell*> _liveCells;
		float _sqsize;
		std::vector<std::vector<GridCell*>> _grid;
		void _generateGrid();
		std::vector<GridCell*> _getNeighbors(GridCell* cell);
		std::vector<int> _countNeighborStatus(GridCell* cell); // pair (# alive, # dead)
};

