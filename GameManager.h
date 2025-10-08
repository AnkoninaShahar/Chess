#pragma once

#include "Board.h"
#include "Piece.cpp"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

#include <typeinfo>
#include <iostream>
#include <SFML\Graphics.hpp>

/// <summary>
/// Manages all the aspects of this game
/// </summary>
class GameManager
{
public:
	GameManager(); // Constructor for the Game Manager
	~GameManager();

	const void DrawScreen(sf::RenderWindow& window);

private:
	Board<Piece>* board; // the Board
	Piece* p = nullptr; 

	// All the pieces in chess
	enum pieces {
		QUEEN,
		KING,
		ROOK,
		KNIGHT,
		BISHOP,
		PAWN,
	};
	pieces piece = pieces::KING;

	int turnNum = 0; // Number of turns

	const void DrawBackground(sf::RenderWindow& window);
	const void DrawBoard(sf::RenderWindow& window);
	const void DrawPieces(sf::RenderWindow& window);

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

	const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateCheckMoves(Piece* p) {
		std::vector<std::pair<sf::Vector2i, Piece*>> allMoves = p->CalculateLegalMoves();

		std::vector<std::vector<Piece*>> boardState(board->GetSize().x, std::vector<Piece*>(board->GetSize().y, nullptr));
		for (int i = 0; i < board->GetSize().x; ++i) {
			for (int j = 0; j < board->GetSize().y; ++j) {
				boardState.at(i).at(j) = board->GetSpace(i, j);
			}
		}

		std::vector<std::pair<sf::Vector2i, Piece*>> checkMoves;
		sf::Vector2i prePos;
		for (std::pair<sf::Vector2i, Piece*> move : allMoves) {
			prePos = { p->GetPosition().x, p->GetPosition().y };

			board->SetSpace(p->GetPosition().x, p->GetPosition().y, nullptr);
			board->SetSpace(p->GetPosition().x + move.first.x, p->GetPosition().y + move.first.y, p);
			//p->SetPosition({ p->GetPosition().x + move.first.x, p->GetPosition().y + move.first.y });

			if (!IsChecked(p->GetColor()))
				checkMoves.push_back(move);

			board->SetSpace(p->GetPosition().x, p->GetPosition().y, nullptr);
			board->SetSpace(prePos.x, prePos.y, p);
			//p->SetPosition({ prePos.x, prePos.y });

			//for (int i = 0; i < board->GetSize().x; ++i) {
			//	for (int j = 0; j < board->GetSize().y; ++j) {
			//		board->SetSpace(i, j, boardState.at(i).at(j));
			//		if (board->GetSpace(i, j) != nullptr)
			//			p->SetPosition({ i, j });
			//	}
			//}
		}

		return checkMoves;
	}
};

