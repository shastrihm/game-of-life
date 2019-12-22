#include "Grid.h"

Grid::Grid(int numCols, int numRows, float sqsize, sf::Color onColor, sf::Color offColor)
{
	this->_numCols = numCols;
	this->_numRows = numRows;
	this->_liveCells;
	this->_sqsize = sqsize;
	this->onColor = onColor;
	this->offColor = offColor;
	this->_grid;
	this->_generateGrid();
}

Grid::~Grid()
{
	for (int i = 0; i < this->_numRows; i++) {
		for (int j = 0; j < this->_numCols; j++) {
			delete this->_grid[i][j];
		}
	}
}

void Grid::draw(sf::RenderWindow *window)
{
	for (int i = 0; i < this->_numRows; i++) {
		for (int j = 0; j < this->_numCols; j++) {
			this->_grid[i][j]->draw(window);
		}
	}
}

void Grid::renderPlayer(Player* player)
{	
	int row = player->getRow();
	int col = player->getCol();
	int dim = player->getDim();
	auto color = player->getColor();
	for (int i = row; i < row + dim; i++)
	{
		for (int j = col; j < col + dim; j++)
		{
			this->_grid[i][j]->setColor(color);
		}
	}
}

void Grid::deRenderPlayer(Player* player)
{
	int row = player->getRow();
	int col = player->getCol();
	int dim = player->getDim();
	auto color = player->getColor();
	for (int i = row; i < row + dim; i++)
	{
		for (int j = col; j < col + dim; j++)
		{	
			auto cell = this->_grid[i][j];
			if (cell->isActive())
			{
				cell->setColor(this->onColor);
			}
			else {
				cell->setColor(this->offColor);
			}
		}
	}
}

void Grid::_generateGrid()
{
	std::vector<GridCell*> row;
	auto SQSIZE = this->_sqsize;
	for (int i = 0; i < this->_numRows; i++){
		for (int j = 0; j < this->_numCols; j++){
			sf::Vector2f pos(SQSIZE * j, SQSIZE * i);
			sf::Vector2f size(SQSIZE, SQSIZE);
			row.push_back(new GridCell(pos, size, j, i, this->onColor, this->offColor));
		}
		this->_grid.push_back(row);
		row.clear();
	}
}

void Grid::clear()
{
	for (int i = 0; i < this->_numRows; i++) {
		for (int j = 0; j < this->_numCols; j++) {
			this->_grid[i][j]->deactivate();
		}
	}
}

void Grid::update()
{
	// Cellular automata rules
	std::vector<std::vector<bool>> newGrid;
	std::vector<bool> row;
	for (int i = 0; i < this->_numRows; i++) {
		for (int j = 0; j < this->_numCols; j++) {
			auto cell = this->_grid[i][j];
			auto count = this->_countNeighborStatus(cell);

			if (cell->isActive() && (count[0] == 2 || count[0] == 3)) { row.push_back(true); }
			else if (!cell->isActive() && count[0] == 3) { row.push_back(true); }
			else { row.push_back(false); };
		}
		newGrid.push_back(row);
		row.clear();
	}
	for (int i = 0; i < this->_numRows; i++) {
		for (int j = 0; j < this->_numCols; j++) {
			bool active = newGrid[i][j];
			if (active) { 
				this->_grid[i][j]->activate();
			}
			else {
				this->_grid[i][j]->deactivate();
			};
		}
	}
}

void Grid::clickAt(std::vector<int> coords)
{
	auto col = coords[0];
	auto row = coords[1];
	auto cell = this->_grid[row][col];
	cell->flipState();
	this->_liveCells.push_back(cell);
}

std::vector<GridCell*> Grid::_getNeighbors(GridCell* cell)
{
	std::vector<GridCell*> neighbs;
	int row = cell->getRow();
	int col = cell->getCol();
	if (row - 1 >= 0) { neighbs.push_back(this->_grid[row - 1][col]); }
	if (row - 1 >= 0 && col - 1 >= 0) { neighbs.push_back(this->_grid[row - 1][col - 1]); }
	if (row - 1 >= 0 && col + 1 < this->_numCols) { neighbs.push_back(this->_grid[row - 1][col + 1]); }
	if (col - 1 >= 0) { neighbs.push_back(this->_grid[row][col - 1]); }
	if (col + 1 < this->_numCols) { neighbs.push_back(this->_grid[row][col + 1]); }
	if (row + 1 < this->_numRows) { neighbs.push_back(this->_grid[row + 1][col]); }
	if (row + 1 < this->_numRows && col - 1 >= 0) { neighbs.push_back(this->_grid[row + 1][col - 1]); }
	if (row + 1 < this->_numRows && col + 1 < this->_numCols) { neighbs.push_back(this->_grid[row + 1][col + 1]); }
	return neighbs;
}

std::vector<int> Grid::_countNeighborStatus(GridCell* cell)
{
	std::vector<int> count = { 0, 0 };
	auto neighbs = this->_getNeighbors(cell);
	for (unsigned i = 0; i < neighbs.size(); i++) {
		auto cell = neighbs[i];
		if (cell->isActive()) {
			count[0]++;
		}
		else {
			count[1]++;
		};
	}
	return count;
}