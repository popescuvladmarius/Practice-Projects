#include "RuleManager.h"
#include "PieceManager.h"
#include "Gamestate.h"

RuleManager::RuleManager(const PieceManager& piece, const Gamestate& state) : piece_ref{piece}, state_ref{state} {}
void RuleManager::whiteKingMoved() {
	isWhiteKingsideCastlingPossible = false;
	isWhiteQueensideCastlingPossible = false;
}
void RuleManager::whiteLeftRookMoved() {
	isWhiteQueensideCastlingPossible = false;
}
void RuleManager::whiteRightRookMoved() {
	isWhiteKingsideCastlingPossible = false;
}
void RuleManager::blackKingMoved() {
	isBlackKingsideCastlingPossible = false;
	isBlackQueensideCastlingPossible = false;
}
void RuleManager::blackLeftRookMoved() {
	isBlackQueensideCastlingPossible = false;
}
void RuleManager::blackRightRookMoved() {
	isBlackKingsideCastlingPossible = false;
}
bool RuleManager::kingsideAreEmpty() {
	switch (state_ref.getTurn()) {
	case Turn::white:
		if (piece_ref.getMasterArray()[7][5] == nullptr && piece_ref.getMasterArray()[7][6] == nullptr) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Turn::black:
		if (piece_ref.getMasterArray()[0][5] == nullptr && piece_ref.getMasterArray()[0][6] == nullptr) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
}
bool RuleManager::queensideAreEmpty() {
	switch (state_ref.getTurn()) {
	case Turn::white:
		if (piece_ref.getMasterArray()[7][1] == nullptr && piece_ref.getMasterArray()[7][2] == nullptr && piece_ref.getMasterArray()[7][3] == nullptr) {
			return true;
		}
		else {
			return false;
		}
		break;
	case Turn::black:
		if (piece_ref.getMasterArray()[0][1] == nullptr && piece_ref.getMasterArray()[0][2] == nullptr && piece_ref.getMasterArray()[0][3] == nullptr) {
			return true;
		}
		else {
			return false;
		}
		break;
	}
}
bool RuleManager::kingsideCastlingIsValid() {
	switch (state_ref.getTurn()) {
	case Turn::white:
		if (isWhiteKingsideCastlingPossible) {
			if (kingsideAreEmpty()) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
		break;
	case Turn::black:
		if (isBlackKingsideCastlingPossible) {
			if (kingsideAreEmpty()) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
		break;
	}
}
bool RuleManager::queensideCastingIsValid() {
	switch (state_ref.getTurn()) {
	case Turn::white:
		if (isWhiteQueensideCastlingPossible) {
			if (queensideAreEmpty()) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
		break;
	case Turn::black:
		if (isBlackQueensideCastlingPossible) {
			if (queensideAreEmpty()) {
				return true;
			}
			else {
				return false;
			}
		}
		return false;
		break;
	}
}
void RuleManager::addToWhiteCheckingPieceArray(Piece* piece) {
	whiteCheckingPieces.push_back(piece);
}
void RuleManager::addToBlackCheckingPieceArray(Piece* piece) {
	blackCheckingPieces.push_back(piece);
}
bool RuleManager::whiteCheckState() { 
	checkStatus = CheckStatus::whiteChecked;
	return whiteCheck; 
}
bool RuleManager::blackCheckState() { 
	checkStatus = CheckStatus::blackChecked;
	return blackCheck; 
}
CheckStatus RuleManager::getCheckStatus() {
	return checkStatus;
}
