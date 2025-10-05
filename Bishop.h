#pragma once

#include "Piece.h"

/// <summary>
/// Represents the Bishop game piece
/// </summary>
class Bishop : public Piece
{
public:
	using Piece::Piece;

	/// <summary>
	/// Finds all the legal bishop moves (diagonal lines)
	/// </summary>
	/// <returns> A list with all the possible legal moves </returns>
	const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() override {
		std::vector<std::pair<sf::Vector2i, Piece*>> moves;

		// Finds all the lines
		std::vector<std::pair<sf::Vector2i, Piece*>> drLine = CalculateLineMoves({ 1, 1 });
		std::vector<std::pair<sf::Vector2i, Piece*>> ulLine = CalculateLineMoves({ -1, -1 });
		std::vector<std::pair<sf::Vector2i, Piece*>> urLine = CalculateLineMoves({ 1, -1 });
		std::vector<std::pair<sf::Vector2i, Piece*>> dlLine = CalculateLineMoves({ -1, 1 });

		// Combines lines into a single list
		moves.insert(moves.end(), drLine.begin(), drLine.end());
		moves.insert(moves.end(), ulLine.begin(), ulLine.end());
		moves.insert(moves.end(), urLine.begin(), urLine.end());
		moves.insert(moves.end(), dlLine.begin(), dlLine.end());

		return moves;
	}
};

