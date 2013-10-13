
#include <fstream>
#include <stdlib.h>
#include <queue>
#include "Tissue.h"
using namespace std;
/*
 * Author: Anant Bhardwaj
 * Date: Sep 30, 2011
 * 
 */

class TissueReactor : public Tissue::Notifiee {
public:
   void onCellNew(Cell::Ptr) {
      cout << "Got new cell." << endl;
   }

   static TissueReactor * TissueReactorIs(Tissue *t) {
      TissueReactor *m = new TissueReactor(t);
      return m;
   }
protected:
   TissueReactor(Tissue *t) : Tissue::Notifiee() {
      notifierIs(t);
   }
};

int main(int argc, const char* argv[]) {
   Cell::Coordinates coord_1 = Cell::Coordinates();
   Cell::Coordinates coord_2 = Cell::Coordinates();
   coord_1.x=1;
   coord_1.y=1;
   coord_1.z=1;
   coord_2.x = 5;
   coord_2.y=5;
   coord_2.z=5;
   cout << "(coord_1 == coord_2) = " << (coord_1 == coord_2) << endl;
   Tissue::Ptr tissue = Tissue::TissueNew("myTissue");

   TissueReactor *m = TissueReactor::TissueReactorIs(tissue.ptr());

   cout << "Adding two cells:" << endl;
   tissue->cellIs(Cell::CellNew(coord_1, tissue.ptr(), Cell::tCell()));
   tissue->cellIs(Cell::CellNew(coord_2, tissue.ptr(), Cell::tCell()));
   Cell::Ptr cell = tissue->cell(coord_1);
   Cell::Ptr cell2 = tissue->cell(coord_2);

   cout << "Current cells in tissue " << tissue->name() << ":" << endl;
   for (Tissue::CellIteratorConst i = tissue->cellIterConst(); i; ++i) {
      cout << i->name() << endl;
   }

   tissue->cellDel(cell2->name());

   cout << "Cells in tissue " << tissue->name() << " after deleting "
        << cell2->name() << ":" << endl;
   for (Tissue::CellIteratorConst i = tissue->cellIterConst(); i; ++i) {
      cout << i->name() << endl;
   }

   cell->membraneNew("Membrane", CellMembrane::north());
   CellMembrane::Ptr mem = cell->membrane(CellMembrane::north());

   AntibodyStrength s = mem->antibodyStrength();
   cout << "mem->antibodyStrength() = " << s << endl;
   mem->antibodyStrengthIs(10);
   s = mem->antibodyStrength();
   cout << "Now mem->antibodyStrength() = " << s << endl;

   return 0;
}
