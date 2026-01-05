#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

/// <summary>
/// Represents a board
/// </summary>
/// <typeparam name="T"> The type of object the board holds </typeparam>
template<typename T>
class Board
{
public:

	// Constructor for board
	Board<T>(int rows = 8, int cols = 8) : rows(rows), cols(cols) {

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

	Board<T>(const Board& copy) {
		board = copy;
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
			float radiusOffset = smallestScreenSide / 50;
			sf::CircleShape circle(spcWidth / 2 - radiusOffset);
			if (GetSpace(spc.x, spc.y) != nullptr) {
				rect.setFillColor(sf::Color(112, 68, 68, 200));

				circle.setFillColor(sf::Color(0, 0, 0, 0));
				circle.setOutlineColor(sf::Color(186, 114, 114, 200));
			}
			else {
				rect.setFillColor(sf::Color(115, 115, 115, 200));

				circle.setFillColor(sf::Color(0, 0, 0, 0));
				circle.setOutlineColor(sf::Color(165, 165, 165, 200));
			}

			rect.setPosition({ spc.x * spcWidth + centerOffset.x, spc.y * spcHeight + centerOffset.y });
			circle.setPosition({ spc.x * spcWidth + centerOffset.x + radiusOffset, spc.y * spcHeight + centerOffset.y + radiusOffset });
			circle.setOutlineThickness(radiusOffset);

			window.draw(rect);
			window.draw(circle);
		}

		sf::RectangleShape boarderRect = sf::RectangleShape({ spcWidth * cols, spcHeight * rows });
		boarderRect.setPosition({ centerOffset.x, centerOffset.y });
		boarderRect.setFillColor(sf::Color(0, 0, 0, 0));
		boarderRect.setOutlineColor(sf::Color(28, 17, 3));
		boarderRect.setOutlineThickness(30);
		window.draw(boarderRect);
	}

	// Translates coordinates to board spaces
	sf::Vector2i PositionToSpace(int x, int y) {
		return sf::Vector2i({ static_cast<int>((x - centerOffset.x) / spcWidth), static_cast<int>((y - centerOffset.y) / spcHeight) });
	}

	std::string PositionToString(int x, int y) {
		char file = static_cast<char>(x + 97);
		char rank = static_cast<char>(rows - y + 48);

		std::string result;
		result.push_back(file);
		result.push_back(rank);

		return result;
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

	void operator= (Board copy){
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				board[i][j] = copy.GetSpace(i, j);
			}
		}
	}

	T*** GetBoard() {
		return board;
	}

	void SetSpace(int row, int col, T* obj) {
		if ((row > -1 && row < rows) && (col > -1 && col < cols))
			board[row][col] = obj;
	}

	T* GetSpace(int row, int col) {
		if ((row > -1 && row < rows) && (col > -1 && col < cols))
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
	T*** board = new T**[0];

	float spcWidth = 0.f;
	float spcHeight = 0.f;

	sf::Vector2f centerOffset;
	std::vector<sf::Vector2i> selectedSpcs;
};
