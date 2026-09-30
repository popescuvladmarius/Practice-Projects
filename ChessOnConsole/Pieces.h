#pragma once
#include "Objects.h"

class PieceManager;

class Piece {
protected:
	Pos pos{};
	Pos endPos{};
	Flag flag{};
	int i{ 1 };
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
	virtual bool isValid() = 0;
	virtual ~Piece() = default;
};

class Pawn : public Piece {
private:
	char graphics{ 'p' };
public:
	Pawn(const PieceManager& ref);
	char getGraphics() const;
	Pos forward();
	Pos forwardDouble();
	Pos captureRight();
	Pos captureLeft();
	bool isValid() override;
};

class Knight : public Piece {
private:
	char graphics{ 'k' };
public:
	Knight(const PieceManager& ref);
	char getGraphics() const;
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
private:
	char graphics{ 'R' };
public:
	Rook(const PieceManager& ref);
	char getGraphics() const;
	bool isValid() override;
};

class Bishop : public Piece {
private:
	char graphics{ 'B' };
public:
	Bishop(const PieceManager& ref);
	char getGraphics() const;
	bool isValid() override;
};

class King : public Piece {
private:
	char graphics{ 'K' };
public:
	King(const PieceManager& ref);
	char getGraphics() const;
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
private:
	char graphics{ 'Q' };
public:
	Queen(const PieceManager& ref);
	char getGraphics() const;
	bool isValid() override;
};