#pragma once

#include "Board.h"
#include "PieceUtilz.h"

#include <string>
#include <vector>
#include <typeinfo>
#include <SFML\Graphics.hpp>

using namespace PieceUtilz; // Extra piece functions

/// <summary>
/// Blueprint class for more specific pieces
/// </summary>
class Piece
{
public:

	// The two sides of chess
	enum color {
		BLACK,
		WHITE
	};

	// Constructors for pieces
	inline Piece(int x, int y, color col, const sf::Vector2i& boardSize);
	inline Piece(const Piece& copy) : pos(copy.pos), col(copy.col), boardSize(copy.boardSize) {}

	inline virtual bool Move(int x, int y);

	inline virtual const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() { return std::vector<std::pair<sf::Vector2i, Piece*>>(0); }

	// Updates the turn number
	virtual void Update(int turnNum) {
		this->turnNum = turnNum;
	}

	const sf::Vector2i GetPosition() {
		return pos;
	}

	const color GetColor() {
		return col;
	}

	const int GetTurn() {
		return turnNum;
	}

	const bool operator== (const Piece& other) {
		return pos == other.pos;
	}

protected:
	sf::Vector2i pos = { 0, 0 };
	color col = WHITE;

	sf::Vector2i boardSize;

	int moveNum = 0;
	int turnNum = 0;

	inline virtual bool IsLegalMove(int x, int y);

	inline const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLineMoves(sf::Vector2i dir);
};

