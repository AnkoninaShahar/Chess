#pragma once

#include "Piece.h"
#include "Board.h"
#include "Utilz.h"

using namespace Utilz;

class NotationManager
{
public:
	NotationManager(Board<Piece>& board) : board(board) {}

	std::string ConvertMoveToString(Piece& piece);

	void SetGameStatus(int status) {
		gameStatus = status;
	}

	void SetChecked(bool isChecked) {
		checked = isChecked;
	}

	void SetLastMoved(Piece* lastMoved) {
		this->lastMoved = lastMoved;
	}

	Piece* GetLastMoved() {
		return lastMoved;
	}
	
	void SetCaptured(bool captured) {
		this->captured = captured;
	}

private:
	Board<Piece>& board;

	int gameStatus = 0;
	bool checked = false;
	Piece* lastMoved = nullptr;
	bool captured = false;
};

