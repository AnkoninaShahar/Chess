#pragma once

#include "Board.h"
#include "Piece.cpp"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Player.h"
#include "NotationManager.h"
#include "Utilz.h"

#include <typeinfo>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace Utilz;

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

	Player* players[2] = { nullptr, nullptr };

	enum status {
		ONGOING,
		DRAW,
		CHECKMATE
	};
	status game = ONGOING;

	NotationManager* printer = nullptr;

	size_t turn = 0; // Number of turns

	bool gameOver = false;

	void DrawBackground(sf::RenderWindow& window) const;
	void DrawBoard(sf::RenderWindow& window);
	void DrawPieces(sf::RenderWindow& window);
	void DrawText(std::string text, sf::Font font, sf::RenderWindow& window);

	void DrawCapturedPieces(sf::RenderWindow& window);

	bool Checkmate(sf::RenderWindow& window);

	bool Draw(sf::RenderWindow& window);
};

