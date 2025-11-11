#pragma once

#include "Board.h"

#include <string>
#include <vector>
#include <typeinfo>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

/// <summary>
/// Blueprint class for more specific pieces
/// </summary>
class Piece
{
public:

	// The two sides of chess
	enum color {
		BLACK,
		WHITE
	};

	enum castle {
		KING_SIDE,
		QUEEN_SIDE,
		NONE
	};

	// Constructors for pieces
	inline Piece(int x, int y, color col, Board<Piece>& board);
	inline Piece(const Piece& copy) : pos(copy.pos), col(copy.col), board(copy.board) {}

	inline ~Piece();

	inline virtual bool Move(int x, int y, std::vector<std::pair<sf::Vector2i, Piece*>> legalMoves);

	inline virtual const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLegalMoves() { return std::vector<std::pair<sf::Vector2i, Piece*>>(0); }

	// Updates the turn number
	virtual void Update(int turnNum) {
		this->turnNum = turnNum;
	}

	inline const bool CanPromote() {
		std::string pieceName = typeid(*this).name();
		return pieceName.find("Pawn") != std::string::npos && (pos.y == 0 || pos.y == 7);
	}

	virtual const void Promote(int choice) {}

	int GetCastleStatus() {
		return castleStatus;
	}

	const void SetCheck(bool inCheck) {
		this->inCheck = inCheck;
	}

	const void SetPosition(sf::Vector2i pos) {
		this->pos = pos;
	}

	const sf::Vector2i GetPosition() {
		return pos;
	}

	const color GetColor() {
		return col;
	}

	const void SetCapture(Piece* capture) {
		this->capture = capture;
	}

	Piece* GetCapture() {
		return capture;
	}

	const int GetTurn() {
		return turnNum;
	}

	const int GetMoveNum() {
		return moveNum;
	}

	sf::Vector2i GetPreviousPosition() {
		return previousPos;
	}

	const bool operator== (const Piece& other) {
		return pos == other.pos;
	}

	std::string GetInfo() {
		std::string className = static_cast<std::string>(typeid(*this).name());
		return "[ NAME: " + className.substr(className.find(' ')) +
			", POSITION: (" + std::to_string(pos.x) + ", " + std::to_string(pos.y) + ") ]";
	}

	void Print() {
		std::cout << GetInfo() << std::endl;
	}

protected:
	sf::Vector2i pos = { 0, 0 };
	sf::Vector2i previousPos = { 0, 0 };
	color col = WHITE;

	Piece* capture = nullptr;

	Board<Piece>& board;

	int moveNum = 0;
	int turnNum = 0;

	bool inCheck = false;

	castle castleStatus = NONE;

	sf::SoundBuffer moveSoundBuffer;
	sf::SoundBuffer captureSoundBuffer;
	sf::Sound *sounds[2] = { nullptr, nullptr };

	inline virtual bool IsLegalMove(int x, int y);

	inline const std::vector<std::pair<sf::Vector2i, Piece*>> CalculateLineMoves(sf::Vector2i dir);
};

