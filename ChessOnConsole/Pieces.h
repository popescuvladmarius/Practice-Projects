#pragma once
#include "Objects.h"

class PieceManager;

class Piece {
protected:
	Pos pos{};
	Pos endPos{};
	Flag flag{};
	bool capture{ false };
	int i{ 1 };
	char graphics{};
	const PieceManager& piece_ref;
public:
	Piece(const PieceManager& ref);
	Pos getPos();
	void setPos(int x, int y);
	void setEndPos(Pos pos);
	void setFlag(Flag input);
	Flag getFlag() const;
	Pos move();
	int dir();
	void setGraphics(char value);
	char getGraphics();
	void didCapture();
	bool checkCapture();
	void resetCapture();
	virtual bool isValid() = 0;
	virtual ~Piece() = default;
};

class Pawn : public Piece {
public:
	Pawn(const PieceManager& ref);
	inline Pos forward();
	inline Pos forwardDouble();
	inline Pos captureRight();
	inline Pos captureLeft();
	bool isValid() override;
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
	bool isValid() override;
};

class Rook : public Piece {
public:
	Rook(const PieceManager& ref);
	bool isValid() override;
};

class Bishop : public Piece {
public:
	Bishop(const PieceManager& ref);
	bool isValid() override;
};

class King : public Piece {
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
	bool isValid() override;
};

class Queen : public Piece {
public:
	Queen(const PieceManager& ref);
	bool isValid() override;
};