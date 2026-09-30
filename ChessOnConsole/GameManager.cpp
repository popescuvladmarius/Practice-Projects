#include "GameManager.h"

bool GameManager::checkState() {
	if (gamestate.getState()) {
		return true;
	}
	return false;
}
void GameManager::selectPiece() {
	controller.select();
	switch (gamestate.getTurn()) {
	case Turn::white:
		if (piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y] && piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]->getFlag() == Flag::white) {
			gamestate.setSelectedPiece(piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]);
		}
		else {
			gamestate.setSelectedPiece(nullptr);
			gamestate.setState(false);
		}
		break;
	case Turn::black:
		if (piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y] && piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]->getFlag() == Flag::black) {
			gamestate.setSelectedPiece(piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]);
		}
		else {
			gamestate.setSelectedPiece(nullptr);
			gamestate.setState(false);
		}
		break;
	}
}
void GameManager::selectMove() {
	if (gamestate.getSelectedPiece()) {
		controller.select();
		gamestate.getSelectedPiece()->setEndPos(controller.getInputPos());
		if (gamestate.getSelectedPiece()->isValid()) {
			gamestate.getSelectedPiece()->move();
			gamestate.setSelectedMove(gamestate.getSelectedPiece()->getPos());
		}
		else {
			gamestate.setState(false);
		}
	}
	else {
		gamestate.setState(false);
	}

}
void GameManager::nextTurn() {
	if (gamestate.getTurn() == Turn::white) {
		gamestate.setTurn(Turn::black);
	}
	else {
		gamestate.setTurn(Turn::white);
	}
}
void GameManager::run() {
	while (gamestate.getState()) {

	}
}