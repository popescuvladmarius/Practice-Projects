#include "Controller.h"

Controller::Controller() {
	files[0] = 'a';
	files[1] = 'b';
	files[2] = 'c';
	files[3] = 'd';
	files[4] = 'e';
	files[5] = 'f';
	files[6] = 'g';
	files[7] = 'h';
}
void Controller::input() {
	std::cin >> inputFile >> inputRank;
}
bool Controller::checkInput() {
	if (inputRank <= 8 && inputRank >= 1) {
		for (std::size_t i = 0; i < 8; ++i) {
			if (inputFile == files[i]) {
				return true;
			}
		}
	}
	return false;
}
Pos Controller::getInputNormalized() {
	int row{};
	int col{};
	Pos temp{};
	for (std::size_t i = 0; i < 8; ++i) {
		if (inputFile == files[i]) {
			col = i;
			break;
		}
	}
	row = 7 - (inputRank - 1);
	temp.x = row;
	temp.y = col;
	return temp;
}
void Controller::select() {
	input();
	if (checkInput()) {
		inputPos = getInputNormalized();
	}
}
Pos Controller::getInputPos() const { return inputPos; }