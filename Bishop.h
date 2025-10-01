#include "Piece.h"

#pragma once
class Bishop : public Piece
{
public:
	using Piece::Piece;
	const std::vector<sf::Vector2i> CalculateLegalMoves() override;
};

