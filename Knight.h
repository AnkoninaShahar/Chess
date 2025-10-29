#pragma once

#include "Piece.h"

/// <summary>
/// Represents the Knight game piece
/// </summary>
class Knight : public Piece
{
public:
	using Piece::Piece; // Uses piece constructors

	/// <summary>
	/// Finds all the legal knight moves (one space & two spaces)
	/// </summary>
	/// <returns> A list with all the possible legal moves </returns>
	const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() override {
		std::vector<std::pair<sf::Vector2i, Piece*>> moves = std::vector<std::pair<sf::Vector2i, Piece*>>(0);

		for (int i = -2; i <= 2; i++) {
			for (int j = -2; j <= 2; j++) {
				if (i == 0 || j == 0)
					continue;
				if (abs(i) != abs(j) && IsLegalMove(pos.x + i, pos.y + j))
					moves.push_back(std::pair<sf::Vector2i, Piece*>({ pos.x + i, pos.y + j }, board.GetSpace(pos.x + i, pos.y + j)));
			}
		}

		return moves;
	}
};

