// SimulationCommand.h

#ifndef SIMULATION_COMMAND_H
#define SIMULATION_COMMAND_H

#include <string>
#include "Tissue.h"
using namespace std;

class SimulationCommand{
public:
	SimulationCommand(string inputLine);

	enum CommandT{
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

	CommandT commandType() const { return type_; }
	string tissueName() const { return tissueName_; }
	Cell::Coordinates coords() const { return coords_; }
	CellMembrane::Side direction() const { return direction_; }
	AntibodyStrength strength() const { return strength_; }

	static inline CommandT noOp() { return noOp_; }
	static inline CommandT tissueNew() { return tissueNew_; }
	static inline CommandT cytotoxicCellNew() { return cytotoxicCellNew_; }
	static inline CommandT helperCellNew() { return helperCellNew_; }
	static inline CommandT infectionStartLocationIs() { return infectionStartLocationIs_; }
	static inline CommandT infectedCellsDel() { return infectedCellsDel_; }
	static inline CommandT cloneNew() { return cloneNew_; }
	static inline CommandT cloneCellsNew() { return cloneCellsNew_; }
	static inline CommandT antibodyStrengthIs() { return antibodyStrengthIs_; }

protected:
	// Instance Variables
	CommandT type_;
	string tissueName_;
	Cell::Coordinates coords_;
	CellMembrane::Side direction_;
	AntibodyStrength strength_;
};

#endif