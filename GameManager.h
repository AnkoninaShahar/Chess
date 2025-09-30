#include "Board.h"
#include <SFML\Graphics.hpp>

#pragma once
class GameManager
{
public:
	GameManager();
	~GameManager();

	const void Render(sf::RenderWindow& window);

private:
	Board* board;
};

