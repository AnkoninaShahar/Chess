#include <cmath>
#include <SFML\Graphics.hpp>

#pragma once
class Board
{
public:
	Board(int rows = 10, int cols = 10);
	~Board();

	const void Render(sf::RenderWindow& window);

	static char** GetBoard() {
		return p_Board;
	}

	static char GetSpace(int row, int col) {
		return p_Board[row][col];
	}

private:
	const int rows, cols;
	static inline char** p_Board = new char*[0];
};

