// SimulatorUtils.h

#ifndef SIMULATOR_UTILS_H
#define SIMULATOR_UTILS_H

#include <string>
#include "Tissue.h"
using namespace std;

class SimulatorUtils{
public: 
	static Cell::Coordinates coordinates(int x, int y, int z);
	static CellMembrane::Side side(string direction);
};

#endif
