// InfectionSimulator.h

#ifndef INFECTION_SIMULATOR_H
#define INFECTION_SIMULATOR_H

#include <string>
#include <map>
#include "Tissue.h"
#include "TissueReactor.h"
#include "SimulationCommand.h"
using namespace std;

typedef pair<Cell::Ptr, CellMembrane::Side> BFSPair;

class InfectionSimulator{
public: 
	void tissueNew(SimulationCommand cmd);
	void cytotoxicCellNew(SimulationCommand cmd);
	void helperCellNew(SimulationCommand cmd);
	void infectionStartLocationIs(SimulationCommand cmd);
	void infectedCellsDel(SimulationCommand cmd);
	void cloneNew(SimulationCommand cmd);
	void cloneCellsNew(SimulationCommand cmd);
	void antibodyStrengthIs(SimulationCommand cmd);

	/* for testing */
	Tissue::Ptr tissue(string tissueName);
	TissueReactor::Ptr tissueReactor(string tissueName);
	void cloneSingleCell(Tissue::Ptr tissue, Cell::Coordinates coords, CellMembrane::Side direction);
	bool existsHealthyCell(Tissue::Ptr tissue, Cell::Coordinates coords);
	queue<BFSPair> healthyNeighbors(Tissue::Ptr tissue, Cell::Ptr cell);
protected:
	/* instance variables */
	map<string, Tissue::Ptr> tissues;
	map<string, TissueReactor::Ptr> tissueReactors;
};

#endif
