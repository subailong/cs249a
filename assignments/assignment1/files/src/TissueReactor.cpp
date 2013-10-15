// #include <fstream>
// #include <stdlib.h>
// #include <queue>
#include "TissueReactor.h"
#include "SimulatorUtils.h"
// using namespace std;

void 
TissueReactor::onCellNew(Cell::Ptr cell) {
   AntibodyStrength strength;
   CellMembrane::Ptr mem;
   CellMembrane::Side side;
   vector<CellMembrane::Side> sides = SimulatorUtils::sides();

   // increase cell counts
	if(cell->cellType() == Cell::cytotoxicCell()){
		numCytotoxicCells_++;
      strength = 100;
   }
   else if (cell->cellType() == Cell::helperCell()){
      numHelperCells_++;
      strength = 0;
   }
   // initialize membranes
   for (size_t i = 0; i < sides.size(); ++i){
      side = sides[i];
      cell->membraneNew("Membrane", side);
      mem = cell->membrane(side);
      mem->antibodyStrengthIs(strength);
   }
}

void 
TissueReactor::onCellDel(Cell::Ptr cell) {
   cout << "Deleted cell." << endl;
}

// CellCount TissueReactor::numCytotoxicCells(){
U64 
TissueReactor::numCytotoxicCells(){
	return numCytotoxicCells_;
}

U64 
TissueReactor::numHelperCells(){
	return numHelperCells_;
}

TissueReactor *
TissueReactor::TissueReactorIs(Tissue *t) {
   TissueReactor *m = new TissueReactor(t);
   m->numCytotoxicCells_ = 0;
   m->numHelperCells_ = 0;
   return m;
}

TissueReactor::TissueReactor(Tissue *t) : Tissue::Notifiee() {
   notifierIs(t);
}
