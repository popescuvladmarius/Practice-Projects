#pragma once
#include "Objects.h"
#include "Gamestate.h"

class GameloopStateMachine {
private:
	Gamestate& state_ref;
	StatusNew loopStatus{ StatusNew::initial };
public:
	GameloopStateMachine(Gamestate& ref) : state_ref{ref} {}
	void updateStatus();
	void resetStatus();
};