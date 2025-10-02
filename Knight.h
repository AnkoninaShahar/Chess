#include "Piece.h"

#include <cmath>

#pragma once
class Knight : public Piece
{
public:
	using Piece::Piece;
	const std::vector<sf::Vector2i> CalculateLegalMoves() override {
		std::vector<sf::Vector2i> moves;

		int dir[4] = { 2, 1, -1, -2 };
		
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (abs(dir[i]) != abs(dir[j]) && IsLegalMove(pos.x + dir[i], pos.y + dir[j])) {
					moves.push_back({ pos.x + dir[i], pos.y + dir[j] });
				}
			}
		}

		return moves;
	}
};

