#include "Piece.h"

// Constructor for Pieces 
Piece::Piece(int x, int y, color col, Board<Piece>& board) : pos({x, y}), col(col), board(board) {
	board.SetSpace(x, y, this);

	// Sets up the game sounds
	//__________________________________________________________
	if (!moveSoundBuffer.loadFromFile("Audio/Move.mp3") || 
		!captureSoundBuffer.loadFromFile("Audio/Capture.mp3"))
		std::cout << "FAILED TO LOAD AUDIO FILE(S)" << std::endl;

	sounds[0] = new sf::Sound(moveSoundBuffer);
	sounds[1] = new sf::Sound(captureSoundBuffer);
}

Piece::~Piece() {
	for (sf::Sound* sound : sounds) {
		delete sound;
	}
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
			if (move.second != nullptr) {
				capture = move.second;
				board.SetSpace(move.second->pos.x, move.second->pos.y, nullptr);
				sounds[1]->play();
			}
			else 
				sounds[0]->play();

			// Moves piece
			board.SetSpace(pos.x, pos.y, nullptr);
			board.SetSpace(x, y, this);
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
	bool isOutOfBounds = (x <= -1 || x >= board.GetSize().x) || (y <= -1 || y >= board.GetSize().y);
	if (!isOutOfBounds) {
		bool isOnOwn = (board.GetSpace(x, y) != nullptr) && ((*board.GetSpace(x, y)).GetColor() == col);
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
		if (board.GetSpace(nextMove.x, nextMove.y) != nullptr) {
			moves.push_back(std::pair<sf::Vector2i, Piece*>(nextMove, board.GetSpace(nextMove.x, nextMove.y)));
			break;
		}
		moves.push_back(std::pair<sf::Vector2i, Piece*>(nextMove, board.GetSpace(nextMove.x, nextMove.y)));
		nextMove = sf::Vector2i({ nextMove.x + dir.x, nextMove.y + dir.y });
	}

	return moves;
}