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

  InfectionSimulator simulator;
  //read data in, parse it, excute commands.
  string textLine;
  while(!infile.eof()){
    getline(infile, textLine);
    simulator.commandIs(textLine);
  }
  return 0;
}
