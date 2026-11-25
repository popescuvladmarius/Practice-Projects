#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "GeneralFunctions.h"

struct Pos {
	int x{};
	int y{};
	bool operator==(const Pos&) const = default;
};

enum class Flag {             //each piece has a flag enum indicating its team
	white,
	black
};

enum class Turn {             //indicates the turn of the match
	white,
	black
};

enum class Status {              //will be deprecated
	init,
	validPiece,
	validMove,
	invalidPiece,
	invalidMove
};                    

enum class LoopStatus {            //this enum represents the main game loop status, initial when the turn starts, 
	initial,                       //pieceSelection, when a piece has been successfully selected 
	pieceSelected,                 //and moveSelected and a move has been successfully selected
	moveSelected
};

enum class CheckStatus {              //will be deprecated
	noneChecked,
	whiteChecked,
	blackChecked,
	bothChecked
};

enum class CastlingMove {           //other if no castling is being performed
	other,
	kingsideCastling,
	queensideCastling
};

enum class MoveType {              //enum used to write to Move struct the type of move performed
	regular,
	kingsideCastling,
	queensideCastling,
	enpassant
};

enum class ActionType {            //it represents the type of action a piece has
	diffusal,                      //diffusal for pieces that act on ranges, like the rook, bishop and queen
	point                          //point for pieces that act on a point, like the pawn, knight and king
};                                 //it is used to differentiate between action types of pieces in order to properly evaluate the checkmate conditions

struct Move {
	Pos move;
	Pos oldPos;
	Piece* piece;
	bool capture;
	MoveType moveType{ MoveType::regular };                 //this struct is used to keep track of each move in the game and it is stored in a vector
};

