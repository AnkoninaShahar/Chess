//#pragma once
//
//#include "Piece.h"
//#include "Board.h"
//#include "GameManager.h"
//
//class NotationManager
//{
//public:
//	NotationManager(Board<Piece>& board, GameManager& gameManager) : board(board), gameManager(gameManager) {}
//
//	std::string ConvertMoveToString(Piece& piece);
//
//	void SetLastMoved(Piece* lastMoved) {
//		this->lastMoved = lastMoved;
//	}
//
//	Piece* GetLastMoved() {
//		return lastMoved;
//	}
//	
//	void SetCaptured(bool captured) {
//		this->captured = captured;
//	}
//
//private:
//	Board<Piece>& board;
//	GameManager& gameManager;
//
//	Piece* lastMoved = nullptr;
//	bool captured = false;
//};
//
