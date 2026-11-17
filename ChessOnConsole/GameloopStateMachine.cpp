#include "GameloopStateMachine.h"

void GameloopStateMachine::updateStatus() {
	switch (loopStatus) {
	case StatusNew::initial:
		loopStatus = StatusNew::pieceSelected;
		break;
	case StatusNew::pieceSelected:
		loopStatus = StatusNew::moveSelected;
		state_ref.nextTurn();
		break;
	}
}
void GameloopStateMachine::resetStatus() {
	loopStatus = StatusNew::initial;
}