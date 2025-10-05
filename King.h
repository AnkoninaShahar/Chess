#pragma once

#include "Piece.h"

/// <summary>
/// Respresents the King game piece
/// </summary>
class King : public Piece
{
public:
	using Piece::Piece; // Uses piece constructors

	/// <summary>
	/// Finds all the legal king moves (one space in any direction, castling, & checks)
	/// </summary>
	/// <returns> A list with all the possible legal moves </returns>
	const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() override {
		std::vector<std::pair<sf::Vector2i, Piece*>> moves;

		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (i == 0 && j == 0)
					continue;
				if (IsLegalMove(pos.x + i, pos.y + j))
					moves.push_back(std::pair<sf::Vector2i, Piece*>({ pos.x + i, pos.y + j }, Board<Piece>::GetSpace(pos.x + i, pos.y + j)));
			}
		}

		// CHECK SYSTEM

		// CASTLE SYSTEM

		return moves;
	}
};

