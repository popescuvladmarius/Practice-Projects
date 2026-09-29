#pragma once
#include "Objects.h"

class Controller {
private:
	Pos inputPos{};
	char inputFile;
	int inputRank;
	std::array<char, 8> files;
public:
	Controller();
	void input();
	bool checkInput();
	Pos getInputNormalized();
	void select();
	Pos getInputPos() const;
};