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
	void input();             //input in file and rank notation
	bool checkInput();              //checks if input respects the board's representation
	Pos getInputNormalized();       //converts the input in array coordinates
	void select();                  //employs all functions above to perform a valid input selection and populate inputPos, within the board's bounds.
	Pos getInputPos() const;        //input getter
};

//the controller expects input using classic chess file and rank notation
//then converts that into array coordinates and assigns them to inputPos