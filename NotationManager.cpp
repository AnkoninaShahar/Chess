#include "NotationManager.h"

void NotationManager::Print(Piece* piece) {
	if (piece != nullptr) {
		if (piece != lastMoved) {
			std::cout << ConvertMoveToString(*piece) << std::endl;
			lastMoved = piece;
		}
	}
}

std::string NotationManager::ConvertMoveToString(Piece& piece) {
	std::string result = "";
	Utilz::Type::classification type = Utilz::Type::Classify(piece);

	switch (type) {
	case static_cast<int>(Utilz::Type::PAWN): {
		if (captured) {
			std::string typeName = board.PositionToString(piece.GetPreviousPosition().x, piece.GetPreviousPosition().y);
			result = typeName.at(0);
			result += "x";
		}
		result += board.PositionToString(piece.GetPosition().x, piece.GetPosition().y);

		if (promotion != 0) {
			result += "=";
			switch (promotion) {
			case 1:
				result += "Q";
				break;
			case 2:
				result += "R";
				break;
			case 3:
				result += "N";
				break;
			case 4:
				result += "B";
				break;
			}
			promotion = 0;
		}
		break;
	}
	case static_cast<int>(Utilz::Type::KNIGHT):
		BaseNotation("N", result, piece);
		break;
	case static_cast<int>(Utilz::Type::BISHOP):
		BaseNotation("B", result, piece);
		break;
	case static_cast<int>(Utilz::Type::ROOK):
		BaseNotation("R", result, piece);
		break;
	case static_cast<int>(Utilz::Type::QUEEN):
		BaseNotation("Q", result, piece);
		break;
	case static_cast<int>(Utilz::Type::KING):
		if (piece.GetCastleStatus() == piece.KING_SIDE)
			return "0-0";
		if (piece.GetCastleStatus() == piece.QUEEN_SIDE)
			return "0-0-0";
		BaseNotation("K", result, piece);
		break;
	}

	if (gameStatus != 0) {
		if (gameStatus == 1)
			result = "1/2-1/2";
		else if (gameStatus == 2)
			result += "#";
	}
	else if (checked)
		result += "+";

	return result;
}

void NotationManager::BaseNotation(std::string type, std::string& notation, Piece& piece) {
	notation = type;
	if (captured)
		notation += "x";
	notation += board.PositionToString(piece.GetPosition().x, piece.GetPosition().y);
}
