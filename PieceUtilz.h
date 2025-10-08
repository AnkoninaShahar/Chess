#pragma once

#include "Piece.h"
#include "Board.h"

#include <vector>

namespace PieceUtilz {

	Board<Piece>* board = nullptr;

	void SetBoard(Board<Piece>* b) {
		board = b;
	}

	bool IsChecked(Piece::color col) {
		std::vector<Piece*> pieces = FindPieces(col);

		for (Piece* p : pieces) {
			for (const auto& move : p->CalculateLegalMoves()) {

				Piece* space = board->GetSpace(move.first.x, move.first.y);
				if (space != board->BLANK_SPACE) {
					std::string pieceName = typeid(*space).name();
					if (pieceName.find("King") != std::string::npos && space->GetColor() != col) {
						return true;
					}
				}

			}
		}

		return false;
	}

	std::vector<Piece*> FindPieces(Piece::color col) {
		std::vector<Piece*> pieces;
		pieces.reserve(16);

		for (int i = 0; i < board->GetSize().x; ++i) {
			for (int j = 0; j < board->GetSize().y; ++j) {
				Piece* p = board->GetSpace(i, j);
				if (p != board->BLANK_SPACE && p->GetColor() == col)
					pieces.push_back(board->GetSpace(i, j));
			}
		}
		return pieces;
	}
}