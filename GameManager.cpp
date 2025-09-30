#include "GameManager.h"

GameManager::GameManager() {
	board = new Board();
}
GameManager::~GameManager() {
	delete board;
}

const void GameManager::Render(sf::RenderWindow& window) {

	// Draws background color
	sf::RectangleShape background;
	background.setSize({ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) });
	background.setFillColor(sf::Color(48, 37, 28));
	window.draw(background);

	// Draws the board
	board->Render(window);
}