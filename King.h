#include "Piece.h"

#pragma once
class King : public Piece
{
public:
	using Piece::Piece;
	const std::vector<sf::Vector2i> CalculateLegalMoves() override {
		std::vector<sf::Vector2i> moves;

		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (i == 0 && j == 0)
					continue;
				if (IsLegalMove(pos.x + i, pos.y + j))
					moves.push_back({ pos.x + i, pos.y + j });
			}
		}

		return moves;
	}
};

