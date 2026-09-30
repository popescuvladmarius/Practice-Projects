#include "PieceManager.h"

void PieceManager::reserve() {
	whitePieces.reserve(16);
	blackPieces.reserve(16);
}
void PieceManager::initializeWhites() {
	whites.getKing().setPos(7, 4);
	whites.getKing().setFlag(Flag::white);
	whitePieces.push_back(&(whites.getKing()));
	masterArray[7][4] = &(whites.getKing());
	whites.getQueen().setPos(7, 3);
	whites.getQueen().setFlag(Flag::white);
	whitePieces.push_back(&(whites.getQueen()));
	masterArray[7][3] = &(whites.getQueen());
	whites.getRook(0).setPos(7, 0);
	whites.getRook(0).setFlag(Flag::white);
	whitePieces.push_back(&(whites.getRook(0)));
	masterArray[7][0] = &(whites.getRook(0));
	whites.getRook(1).setPos(7, 7);
	whites.getRook(1).setFlag(Flag::white);
	whitePieces.push_back(&(whites.getRook(1)));
	masterArray[7][7] = &(whites.getRook(1));
	whites.getBishop(0).setPos(7, 2);
	whites.getBishop(0).setFlag(Flag::white);
	whitePieces.push_back(&(whites.getBishop(0)));
	masterArray[7][2] = &(whites.getBishop(0));
	whites.getBishop(1).setPos(7, 5);
	whites.getBishop(1).setFlag(Flag::white);
	whitePieces.push_back(&(whites.getBishop(1)));
	masterArray[7][5] = &(whites.getBishop(1));
	whites.getKnight(0).setPos(7, 1);
	whites.getKnight(0).setFlag(Flag::white);
	whitePieces.push_back(&(whites.getKnight(0)));
	masterArray[7][1] = &(whites.getKnight(0));
	whites.getKnight(1).setPos(7, 6);
	whites.getKnight(1).setFlag(Flag::white);
	whitePieces.push_back(&(whites.getKnight(1)));
	masterArray[7][6] = &(whites.getKnight(1));
	for (std::size_t i = 0; i < 8; ++i) {
		whites.getPawn(i).setPos(6, i);
		whites.getPawn(i).setFlag(Flag::white);
		whitePieces.push_back(&(whites.getPawn(i)));
		masterArray[6][i] = &(whites.getPawn(i));
	}
}
void PieceManager::initializeBlacks() {
	blacks.getKing().setPos(0, 4);
	blacks.getKing().setFlag(Flag::black);
	blackPieces.push_back(&(blacks.getKing()));
	masterArray[0][4] = &(blacks.getKing());
	blacks.getQueen().setPos(0, 3);
	blacks.getQueen().setFlag(Flag::black);
	blackPieces.push_back(&(blacks.getQueen()));
	masterArray[0][3] = &(blacks.getQueen());
	blacks.getRook(0).setPos(0, 0);
	blacks.getRook(0).setFlag(Flag::black);
	blackPieces.push_back(&(blacks.getRook(0)));
	masterArray[0][0] = &(blacks.getRook(0));
	blacks.getRook(1).setPos(0, 7);
	blacks.getRook(1).setFlag(Flag::black);
	blackPieces.push_back(&(blacks.getRook(1)));
	masterArray[0][7] = &(blacks.getRook(1));
	blacks.getBishop(0).setPos(0, 2);
	blacks.getBishop(0).setFlag(Flag::black);
	blackPieces.push_back(&(blacks.getBishop(0)));
	masterArray[0][2] = &(blacks.getBishop(0));
	blacks.getBishop(1).setPos(0, 5);
	blacks.getBishop(1).setFlag(Flag::black);
	blackPieces.push_back(&(blacks.getBishop(1)));
	masterArray[0][5] = &(blacks.getBishop(1));
	blacks.getKnight(0).setPos(0, 1);
	blacks.getKnight(0).setFlag(Flag::black);
	blackPieces.push_back(&(blacks.getKnight(0)));
	masterArray[0][1] = &(blacks.getKnight(0));
	blacks.getKnight(1).setPos(0, 6);
	blacks.getKnight(1).setFlag(Flag::black);
	blackPieces.push_back(&(blacks.getKnight(1)));
	masterArray[0][6] = &(blacks.getKnight(1));
	for (std::size_t i = 0; i < 8; ++i) {
		blacks.getPawn(i).setPos(1, i);
		blacks.getPawn(i).setFlag(Flag::black);
		blackPieces.push_back(&(blacks.getPawn(i)));
		masterArray[1][i] = &(blacks.getPawn(i));
	}
}
void PieceManager::initializeArray() {
	for (std::size_t i = 2; i <= 5; ++i) {
		for (std::size_t j = 0; j < masterArray.size(); ++j) {
			masterArray[i][j] = nullptr;
		}
	}
}
PieceManager::PieceManager() :
		whites(*this),
		blacks(*this)
	{
		reserve();
		initializeWhites();
		initializeBlacks();
		initializeArray();
	}
    Pos PieceManager::getWhiteKingPos() { return whites.getKing().getPos(); }
	char PieceManager::getWhiteKingGraphics() { return 'K'; }
	Pos PieceManager::getWhiteQueenPos() { return whites.getQueen().getPos(); }
	char PieceManager::getWhiteQueenGraphics() { return 'Q'; }
	Pos PieceManager::getWhiteRookPos(int i) { return whites.getRook(i).getPos(); }
	char PieceManager::getWhiteRookGraphics() { return 'R'; }
	Pos PieceManager::getWhiteBishopPos(int i) { return whites.getBishop(i).getPos(); }
	char PieceManager::getWhiteBishopGraphics() { return 'B'; }
	Pos PieceManager::getWhiteKnightPos(int i) { return whites.getKnight(i).getPos(); }
	char PieceManager::getWhiteKnightGraphics() { return 'C'; }
	Pos PieceManager::getWhitePawnPos(int i) { return whites.getPawn(i).getPos(); }
	char PieceManager::getWhitePawnGraphics() { return 'P'; }
	Pos PieceManager::getBlackKingPos() { return blacks.getKing().getPos(); }
	char PieceManager::getBlackKingGraphics() { return 'k'; }
	Pos PieceManager::getBlackQueenPos() { return blacks.getQueen().getPos(); }
	char PieceManager::getBlackQueenGraphics() { return 'q'; }
	Pos PieceManager::getBlackRookPos(int i) { return blacks.getRook(i).getPos(); }
	char PieceManager::getBlackRookGraphics() { return 'r'; }
	Pos PieceManager::getBlackBishopPos(int i) { return blacks.getBishop(i).getPos(); }
	char PieceManager::getBlackBishopGraphics() { return 'b'; }
	Pos PieceManager::getBlackKnightPos(int i) { return blacks.getKnight(i).getPos(); }
	char PieceManager::getBlackKnightGraphics() { return 'c'; }
	Pos PieceManager::getBlackPawnPos(int i) { return blacks.getPawn(i).getPos(); }
	char PieceManager::getBlackPawnGraphics() { return 'p'; }
	std::vector<Piece*> PieceManager::getWhiteVector() { return whitePieces; }
	std::vector<Piece*> PieceManager::getBlackVector() { return blackPieces; }
	const std::array<std::array<Piece*, 8>, 8> PieceManager::getMasterArray() const { return masterArray; }