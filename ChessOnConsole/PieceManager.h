#pragma once
#include <vector>
#include <array>
#include "Team.h"
#include "PieceManager.h"
#include "RuleManager.h"
#include "Gamestate.h"

class Pos;
class Piece;
class RuleManager;
class Gamestate;

class PieceManager {
private:
	std::unordered_map<std::string, Pos> pieceInitialPositions{                //this map stores all the initial positions for all pieces as a reference
	{"WhiteKing", {7, 4} },
	{"WhiteQueen", {7, 3}},
	{"WhiteLeftRook", {7, 0}},
	{"WhiteRightRook", {7, 7}},
	{"WhiteLeftBishop", {7, 2}},
	{"WhiteRightBishop", {7, 5}},
	{"WhiteLeftKnight", {7, 1}},
	{"WhiteRightKnight", {7, 6}},
	{"BlackKing", {0, 4}},
	{"BlackQueen", {0, 3}},
	{"BlackLeftRook", {0, 0}},
	{"BlackRightRook", {0, 7}},
	{"BlackLeftBishop", {0, 2}},
	{"BlackRightBishop", {0, 5}},
	{"BlackLeftKnight", {0, 1}},
	{"BlackRightKnight", {0, 6}}
	};
	std::unordered_map<std::string, int> pawnInitialPositions{                //the pawns positions are only stored through their row coord
		{"WhitePawns", 6},
		{"BlackPawns", 1}
	};
	RuleManager& rule_ref;
	Gamestate& state_ref;
	Team whites;                             
	Team blacks;
	std::vector<Piece*> whitePieces;                          //stores pointers to all the white pieces
	std::vector<Piece*> blackPieces;                         //same for blacks
	std::array<std::array <Piece*, 8>, 8> masterArray;            //the global logical unit of the game, stores pointers to all pieces in the game and is consulted for most operations
	void reserve();                      //allocates space for the whitePieces and blackPieces vectors
	void initializeWhites();            //initializes the white team pieces with their initial positions, their flags, graphics and adds a pointer to the initialized piece to whitePieces vector
	void initializeBlacks();            //same for blacks
	void initializeArray();             //initializes the masterArray with the positions of all the pieces, all these private functions are called in the constructor
public:
	PieceManager(RuleManager& ref, Gamestate& state);
	std::vector<Piece*>& getWhiteVector();
	std::vector<Piece*>& getBlackVector();
	const King& view_whiteKing() const;            //offers a viewer on the white king, used mainly to get the position
	const King& view_blackKing() const;            //viewer
	const Queen& view_whiteQueen() const;          //viewer
	const Queen& view_blackQueen() const;           //viewer
	const Rook& view_whiteRook_left() const;          //viewer
	const Rook& view_whiteRook_right() const;         //viewer
	const Rook& view_blackRook_left() const;          //viewer
	const Rook& view_blackRook_right() const;          //viewer
	const std::unordered_map<std::string, Pos>& getPieceMap() const;
	const std::unordered_map<std::string, int>& getPawnMap() const;
	const std::array<std::array<Piece*, 8>, 8>& getMasterArray() const;
	void updateArray(const Move& move);              //updates the array with the new positions of the pieces by reading the most recent Move from Gamestate's moveCollection
	void notify_whiteKingMoved() const;              //tells RuleManager that the white king moved, to invalidate the castling
	void notify_whiteLeftRookMoved() const;          //tells RuleManager that the white left rook moved, to invalidate the castling
	void notify_whiteRightRookMoved() const;         //tells RuleManager that the white right rook moved, to invalidate the castling
	void notify_blackKingMoved() const;              //tells RuleManager that the black king moved, to invalidate the castling
	void notify_blackLeftRookMoved() const;          //tells RuleManager that the black left rook moved, to invalidate the castling
	void notify_blackRightRookMoved() const;           //tells RuleManager that the black right rook moved, to invalidate the castling
	bool queryKingsideCastling() const;               //invokes kingsideCastlingIsValid() from RuleManager
	bool queryQueensideCastling() const;              //invokes queensideCastingIsValid() from RuleManager
	void signalCheck(Piece* checkingPiece);            //signals the check by setting the king's check boolean to true and adds the checking pieces to Gamestate's checking pieces vectors
	void triggerGlobalScan();                        //fires the checkScanner() function for all the pieces in both teams
	void triggerTeamScan(Turn turn);                //fires the checkScanner() function only for the pieces in the team specified by the flag argument
	King* getOtherKing(King* selectedKing);         //gets a pointer to the other king by suppplying the selected king
	Piece* getSelectedPiece();                     //to be deprecated
};
