#include "GameManager.h"

// Game Manager Constructor
GameManager::GameManager() {
	printer = new NotationManager(board);

	players[0] = new Player(board, Piece::WHITE, *printer); 
	players[1] = new Player(board, Piece::BLACK, *printer);

	// Sets up the game pieces
	//__________________________________________________________

	new King(4, 7, Piece::WHITE, board);
	new King(4, 0, Piece::BLACK, board);

	new Queen(3, 7, Piece::WHITE, board);
	new Queen(3, 0, Piece::BLACK, board);

	new Bishop(2, 7, Piece::WHITE, board);
	new Bishop(5, 7, Piece::WHITE, board);
	new Bishop(2, 0, Piece::BLACK, board);
	new Bishop(5, 0, Piece::BLACK, board);

	new Knight(1, 7, Piece::WHITE, board);
	new Knight(6, 7, Piece::WHITE, board);
	new Knight(1, 0, Piece::BLACK, board);
	new Knight(6, 0, Piece::BLACK, board);

	new Rook(0, 7, Piece::WHITE, board);
	new Rook(7, 7, Piece::WHITE, board);
	new Rook(0, 0, Piece::BLACK, board);
	new Rook(7, 0, Piece::BLACK, board);

	for (int i = 0; i < 8; ++i) {
		new Pawn(i, 1, Piece::BLACK, board);
		new Pawn(i, 6, Piece::WHITE, board);
	}
}

// Deletes the board
GameManager::~GameManager() {
}

void GameManager::Update(sf::RenderWindow& window) {
	current = players[turn % 2 == 0];

	DrawScreen(window);

	if (current->GetHeld() == nullptr)
		gameOver = Draw(window) || Checkmate(window);

	if (gameOver)
		printer->SetGameStatus(game);
	printer->Print(current->GetLastMoved());

	if (!gameOver)
		turn = players[0]->GetMoveHistory().size() + players[1]->GetMoveHistory().size() + 1;
}

// GRAPHICS SYSTEM
//___________________________________________________________________

/// <summary>
/// Renders every aspect of the screen
/// </summary>
/// <param name="window"> The window drawn on </param>
void GameManager::DrawScreen(sf::RenderWindow& window) {
	DrawBackground(window);
	DrawBoard(window);
}
/// <summary>
/// Renders the background color behind the board
/// </summary>
/// <param name="window"> The window drawn on </param>
void GameManager::DrawBackground(sf::RenderWindow& window) const {

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
void GameManager::DrawBoard(sf::RenderWindow& window) {

	// Draws the board
	board.Render(window);
	DrawPieces(window);

	if (!gameOver)
		current->ControlBoard(window);

	DrawCapturedPieces(window);
}
/// <summary>
/// Renders the pieces
/// </summary>
/// <param name="window"> The window drawn on </param>
void GameManager::DrawPieces(sf::RenderWindow& window) const {
	sf::Texture tex;
	sf::Vector2i texSize;
	sf::IntRect rects[12];
	float smallestScreenSide;
	Utilz::General::GetDrawingUtensils(tex, texSize, rects, smallestScreenSide, window);

	// Draws the sprites
	for (int i = 0; i < board.GetSize().x; ++i) {
		for (int j = 0; j < board.GetSize().y; ++j) {
			if (board.GetSpace(i, j) != nullptr) {
				board.GetSpace(i, j)->Update(static_cast<int>(turn));

				Utilz::Type::classification type = Utilz::Type::Classify(*board.GetSpace(i, j));
				int typeValue = static_cast<int>(type);

				sf::Sprite sprite(tex);
				sprite.setTextureRect(rects[((*board.GetSpace(i, j)).GetColor() == Piece::WHITE) ? typeValue + 6 : typeValue]);
				sprite.setPosition({ i * board.GetSpaceSize().x + board.GetBoardOffset().x, j * board.GetSpaceSize().y + board.GetBoardOffset().y});
				sprite.setScale({ smallestScreenSide / 500, smallestScreenSide / 500 });
				window.draw(sprite);
			}
		}
	}
}
void GameManager::DrawCapturedPieces(sf::RenderWindow& window) const {
	sf::Texture tex;
	sf::Vector2i texSize;
	sf::IntRect rects[12];
	float smallestScreenSide;
	Utilz::General::GetDrawingUtensils(tex, texSize, rects, smallestScreenSide, window);

	std::vector<Piece*> captured = players[0]->GetCaptured();
	for (Piece* capture : players[1]->GetCaptured())
		captured.push_back(capture);

	int whitePos = 0, blackPos = 0;
	for (Piece* pieceCaptured : captured) {
		Utilz::Type::classification type = Utilz::Type::Classify(*pieceCaptured);
		int typeValue = static_cast<int>(type);

		sf::Sprite sprite(tex);
		if ((*pieceCaptured).GetColor() == Piece::WHITE) {
			sprite.setTextureRect(rects[typeValue + 6]);
			sprite.setPosition({ 5 + static_cast<float>(whitePos) * smallestScreenSide / 20, 0 });
			whitePos++;
		}
		else {
			sprite.setTextureRect(rects[typeValue]);
			sprite.setPosition({ 5 + static_cast<float>(blackPos) * smallestScreenSide / 20, static_cast<float>(window.getSize().y) - smallestScreenSide / 12.5f });
			blackPos++;
		}
		sprite.setScale({ smallestScreenSide / 850, smallestScreenSide / 850 });
		window.draw(sprite);
	}
}
void GameManager::DrawText(std::string text, sf::Font font, sf::RenderWindow& window) const {
	sf::Text drawText(font, text, 20);
	drawText.setPosition({ 20, 20 });
	drawText.setOutlineColor(sf::Color::Black);
	drawText.setOutlineThickness(5);
	drawText.setFillColor(sf::Color::White);

	window.draw(drawText);
}


// GAME END SYSTEM
//___________________________________________________________________

bool GameManager::Checkmate(sf::RenderWindow& window) {
	std::vector<Piece*> pieces = Utilz::General::FindPieces(board, static_cast<Piece::color>(turn % 2 == 0));

	size_t numberOfMoves = 0;
	for (Piece* piece : pieces)
		numberOfMoves += players[turn % 2]->CalculateCheckMoves(piece).size();

	if (numberOfMoves == 0) {
		sf::Font font("Fonts/Maketa.ttf");
		std::string text = (turn % 2 == 0) ? "BLACK" : "WHITE";
		text += " WINS!";

		DrawText(text, font, window);

		game = CHECKMATE;
		return true;
	}
	return false;
}
bool GameManager::Draw(sf::RenderWindow& window) {
	if (players[turn % 2]->CheckDraw()) {
		sf::Font font("Fonts/Maketa.ttf");
		std::string text = "DRAW!";

		DrawText(text, font, window);
		game = DRAW;
		return true;
	}
	return false;
}