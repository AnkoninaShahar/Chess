#pragma once

#include "Piece.h"

/// <summary>
/// Represents the Queen game piece
/// </summary>
class Queen : public Piece
{
public:
	using Piece::Piece; // Uses piece constructors

	/// <summary>
	/// Finds all the legal queen moves (straight & diagonal lines)
	/// </summary>
	/// <returns> A list with all the possible legal moves </returns>
	const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() override {
		std::vector<std::pair<sf::Vector2i, Piece*>> moves;

		// STRAIGHT LINES
		//______________________________________________________
		std::vector<std::pair<sf::Vector2i, Piece*>> rLine = CalculateLineMoves({ 1, 0 });
		std::vector<std::pair<sf::Vector2i, Piece*>> lLine = CalculateLineMoves({ -1, 0 });
		std::vector<std::pair<sf::Vector2i, Piece*>> uLine = CalculateLineMoves({ 0, -1 });
		std::vector<std::pair<sf::Vector2i, Piece*>> dLine = CalculateLineMoves({ 0, 1 });

		moves.insert(moves.end(), rLine.begin(), rLine.end());
		moves.insert(moves.end(), lLine.begin(), lLine.end());
		moves.insert(moves.end(), uLine.begin(), uLine.end());
		moves.insert(moves.end(), dLine.begin(), dLine.end());

		// DIAGONAL LINES
		//______________________________________________________
		std::vector<std::pair<sf::Vector2i, Piece*>> drLine = CalculateLineMoves({ 1, 1 });
		std::vector<std::pair<sf::Vector2i, Piece*>> ulLine = CalculateLineMoves({ -1, -1 });
		std::vector<std::pair<sf::Vector2i, Piece*>> urLine = CalculateLineMoves({ 1, -1 });
		std::vector<std::pair<sf::Vector2i, Piece*>> dlLine = CalculateLineMoves({ -1, 1 });

		moves.insert(moves.end(), drLine.begin(), drLine.end());
		moves.insert(moves.end(), ulLine.begin(), ulLine.end());
		moves.insert(moves.end(), urLine.begin(), urLine.end());
		moves.insert(moves.end(), dlLine.begin(), dlLine.end());

		return moves;
	}
};


