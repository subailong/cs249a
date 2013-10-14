// InfectionSimulator.h

#ifndef INFECTION_SIMULATOR_H
#define INFECTION_SIMULATOR_H

#include <string>
#include <map>
#include "Tissue.h"
#include "TissueReactor.h"
#include "SimulationCommand.h"
using namespace std;

class InfectionSimulator{
public: 
	void tissueNew(SimulationCommand cmd);

	/* for testing */
	Tissue::Ptr tissue(string tissueName);
	TissueReactor::Ptr tissueReactor(string tissueName);
protected:
	/* instance variables */
	map<string, Tissue::Ptr> tissues;
	map<string, TissueReactor::Ptr> tissueReactors;
};

#endif
