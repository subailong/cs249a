// SimulatorUtils.cpp implementation

#include "SimulatorUtils.h"

Cell::Coordinates SimulatorUtils::coordinates(int x, int y, int z){
	Cell::Coordinates c;
	c.x = x;
	c.y = y;
	c.z = z;
	return c;
}

CellMembrane::Side SimulatorUtils::side(string direction){
	if (direction == "north")
		return CellMembrane::north_;
	if (direction == "south")
		return CellMembrane::south_;
	if (direction == "east")
		return CellMembrane::east_;
	if (direction == "west")
		return CellMembrane::west_;
	if (direction == "up")
		return CellMembrane::up_;
	if (direction == "down")
		return CellMembrane::down_;
	throw;
}

