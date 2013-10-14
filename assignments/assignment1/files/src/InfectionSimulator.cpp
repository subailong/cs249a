// InfectionSimulator.cpp implementation

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "InfectionSimulator.h"
#include "SimulationCommand.h"

void 
InfectionSimulator::commandIs(string inputLine){
	SimulationCommand cmd = SimulationCommand(inputLine);
	switch(cmd.type){
		case SimulationCommand::noOp_:
			cout << "noop" << endl;
			return;
		case SimulationCommand::tissueNew_:
			cout << "tissueNew" << endl;
			break;
		case SimulationCommand::cytotoxicCellNew_:
			cout << "cytotoxicCellNew" << endl;
			break;
		case SimulationCommand::helperCellNew_:
			cout << "helperCellNew" << endl;
			break;
		case SimulationCommand::infectionStartLocationIs_:
			cout << "infectionStartLocationIs" << endl;
			break;
		case SimulationCommand::infectedCellsDel_:
			cout << "infectedCellsDel" << endl;
			break;
		case SimulationCommand::cloneNew_:
			cout << "cloneNew" << endl;
			break;
		case SimulationCommand::cloneCellsNew_:
			cout << "cloneCellsNew" << endl;
			break;
		case SimulationCommand::antibodyStrengthIs_:
			cout << "antibodyStrengthIs" << endl;
			break;
		default:
			throw;
	}
}

