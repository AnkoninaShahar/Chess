#include "Pawn.h"

const std::vector<sf::Vector2i> Pawn::CalculateLegalMoves() {
	std::vector<sf::Vector2i> moves;

	if (IsLegalMove(pos.x, pos.y + 1) && Board<Piece>::GetSpace(pos.x, pos.y + 1) == nullptr)
		moves.push_back({ pos.x, pos.y + 1 });

	for (int i = -1; i <= 1; ++i) {
		if (i != 0 && Board<Piece>::GetSpace(pos.x + i, pos.y + 1))
			moves.push_back({ pos.x + i, pos.y + 1});
	}

	return moves;
}