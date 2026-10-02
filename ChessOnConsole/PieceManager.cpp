#include "PieceManager.h"

void PieceManager::reserve() {
	whitePieces.reserve(16);
	blackPieces.reserve(16);
}
void PieceManager::initializeWhites() {
	whites.getKing().setPos(7, 4);
	whites.getKing().setFlag(Flag::white);
	whites.getKing().setGraphics('K');
	whitePieces.push_back(&(whites.getKing()));
	whites.getQueen().setPos(7, 3);
	whites.getQueen().setFlag(Flag::white);
	whites.getQueen().setGraphics('Q');
	whitePieces.push_back(&(whites.getQueen()));
	whites.getRook(0).setPos(7, 0);
	whites.getRook(0).setFlag(Flag::white);
	whites.getRook(0).setGraphics('R');
	whitePieces.push_back(&(whites.getRook(0)));
	whites.getRook(1).setPos(7, 7);
	whites.getRook(1).setFlag(Flag::white);
	whites.getRook(1).setGraphics('R');
	whitePieces.push_back(&(whites.getRook(1)));
	whites.getBishop(0).setPos(7, 2);
	whites.getBishop(0).setFlag(Flag::white);
	whites.getBishop(0).setGraphics('B');
	whitePieces.push_back(&(whites.getBishop(0)));
	whites.getBishop(1).setPos(7, 5);
	whites.getBishop(1).setFlag(Flag::white);
	whites.getBishop(1).setGraphics('B');
	whitePieces.push_back(&(whites.getBishop(1)));
	whites.getKnight(0).setPos(7, 1);
	whites.getKnight(0).setFlag(Flag::white);
	whites.getKnight(0).setGraphics('C');
	whitePieces.push_back(&(whites.getKnight(0)));
	whites.getKnight(1).setPos(7, 6);
	whites.getKnight(1).setFlag(Flag::white);
	whites.getKnight(1).setGraphics('C');
	whitePieces.push_back(&(whites.getKnight(1)));
	for (std::size_t i = 0; i < 8; ++i) {
		whites.getPawn(i).setPos(6, i);
		whites.getPawn(i).setFlag(Flag::white);
		whites.getPawn(i).setGraphics('P');
		whitePieces.push_back(&(whites.getPawn(i)));
	}
}
void PieceManager::initializeBlacks() {
	blacks.getKing().setPos(0, 4);
	blacks.getKing().setFlag(Flag::black);
	blacks.getKing().setGraphics('k');
	blackPieces.push_back(&(blacks.getKing()));
	blacks.getQueen().setPos(0, 3);
	blacks.getQueen().setFlag(Flag::black);
	blacks.getQueen().setGraphics('q');
	blackPieces.push_back(&(blacks.getQueen()));
	blacks.getRook(0).setPos(0, 0);
	blacks.getRook(0).setFlag(Flag::black);
	blacks.getRook(0).setGraphics('r');
	blackPieces.push_back(&(blacks.getRook(0)));
	blacks.getRook(1).setPos(0, 7);
	blacks.getRook(1).setFlag(Flag::black);
	blacks.getRook(1).setGraphics('r');
	blackPieces.push_back(&(blacks.getRook(1)));
	blacks.getBishop(0).setPos(0, 2);
	blacks.getBishop(0).setFlag(Flag::black);
	blacks.getBishop(0).setGraphics('b');
	blackPieces.push_back(&(blacks.getBishop(0)));
	blacks.getBishop(1).setPos(0, 5);
	blacks.getBishop(1).setFlag(Flag::black);
	blacks.getBishop(1).setGraphics('b');
	blackPieces.push_back(&(blacks.getBishop(1)));
	blacks.getKnight(0).setPos(0, 1);
	blacks.getKnight(0).setFlag(Flag::black);
	blacks.getKnight(0).setGraphics('c');
	blackPieces.push_back(&(blacks.getKnight(0)));
	blacks.getKnight(1).setPos(0, 6);
	blacks.getKnight(1).setFlag(Flag::black);
	blacks.getKnight(1).setGraphics('c');
	blackPieces.push_back(&(blacks.getKnight(1)));
	for (std::size_t i = 0; i < 8; ++i) {
		blacks.getPawn(i).setPos(1, i);
		blacks.getPawn(i).setFlag(Flag::black);
		blacks.getPawn(i).setGraphics('p');
		blackPieces.push_back(&(blacks.getPawn(i)));
	}
}
void PieceManager::initializeArray() {
	masterArray[7][4] = &(whites.getKing());
	masterArray[7][3] = &(whites.getQueen());
	masterArray[7][0] = &(whites.getRook(0));
	masterArray[7][7] = &(whites.getRook(1));
	masterArray[7][2] = &(whites.getBishop(0));
	masterArray[7][5] = &(whites.getBishop(1));
	masterArray[7][1] = &(whites.getKnight(0));
	masterArray[7][6] = &(whites.getKnight(1));
	for (std::size_t i = 0; i < 8; ++i) {
		masterArray[6][i] = &(whites.getPawn(i));
	}
    masterArray[0][4] = &(blacks.getKing());
    masterArray[0][3] = &(blacks.getQueen());
    masterArray[0][0] = &(blacks.getRook(0));
    masterArray[0][7] = &(blacks.getRook(1));
    masterArray[0][2] = &(blacks.getBishop(0));
    masterArray[0][5] = &(blacks.getBishop(1));
    masterArray[0][1] = &(blacks.getKnight(0));
    masterArray[0][6] = &(blacks.getKnight(1));
    for (std::size_t i = 0; i < 8; ++i) {
	masterArray[1][i] = &(blacks.getPawn(i));
}
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
	std::vector<Piece*> PieceManager::getWhiteVector() { return whitePieces; }
	std::vector<Piece*> PieceManager::getBlackVector() { return blackPieces; }
	const std::array<std::array<Piece*, 8>, 8> PieceManager::getMasterArray() const { return masterArray; }