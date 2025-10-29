#pragma once

#include "Board.h"
#include "Piece.cpp"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "NotationManager.h"
#include "Utilz.h"

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

	void DrawScreen(sf::RenderWindow& window);

	bool IsChecked(Piece::color col) const;
	bool CheckDraw();

	bool IsGameOver() {
		return gameOver;
	}

	// All the types of pieces in chess
	enum class Classification {
		QUEEN,
		KING,
		ROOK,
		KNIGHT,
		BISHOP,
		PAWN,
	};

	Classification Classify(const Piece& piece) {
		std::string pieceName = typeid(piece).name();

		Classification type = Classification::PAWN;

		if (pieceName.find("Pawn") != std::string::npos) type = Classification::PAWN;
		else if (pieceName.find("Knight") != std::string::npos) type = Classification::KNIGHT;
		else if (pieceName.find("Bishop") != std::string::npos) type = Classification::BISHOP;
		else if (pieceName.find("Rook") != std::string::npos) type = Classification::ROOK;
		else if (pieceName.find("Queen") != std::string::npos) type = Classification::QUEEN;
		else if (pieceName.find("King") != std::string::npos) type = Classification::KING;

		return type;
	}

private:
	mutable Board<Piece> board; // the Board
	Piece* selected = nullptr; 
	Piece* held = nullptr;
	Piece* lastMoved = nullptr;

	//NotationManager* printer = nullptr;


	//Piece* lastMovedCheck = nullptr;

	//classification type = KING;

	std::vector<Piece*> captured;
	//bool captureTurn = false;
	std::vector<sf::Vector2i> moveHistory;

	int turn = 0; // Number of turns
	size_t numberCaptured = 0;
	int fiftyMoveLimit = 0;

	bool gameOver = false;
	bool mouseClicked = false;

	void DrawBackground(sf::RenderWindow& window) const;
	void DrawBoard(sf::RenderWindow& window);
	void DrawPieces(sf::RenderWindow& window);
	void DrawText(std::string text, sf::Font font, sf::RenderWindow& window);

	void ControlBoard(sf::RenderWindow& window);
	void SelectPiece(sf::RenderWindow& window);
	void HoldPiece(sf::RenderWindow& window);
	void ReleasePiece(sf::RenderWindow& window);
	void MovePiece(Piece* piece);
	void SelectPromotion();

	void DrawCapturedPieces(sf::RenderWindow& window);

	std::vector<std::pair<sf::Vector2i, Piece*>> CalculateCheckMoves(Piece* p);
	bool Checkmate(sf::RenderWindow& window);

	bool Draw(sf::RenderWindow& window);

	std::vector<Piece*> FindPieces(Piece::color col) const;
	void GetDrawingUtensils(sf::Texture& tex, sf::Vector2i& texSize, sf::IntRect rects[], float& smallestScreenSide, sf::RenderWindow& window);
};

