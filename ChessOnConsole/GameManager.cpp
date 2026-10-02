#include "GameManager.h"

bool GameManager::checkState() {
	if (gamestate.getState()) {
		return true;
	}
	return false;
}
void GameManager::selectPiece() {
	while (gamestate.getStatus() != Status::validPiece) {
		if (gamestate.getStatus() == Status::invalidPiece) {
			invalidPieceMessage();
		}
		controller.select();
		switch (gamestate.getTurn()) {
		case Turn::white:
			if (piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y] && piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]->getFlag() == Flag::white) {
				gamestate.setSelectedPiece(piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]);
				gamestate.setStatus(Status::validPiece);
			}
			else {
				gamestate.setSelectedPiece(nullptr);
				gamestate.setStatus(Status::invalidPiece);
			}
			break;
		case Turn::black:
			if (piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y] && piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]->getFlag() == Flag::black) {
				gamestate.setSelectedPiece(piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]);
				gamestate.setStatus(Status::validPiece);
			}
			else {
				gamestate.setSelectedPiece(nullptr);
				gamestate.setStatus(Status::invalidPiece);
			}
			break;
		}

	}
}
void GameManager::selectMove() {
	while (gamestate.getStatus() != Status::validMove) {
		if (gamestate.getStatus() == Status::invalidMove) {
			invalidMoveMessage();
		}
			controller.select();
			gamestate.getSelectedPiece()->setEndPos(controller.getInputPos());
			if (gamestate.getSelectedPiece()->isValid()) {
				gamestate.getSelectedPiece()->move();
				gamestate.setSelectedMove(gamestate.getSelectedPiece()->getPos());
				gamestate.setStatus(Status::validMove);

			}
			else {
				gamestate.setStatus(Status::invalidMove);
			}
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
	while (checkState()) {
			board.render();
			selectPiece();
			selectMove();
			board.writeBoard();
			nextTurn();
	}
}
