#include "Piece.h"

#pragma once
class Pawn : public Piece
{
public:
	using Piece::Piece;
	const std::vector<sf::Vector2i> CalculateLegalMoves() override {
		std::vector<sf::Vector2i> moves;

		int dir = 0;
		if (col == WHITE)
			dir = -1;
		else
			dir = 1;

		for (int i = -1; i <= 1; ++i) {
			if (i != 0 && Board<Piece>::GetSpace(pos.x + i, pos.y + dir))
				moves.push_back({ pos.x + i, pos.y + dir });
			else if (i == 0 && IsLegalMove(pos.x, pos.y + dir) && Board<Piece>::GetSpace(pos.x, pos.y + dir) == nullptr)
				moves.push_back({ pos.x, pos.y + dir });
		}

		return moves;
	}
};

