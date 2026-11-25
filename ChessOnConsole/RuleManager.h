#pragma once
#include <vector>

class PieceManager;
class Gamestate;
class Piece;
enum class CheckStatus;

class RuleManager {
private:
	const PieceManager& piece_ref;
	const Gamestate& state_ref;
	CheckStatus checkStatus{ CheckStatus::noneChecked };              //to be deprecated
	bool whiteCheck{ false };            //to be deprecated
	bool blackCheck{ false };            //to be deprecated
	bool checkmate{ false };             //to be deprecated
	bool isWhiteKingsideCastlingPossible{ true };                 //if false the white kingside castling move is prohibited for the rest of the game
	bool isWhiteQueensideCastlingPossible{ true };                //if false the white queenside castling move is prohibited for the rest of the game
	bool isBlackKingsideCastlingPossible{ true };                 //if false the black kingside castling move is prohibited for the rest of the game
	bool isBlackQueensideCastlingPossible{ true };                //if false the black queenside castling move is prohibited for the rest of the game
public:
	RuleManager(const PieceManager& piece, const Gamestate& state);
	void whiteKingMoved();              //sets isWhiteKingsideCastlingPossible and isWhiteQueensideCastlingPossible as false and invalidates any castling move for the whites
	void whiteLeftRookMoved();          //sets isWhiteQueensideCastlingPossible as false and invalidates the queenside castling for whites
	void whiteRightRookMoved();         //sets isWhiteKingsideCastlingPossible as false and invalidates the kingside castling for whites
	void blackKingMoved();              //sets isBlackKingsideCastlingPossible and isBlackQueensideCastlingPossible as false and invalidates any castling move for the blacks
	void blackLeftRookMoved();          //sets isBlackQueensideCastlingPossible as false and invalidates the queenside castling for blacks
	void blackRightRookMoved();         //sets isBlackKingsideCastlingPossible as false and invalidates the kingside castling for blacks
	bool kingsideAreEmpty();            //checks if the squares between the king and the right rook are empty as a necessary condition for the castling move to be performed
	bool queensideAreEmpty();           //same thing for the squares between the king and the left rook
	bool kingsideCastlingIsValid();        //ultimately checks if the kingside castling move can be performed based on the corresponding boolean above and the output of the kingsideAreEmpty() function
	bool queensideCastingIsValid();        //same thing for queenside castling
	void addToWhiteCheckingPieceArray(Piece* piece);            //to be deprecated
	void addToBlackCheckingPieceArray(Piece* piece);           //to be deprecated
	bool whiteCheckState();                //to be deprecated
	bool blackCheckState();                //to be deprecated
	CheckStatus getCheckStatus();          //to be deprecated
};