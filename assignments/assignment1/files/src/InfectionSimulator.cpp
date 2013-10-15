// InfectionSimulator.cpp implementation

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "InfectionSimulator.h"
#include "SimulationCommand.h"
#include "SimulatorUtils.h"
#include "Tissue.h"

void cloneSingleCell(Tissue::Ptr, Cell::Coordinates, CellMembrane::Side );

void 
InfectionSimulator::tissueNew(SimulationCommand cmd){
	cout << "-- tissueNew" << endl;
	if (cmd.commandType() != SimulationCommand::tissueNew()) 
		throw;
	Tissue::Ptr tissue = Tissue::TissueNew(cmd.tissueName());
	tissues[cmd.tissueName()] = tissue;
	tissueReactors[cmd.tissueName()] = TissueReactor::TissueReactorIs(tissue.ptr());
}

void 
InfectionSimulator::cytotoxicCellNew(SimulationCommand cmd){
	cout << "-- cytotoxicCellNew" << endl;
	if (cmd.commandType() != SimulationCommand::cytotoxicCellNew())
		throw;
	Tissue::Ptr tissue = tissues[cmd.tissueName()];
	Cell::Ptr cell = Cell::CellNew(cmd.coords(), tissue.ptr(), Cell::cytotoxicCell());
	tissue->cellIs(cell);
}

void 
InfectionSimulator::helperCellNew(SimulationCommand cmd){
	cout << "-- helperCellNew" << endl;
	if (cmd.commandType() != SimulationCommand::helperCellNew())
		throw;
	Tissue::Ptr tissue = tissues[cmd.tissueName()];
	Cell::Ptr cell = Cell::CellNew(cmd.coords(), tissue.ptr(), Cell::helperCell());
	tissue->cellIs(cell);
}

void 
InfectionSimulator::infectionStartLocationIs(SimulationCommand cmd){
	cout << "infectionStartLocationIs" << "--not implemented yet!" << endl;
}

void 
InfectionSimulator::infectedCellsDel(SimulationCommand cmd){
	cout << "-- infectedCellsDel" << endl;
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
	cout << "-- cloneNew" << endl;
	if (cmd.commandType() != SimulationCommand::cloneNew())
		throw;
	cloneSingleCell(tissues[cmd.tissueName()], cmd.coords(), cmd.direction());
}

void 
InfectionSimulator::cloneCellsNew(SimulationCommand cmd){
	cout << "-- cloneCellsNew" << endl;
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
	cout << "antibodyStrengthIs" << "--not implemented yet!" << endl;
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
cloneSingleCell(Tissue::Ptr tissue, Cell::Coordinates coords, CellMembrane::Side direction){
	Cell::Ptr motherCell = tissue->cell(coords);
	Cell::Coordinates cloneCoords = SimulatorUtils::adjacentCoordinates(coords, direction);
	Cell::Ptr cloneCell = Cell::CellNew(cloneCoords, tissue.ptr(), motherCell->cellType());
	cloneCell->healthIs(motherCell->health());
	tissue->cellIs(cloneCell);
}
