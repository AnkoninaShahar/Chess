#pragma once

#include "Board.h"

#include <string>
#include <vector>
#include <typeinfo>
#include <SFML\Graphics.hpp>

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

	inline virtual bool Move(int x, int y, std::vector<std::pair<sf::Vector2i, Piece*>> legalMoves);

	inline virtual const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() { return std::vector<std::pair<sf::Vector2i, Piece*>>(0); }

	// Updates the turn number
	virtual void Update(int turnNum) {
		this->turnNum = turnNum;
	}

	inline const bool CanPromote() {
		std::string pieceName = typeid(*this).name();
		return pieceName.find("Pawn") != std::string::npos && (pos.y == 0 || pos.y == 7);
	}

	virtual const void Promote(int choice) {}

	const void SetCheck(bool inCheck) {
		this->inCheck = inCheck;
	}

	const void SetPosition(sf::Vector2i pos) {
		this->pos = pos;
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

	const int GetMoveNum() {
		return moveNum;
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

	bool inCheck = false;

	inline virtual bool IsLegalMove(int x, int y);

	inline const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLineMoves(sf::Vector2i dir);
};

