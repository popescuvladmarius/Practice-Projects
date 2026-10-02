#pragma once
#include "Objects.h"

class PieceManager;

class Piece {
protected:
	Pos pos{};
	Pos endPos{};
	Flag flag{};
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
	virtual bool isValid() = 0;
	virtual ~Piece() = default;
};

class Pawn : public Piece {
public:
	Pawn(const PieceManager& ref);
	Pos forward();
	Pos forwardDouble();
	Pos captureRight();
	Pos captureLeft();
	bool isValid() override;
};

class Knight : public Piece {
public:
	Knight(const PieceManager& ref);
	Pos getUpRightJump();
	Pos getUpLeftJump();
	Pos getDownRightJump();
	Pos getDownLeftJump();
	Pos getRightUpJump();
	Pos getRightDownJump();
	Pos getLeftUpJump();
	Pos getLeftDownJump();
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
	Pos forward();
	Pos backwards();
	Pos right();
	Pos left();
	Pos up_right();
	Pos up_left();
	Pos down_right();
	Pos down_left();
	bool isValid() override;
};

class Queen : public Piece {
public:
	Queen(const PieceManager& ref);
	bool isValid() override;
};