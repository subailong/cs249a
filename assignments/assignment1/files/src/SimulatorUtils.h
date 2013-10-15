// SimulatorUtils.h

#ifndef SIMULATOR_UTILS_H
#define SIMULATOR_UTILS_H

#include <string>
#include <vector>
#include "Tissue.h"
using namespace std;

class SimulatorUtils{
public: 
	static Cell::Coordinates toCoordinates(int x, int y, int z);
	static CellMembrane::Side toSide(string direction);
	static vector<CellMembrane::Side> sides();
	static Cell::Coordinates adjacentCoordinates(Cell::Coordinates coords, CellMembrane::Side direction);
// TODO: remove comments
// protected:
	// static vector<CellMembrane::Side> sides_;
};

#endif
