//#include "NotationManager.h"
//
//std::string NotationManager::ConvertMoveToString(Piece& piece) {
//	 std::string result = "";
//	 GameManager::Classification type = gameManager.Classify(piece);
//	 int typeValue = static_cast<int>(type);
//
//	 switch (typeValue) {
//	 case static_cast<int>(GameManager::Classification::PAWN):
//		 break;
//	 case static_cast<int>(GameManager::Classification::KNIGHT):
//		 result = "N";
//		 break;
//	 case static_cast<int>(GameManager::Classification::BISHOP):
//		 result = "B";
//		 break;
//	 case static_cast<int>(GameManager::Classification::ROOK):
//		 result = "R";
//		 break;
//	 case static_cast<int>(GameManager::Classification::QUEEN):
//		 result = "Q";
//		 break;
//	 case static_cast<int>(GameManager::Classification::KING):
//		 result = "K";
//		 break;
//	 }
//
//	 if (captured)
//		 result += "x";
//
//	 result += board.PositionToString(piece.GetPosition().x, piece.GetPosition().y);
//
//	 if (gameManager.IsGameOver()) {
//		 if (gameManager.CheckDraw())
//			 result = "1/2-1/2";
//		 else
//			 result += "#";
//	 }
//	 else if (gameManager.IsChecked(static_cast<Piece::color>(abs(piece.GetColor() - 1))))
//		 result += "+";
//
//	 return result;
//}
