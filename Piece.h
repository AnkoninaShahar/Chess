#include "AbstractPiece.h"

#pragma once
class Piece : AbstractPiece
{
public:
	enum color {
		BLACK,
		WHITE
	};

	inline Piece(int x, int y, color col, const sf::Vector2i& boardSize);
	inline Piece(const Piece& copy) : pos(copy.pos), col(copy.col), boardSize(copy.boardSize) {}

	inline void Move(int x, int y) override;

	inline virtual const std::vector<sf::Vector2i> CalculateLegalMoves() override { return std::vector<sf::Vector2i>(0); }

	const sf::Vector2i GetPosition() {
		return pos;
	}

	const color GetColor() {
		return col;
	}

protected:
	sf::Vector2i pos = { 0, 0 };
	color col = WHITE;

	sf::Vector2i boardSize;

	inline virtual bool IsLegalMove(int x, int y) override;
};

