// InfectionSimulator.cpp implementation

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "InfectionSimulator.h"
#include "SimulationCommand.h"
#include "SimulatorUtils.h"
#include "Tissue.h"

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
	for (Tissue::CellIteratorConst cell = tissue->cellIterConst(); cell; ++cell) {
		if (cell->health() == Cell::infected()){
			tissue->cellDel(cell->name());
		}
   	}
}

void 
InfectionSimulator::cloneNew(SimulationCommand cmd){
	cout << "-- cloneNew" << endl;
	if (cmd.commandType() != SimulationCommand::cloneNew())
		throw;
	Tissue::Ptr tissue = tissues[cmd.tissueName()];
	Cell::Ptr motherCell = tissue->cell(cmd.coords());
	Cell::Coordinates cloneCoords = SimulatorUtils::adjacentCoordinates(cmd.coords(), cmd.direction());
	Cell::Ptr cloneCell = Cell::CellNew(cloneCoords, tissue.ptr(), motherCell->cellType());
	cloneCell->healthIs(motherCell->health());
	tissue->cellIs(cloneCell);
}

void 
InfectionSimulator::cloneCellsNew(SimulationCommand cmd){
	cout << "cloneCellsNew" << "--not implemented yet!" << endl;
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