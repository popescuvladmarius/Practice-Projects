#include "GameManager.h"
//it checks if the input coordinates correspond to a piece in the current team, by switching on the turn. If yes it assigns the selected piece to the selected_piece pointer in Gamestate and sets the loop status to pieceSelected, so that the move can be then selected 
void GameManager::selectPiece(char& counter) {
		switch (gamestate.getTurn()) {
		case Turn::white:
			if (piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y] && piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]->getFlag() == Flag::white) {
				gamestate.setSelectedPiece(piecemanager.getMasterArray()[controller.getInputPos().x][controller.getInputPos().y]);
				gamestate.setLoopStatus(LoopStatus::pieceSelected);
				--counter;                 //decrements the counter only if the condition is true
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
//the function first differentiates the selected piece between the king and all other pieces in order to cover the situation in which the king performs a move that might put it in danger,
//by stepping into a threatened square, in which case it is brought back to the old position
//it first checks if the selected_piece is a king, then if the move selected by the controller is valid according to the king's move rules, 
//it cheks if it is a regular move or a castling move by switching on the move type.
//if it is either a kingside castling or queenside castling move, it fires the kingsideStepping()/queensideStepping() function in a loop 2 times and if after
//triggering the triggerGlobalScan() it's not under check it increments a counter. If it's under check the move is undone, it breaks from the loop, all the involved resets performed and the loop status put to initial.
//If the counter == 2, the move is added to Gamestate's moveCollection, the masterArray in PieceManager updated, the loop status put to moveSelected and the involved resets performed.
//performs the same thing if the move type is regular.
//if the piece selected is not a king, then it checks its validity, performs the move, fires triggerTeamScan() to signal any potential checks to the enemy king, caches the move, updates the master array
//and puts loop status to moveSelected, signaling the end of a loop iteration. If the move is invalid, it performs the involved resets and sets the loop status to initial in order to reselect a piece and
//perform a new move within the same turn
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
//this function fires only if the current team is under check. The move selected through input is verified if valid, triggerGlobalScan() fired and if the king is no longer under check after the move has 
//been made the move is validated and loop status set to moveSelected, signaling the end of one loop iteration. If it is still under check the move is undone, involved resets performed and 
//the loop status is set to initial so that another piece selection and move might occur
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
//this function interprets the input given by the player according to the status of the loop, allowing only the functions to be called that correspond to their stage
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
//it does the same thing as interpretSelection() but during check, by calling selectEvadingMove() instead of selectMove() inside the pieceSelected stage
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
//this function tells us if the king of the current team is under check and returns a pointer to it if true, otherwise nullptr.
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
//under work. This function must evaluate if it's checkmate or not by firing the basic moves of the king and other pieces to see if there is at least one move that can lift the
//check, either by having the king reposition to a safe square, or any other piece capture the threatening enemy piece. If the checking piece has ActionType::diffusal, it additionaly checks
//if any other piece can block the range of the diffusal piece and protect the king
bool GameManager::isCheckmate() {
	switch (gamestate.getTurn()) {
	case Turn::white:
		for (auto checkingPiece : gamestate.getWhiteCheckingPieces()) {
			if (checkingPiece->getActionType() == ActionType::point) {
				for (auto piece : piecemanager.getWhiteVector()) {
					if () {

					}
				}
			}
			if (checkingPiece->getActionType() == ActionType::diffusal) {
				for (auto piece : piecemanager.getWhiteVector()) {
					if () {

					}
				}
			}
		}
		if (gamestate.getSelectedPiece()->getActionType() == ActionType::diffusal) {
			for (auto piece : piecemanager.getWhiteVector()) {
				if () {

				}
			}
		}
		break;
	case Turn::black:

		break;
	}
}
//The game loop is structured upon 2 loops. It runs the Gamestate's state as the main loop and employs internally a secondary loop that runs on the loop status/stage.
//The game expects the player to just select inputs, and according to their validity, the input is interpreted either as a piece selection or a move selection.
//In order for the game to interpret the input properly, the loop iteration has been divided into three stages. Initial for when the turn begins, pieceSelected when a valid piece selection
//has been performed, and moveSelected for when a valid move selection has been perfromed. interpretSelection() and handleCheck() functions handle this logic.
//This allows the player to perform an indefinite number of inputs, by continuously selecting between pieces and having the chance to select any other piece if the move selection is invalid. 
//All this until a full loop cycle has been completed with LoopStatus::moveSelected status, which exits the inner loop and allows the turn to be switched.
void GameManager::run() {
	while (gamestate.getState()) {
		board.render();
		while (gamestate.getLoopStatus() != LoopStatus::moveSelected) {
			if (getCheckedKing()) {
				//isCheckmate() must run here, breaking the outer loop if true and ending the game
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

