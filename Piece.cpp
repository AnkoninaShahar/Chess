#include "Piece.h"

// Constructor for Pieces 
Piece::Piece(int x, int y, color col, const sf::Vector2i& boardSize) : pos({x, y}), col(col), boardSize(boardSize) {
	Board<Piece>::SetSpace(x, y, this);
}

/// <summary>
/// Moves this piece to a given (x, y) position
/// </summary>
/// <param name="x"> x-coordinate of the position </param>
/// <param name="y"> y-coordinate of the position </param>
/// <returns> True: move was made; False: move was not made</returns>
bool Piece::Move(int x, int y, std::vector<std::pair<sf::Vector2i, Piece*>> legalMoves) {
	for (std::pair<sf::Vector2i, Piece*> move : legalMoves) {
		if (move.first == sf::Vector2i({ x, y })) {
			
			// Captures other piece
			if (move.second != Board<Piece>::BLANK_SPACE)
				Board<Piece>::SetSpace(move.second->pos.x, move.second->pos.y, nullptr);

			// Moves piece
			Board<Piece>::SetSpace(pos.x, pos.y, nullptr);
			Board<Piece>::SetSpace(x, y, this);
			pos = { x, y };

			moveNum++;
			return true;
		}
	}
	return false;
}

/// <summary>
/// Checks if a move is legal given a move
/// </summary>
/// <param name="x"> x-coordinate of a move </param>
/// <param name="y"> y-coordinate of a move </param>
/// <returns> True: move is legal; False: move is illegal </returns>
bool Piece::IsLegalMove(int x, int y) {
	bool isOutOfBounds = (x <= -1 || x >= boardSize.x) || (y <= -1 || y >= boardSize.y);
	if (!isOutOfBounds) {
		bool isOnOwn = (Board<Piece>::GetSpace(x, y) != Board<Piece>::BLANK_SPACE) && ((*Board<Piece>::GetSpace(x, y)).GetColor() == col);
		return !isOnOwn;
	}
	else
		return !isOutOfBounds;
}

/// <summary>
/// Finds all moves in a line (straight or diagonal)
/// </summary>
/// <param name="dir"> Direction of the line </param>
/// <returns> A list of all the moves </returns>
const std::vector<std::pair<sf::Vector2i, Piece*>> Piece::CalculateLineMoves(sf::Vector2i dir) {
	std::vector<std::pair<sf::Vector2i, Piece*>> moves = std::vector<std::pair<sf::Vector2i, Piece*>>(0);

	sf::Vector2i nextMove = sf::Vector2i({ pos.x + dir.x, pos.y + dir.y });
	while (IsLegalMove(nextMove.x, nextMove.y)) {
		if (Board<Piece>::GetSpace(nextMove.x, nextMove.y) != Board<Piece>::BLANK_SPACE) {
			moves.push_back(std::pair<sf::Vector2i, Piece*>(nextMove, Board<Piece>::GetSpace(nextMove.x, nextMove.y)));
			break;
		}
		moves.push_back(std::pair<sf::Vector2i, Piece*>(nextMove, Board<Piece>::GetSpace(nextMove.x, nextMove.y)));
		nextMove = sf::Vector2i({ nextMove.x + dir.x, nextMove.y + dir.y });
	}

	return moves;
}