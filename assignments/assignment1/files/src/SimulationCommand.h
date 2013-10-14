// SimulationCommand.h

#ifndef SIMULATION_COMMAND_H
#define SIMULATION_COMMAND_H

#include <string>
#include "Tissue.h"
using namespace std;

class SimulationCommand{
public:
	SimulationCommand(string inputLine);

	enum commandT{
		noOp_,
		tissueNew_,
		cytotoxicCellNew_, 
		helperCellNew_, 
		infectionStartLocationIs_,
		infectedCellsDel_,
		cloneNew_,
		cloneCellsNew_,
		antibodyStrengthIs_
	};

	// Instance Variables
	commandT type;
	string tissueName;
	Cell::Coordinates coords;
	CellMembrane::Side direction;
	AntibodyStrength strength;
};

#endif