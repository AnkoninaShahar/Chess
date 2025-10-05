#pragma once

#include "Piece.h"

/// <summary>
/// Represents the Rook game piece
/// </summary>
class Rook : public Piece
{
public:
	using Piece::Piece; // Uses piece constructors

	/// <summary>
	/// Finds all the legal rook moves (straight lines)
	/// </summary>
	/// <returns> A list with all the possible legal moves </returns>
	const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() override {
		std::vector<std::pair<sf::Vector2i, Piece*>> moves;

		// Finds all the lines
		std::vector<std::pair<sf::Vector2i, Piece*>> rLine = CalculateLineMoves({ 1, 0 });
		std::vector<std::pair<sf::Vector2i, Piece*>> lLine = CalculateLineMoves({ -1, 0 });
		std::vector<std::pair<sf::Vector2i, Piece*>> uLine = CalculateLineMoves({ 0, -1 });
		std::vector<std::pair<sf::Vector2i, Piece*>> dLine = CalculateLineMoves({ 0, 1 });

		// Combines lines into a single list
		moves.insert(moves.end(), rLine.begin(), rLine.end());
		moves.insert(moves.end(), lLine.begin(), lLine.end());
		moves.insert(moves.end(), uLine.begin(), uLine.end());
		moves.insert(moves.end(), dLine.begin(), dLine.end());

		return moves;
	}
};

