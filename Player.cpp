#include "Player.h"

Player::Player(Board<Piece>& board, Piece::color color, NotationManager& printer) : board(board), color(color), printer(printer) {}

void Player::ControlBoard(sf::RenderWindow& window) {
	if (selected != nullptr && selected->CanPromote())
		SelectPromotion();
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		if (mouseClicked)
			HoldPiece(window);
		else
			SelectPiece(window);
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		ReleasePiece(window);
}

void Player::SelectPiece(sf::RenderWindow& window) {
	bool moved = false;

	board.ClearSelectedSpaces();
	sf::Vector2i boardPos = board.PositionToSpace(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	board.AddSelectedSpace(boardPos.x, boardPos.y);

	if (selected != nullptr && boardPos != selected->GetPosition() && color == selected->GetColor()) {
		if (selected->Move(boardPos.x, boardPos.y, CalculateCheckMoves(selected)) && !selected->CanPromote()) {
			MovePiece(selected);
			moved = true;
		}
		selected = nullptr;
	}
	
	if (!moved) {
		selected = board.GetSpace(boardPos.x, boardPos.y);
		if (selected != nullptr && color == selected->GetColor()) {
			selected->SetCheck(IsChecked(selected->GetColor()));
			for (std::pair<sf::Vector2i, Piece*> move : CalculateCheckMoves(selected)) {
				board.AddSelectedSpace(move.first.x, move.first.y);
			}
		}
	}

	mouseClicked = true;
}

void Player::HoldPiece(sf::RenderWindow& window) {
	held = selected;
	if (held != nullptr) {
		board.SetSpace(held->GetPosition().x, held->GetPosition().y, nullptr);

		Utilz::Type::classification type = Utilz::Type::Classify(*held);
		int typeValue = static_cast<int>(type);

		sf::Texture tex;
		sf::Vector2i texSize;
		sf::IntRect rects[12];
		float smallestScreenSide;
		Utilz::General::GetDrawingUtensils(tex, texSize, rects, smallestScreenSide, window);

		sf::Sprite sprite(tex);
		sprite.setTextureRect(rects[((*held).GetColor() == Piece::WHITE) ? typeValue + 6 : typeValue]);
		sprite.setPosition({ static_cast<float>(sf::Mouse::getPosition(window).x) - 30 * smallestScreenSide / 500,
			static_cast<float>(sf::Mouse::getPosition(window).y) - 30 * smallestScreenSide / 500 });
		sprite.setScale({ smallestScreenSide / 500, smallestScreenSide / 500 });
		window.draw(sprite);
	}
}

void Player::ReleasePiece(sf::RenderWindow& window) {
	if (held != nullptr) {
		sf::Vector2i boardPos = board.PositionToSpace(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

		if (held != nullptr && boardPos != held->GetPosition() && color == held->GetColor()) {
			if (held->Move(boardPos.x, boardPos.y, CalculateCheckMoves(held)) && !held->CanPromote())
				MovePiece(held);
			board.ClearSelectedSpaces();
		}
		board.SetSpace(held->GetPosition().x, held->GetPosition().y, held);
	}

	held = nullptr;
	mouseClicked = false;
}

void Player::MovePiece(Piece* piece) {
	if (piece->GetCapture() != nullptr) {
		captured.push_back(piece->GetCapture());
		piece->SetCapture(nullptr);
		printer.SetCaptured(true);
	}
	else {
		printer.SetCaptured(false);
	}

	printer.SetChecked(IsChecked(static_cast<Piece::color>(abs(piece->GetColor() - 1))));
	moveHistory.push_back(piece->GetPosition());

	lastMoved = piece;
	fiftyMoveLimit++;
}

void Player::SelectPromotion() {
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
		//turn++;
		moveHistory.push_back(selected->GetPosition());

		selected = nullptr;
	}
}

std::vector<std::pair<sf::Vector2i, Piece*>> Player::CalculateCheckMoves(Piece* p) {
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

		if (!IsChecked(color))
			checkMoves.push_back(move);

		for (int i = 0; i < board.GetSize().x; ++i) {
			for (int j = 0; j < board.GetSize().y; ++j) {
				board.SetSpace(i, j, boardState.at(i).at(j));
			}
		}
	}

	return checkMoves;
}

bool Player::IsChecked(Piece::color col) const {
	col = static_cast<Piece::color>(1 - col);
	std::vector<Piece*> pieces = Utilz::General::FindPieces(board, col);

	for (Piece* p : pieces) {
		for (const auto& move : p->CalculateLegalMoves()) {

			Piece* space = board.GetSpace(move.first.x, move.first.y);
			if (space != nullptr) {
				std::string pieceName = typeid(*space).name();
				if (pieceName.find("King") != std::string::npos && space->GetColor() != col) {
					return true;
				}
			}

		}
	}

	return false;
}

bool Player::CheckDraw() {

	// STALEMATE
	Piece::color currentColor = color;
	size_t totalMoves = 0;
	for (Piece* piece : Utilz::General::FindPieces(board, currentColor)) {
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
	std::vector<Piece*> pieces = Utilz::General::FindPieces(board, Piece::WHITE);
	std::vector<Piece*> blackPieces = Utilz::General::FindPieces(board, Piece::BLACK);
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
	if ((lastMoved != nullptr && Utilz::Type::Classify(*lastMoved) == Utilz::Type::classification::PAWN) || numberCaptured != captured.size()) {
		fiftyMoveLimit = 0;
		numberCaptured = captured.size();
	}
	if (fiftyMoveLimit >= 100)
		return true;

	return false;
}

