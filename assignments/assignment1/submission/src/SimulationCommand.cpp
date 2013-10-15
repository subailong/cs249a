// SimulationCommand.cpp implementation

#include "SimulationCommand.h"
#include "SimulatorUtils.h"

SimulationCommand::SimulationCommand(string inputLine){
	type_ = noOp_;
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
    		type_ = tissueNew_;
    		istream >> tissueName_;
    	}
    	else{
    		tissueName_ = token;
    		istream >> token;
    		if (token == "cytotoxicCellNew"){
    			type_ = cytotoxicCellNew_;
    			istream >> x >> y >> z;
    			coords_ = SimulatorUtils::toCoordinates(x, y, z);
    		}
    		else if (token == "helperCellNew"){
    			type_ = helperCellNew_;
    			istream >> x >> y >> z;
    			coords_ = SimulatorUtils::toCoordinates(x, y, z);
    		}
    		else if (token == "infectionStartLocationIs"){
    			type_ = infectionStartLocationIs_;
    			istream >> x >> y >> z >> direction >> strength;
    			coords_ = SimulatorUtils::toCoordinates(x, y, z);
    			direction_ = SimulatorUtils::toSide(direction);
    			strength_ = AntibodyStrength(strength);
    		}
    		else if (token == "infectedCellsDel"){
    			type_ = infectedCellsDel_;
    		}
    		else if (token == "cloneCellsNew"){
    			type_ = cloneCellsNew_;
    			istream >> direction;
    			direction_ = SimulatorUtils::toSide(direction);
    		}
    	}
    }
    else if (token == "Cell"){
    	istream >> tissueName_;
    	istream >> x >> y >> z;
    	coords_ = SimulatorUtils::toCoordinates(x, y, z);
    	istream >> token;
    	if (token == "cloneNew"){
    		type_ = cloneNew_;
    		istream >> direction;
    		direction_ = SimulatorUtils::toSide(direction);
    	}
    	else if (token == "membrane" || token == "Membrane"){
    		istream >> direction >> token >> strength;
    		if (token == "antibodyStrengthIs"){
    			type_ = antibodyStrengthIs_;
    			direction_ = SimulatorUtils::toSide(direction);
    			strength_ = AntibodyStrength(strength);
    		}
    	}
    }
}