#include <fstream>
#include <stdlib.h>
#include <queue>
#include "Tissue.h"
#include "InfectionSimulator.h"
using namespace std;

/*
  The main takes in one input, the file name with the rules.
  The rules are then executed and the appropriate statistics are printed
  to the console.
*/
int main(int argc, const char* argv[]) {
  ifstream infile(argv[1]);
  if(infile.fail()){
    //File error. Halt program.
    cout << "error reading file" << endl;
    return 1;
  }

  //read data in, parse it, excute commands.
  InfectionSimulator simulator;
  string textLine;
  while(!infile.eof()){
    getline(infile, textLine);
    try {
      SimulationCommand cmd = SimulationCommand(textLine);  
      if (cmd.commandType() == SimulationCommand::noOp())
        continue;
      else if (cmd.commandType() == SimulationCommand::tissueNew())
        simulator.tissueNew(cmd);
      else if (cmd.commandType() == SimulationCommand::cytotoxicCellNew())
        simulator.cytotoxicCellNew(cmd);
      else if (cmd.commandType() == SimulationCommand::helperCellNew())
        simulator.helperCellNew(cmd);
      else if (cmd.commandType() == SimulationCommand::infectionStartLocationIs())
        simulator.infectionStartLocationIs(cmd);
      else if (cmd.commandType() == SimulationCommand::infectedCellsDel())
        simulator.infectedCellsDel(cmd);
      else if (cmd.commandType() == SimulationCommand::cloneNew())
        simulator.cloneNew(cmd);
      else if (cmd.commandType() == SimulationCommand::cloneCellsNew())
        simulator.cloneCellsNew(cmd);
      else if (cmd.commandType() == SimulationCommand::antibodyStrengthIs())
        simulator.antibodyStrengthIs(cmd);
      else
        throw;
    }
    // TODO: test exceptions, throw better exceptions
    catch( const exception & ex ) {
       cout << ex.what() << endl;
    }
  }
  return 0;
}
