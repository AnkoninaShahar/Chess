#pragma once

#include "Piece.h"
#include "Rook.h"

/// <summary>
/// Respresents the King game piece
/// </summary>
class King : public Piece
{
public:
	using Piece::Piece; // Uses piece constructors

	// Checks move along with checking if the king castled
	inline bool Move(int x, int y, std::vector<std::pair<sf::Vector2i, Piece*>> legalMoves) override {
		sf::Vector2i prePos = pos;
		if (Piece::Move(x, y, legalMoves)) {
			if (moveNum == 1) {
				if (prePos.x - pos.x == 2) {
					Piece* rook = board.GetSpace(0, pos.y);
					MoveRook(rook, { pos.x + 1, pos.y });
				}
				else if (pos.x - prePos.x == 2) {
					Piece* rook = board.GetSpace(7, pos.y);
					MoveRook(rook, { pos.x - 1, pos.y });
				}
			}

			return true;
		}
		return false;
	}

	/// <summary>
	/// Finds all the legal king moves (one space in any direction, castling, & checks)
	/// </summary>
	/// <returns> A list with all the possible legal moves </returns>
	const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() override {
		std::vector<std::pair<sf::Vector2i, Piece*>> moves;

		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				if (i == 0 && j == 0)
					continue;
				if (IsLegalMove(pos.x + i, pos.y + j))
					moves.push_back(std::pair<sf::Vector2i, Piece*>({ pos.x + i, pos.y + j }, board.GetSpace(pos.x + i, pos.y + j)));
			}
		}

		Piece* r1 = board.GetSpace(0, pos.y);
		Piece* r2 = board.GetSpace(7, pos.y);

		if (moveNum == 0 && !inCheck) {
			if (IsRook(r1) && r1->GetMoveNum() == 0) {
				bool pathCleared = true;

				for (int i = 1; i <= 3; ++i) {
					if (board.GetSpace(i, pos.y) != nullptr) {
						pathCleared = false;
						break;
					}
				}

				if (pathCleared)
					moves.push_back(std::pair<sf::Vector2i, Piece*>({ pos.x - 2, pos.y }, board.GetSpace(pos.x - 2, pos.y)));
			}

			if (IsRook(r2) && r2->GetMoveNum() == 0) {
				bool pathCleared = true;

				for (int i = 5; i <= 6; ++i) {
					if (board.GetSpace(i, pos.y) != nullptr) {
						pathCleared = false;
						break;
					}
				}

				if (pathCleared)
					moves.push_back(std::pair<sf::Vector2i, Piece*>({ pos.x + 2, pos.y }, board.GetSpace(pos.x + 2, pos.y)));
			}
		}

		return moves;
	}

	/// <summary>
	/// Checks that a piece is a rook
	/// </summary>
	/// <param name="p"> The piece being checked </param>
	/// <returns> True: the piece is a rook; False: the piece is not a rook </returns>
	const bool IsRook(Piece* p) {
		if (p != nullptr) {
			std::string pieceName = typeid(*p).name();
			return pieceName.find("Rook") != std::string::npos;
		}
		return false;
	}

	/// <summary>
	/// Moves a rook
	/// </summary>
	/// <param name="r"> The rook being moved </param>
	/// <param name="pos"> The new position of the rook </param>
	const void MoveRook(Piece* r, sf::Vector2i pos) {
		board.SetSpace(r->GetPosition().x, this->pos.y, nullptr);
		board.SetSpace(pos.x, this->pos.y, r);

		r->SetPosition(pos);
	}
};

