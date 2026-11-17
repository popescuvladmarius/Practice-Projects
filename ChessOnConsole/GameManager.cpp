#include "GameManager.h"

void GameManager::selectPiece(char& counter) {
		switch (gamestate.getTurn()) {
		case Turn::white:
			if (piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y] && piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]->getFlag() == Flag::white) {
				gamestate.setSelectedPiece(piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]);
				gamestate.setLoopStatus(LoopStatus::pieceSelected);
				--counter;
			}
			break;
		case Turn::black:
			if (piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y] && piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]->getFlag() == Flag::black) {
				gamestate.setSelectedPiece(piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]);
				gamestate.setLoopStatus(LoopStatus::pieceSelected);
				--counter;
			}
			break;
		}
}
void GameManager::selectMove() {
		if (dynamic_cast<King*>(gamestate.getSelectedPiece())) {
			auto selectedKing{ dynamic_cast<King*>(gamestate.getSelectedPiece()) };
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
							selectedKing->resetCapture();
							selectedKing->resetCheck();
							piecemanager.getOtherKing(selectedKing)->resetCheck();
							selectedKing->resetCastlingMove();
							gamestate.setLoopStatus(LoopStatus::initial);
							gamestate.setSelectedPiece(nullptr);
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
						gamestate.setLoopStatus(LoopStatus::moveSelected);
						gamestate.setSelectedPiece(nullptr);
					}
					break;
				case CastlingMove::queensideCastling:
					for (std::size_t i = 0; i < 2; ++i) {
						selectedKing->queensideStepping();
						piecemanager.triggerGlobalScan();
						if (selectedKing->getCheckState()) {
							selectedKing->undoMove();
							selectedKing->resetCapture();
							selectedKing->resetCheck();
							piecemanager.getOtherKing(selectedKing)->resetCheck();
							selectedKing->resetCastlingMove();
							gamestate.setLoopStatus(LoopStatus::initial);
							gamestate.setSelectedPiece(nullptr);
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
						gamestate.setLoopStatus(LoopStatus::moveSelected);
						gamestate.setSelectedPiece(nullptr);
					}
					break;
				case CastlingMove::other:
					selectedKing->move();
					piecemanager.triggerGlobalScan();
					if (selectedKing->getCheckState()) {
						selectedKing->undoMove();
						selectedKing->resetCapture();
						selectedKing->resetCheck();
						piecemanager.getOtherKing(selectedKing)->resetCheck();
						gamestate.setLoopStatus(LoopStatus::initial);
						gamestate.setSelectedPiece(nullptr);
					}
					else {
						gamestate.addMove(gamestate.getSelectedPiece());
						piecemanager.updateArray(gamestate.readMove());
						selectedKing->resetCapture();
						gamestate.setLoopStatus(LoopStatus::moveSelected);
						gamestate.setSelectedPiece(nullptr);
					}
					break;
				}
			}
			else {
				gamestate.setLoopStatus(LoopStatus::initial);
				gamestate.setSelectedPiece(nullptr);
			}
		}
		else {
			gamestate.getSelectedPiece()->setEndPos(controller.getInputPos());
			if (gamestate.getSelectedPiece()->isValid()) {
				gamestate.getSelectedPiece()->move();
				piecemanager.triggerTeamScan(gamestate.getTurn());
				gamestate.addMove(gamestate.getSelectedPiece());
				piecemanager.updateArray(gamestate.readMove());
				gamestate.getSelectedPiece()->resetCapture();
				gamestate.setLoopStatus(LoopStatus::moveSelected);
				gamestate.setSelectedPiece(nullptr);
			}
			else {
				gamestate.setLoopStatus(LoopStatus::initial);
				gamestate.setSelectedPiece(nullptr);
			}
		}
}
void GameManager::selectEvadingMove() {
	gamestate.getSelectedPiece()->setEndPos(controller.getInputPos());
	if (gamestate.getSelectedPiece()->isValid()) {
		gamestate.getSelectedPiece()->move();
		piecemanager.triggerGlobalScan();
		if (!(getCheckedKing()->getCheckState())) {
			gamestate.addMove(gamestate.getSelectedPiece());
			piecemanager.updateArray(gamestate.readMove());
			gamestate.getSelectedPiece()->resetCapture();
			getCheckedKing()->resetCheck();
			gamestate.setLoopStatus(LoopStatus::moveSelected);
			gamestate.setSelectedPiece(nullptr);
		}
		else {
			gamestate.getSelectedPiece()->undoMove();
			gamestate.getSelectedPiece()->resetCapture();
			piecemanager.getOtherKing(getCheckedKing())->resetCheck();
			gamestate.setLoopStatus(LoopStatus::initial);
			gamestate.setSelectedPiece(nullptr);
		}
	}
	else {
		gamestate.setLoopStatus(LoopStatus::initial);
		gamestate.setSelectedPiece(nullptr);
	}
}
void GameManager::interpretSelection() {
	char selectionLimit{ 1 };
	switch (gamestate.getLoopStatus()) {
	case LoopStatus::initial:
		selectPiece(selectionLimit);
		break;
	case LoopStatus::pieceSelected:
		selectPiece(selectionLimit);
		if (selectionLimit > 0) {
			selectMove();
		}
		break;
	}
}
void GameManager::handleCheck() {
	char selectionLimit{ 1 };
	switch (gamestate.getLoopStatus()) {
	case LoopStatus::initial:
		selectPiece(selectionLimit);
		break;
	case LoopStatus::pieceSelected:
		selectPiece(selectionLimit);
		if (selectionLimit > 0) {
			selectEvadingMove();
		}
		break;
	}
}
King* GameManager::getCheckedKing() {
	switch (gamestate.getTurn()) {
	case Turn::white:
		auto checkedKingWhite{ dynamic_cast<King*>(piecemanager.getMasterArray()[piecemanager.view_whiteKing().getPos().x][piecemanager.view_whiteKing().getPos().y]) };
		if (checkedKingWhite->getCheckState())
			return checkedKingWhite;
		else
			return nullptr;
		break;
	case Turn::black:
		auto checkedKingBlack{ dynamic_cast<King*>(piecemanager.getMasterArray()[piecemanager.view_blackKing().getPos().x][piecemanager.view_blackKing().getPos().y]) };
		if (checkedKingBlack->getCheckState())
			return checkedKingBlack;
		else
			return nullptr;
		break;
	}
}
void GameManager::run() {
	while (gamestate.getState()) {
		board.render();
		while (gamestate.getLoopStatus() != LoopStatus::moveSelected) {
			if (getCheckedKing()) {
				controller.select();
				handleCheck();
			}
			else {
				controller.select();
				interpretSelection();
			}
		}
	}
	board.writeBoard();
	gamestate.nextTurn();
}

