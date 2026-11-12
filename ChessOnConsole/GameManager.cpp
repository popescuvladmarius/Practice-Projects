#include "GameManager.h"

bool GameManager::isStateValid() {
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
		if (dynamic_cast<King*>(gamestate.getSelectedPiece())) {
			auto selectedKing{ dynamic_cast<King*>(gamestate.getSelectedPiece()) };
				controller.select();
				selectedKing->setEndPos(controller.getInputPos());
				if (selectedKing->isValid()) {
					switch (selectedKing->getCastlingMove()) {
					int validMovesCounter{ 0 };
					case CastlingMove::kingsideCastling:
						for (std::size_t i = 0; i < 2; ++i) {
							selectedKing->kingsideStepping();
							piecemanager.triggerGlobalScan();
							if (selectedKing->getCheckState()) {
								selectedKing->undoMove();
								selectedKing->resetCheck();
								gamestate.setStatus(Status::invalidMove);
								break;
							}
							else {
								++validMovesCounter;
							}
						}
						if (validMovesCounter == 2) {
							gamestate.addMove(gamestate.getSelectedPiece(), MoveType::kingsideCastling);
							piecemanager.updateArray(gamestate.readMove());
							selectedKing->resetCapture();
							selectedKing->resetCastlingMove();
							gamestate.setStatus(Status::validMove);
						}
						break;
					case CastlingMove::queensideCastling:
						for (std::size_t i = 0; i < 2; ++i) {
							selectedKing->queensideStepping();
							piecemanager.triggerGlobalScan();
							if (selectedKing->getCheckState()) {
								selectedKing->undoMove();
								selectedKing->resetCheck();
								gamestate.setStatus(Status::invalidMove);
								break;
							}
							else {
								++validMovesCounter;
							}
						}
						if (validMovesCounter == 2) {
							gamestate.addMove(gamestate.getSelectedPiece(), MoveType::queensideCastling);
							piecemanager.updateArray(gamestate.readMove());
							selectedKing->resetCapture();
							selectedKing->resetCastlingMove();
							gamestate.setStatus(Status::validMove);
						}
						break;
					case CastlingMove::other:
						selectedKing->move();
						piecemanager.triggerGlobalScan();
						if (selectedKing->getCheckState()) {
							selectedKing->undoMove();
							selectedKing->resetCheck();
							gamestate.setStatus(Status::invalidMove);
						}
						else {
							gamestate.addMove(gamestate.getSelectedPiece());
							piecemanager.updateArray(gamestate.readMove());
							selectedKing->resetCapture();
							gamestate.setStatus(Status::validMove);
						}
						break;
					}
				}
				else {
					gamestate.setStatus(Status::invalidMove);
				}
		}
		else {
			controller.select();
			gamestate.getSelectedPiece()->setEndPos(controller.getInputPos());
			if (gamestate.getSelectedPiece()->isValid()) {
				gamestate.getSelectedPiece()->move();
				piecemanager.triggerTeamScan(gamestate.getTurn());
				gamestate.addMove(gamestate.getSelectedPiece());
				piecemanager.updateArray(gamestate.readMove());
				gamestate.getSelectedPiece()->resetCapture();
				gamestate.setStatus(Status::validMove);
			}
			else {
				gamestate.setStatus(Status::invalidMove);
			}
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
	while (isStateValid()) {
			board.render();
			selectPiece();
			selectMove();
			board.writeBoard();
			nextTurn();
	}
}
