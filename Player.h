#pragma once

#include "Piece.h"
#include "Board.h"
#include "NotationManager.h"
#include "Utilz.h"

using namespace Utilz;

class Player
{
public:
	Player(Board<Piece>& board, Piece::color color, NotationManager& printer);

	void ControlBoard(sf::RenderWindow& window);
	void SelectPiece(sf::RenderWindow& window);
	void HoldPiece(sf::RenderWindow& window);
	void ReleasePiece(sf::RenderWindow& window);
	void MovePiece(Piece* piece);
	void SelectPromotion();

	std::vector<std::pair<sf::Vector2i, Piece*>> CalculateCheckMoves(Piece* p);
	bool IsChecked(Piece::color col) const;

	bool CheckDraw();

	std::vector<Piece*> GetCaptured() {
		return captured;
	}

	std::vector<sf::Vector2i> GetMoveHistory() {
		return moveHistory;
	}

	Piece* GetLastMoved() {
		return lastMoved;
	}

	Piece* GetHeld() {
		return held;
	}
	
	void Print() {
		std::string heldInfo = (held != nullptr) ? held->GetInfo() : "None";
		std::string selectedInfo = (selected != nullptr) ? selected->GetInfo() : "None";
		std::cout << "HELD: " << heldInfo << "\tSELCTED: "
			<< selectedInfo << "\tMOUSE CLICKED: " << mouseClicked << std::endl;
	}

private:
	Board<Piece>& board;
	Piece::color color;

	NotationManager& printer;

	Piece* selected = nullptr;
	Piece* held = nullptr;
	Piece* lastMoved = nullptr;

	std::vector<sf::Vector2i> moveHistory;
	std::vector<Piece*> captured;

	size_t numberCaptured = 0;

	int fiftyMoveLimit = 0;

	bool mouseClicked = false;
};

