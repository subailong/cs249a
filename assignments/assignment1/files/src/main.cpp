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
      switch(cmd.type){
        case SimulationCommand::noOp_:
          break;
        case SimulationCommand::tissueNew_:
          simulator.tissueNew(cmd);
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
    // TODO: test exceptions, throw better exceptions
    catch( const exception & ex ) {
       cout << ex.what() << endl;
    }
  }
  return 0;
}
