#pragma once
#include "Objects.h"

class PieceManager;

class Piece {
protected:
	Pos pos{};
	Pos endPos{};
	Pos oldPos{};
	Flag flag{};
	bool capture{ false };
	bool moved{ false };
	bool locked{ false };
	char graphics{};
	const PieceManager& piece_ref;
public:
	Piece(const PieceManager& ref);
	Pos getPos() const;
	Pos getOldPos() const;
	void setPos(int x, int y);
	void setEndPos(Pos pos);
	void setFlag(Flag input);
	Flag getFlag() const;
	void move();
	int dir();
	void setGraphics(char value);
	char getGraphics() const;
	void didCapture();
	bool checkCapture() const;
	void resetCapture();
	void hasMovedOnce();
	bool lock();
	bool unlock();
	virtual bool isValid() = 0;
	virtual bool checkScanner() = 0;
	virtual bool kingsideScanner() = 0;
	virtual bool queensideScanner() = 0;
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
	bool checkScanner() override;
	bool kingsideScanner() override;
	bool queensideScanner() override;
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
	bool checkScanner() override;
	bool kingsideScanner() override;
	bool queensideScanner() override;
};

class Rook : public Piece {
public:
	Rook(const PieceManager& ref);
	bool isValid() override;
	bool checkScanner() override;
	bool kingsideScanner() override;
	bool queensideScanner() override;
};

class Bishop : public Piece {
public:
	Bishop(const PieceManager& ref);
	bool isValid() override;
	bool checkScanner() override;
	bool kingsideScanner() override;
	bool queensideScanner() override;
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
	bool checkScanner() override;
	bool kingsideScanner() override;
	bool queensideScanner() override;
};

class Queen : public Piece {
public:
	Queen(const PieceManager& ref);
	bool isValid() override;
	bool checkScanner() override;
	bool kingsideScanner() override;
	bool queensideScanner() override;
};