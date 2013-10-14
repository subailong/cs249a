// SimulationCommand.cpp implementation

#include "SimulationCommand.h"
#include "SimulatorUtils.h"

SimulationCommand::SimulationCommand(string inputLine){
	type = noOp_;
    if (inputLine.length() == 0 || inputLine[0] == '#') 
    	return;
    stringstream istream(inputLine);
    string token;
    int x, y, z, strength;
    string direction;
    
    istream >> token;
    if (token == "Tissue"){
    	istream >> token;
    	if (token == "tissueNew"){
    		type = tissueNew_;
    		istream >> tissueName;
    	}
    	else{
    		tissueName = token;
    		istream >> token;
    		if (token == "cytotoxicCellNew"){
    			type = cytotoxicCellNew_;
    			istream >> x >> y >> z;
    			coords = SimulatorUtils::coordinates(x, y, z);
    		}
    		else if (token == "helperCellNew"){
    			type = helperCellNew_;
    			istream >> x >> y >> z;
    			coords = SimulatorUtils::coordinates(x, y, z);
    		}
    		else if (token == "infectionStartLocationIs"){
    			type = infectionStartLocationIs_;
    			istream >> x >> y >> z >> direction >> strength;
    			coords = SimulatorUtils::coordinates(x, y, z);
    			this->direction = SimulatorUtils::side(direction);
    			this->strength = AntibodyStrength(strength);
    		}
    		else if (token == "infectedCellsDel"){
    			type = infectedCellsDel_;
    		}
    		else if (token == "cloneCellsNew"){
    			type = cloneCellsNew_;
    			istream >> direction;
    			this->direction = SimulatorUtils::side(direction);
    		}
    	}
    }
    else if (token == "Cell"){
    	istream >> tissueName;
    	istream >> x >> y >> z;
    	coords = SimulatorUtils::coordinates(x, y, z);
    	istream >> token;
    	if (token == "cloneNew"){
    		type = cloneNew_;
    		istream >> direction;
    		this->direction = SimulatorUtils::side(direction);
    	}
    	else if (token == "membrane"){
    		istream >> direction >> token >> strength;
    		if (token == "antibodyStrengthIs"){
    			type = antibodyStrengthIs_;
    			this->direction = SimulatorUtils::side(direction);
    			this->strength = AntibodyStrength(strength);
    		}
    	}
    }
}