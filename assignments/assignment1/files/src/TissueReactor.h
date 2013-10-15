#include <fstream>
#include <stdlib.h>
#include <queue>
#include "Tissue.h"
using namespace std;

class TissueReactor : public Tissue::Notifiee {
public:
   typedef Fwk::Ptr<TissueReactor const> PtrConst;
   typedef Fwk::Ptr<TissueReactor> Ptr;
   
   void onCellNew(Cell::Ptr);
   void onCellDel(Cell::Ptr);

   U64 numCytotoxicCells();
   U64 numHelperCells();

   static TissueReactor *TissueReactorIs(Tissue *t);
protected:
   TissueReactor(Tissue *t);
   U64 numCytotoxicCells_;
   U64 numHelperCells_;
};