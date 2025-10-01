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

#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();

	const void Render(sf::RenderWindow& window);

private:
	Board<Piece>* board;

	enum pieces {
		QUEEN,
		KING,
		ROOK,
		KNIGHT,
		BISHOP,
		PAWN,
	};
	pieces piece = pieces::KING;
};

