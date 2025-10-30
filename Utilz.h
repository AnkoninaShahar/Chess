#pragma once

#include "Piece.h"

namespace Utilz {
	class Type {
	public:
		// All the types of pieces in chess
		enum classification {
			QUEEN,
			KING,
			ROOK,
			KNIGHT,
			BISHOP,
			PAWN,
		};

		static classification Classify(const Piece& piece) {
			std::string pieceName = typeid(piece).name();

			classification type = classification::PAWN;

			if (pieceName.find("Pawn") != std::string::npos) type = classification::PAWN;
			else if (pieceName.find("Knight") != std::string::npos) type = classification::KNIGHT;
			else if (pieceName.find("Bishop") != std::string::npos) type = classification::BISHOP;
			else if (pieceName.find("Rook") != std::string::npos) type = classification::ROOK;
			else if (pieceName.find("Queen") != std::string::npos) type = classification::QUEEN;
			else if (pieceName.find("King") != std::string::npos) type = classification::KING;

			return type;
		}
	};
}