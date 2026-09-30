#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include "GeneralFunctions.h"

struct Pos {
	int x{};
	int y{};
	bool operator==(const Pos&) const = default;
};

enum class Flag {
	white,
	black
};

enum class Turn {
	white,
	black
};


