// SimulatorUtils.cpp implementation

#include "SimulatorUtils.h"

Cell::Coordinates 
SimulatorUtils::toCoordinates(int x, int y, int z){
	Cell::Coordinates c;
	c.x = x;
	c.y = y;
	c.z = z;
	return c;
}

CellMembrane::Side 
SimulatorUtils::toSide(string direction){
	if (direction == "north")
		return CellMembrane::north();
	if (direction == "south")
		return CellMembrane::south();
	if (direction == "east")
		return CellMembrane::east();
	if (direction == "west")
		return CellMembrane::west();
	if (direction == "up")
		return CellMembrane::up();
	if (direction == "down")
		return CellMembrane::down();
	throw;
}

// TODO: make this a static var, dont create the vector on every call
vector<CellMembrane::Side> 
SimulatorUtils::sides(){
	vector<CellMembrane::Side> sides = vector<CellMembrane::Side>();
	sides.push_back(CellMembrane::north());
	sides.push_back(CellMembrane::south());
	sides.push_back(CellMembrane::east());
	sides.push_back(CellMembrane::west());
	sides.push_back(CellMembrane::up());
	sides.push_back(CellMembrane::down());
	return sides;
}
