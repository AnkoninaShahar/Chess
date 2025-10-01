#include "Piece.h"

#pragma once
class Knight : public Piece
{
public:
	using Piece::Piece;
	const std::vector<sf::Vector2i> CalculateLegalMoves() override;
};

