#pragma once

#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"

/// <summary>
/// Represents the Pawn game piece
/// </summary>
class Pawn : public Piece
{
public:
	using Piece::Piece; // Uses piece constructors

	// Deletes the en-passantable pawn
	~Pawn() {
		if (enPassantablePiece != nullptr)
			delete enPassantablePiece;
	}

	// Checks move along with checking if the pawn is en-passantable
	inline bool Move(int x, int y) override {
		sf::Vector2i prePos = pos;
		if (Piece::Move(x, y)) {
			if (moveNum == 1 && abs(pos.y - prePos.y) == 2)
				enPassantablePiece = new std::pair<Pawn, int>(*this, turnNum);
			return true;
		}
		return false;
	}

	/// <summary>
	/// Finds all the legal pawn moves (one space forward, two spaces forward, taking diagonally, en passant, & promoting)
	/// </summary>
	/// <returns> A list with all the possible legal moves </returns>
	const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() override {
		std::vector<std::pair<sf::Vector2i, Piece*>> moves = std::vector<std::pair<sf::Vector2i, Piece*>>(0);

		int dir = 1 - col * 2; // Direction based on the color of the pawn
		for (int i = -1; i <= 1; ++i) {
			if (i != 0 && IsLegalMove(pos.x + i, pos.y + dir)) {
				// Take diagonally
				if (Board<Piece>::GetSpace(pos.x + i, pos.y + dir) != Board<Piece>::BLANK_SPACE) {
					moves.push_back(std::pair<sf::Vector2i, Piece*>({ pos.x + i, pos.y + dir }, Board<Piece>::GetSpace(pos.x + i, pos.y + dir)));
				}

				// En Passant
				if (enPassantablePiece != nullptr && Board<Piece>::GetSpace(pos.x + i, pos.y) != Board<Piece>::BLANK_SPACE) {
					if (enPassantablePiece->first == *Board<Piece>::GetSpace(pos.x + i, pos.y) && (turnNum == enPassantablePiece->second + 1))
						moves.push_back(std::pair<sf::Vector2i, Piece*>({ pos.x + i, pos.y + dir }, Board<Piece>::GetSpace(pos.x + i, pos.y)));
				}
			}
			// Move one space forward
			else if (i == 0 && IsLegalMove(pos.x, pos.y + dir) && Board<Piece>::GetSpace(pos.x, pos.y + dir) == Board<Piece>::BLANK_SPACE)
				moves.push_back(std::pair<sf::Vector2i, Piece*>({ pos.x, pos.y + dir }, Board<Piece>::GetSpace(pos.x, pos.y + dir)));
		}

		// Move 2 spaces first move
		if (moveNum == 0) {
			if (IsLegalMove(pos.x, pos.y + dir) && Board<Piece>::GetSpace(pos.x, pos.y + 2 * dir) == nullptr)
				moves.push_back(std::pair<sf::Vector2i, Piece*>({ pos.x, pos.y + 2 * dir }, Board<Piece>::GetSpace(pos.x, pos.y + 2 * dir)));
		}

		return moves;
	}

	const void Promote(int choice) override {
		switch (choice) {
		case 1:
			new Queen(pos.x, pos.y, col, boardSize);
			break;
		case 2:
			new Rook(pos.x, pos.y, col, boardSize);
			break;
		case 3:
			new Knight(pos.x, pos.y, col, boardSize);
			break;
		default:
			new Bishop(pos.x, pos.y, col, boardSize);
			break;
		}
	}

private:
	static inline std::pair<Pawn, int>* enPassantablePiece = nullptr; // Tracks the pawn that is en-passantable
};

