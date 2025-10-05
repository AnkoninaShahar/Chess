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

};

