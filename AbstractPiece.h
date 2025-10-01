#include "Board.h"

#include <string>
#include <vector>
#include <SFML\Graphics.hpp>

#pragma once
class AbstractPiece
{
public:
	//inline virtual  ~AbstractPiece() = 0;

	inline virtual void Move(int x, int y) = 0;
	inline virtual const std::vector<sf::Vector2i> CalculateLegalMoves() = 0;

protected:
	inline virtual bool IsLegalMove(int x, int y) = 0;
};
