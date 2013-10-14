// InfectionSimulator.cpp implementation

#include <stdlib.h>
#include <iostream>
#include <vector>
#include <sstream>
#include "InfectionSimulator.h"
#include "SimulationCommand.h"

void 
InfectionSimulator::tissueNew(SimulationCommand cmd){
	if (cmd.type != SimulationCommand::tissueNew_) 
		throw;
	Tissue::Ptr tissue = Tissue::TissueNew(cmd.tissueName);
	tissues[cmd.tissueName] = tissue;
	tissueReactors[cmd.tissueName] = TissueReactor::TissueReactorIs(tissue.ptr());
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