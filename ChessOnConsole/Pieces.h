#pragma once
#include "Objects.h"

//each piece inherits from the abstract class Piece, which defines the basic piece logic every piece executes
//each piece implements its own move logic

class PieceManager;

class Piece {
protected:
	Pos pos{};                 //the current position of the piece
	Pos endPos{};              //the position that the input assigns to the piece, which represents the target move. It is checked against the piece's move rules and if validated by isValid() it is assigned to pos through move(), updating the piece's position
	Pos oldPos;                //oldPos must be initialized with pos in piecemanager just like pos in the initializer functions
	Pos virtualPos{};            //will be deprecated? A position that is used in checkmate evaluation instead of pos. 
	Pos cachedPos{};               //will be deprecated? Caches the current pos, used in checkmate evaluation
	Flag flag{};                   //each piece stores the flag of its team
	ActionType actionType;              //ActionType::point if king, knight or pawn. ActionType::diffusal if rook, bishop or queen. Used for checkmate evaluation
	bool capture{ false };           //indicates the piece has performed a capture
	bool moved{ false };             //becomes true at first move
	bool locked{ false };            //becomes true if the piece is between a diffusal range piece and the king, locking it in place in order to defend the king
	char graphics{};                 //a char that is printed by the board to represent each piece
	const PieceManager& piece_ref;
public:
	Piece(const PieceManager& ref, ActionType action);
	Pos getPos() const;
	Pos getOldPos() const;
	void setPos(int x, int y);
	void setEndPos(Pos pos);
	void setFlag(Flag input);
	Flag getFlag() const;
	void move();                      //moves the piece to the selected position only after it has been validated by isValid()
	void undoMove();                  //undoes the move by assigning to pos the value stored in oldPos
	int dir();                        //this function outputs 1 if black and -1 if white and it's used for movement arithmetics, in order to direct the move of the pieces in their corresponding directions by taking into account their flag, as the global master array's coordinates are the only ones being used
	void setGraphics(char value);
	char getGraphics() const;
	void didCapture();                //fires if the piece performs a capture
	bool checkCapture() const;        //returns the state of the capture boolean
	void resetCapture();              //resets the capture boolean to false
	void hasMovedOnce();              //sets the moved boolean to true 
	ActionType getActionType() const;
	void lock();              //locked = true, still to implement
	void unlock();            //locked = false, still to implement
	virtual std::vector<Pos> getBaseMovesIteration(Pos checkingPiecePos) = 0;              //under work. Fires all base moves for the piece, gathers only the valid ones in a vector that is fed to GameManager class to evaluate the checkmate condition. Takes the position of the checking piece as argument to fire only the moves that are relevant and optimize away all other moves 
	virtual bool isValid() = 0;                          //validates a move selection, it verifies if the move rule for the selected piece is respected and checks for collisions
	virtual bool checkScanner() = 0;                     //each piece scans for the king and signals a check if in range or locks the piece in between if the case
	virtual ~Piece() = default;
};

class Pawn : public Piece {
public:
	Pawn(const PieceManager& ref);
	inline Pos forward();
	inline Pos forwardDouble();
	inline Pos captureRight();
	inline Pos captureLeft();
	void promotion();                 //still to implement
	std::vector<Pos> getBaseMovesIteration(Pos checkingPiecePos) override;
	bool isValid() override;
	bool checkScanner() override;
};

class Knight : public Piece {
public:
	Knight(const PieceManager& ref);
	inline Pos getUpRightJump();
	inline Pos getUpLeftJump();
	inline Pos getDownRightJump();
	inline Pos getDownLeftJump();
	inline Pos getRightUpJump();
	inline Pos getRightDownJump();
	inline Pos getLeftUpJump();
	inline Pos getLeftDownJump();
	std::vector<Pos> getBaseMovesIteration(Pos checkingPiecePos) override;
	bool isValid() override;
	bool checkScanner() override;
};

class Rook : public Piece {
public:
	Rook(const PieceManager& ref);
	std::vector<Pos> getBaseMovesIteration(Pos checkingPiecePos) override;
	bool isValid() override;
	bool checkScanner() override;
};

class Bishop : public Piece {
public:
	Bishop(const PieceManager& ref);
	std::vector<Pos> getBaseMovesIteration(Pos checkingPiecePos) override;
	bool isValid() override;
	bool checkScanner() override;
};

class King : public Piece {
private:
	CastlingMove castlingMoveSelected{ CastlingMove::other };               //enum to designate if the king is performing a regular move or a specific castling move
	bool check{ false };               //boolean flag that is set to true if under check
public:
	King(const PieceManager& ref);
	inline Pos forward();
	inline Pos backwards();
	inline Pos right();
	inline Pos left();
	inline Pos up_right();
	inline Pos up_left();
	inline Pos down_right();
	inline Pos down_left();
	inline Pos kingsideCastling();                  //this function is a blueprint of the position the king would assume if kingside castling is validated, does not perform the actual move
	inline Pos queensideCastling();                //idem with queenside castling
	inline Pos kingsideStepping();                 //as per the rules of chess, both squares that lie between the king and right rook must be empty and not under threat, so the function is fired 2 times when kingside castling is validated, once per each step it makes so that the king is checked if under attack in the square it steps into
	inline Pos queensideStepping();               //same with queenside castling
	void resetCastlingMove();                    //puts the castlingMoveSelected enum to CastlingMove::other
	CastlingMove getCastlingMove();
	void setCheck();             //sets check boolean to true
	void resetCheck();             //sets check boolean to false
	bool getCheckState() const;          //gets check boolean
	std::vector<Pos> getBaseMovesIteration(Pos checkingPiecePos) override;
	bool isValid() override;
	bool checkScanner() override;
};

class Queen : public Piece {
public:
	Queen(const PieceManager& ref);
	std::vector<Pos> getBaseMovesIteration(Pos checkingPiecePos) override;
	bool isValid() override;
	bool checkScanner() override;
};