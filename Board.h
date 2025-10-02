#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

#pragma once
template<typename T>
class Board
{
public:
	//static const T* BLANK_SPACE;

	Board<T>(int rows = 8, int cols = 8) : rows(rows), cols(cols) {
		//BLANK_SPACE = nullptr;

		p_Board = new T * *[rows];

		for (int i = 0; i < rows; ++i) {
			p_Board[i] = new T * [cols];
		}

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				p_Board[i][j] = nullptr;
			}
		}
	}
	~Board() {
		for (int i = 0; i < rows; ++i) {
			delete[] p_Board[i];
		}

		delete[] p_Board;
		p_Board = nullptr;
	}

	const void Render(sf::RenderWindow& window) {
		sf::Vector2f windowSize = { static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) };
		float smallestScreenSide = fminf(windowSize.x, windowSize.y);

		spcWidth = smallestScreenSide / cols;
		spcHeight = smallestScreenSide / rows;

		centerOffset = { windowSize.x / 2 - (spcWidth * cols) / 2, windowSize.y / 2 - (spcHeight * rows) / 2 };

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {

				sf::RectangleShape rect = sf::RectangleShape({ spcWidth, spcHeight });
				rect.setPosition({ j * spcWidth + centerOffset.x, i * spcHeight + centerOffset.y });

				if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
					rect.setFillColor(sf::Color(207, 207, 207));
				else
					rect.setFillColor(sf::Color(86, 112, 80));

				for (sf::Vector2i spc : selectedSpcs) {
					if (spc == sf::Vector2i({ j, i }))
						rect.setFillColor(sf::Color(186, 114, 114));
				}

				window.draw(rect);
			}
		}
	}

	sf::Vector2i PositionToSpace(int x, int y) {
		return sf::Vector2i({ static_cast<int>((x - centerOffset.x) / spcWidth), static_cast<int>((y - centerOffset.y) / spcHeight) });
	}

	void AddSelectedSpace(int row, int col) {
		if ((row > -1 && row < rows) && (col > -1 && col < cols))
			selectedSpcs.push_back(sf::Vector2i(row, col));
	}

	void ClearSelectedSpaces() {
		selectedSpcs.clear();
	}

	static T*** GetBoard() {
		return p_Board;
	}

	static void SetSpace(int row, int col, T* p) {
		if ((row > -1 && row < sizeof(*p_Board)) && (col > -1 && col < sizeof(*p_Board[0])))
			p_Board[row][col] = p;
	}

	static T* GetSpace(int row, int col) {
		if ((row > -1 && row < sizeof(*p_Board)) && (col > -1 && col < sizeof(*p_Board[0])))
			return p_Board[row][col];
		else
			return nullptr;
	}
	
	const sf::Vector2i GetSize() {
		return { cols, rows };
	}

private:
	const int rows, cols;
	static inline T*** p_Board = new T**[0];

	float spcWidth = 0.f;
	float spcHeight = 0.f;

	sf::Vector2f centerOffset;
	std::vector<sf::Vector2i> selectedSpcs;
};
