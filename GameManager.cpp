#include "GameManager.h"

// Game Manager Constructor
GameManager::GameManager() {
	board = new Board<Piece>(); // Creates the board

	// Sets up the game pieces
	//__________________________________________________________

	new King(4, 7, Piece::WHITE, board->GetSize());
	new King(4, 0, Piece::BLACK, board->GetSize());

	new Queen(3, 7, Piece::WHITE, board->GetSize());
	new Queen(3, 0, Piece::BLACK, board->GetSize());

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

// Deletes the board
GameManager::~GameManager() {
	delete board;
}

/// <summary>
/// Renders every aspect of the screen
/// </summary>
/// <param name="window"> The window drawn on </param>
const void GameManager::DrawScreen(sf::RenderWindow& window) {
	DrawBackground(window);
	DrawBoard(window);
	DrawPieces(window);

	//std::cout << IsChecked(Piece::BLACK) << std::endl;
	//std::cout << IsChecked(Piece::WHITE) << std::endl;
}

/// <summary>
/// Renders the background color behind the board
/// </summary>
/// <param name="window"> The window drawn on </param>
const void GameManager::DrawBackground(sf::RenderWindow& window) {

	// Draws background color
	sf::RectangleShape background;
	background.setSize({ static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y) });
	background.setFillColor(sf::Color(48, 37, 28));
	window.draw(background);
}

/// <summary>
/// Renders the board
/// </summary>
/// <param name="window"> The window drawn on </param>
const void GameManager::DrawBoard(sf::RenderWindow& window) {

	// Draws the board
	board->Render(window);

	if (p != nullptr && p->CanPromote()) {
		int choice = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
			choice = 1;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
			choice = 2;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
			choice = 3;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4))
			choice = 4;

		if (choice != 0) {
			p->Promote(choice);
			turnNum++;
			p = nullptr;
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		board->ClearSelectedSpaces();
		sf::Vector2i boardPos = board->PositionToSpace(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		board->AddSelectedSpace(boardPos.x, boardPos.y);

		if (p != board->BLANK_SPACE && boardPos != p->GetPosition() && (turnNum % 2 == 0) == p->GetColor()) {

			//std::vector<std::pair<sf::Vector2i, Piece*>> moves;
			//if (IsChecked(p->GetColor()))
			//	moves = CalculateCheckMoves(p);
			//else 
			//	moves = p->CalculateLegalMoves();

			if (p->Move(boardPos.x, boardPos.y, CalculateCheckMoves(p)) && !p->CanPromote())
				turnNum++;
			p = nullptr;
		}
		else {
			p = board->GetSpace(boardPos.x, boardPos.y);
			if (p != board->BLANK_SPACE && (turnNum % 2 == 0) == p->GetColor()) {
				p->SetCheck(IsChecked(p->GetColor()));

				//std::vector<std::pair<sf::Vector2i, Piece*>> moves;
				//if (IsChecked(p->GetColor()))
				//	moves = CalculateCheckMoves(p);
				//else
				//	moves = p->CalculateLegalMoves();

				for (std::pair<sf::Vector2i, Piece*> move : CalculateCheckMoves(p)) {
					board->AddSelectedSpace(move.first.x, move.first.y);
				}
			}
		}
	}
}

/// <summary>
/// Renders the pieces
/// </summary>
/// <param name="window"> The window drawn on </param>
const void GameManager::DrawPieces(sf::RenderWindow& window) {

	// Loads the texture
	sf::Texture tex;
	if (!tex.loadFromFile("Sprites/Chess_Sprite_Sheet.png"))
		window.close();

	// Seperates the sprites
	sf::Vector2i texSize = { static_cast<int>(tex.getSize().x), static_cast<int>(tex.getSize().y) };
	sf::IntRect rects[12];
	for (int i = 0; i < 12; ++i) {
		rects[i] = sf::IntRect({ texSize.x * ((i >= 6) ? (i - 6) : i) / 6, ((i >= 6) ? texSize.y / 2 : 0) }, { texSize.x / 6, texSize.y / 2 });
	}

	// Draws the sprites
	float smallestScreenSide = fminf(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	for (int i = 0; i < board->GetSize().x; ++i) {
		for (int j = 0; j < board->GetSize().y; ++j) {
			if (board->GetSpace(i, j) != board->BLANK_SPACE) {
				board->GetSpace(i, j)->Update(turnNum);

				std::string pieceName = typeid(*board->GetSpace(i, j)).name();

				if (pieceName.find("Pawn") != std::string::npos) piece = PAWN;
				else if (pieceName.find("Knight") != std::string::npos) piece = KNIGHT;
				else if (pieceName.find("Bishop") != std::string::npos) piece = BISHOP;
				else if (pieceName.find("Rook") != std::string::npos) piece = ROOK;
				else if (pieceName.find("Queen") != std::string::npos) piece = QUEEN;
				else if (pieceName.find("King") != std::string::npos) piece = KING;

				sf::Sprite sprite(tex);
				sprite.setTextureRect(rects[((*board->GetSpace(i, j)).GetColor() == Piece::WHITE) ? piece + 6 : piece]);
				sprite.setPosition({ i * board->GetSpaceSize().x + board->GetBoardOffset().x, j * board->GetSpaceSize().y + board->GetBoardOffset().y});
				sprite.setScale({ smallestScreenSide / 500, smallestScreenSide / 500 });
				window.draw(sprite);
			}
		}
	}
}
