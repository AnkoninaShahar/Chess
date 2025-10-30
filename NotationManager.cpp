#include "NotationManager.h"

std::string NotationManager::ConvertMoveToString(Piece& piece) {
	std::string result = "";
	Utilz::Type::classification type = Utilz::Type::Classify(piece);

	switch (type) {
	case static_cast<int>(Utilz::Type::PAWN):
		break;
	case static_cast<int>(Utilz::Type::KNIGHT):
		result = "N";
		break;
	case static_cast<int>(Utilz::Type::BISHOP):
		result = "B";
		break;
	case static_cast<int>(Utilz::Type::ROOK):
		result = "R";
		break;
	case static_cast<int>(Utilz::Type::QUEEN):
		result = "Q";
		break;
	case static_cast<int>(Utilz::Type::KING):
		result = "K";
		break;
	}

	if (captured)
		result += "x";

	result += board.PositionToString(piece.GetPosition().x, piece.GetPosition().y);
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
