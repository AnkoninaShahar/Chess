#pragma once

#include "Piece.h"
#include "Board.h"

namespace Utilz {
	class General {
	public:
		static std::vector<Piece*> FindPieces(Board<Piece>& board, Piece::color col) {
			std::vector<Piece*> pieces;
			pieces.reserve(16);

			for (int i = 0; i < board.GetSize().x; ++i) {
				for (int j = 0; j < board.GetSize().y; ++j) {
					Piece* p = board.GetSpace(i, j);
					if (p != nullptr && p->GetColor() == col)
						pieces.push_back(board.GetSpace(i, j));
				}
			}
			return pieces;
		}

		static void GetDrawingUtensils(sf::Texture& tex, sf::Vector2i& texSize, sf::IntRect rects[], float& smallestScreenSide, sf::RenderWindow& window) {
			// Loads the texture
			if (!tex.loadFromFile("Sprites/Chess_Sprite_Sheet.png"))
				window.close();

			// Seperates the sprites
			texSize = { static_cast<int>(tex.getSize().x), static_cast<int>(tex.getSize().y) };
			for (int i = 0; i < 12; ++i)
				rects[i] = sf::IntRect({ texSize.x * ((i >= 6) ? (i - 6) : i) / 6, ((i >= 6) ? texSize.y / 2 : 0) }, { texSize.x / 6, texSize.y / 2 });

			smallestScreenSide = fminf(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
		}

	};

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