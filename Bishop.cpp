#include "Bishop.h"

const std::vector<sf::Vector2i> Bishop::CalculateLegalMoves() {
	std::vector<sf::Vector2i> moves;

	for (int i = 1; i < boardSize.x; ++i) {
		if (!IsLegalMove(pos.x + i, pos.y + i))
			break;
		else if (Board<Piece>::GetSpace(pos.x + i, pos.y + i) != nullptr) {
			moves.push_back({ pos.x + i, pos.y + i });
			break;
		}
		moves.push_back({ pos.x + i, pos.y + i });
	}
	for (int i = 1; i < boardSize.x; ++i) {
		if (!IsLegalMove(pos.x - i, pos.y + i))
			break;
		else if (Board<Piece>::GetSpace(pos.x - i, pos.y + i) != nullptr) {
			moves.push_back({ pos.x - i, pos.y + i });
			break;
		}
		moves.push_back({ pos.x - i, pos.y + i });
	}
	for (int i = 1; i < boardSize.x; ++i) {
		if (!IsLegalMove(pos.x + i, pos.y - i))
			break;
		else if (Board<Piece>::GetSpace(pos.x + i, pos.y - i) != nullptr) {
			moves.push_back({ pos.x + i, pos.y - i });
			break;
		}
		moves.push_back({ pos.x + i, pos.y - i });
	}
	for (int i = 1; i < boardSize.x; ++i) {
		if (!IsLegalMove(pos.x - i, pos.y - i))
			break;
		else if (Board<Piece>::GetSpace(pos.x - i, pos.y - i) != nullptr) {
			moves.push_back({ pos.x - i, pos.y - i });
			break;
		}
		moves.push_back({ pos.x - i, pos.y - i });
	}

	return moves;
}
