#include "Piece.h"

#pragma once
class Knight : public Piece
{
public:
	using Piece::Piece;
	const std::vector<sf::Vector2i> CalculateLegalMoves() override {
		std::vector<sf::Vector2i> moves {
			{ pos.x + 3, pos.y + 1 },
			{ pos.x + 3, pos.y - 1 },
			{ pos.x - 3, pos.y + 1 },
			{ pos.x - 3, pos.y - 1 },
			{ pos.x + 1, pos.y + 3 },
			{ pos.x + 1, pos.y - 3 },
			{ pos.x - 1, pos.y + 3 },
			{ pos.x - 1, pos.y - 3 }
		};

		for (auto move = moves.end() - 1; move != moves.begin(); --move) {
			if (!IsLegalMove((*move).x, (*move).y))
				moves.erase(move);
		}

		return moves;
	}
};

