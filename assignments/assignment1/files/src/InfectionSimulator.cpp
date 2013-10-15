// InfectionSimulator.cpp implementation

#include <stdlib.h>
#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include <sstream>
#include "InfectionSimulator.h"
#include "SimulationCommand.h"
#include "SimulatorUtils.h"
#include "Tissue.h"

int numInfectedCells(Tissue::Ptr tissue);
int infectionSpread(Tissue::Ptr tissue);

void 
InfectionSimulator::tissueNew(SimulationCommand cmd){
	if (cmd.commandType() != SimulationCommand::tissueNew()) 
		throw;
	Tissue::Ptr tissue = Tissue::TissueNew(cmd.tissueName());
	tissues[cmd.tissueName()] = tissue;
	tissueReactors[cmd.tissueName()] = TissueReactor::TissueReactorIs(tissue.ptr());
}

void 
InfectionSimulator::cytotoxicCellNew(SimulationCommand cmd){
	if (cmd.commandType() != SimulationCommand::cytotoxicCellNew())
		throw;
	Tissue::Ptr tissue = tissues[cmd.tissueName()];
	Cell::Ptr cell = Cell::CellNew(cmd.coords(), tissue.ptr(), Cell::cytotoxicCell());
	tissue->cellIs(cell);
}

void 
InfectionSimulator::helperCellNew(SimulationCommand cmd){
	if (cmd.commandType() != SimulationCommand::helperCellNew())
		throw;
	Tissue::Ptr tissue = tissues[cmd.tissueName()];
	Cell::Ptr cell = Cell::CellNew(cmd.coords(), tissue.ptr(), Cell::helperCell());
	tissue->cellIs(cell);
}

void 
InfectionSimulator::infectionStartLocationIs(SimulationCommand cmd){
	if (cmd.commandType() != SimulationCommand::infectionStartLocationIs())
		throw;
	Tissue::Ptr tissue = tissues[cmd.tissueName()];
	TissueReactor::Ptr tissueReactor = tissueReactors[cmd.tissueName()];
	queue<BFSPair> currentBFSLevelNodes;
	queue<BFSPair> nextBFSLevelNodes;
	AntibodyStrength strength = cmd.strength();
	Cell::Ptr cell;
	CellMembrane::Side side;
	CellMembrane::Ptr mem;
	int strengthDelta;
	int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0;
	int bfsLevel = 0;
	int maxBfsLevel = 0;

	if(existsHealthyCell(tissue, cmd.coords())){
		BFSPair p = make_pair(tissue->cell(cmd.coords()), cmd.direction());
		nextBFSLevelNodes.push(p);
	}

	while(!currentBFSLevelNodes.empty() || !nextBFSLevelNodes.empty()){
		if(currentBFSLevelNodes.empty()){
			bfsLevel++;
			currentBFSLevelNodes = nextBFSLevelNodes;
			nextBFSLevelNodes = queue<BFSPair>();
		}
		while(!currentBFSLevelNodes.empty()){
			BFSPair p = currentBFSLevelNodes.front();
			currentBFSLevelNodes.pop();
			cell = p.first;
			side = p.second;
			mem = cell->membrane(side);
			
			if(cell->health() == Cell::healthy()){
				/* infection attempt */
				b++;
				strengthDelta = strength.value() - mem->antibodyStrength().value();
				c += strengthDelta;
				/* can infect */
				if (strengthDelta > 0){
					maxBfsLevel = (bfsLevel > maxBfsLevel) ? bfsLevel : maxBfsLevel;
					cell->healthIs(Cell::infected());
					queue<BFSPair> neighbors = healthyNeighbors(tissue, cell);
					/* enqueue infectable neighbors to next BFS level queue */
					while(!neighbors.empty()){
						nextBFSLevelNodes.push(neighbors.front());
						neighbors.pop();
					}
				}
			}
		}
	}

	a = numInfectedCells(tissue);
	d = tissueReactor->numCytotoxicCells();
	e = tissueReactor->numHelperCells();
	f = infectionSpread(tissue);
	g = maxBfsLevel;
	cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << " " << g << endl;
}

void 
InfectionSimulator::infectedCellsDel(SimulationCommand cmd){
	if (cmd.commandType() != SimulationCommand::infectedCellsDel())
		throw;
	Tissue::Ptr tissue = tissues[cmd.tissueName()];
	vector<string> cellsToDelete;
	for (Tissue::CellIteratorConst cell = tissue->cellIterConst(); cell; ++cell) {
		if (cell->health() == Cell::infected()){
			cellsToDelete.push_back(cell->name());
		}
   	}
	for (size_t i = 0; i < cellsToDelete.size(); ++i) {
		tissue->cellDel(cellsToDelete[i]);
   	}
}

void 
InfectionSimulator::cloneNew(SimulationCommand cmd){
	if (cmd.commandType() != SimulationCommand::cloneNew())
		throw;
	cloneSingleCell(tissues[cmd.tissueName()], cmd.coords(), cmd.direction());
}

void 
InfectionSimulator::cloneCellsNew(SimulationCommand cmd){
	if (cmd.commandType() != SimulationCommand::cloneCellsNew())
		throw;
	Tissue::Ptr tissue = tissues[cmd.tissueName()];
	vector<Cell::Coordinates> cellsToClone;
	for (Tissue::CellIteratorConst cell = tissue->cellIterConst(); cell; ++cell)
		cellsToClone.push_back(cell->location());
	for (size_t i = 0; i < cellsToClone.size(); ++i) {
		try{
			cloneSingleCell(tissue, cellsToClone[i], cmd.direction());
		}
		catch(Fwk::NameInUseException) {}
	}
}

void 
InfectionSimulator::antibodyStrengthIs(SimulationCommand cmd){
	if (cmd.commandType() != SimulationCommand::antibodyStrengthIs())
		throw;
	Tissue::Ptr tissue = tissues[cmd.tissueName()];
	Cell::Ptr cell = tissue->cell(cmd.coords());
	CellMembrane::Ptr mem = cell->membrane(cmd.direction());
	mem->antibodyStrengthIs(cmd.strength());	
}

/* for testing */
Tissue::Ptr 
InfectionSimulator::tissue(string tissueName){
	return tissues[tissueName];
}

TissueReactor::Ptr 
InfectionSimulator::tissueReactor(string tissueName){
	return tissueReactors[tissueName];
}



/* Helper functions */

void 
InfectionSimulator::cloneSingleCell(Tissue::Ptr tissue, Cell::Coordinates coords, CellMembrane::Side direction){
	Cell::Ptr motherCell = tissue->cell(coords);
	Cell::Coordinates cloneCoords = SimulatorUtils::adjacentCoordinates(coords, direction);
	Cell::Ptr cloneCell = Cell::CellNew(cloneCoords, tissue.ptr(), motherCell->cellType());
	cloneCell->healthIs(motherCell->health());
	tissue->cellIs(cloneCell);
	vector<CellMembrane::Side> sides = SimulatorUtils::sides();
	CellMembrane::Side side;

	/* copy membranes' antibodyStrenghts */
	for (size_t i = 0; i < sides.size(); ++i){
		side = sides[i];
		AntibodyStrength s = motherCell->membrane(side)->antibodyStrength();
		cloneCell->membrane(side)->antibodyStrengthIs(s);
   	}
}

bool 
InfectionSimulator::existsHealthyCell(Tissue::Ptr tissue, Cell::Coordinates coords){
	Cell::Ptr cell = tissue->cell(coords);
	return cell.ptr() && (cell->health() == Cell::healthy());
}

queue<BFSPair>
InfectionSimulator::healthyNeighbors(Tissue::Ptr tissue, Cell::Ptr cell){
	queue<BFSPair> q;
	vector<CellMembrane::Side> sides = SimulatorUtils::sides();
	for (size_t i = 0; i < sides.size(); ++i){
		CellMembrane::Side side = sides[i];
		CellMembrane::Side oppositeSide = SimulatorUtils::oppositeSide(side);
		Cell::Coordinates adjacentCoords = SimulatorUtils::adjacentCoordinates(cell->location(), side);
		if (existsHealthyCell(tissue, adjacentCoords)){
			BFSPair p = make_pair(tissue->cell(adjacentCoords), oppositeSide);
			q.push(p);
		}
   	}
   	return q;
}

int 
numInfectedCells(Tissue::Ptr tissue){
	int count = 0;

	for (Tissue::CellIteratorConst cell = tissue->cellIterConst(); cell; ++cell) {
		if (cell->health() == Cell::infected())
			count++;
   	}

	return count;
}

int 
infectionSpread(Tissue::Ptr tissue){
	int x_max = -51, y_max = -51, z_max = -51;
	int x_min = 51, y_min = 51, z_min = 51;
	bool foundInfection = false;
	for (Tissue::CellIteratorConst cell = tissue->cellIterConst(); cell; ++cell) {
		if (cell->health() == Cell::infected()){
			foundInfection = true;
			Cell::Coordinates coords = cell->location();
			x_max = (coords.x > x_max) ? coords.x : x_max;
			x_min = (coords.x < x_min) ? coords.x : x_min;
			y_max = (coords.y > y_max) ? coords.y : y_max;
			y_min = (coords.y < y_min) ? coords.y : y_min;
			z_max = (coords.z > z_max) ? coords.z : z_max;
			z_min = (coords.z < z_min) ? coords.z : z_min;
		}
   	}
   	int spread = foundInfection ? (x_max - x_min + 1) * (y_max - y_min + 1) * (z_max - z_min + 1) : 0;
	return spread;
}
