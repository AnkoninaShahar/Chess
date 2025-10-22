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

	void DrawScreen(sf::RenderWindow& window);

private:
	mutable Board<Piece> board; // the Board
	Piece* selected = nullptr; 
	Piece* held = nullptr;
	Piece* lastMoved = nullptr;
	Piece* lastMovedCheck = nullptr;

	// All the types of pieces in chess
	enum classification {
		QUEEN,
		KING,
		ROOK,
		KNIGHT,
		BISHOP,
		PAWN,
	};
	classification type = KING;

	std::vector<Piece*> captured;
	bool captureTurn = false;
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

	bool IsChecked(Piece::color col) const;
	std::vector<std::pair<sf::Vector2i, Piece*>> CalculateCheckMoves(Piece* p);
	bool Checkmate(sf::RenderWindow& window);

	bool CheckDraw();
	bool Draw(sf::RenderWindow& window);

	std::vector<Piece*> FindPieces(Piece::color col) const;
	GameManager::classification ClassifyPiece(const Piece& piece);
	void GetDrawingUtensils(sf::Texture& tex, sf::Vector2i& texSize, sf::IntRect rects[], float& smallestScreenSide, sf::RenderWindow& window);
	std::string ConvertMoveToString(Piece& piece);
};

