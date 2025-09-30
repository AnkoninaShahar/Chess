#include "Board.h"

Board::Board(int rows, int cols) : rows(rows), cols(cols) {
	p_Board = new char* [rows];

	for (int i = 0; i < rows; ++i) {
		p_Board[i] = new char[cols];
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {

			p_Board[i][j] = '0';

		}
	}
}

Board::~Board() {
	for (int i = 0; i < rows; ++i) {
		delete[] p_Board[i];
	}

	delete[] p_Board;
	p_Board = nullptr;
}

const void Board::Render(sf::RenderWindow& window) {
	sf::Vector2f windowSize = { static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) };
	float smallestScreenSide = fminf(windowSize.x, windowSize.y);

	float width = smallestScreenSide / cols;
	float height = smallestScreenSide / rows;

	sf::Vector2f centerOffset = { windowSize.x / 2 - (width * cols) / 2, windowSize.y / 2 - (height * rows) / 2 };

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {

			sf::RectangleShape rect = sf::RectangleShape({ width, height });
			rect.setPosition({ j * width + centerOffset.x, i * height + centerOffset.y});

			if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
				rect.setFillColor(sf::Color(207, 207, 207));
			else
				rect.setFillColor(sf::Color(40, 74, 39));

			window.draw(rect);
		}
	}
}