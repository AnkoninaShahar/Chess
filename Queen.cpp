#include "Queen.h"

const std::vector<sf::Vector2i> Queen::CalculateLegalMoves() {
	std::vector<sf::Vector2i> moves;
	
	// Straight
	for (int i = 1; i < boardSize.x; ++i) {
		if (!IsLegalMove(pos.x + i, pos.y))
			break;
		else if (Board<Piece>::GetSpace(pos.x + i, pos.y) != nullptr) {
			moves.push_back({ pos.x + i, pos.y });
			break;
		}
		moves.push_back({ pos.x + i, pos.y });
	}
	for (int i = 1; i < boardSize.x; ++i) {
		if (!IsLegalMove(pos.x, pos.y + i))
			break;
		else if (Board<Piece>::GetSpace(pos.x, pos.y + i) != nullptr) {
			moves.push_back({ pos.x, pos.y + i });
			break;
		}
		moves.push_back({ pos.x, pos.y + i });
	}
	for (int i = 1; i < boardSize.x; ++i) {
		if (!IsLegalMove(pos.x - i, pos.y))
			break;
		else if (Board<Piece>::GetSpace(pos.x - i, pos.y) != nullptr) {
			moves.push_back({ pos.x - i, pos.y });
			break;
		}
		moves.push_back({ pos.x - i, pos.y });
	}
	for (int i = 1; i < boardSize.x; ++i) {
		if (!IsLegalMove(pos.x, pos.y - i))
			break;
		else if (Board<Piece>::GetSpace(pos.x, pos.y - i) != nullptr) {
			moves.push_back({ pos.x, pos.y - i });
			break;
		}
		moves.push_back({ pos.x, pos.y - i });
	}

	// Diagonals
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
