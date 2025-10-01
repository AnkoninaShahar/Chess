#include "Knight.h"

const std::vector<sf::Vector2i> Knight::CalculateLegalMoves() {
	std::vector<sf::Vector2i> moves;
	moves.push_back({ pos.x + 3, pos.y + 1 });
	moves.push_back({ pos.x + 3, pos.y - 1 });
	moves.push_back({ pos.x - 3, pos.y + 1 });
	moves.push_back({ pos.x - 3, pos.y - 1 });
	moves.push_back({ pos.x + 1, pos.y + 3 });
	moves.push_back({ pos.x + 1, pos.y - 3 });
	moves.push_back({ pos.x - 1, pos.y + 3 });
	moves.push_back({ pos.x - 1, pos.y - 3 });

	for (auto move = moves.end(); move != moves.begin(); --move) {
		if (!IsLegalMove((*move).x, (*move).y))
			moves.erase(move);
	}

	return moves;
}
