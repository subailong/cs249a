// #include <fstream>
// #include <stdlib.h>
// #include <queue>
#include "TissueReactor.h"
// using namespace std;

void TissueReactor::onCellNew(Cell::Ptr) {
   cout << "Got new cell." << endl;
}

void TissueReactor::onCellDel(Cell::Ptr) {
   cout << "Deleted cell." << endl;
}

TissueReactor *TissueReactor::TissueReactorIs(Tissue *t) {
   TissueReactor *m = new TissueReactor(t);
   return m;
}

TissueReactor::TissueReactor(Tissue *t) : Tissue::Notifiee() {
   notifierIs(t);
}
