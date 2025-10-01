#include "Piece.h"
#include "board.h"

Piece::Piece(int x, int y, color col, const sf::Vector2i& boardSize) : pos({x, y}), col(col), boardSize(boardSize) {
	Board<Piece>::SetSpace(x, y, this);
}

void Piece::Move(int x, int y) {
	std::vector<sf::Vector2i> moves = CalculateLegalMoves();
	if (std::find(moves.begin(), moves.end(), sf::Vector2i({ x, y })) != moves.end()) {
		if (Board<Piece>::GetSpace(x, y) != nullptr) {
			// CAPTURE
		}
		Board<Piece>::SetSpace(pos.x, pos.y, nullptr);
		Board<Piece>::SetSpace(x, y, this);
	}
}

bool Piece::IsLegalMove(int x, int y) {
	bool isOnOwn = Board<Piece>::GetSpace(x, y)->GetColor() == col;
	bool isOutOfBounds = (x <= -1 || x >= boardSize.x) && (y <= -1 || y >= boardSize.y);

	return !isOnOwn && !isOutOfBounds;
}