#pragma once

#include <iostream>
#include <cmath>
#include <SFML\Graphics.hpp>

/// <summary>
/// Represents a board
/// </summary>
/// <typeparam name="T"> The type of object the board holds </typeparam>
template<typename T>
class Board
{
public:
	static inline const T* BLANK_SPACE; // Is a blank space

	// Constructor for board
	Board<T>(int rows = 8, int cols = 8) : rows(rows), cols(cols) {
		BLANK_SPACE = nullptr;

		// Sets up the board as a 2 dimensional array
		board = new T * *[rows];
		for (int i = 0; i < rows; ++i) {
			board[i] = new T * [cols];
		}
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				board[i][j] = nullptr;
			}
		}
	}

	// Deletes the board
	~Board() {
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				delete board[i][j];
			}
		}

		for (int i = 0; i < rows; ++i) {
			delete[] board[i];
		}

		delete[] board;
		board = nullptr;
	}

	/// <summary>
	/// Renders the board
	/// </summary>
	/// <param name="window"> Window that is drawn on </param>
	const void Render(sf::RenderWindow& window) {

		// Calculates useful values
		sf::Vector2f windowSize = { static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) };
		float smallestScreenSide = fminf(windowSize.x, windowSize.y);

		spcWidth = smallestScreenSide / cols;
		spcHeight = smallestScreenSide / rows;

		centerOffset = { windowSize.x / 2 - (spcWidth * cols) / 2, windowSize.y / 2 - (spcHeight * rows) / 2 };

		// Draws the checkered design
		sf::RectangleShape rect = sf::RectangleShape({ spcWidth, spcHeight });
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) { 
				rect.setPosition({ j * spcWidth + centerOffset.x, i * spcHeight + centerOffset.y });
				if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
					rect.setFillColor(sf::Color(207, 207, 207));
				else
					rect.setFillColor(sf::Color(86, 112, 80));

				window.draw(rect);
			}
		}

		// Draws spaces that are selected
		for (sf::Vector2i spc : selectedSpcs) {
			rect.setPosition({ spc.x * spcWidth + centerOffset.x, spc.y * spcHeight + centerOffset.y });
			rect.setFillColor(sf::Color(186, 114, 114, 200));

			window.draw(rect);
		}
	}

	// Translates coordinates to board spaces
	sf::Vector2i PositionToSpace(int x, int y) {
		return sf::Vector2i({ static_cast<int>((x - centerOffset.x) / spcWidth), static_cast<int>((y - centerOffset.y) / spcHeight) });
	}

	void AddSelectedSpace(int row, int col) {
		if ((row > -1 && row < rows) && (col > -1 && col < cols))
			selectedSpcs.push_back(sf::Vector2i(row, col));
	}

	std::vector<sf::Vector2i> GetSelectedSpaces() {
		return selectedSpcs;
	}

	void ClearSelectedSpaces() {
		selectedSpcs.clear();
	}

	static T*** GetBoard() {
		return board;
	}

	static void SetSpace(int row, int col, T* obj) {
		if ((row > -1 && row < sizeof(*board)) && (col > -1 && col < sizeof(*board[0])))
			board[row][col] = obj;
	}

	static T* GetSpace(int row, int col) {
		if ((row > -1 && row < sizeof(*board)) && (col > -1 && col < sizeof(*board[0])))
			return board[row][col];
		else
			return nullptr;
	}
	
	const sf::Vector2i GetSize() {
		return { cols, rows };
	}

	const sf::Vector2f GetSpaceSize() {
		return { spcWidth, spcHeight };
	}

	const sf::Vector2f GetBoardOffset() {
		return centerOffset;
	}

private:
	const int rows, cols;
	static inline T*** board = new T**[0];

	float spcWidth = 0.f;
	float spcHeight = 0.f;

	sf::Vector2f centerOffset;
	std::vector<sf::Vector2i> selectedSpcs;
};
