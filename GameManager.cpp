#include "GameManager.h"

// Game Manager Constructor
GameManager::GameManager() {
	captured.reserve(30);

	// Sets up the game pieces
	//__________________________________________________________

	new King(4, 7, Piece::WHITE, board.GetSize());
	new King(4, 0, Piece::BLACK, board.GetSize());

	new Queen(3, 7, Piece::WHITE, board.GetSize());
	new Queen(3, 0, Piece::BLACK, board.GetSize());

	new Bishop(2, 7, Piece::WHITE, board.GetSize());
	new Bishop(5, 7, Piece::WHITE, board.GetSize());
	new Bishop(2, 0, Piece::BLACK, board.GetSize());
	new Bishop(5, 0, Piece::BLACK, board.GetSize());

	new Knight(1, 7, Piece::WHITE, board.GetSize());
	new Knight(6, 7, Piece::WHITE, board.GetSize());
	new Knight(1, 0, Piece::BLACK, board.GetSize());
	new Knight(6, 0, Piece::BLACK, board.GetSize());

	new Rook(0, 7, Piece::WHITE, board.GetSize());
	new Rook(7, 7, Piece::WHITE, board.GetSize());
	new Rook(0, 0, Piece::BLACK, board.GetSize());
	new Rook(7, 0, Piece::BLACK, board.GetSize());

	for (int i = 0; i < 8; ++i) {
		new Pawn(i, 1, Piece::BLACK, board.GetSize());
		new Pawn(i, 6, Piece::WHITE, board.GetSize());
	}
}

// Deletes the board
GameManager::~GameManager() {
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

	if (held == nullptr)
		gameOver = Draw(window) || Checkmate(window);
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
		ControlBoard(window);

	DrawCapturedPieces(window);
}
/// <summary>
/// Renders the pieces
/// </summary>
/// <param name="window"> The window drawn on </param>
void GameManager::DrawPieces(sf::RenderWindow& window) {
	sf::Texture tex;
	sf::Vector2i texSize;
	sf::IntRect rects[12];
	float smallestScreenSide;
	GetDrawingUtensils(tex, texSize, rects, smallestScreenSide, window);

	// Draws the sprites
	for (int i = 0; i < board.GetSize().x; ++i) {
		for (int j = 0; j < board.GetSize().y; ++j) {
			if (board.GetSpace(i, j) != board.BLANK_SPACE) {
				board.GetSpace(i, j)->Update(turn);

				classification type = ClassifyPiece(*board.GetSpace(i, j));

				sf::Sprite sprite(tex);
				sprite.setTextureRect(rects[((*board.GetSpace(i, j)).GetColor() == Piece::WHITE) ? type + 6 : type]);
				sprite.setPosition({ i * board.GetSpaceSize().x + board.GetBoardOffset().x, j * board.GetSpaceSize().y + board.GetBoardOffset().y});
				sprite.setScale({ smallestScreenSide / 500, smallestScreenSide / 500 });
				window.draw(sprite);
			}
		}
	}
}
void GameManager::DrawCapturedPieces(sf::RenderWindow& window) {
	sf::Texture tex;
	sf::Vector2i texSize;
	sf::IntRect rects[12];
	float smallestScreenSide;
	GetDrawingUtensils(tex, texSize, rects, smallestScreenSide, window);

	int whitePos = 0, blackPos = 0;
	for (Piece* pieceCaptured : captured) {
		classification type = ClassifyPiece(*pieceCaptured);

		sf::Sprite sprite(tex);
		if ((*pieceCaptured).GetColor() == Piece::WHITE) {
			sprite.setTextureRect(rects[type + 6]);
			sprite.setPosition({ 5 + static_cast<float>(whitePos) * smallestScreenSide / 20, 0 });
			whitePos++;
		}
		else {
			sprite.setTextureRect(rects[type]);
			sprite.setPosition({ 5 + static_cast<float>(blackPos) * smallestScreenSide / 20, static_cast<float>(window.getSize().y) - smallestScreenSide / 12.5f });
			blackPos++;
		}
		sprite.setScale({ smallestScreenSide / 850, smallestScreenSide / 850 });
		window.draw(sprite);
	}
}
void GameManager::DrawText(std::string text, sf::Font font, sf::RenderWindow& window) {
	sf::Text drawText(font, text, 20);
	drawText.setPosition({ 20, 20 });
	drawText.setOutlineColor(sf::Color::Black);
	drawText.setOutlineThickness(5);
	drawText.setFillColor(sf::Color::White);

	window.draw(drawText);
}

// CONTROL SYSTEM
//___________________________________________________________________

void GameManager::ControlBoard(sf::RenderWindow& window) {
	if (selected != nullptr && selected->CanPromote())
		SelectPromotion();
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (mouseClicked)
			HoldPiece(window);
		else
			SelectPiece(window);
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		ReleasePiece(window);
	}
}
void GameManager::SelectPiece(sf::RenderWindow& window) {
	board.ClearSelectedSpaces();
	sf::Vector2i boardPos = board.PositionToSpace(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	board.AddSelectedSpace(boardPos.x, boardPos.y);

	if (selected != board.BLANK_SPACE && boardPos != selected->GetPosition() && (turn % 2 == 0) == selected->GetColor()) {
		if (selected->Move(boardPos.x, boardPos.y, CalculateCheckMoves(selected)) && !selected->CanPromote())
			MovePiece(selected);
		selected = nullptr;
	}

	selected = board.GetSpace(boardPos.x, boardPos.y);
	if (selected != board.BLANK_SPACE && (turn % 2 == 0) == selected->GetColor()) {
		selected->SetCheck(IsChecked(selected->GetColor()));
		for (std::pair<sf::Vector2i, Piece*> move : CalculateCheckMoves(selected)) {
			board.AddSelectedSpace(move.first.x, move.first.y);
		}
	}

	mouseClicked = true;
}
void GameManager::HoldPiece(sf::RenderWindow& window) {
	held = selected;
	if (held != nullptr) {
		board.SetSpace(held->GetPosition().x, held->GetPosition().y, nullptr);

		classification type = ClassifyPiece(*held);

		sf::Texture tex;
		sf::Vector2i texSize;
		sf::IntRect rects[12];
		float smallestScreenSide;
		GetDrawingUtensils(tex, texSize, rects, smallestScreenSide, window);

		sf::Sprite sprite(tex);
		sprite.setTextureRect(rects[((*held).GetColor() == Piece::WHITE) ? type + 6 : type]);
		sprite.setPosition({ static_cast<float>(sf::Mouse::getPosition(window).x) - 30 * smallestScreenSide / 500,
			static_cast<float>(sf::Mouse::getPosition(window).y) - 30 * smallestScreenSide / 500 });
		sprite.setScale({ smallestScreenSide / 500, smallestScreenSide / 500 });
		window.draw(sprite);
	}
}
void GameManager::ReleasePiece(sf::RenderWindow& window) {
	if (held != nullptr) {
		sf::Vector2i boardPos = board.PositionToSpace(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		if (held != board.BLANK_SPACE && boardPos != held->GetPosition() && (turn % 2 == 0) == held->GetColor()) {
			if (held->Move(boardPos.x, boardPos.y, CalculateCheckMoves(held)) && !held->CanPromote())
				MovePiece(held);
			board.ClearSelectedSpaces();
		}
		board.SetSpace(held->GetPosition().x, held->GetPosition().y, held);
	}

	held = nullptr;
	mouseClicked = false;
}
void GameManager::MovePiece(Piece* piece) {
	if (piece->GetCapture() != nullptr) {
		captured.push_back(piece->GetCapture());
		piece->SetCapture(nullptr);
	}

	turn++;
	moveHistory.push_back(piece->GetPosition());

	lastMoved = piece;
	fiftyMoveLimit++;

	std::cout << ConvertMoveToString(*piece) << std::endl;
}
void GameManager::SelectPromotion() {
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
		selected->Promote(choice);
		if (selected->GetCapture() != nullptr) {
			captured.push_back(selected->GetCapture());
			selected->SetCapture(nullptr);
		}
		turn++;
		moveHistory.push_back(selected->GetPosition());

		selected = nullptr;
	}
}

// CHECKING SYSTEM
//___________________________________________________________________

bool GameManager::IsChecked(Piece::color col) const {
	col = static_cast<Piece::color>(1 - col);
	std::vector<Piece*> pieces = FindPieces(col);

	for (Piece* p : pieces) {
		for (const auto& move : p->CalculateLegalMoves()) {

			Piece* space = board.GetSpace(move.first.x, move.first.y);
			if (space != board.BLANK_SPACE) {
				std::string pieceName = typeid(*space).name();
				if (pieceName.find("King") != std::string::npos && space->GetColor() != col) {
					return true;
				}
			}

		}
	}

	return false;
}
std::vector<std::pair<sf::Vector2i, Piece*>> GameManager::CalculateCheckMoves(Piece* p) {
	std::vector<std::pair<sf::Vector2i, Piece*>> allMoves = p->CalculateLegalMoves();

	std::vector<std::vector<Piece*>> boardState(board.GetSize().x, std::vector<Piece*>(board.GetSize().y, nullptr));
	for (int i = 0; i < board.GetSize().x; ++i) {
		for (int j = 0; j < board.GetSize().y; ++j) {
			boardState.at(i).at(j) = board.GetSpace(i, j);
		}
	}

	std::vector<std::pair<sf::Vector2i, Piece*>> checkMoves;
	sf::Vector2i prePos;
	for (std::pair<sf::Vector2i, Piece*> move : allMoves) {
		prePos = { p->GetPosition().x, p->GetPosition().y };

		board.SetSpace(p->GetPosition().x, p->GetPosition().y, nullptr);
		board.SetSpace(move.first.x, move.first.y, p);

		if (!IsChecked(p->GetColor()))
			checkMoves.push_back(move);

		for (int i = 0; i < board.GetSize().x; ++i) {
			for (int j = 0; j < board.GetSize().y; ++j) {
				board.SetSpace(i, j, boardState.at(i).at(j));
			}
		}
	}

	return checkMoves;
}
bool GameManager::Checkmate(sf::RenderWindow& window) {
	std::vector<Piece*> pieces = FindPieces(static_cast<Piece::color>(turn % 2 == 0));

	size_t numberOfMoves = 0;
	for (Piece* piece : pieces) {
		numberOfMoves += CalculateCheckMoves(piece).size();
	}

	if (numberOfMoves == 0) {
		sf::Font font("Fonts/Maketa.ttf");
		std::string text = (turn % 2 == 0) ? "BLACK" : "WHITE";
		text += " WINS!";

		DrawText(text, font, window);
		return true;
	}
	return false;
}

// DRAWING SYSTEM
//___________________________________________________________________

bool GameManager::CheckDraw() {

	// STALEMATE
	Piece::color currentColor = static_cast<Piece::color>(turn % 2 == 0);
	size_t totalMoves = 0;
	for (Piece* piece : FindPieces(currentColor)) {
		totalMoves += CalculateCheckMoves(piece).size();
	}
	if (totalMoves == 0 && !IsChecked(currentColor))
		return true;

	// THREEFOLD REPITITION
	if (moveHistory.size() >= 6) {
		if (moveHistory.at(moveHistory.size() - 1) == moveHistory.at(moveHistory.size() - 3) &&
			moveHistory.at(moveHistory.size() - 3) == moveHistory.at(moveHistory.size() - 5)) {
			if (moveHistory.at(moveHistory.size() - 2) == moveHistory.at(moveHistory.size() - 4) &&
				moveHistory.at(moveHistory.size() - 4) == moveHistory.at(moveHistory.size() - 6))
				return true;
		}
	}

	// INSUFFICIENT MATERIAL
	std::vector<Piece*> pieces = FindPieces(Piece::WHITE);
	std::vector<Piece*> blackPieces = FindPieces(Piece::BLACK);
	pieces.insert(pieces.end(), blackPieces.begin(), blackPieces.end());
	if (pieces.size() <= 3) {
		std::string remainingPiecesTypes[3] = { "", "", "" };
		size_t index = 0;
		for (Piece* piece : pieces) {
			std::string pieceName = typeid(*piece).name();
			remainingPiecesTypes[index] = pieceName;
			index++;
		}

		int drawCount = 0;
		for (std::string pieceType : remainingPiecesTypes) {
			if (pieceType.find("King") != std::string::npos ||
				pieceType.find("Knight") != std::string::npos ||
				pieceType.find("Bishop") != std::string::npos ||
				pieceType.length() == 0)
				drawCount++;
		}

		if (drawCount == 3)
			return true;
	}


	// 50-MOVE RULE
	if ((lastMoved != nullptr && ClassifyPiece(*lastMoved) == PAWN) || numberCaptured != captured.size()) {
		fiftyMoveLimit = 0;
		numberCaptured = captured.size();
	}
	if (fiftyMoveLimit >= 100)
		return true;

	return false;
}
bool GameManager::Draw(sf::RenderWindow& window) {
	if (CheckDraw()) {
		sf::Font font("Fonts/Maketa.ttf");
		std::string text = "DRAW!";

		DrawText(text, font, window);
		return true;
	}
	return false;
}

// UTILITY FUNCTIONS
//___________________________________________________________________

std::vector<Piece*> GameManager::FindPieces(Piece::color col) const {
	std::vector<Piece*> pieces;
	pieces.reserve(16);

	for (int i = 0; i < board.GetSize().x; ++i) {
		for (int j = 0; j < board.GetSize().y; ++j) {
			Piece* p = board.GetSpace(i, j);
			if (p != board.BLANK_SPACE && p->GetColor() == col)
				pieces.push_back(board.GetSpace(i, j));
		}
	}
	return pieces;
}
GameManager::classification GameManager::ClassifyPiece(const Piece& piece) {
	std::string pieceName = typeid(piece).name();

	classification type = PAWN;

	if (pieceName.find("Pawn") != std::string::npos) type = PAWN;
	else if (pieceName.find("Knight") != std::string::npos) type = KNIGHT;
	else if (pieceName.find("Bishop") != std::string::npos) type = BISHOP;
	else if (pieceName.find("Rook") != std::string::npos) type = ROOK;
	else if (pieceName.find("Queen") != std::string::npos) type = QUEEN;
	else if (pieceName.find("King") != std::string::npos) type = KING;

	return type;
}
void GameManager::GetDrawingUtensils(sf::Texture& tex, sf::Vector2i& texSize, sf::IntRect rects[], float& smallestScreenSide, sf::RenderWindow& window) {
	// Loads the texture
	if (!tex.loadFromFile("Sprites/Chess_Sprite_Sheet.png"))
		window.close();

	// Seperates the sprites
	texSize = { static_cast<int>(tex.getSize().x), static_cast<int>(tex.getSize().y) };
	for (int i = 0; i < 12; ++i)
		rects[i] = sf::IntRect({ texSize.x * ((i >= 6) ? (i - 6) : i) / 6, ((i >= 6) ? texSize.y / 2 : 0) }, { texSize.x / 6, texSize.y / 2 });

	smallestScreenSide = fminf(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
}
std::string GameManager::ConvertMoveToString(Piece& piece) {
	std::string result = "";

	classification type = ClassifyPiece(piece);
	switch (type) {
	case PAWN:
		break;
	case KNIGHT:
		result = "N";
		break;
	case BISHOP:
		result = "B";
		break;
	case ROOK:
		result = "R";
		break;
	case QUEEN:
		result = "Q";
		break;
	case KING:
		result = "K";
		break;
	}
	result += board.PositionToString(piece.GetPosition().x, piece.GetPosition().y);

	if (gameOver && !CheckDraw())
		result += "#";
	else if (IsChecked(static_cast<Piece::color>(abs(piece.GetColor() - 1))))
		result += "+";

	return result;
}
