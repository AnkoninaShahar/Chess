#include "GameManager.h"

GameManager::GameManager() {
	board = new Board<Piece>();

	new King(3, 7, Piece::WHITE, board->GetSize());
	new King(3, 0, Piece::BLACK, board->GetSize());

	new Queen(4, 7, Piece::WHITE, board->GetSize());
	new Queen(4, 0, Piece::BLACK, board->GetSize());

	new Bishop(2, 7, Piece::WHITE, board->GetSize());
	new Bishop(5, 7, Piece::WHITE, board->GetSize());
	new Bishop(2, 0, Piece::BLACK, board->GetSize());
	new Bishop(5, 0, Piece::BLACK, board->GetSize());

	new Knight(1, 7, Piece::WHITE, board->GetSize());
	new Knight(6, 7, Piece::WHITE, board->GetSize());
	new Knight(1, 0, Piece::BLACK, board->GetSize());
	new Knight(6, 0, Piece::BLACK, board->GetSize());

	new Rook(0, 7, Piece::WHITE, board->GetSize());
	new Rook(7, 7, Piece::WHITE, board->GetSize());
	new Rook(0, 0, Piece::BLACK, board->GetSize());
	new Rook(7, 0, Piece::BLACK, board->GetSize());

	for (int i = 0; i < 8; ++i) {
		new Pawn(i, 1, Piece::BLACK, board->GetSize());
		new Pawn(i, 6, Piece::WHITE, board->GetSize());
	}
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

	sf::Texture tex;
	if (!tex.loadFromFile("Sprites/Chess_Sprite_Sheet.png"))
		window.close();

	sf::Vector2i texSize = { static_cast<int>(tex.getSize().x), static_cast<int>(tex.getSize().y) };
	sf::IntRect rects[12];

	for (int i = 0; i < 12; ++i) {
		rects[i] = sf::IntRect({ texSize.x * ((i >= 6) ? (i - 6) : i) / 6, ((i >= 6) ? texSize.y / 2 : 0) }, { texSize.x / 6, texSize.y / 2 });
	}

	sf::Vector2f windowSize = { static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) };
	float smallestScreenSide = fminf(windowSize.x, windowSize.y);

	float width = smallestScreenSide / board->GetSize().x;
	float height = smallestScreenSide / board->GetSize().y;

	sf::Vector2f centerOffset = { windowSize.x / 2 - (width * board->GetSize().y) / 2, windowSize.y / 2 - (height * board->GetSize().x) / 2 };

	for (int i = 0; i < board->GetSize().x; ++i) {
		for (int j = 0; j < board->GetSize().y; ++j) {
			if (board->GetSpace(i, j) != nullptr) {
				std::string pieceName = typeid(*board->GetSpace(i, j)).name();

				if (pieceName.find("Pawn") != std::string::npos) piece = PAWN;
				else if (pieceName.find("Knight") != std::string::npos) piece = KNIGHT;
				else if (pieceName.find("Bishop") != std::string::npos) piece = BISHOP;
				else if (pieceName.find("Rook") != std::string::npos) piece = ROOK;
				else if (pieceName.find("Queen") != std::string::npos) piece = QUEEN;
				else if (pieceName.find("King") != std::string::npos) piece = KING;

				sf::Sprite sprite(tex);
				sprite.setTextureRect(rects[(board->GetSpace(i, j)->GetColor() == Piece::WHITE) ? piece + 6 : piece]);
				sprite.setPosition({ i * width + centerOffset.x, j * height + centerOffset.y});
				sprite.setScale({ smallestScreenSide / 500, smallestScreenSide / 500 });
				window.draw(sprite);
			}
		}
	}
}