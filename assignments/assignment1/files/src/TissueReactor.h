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

   static TissueReactor *TissueReactorIs(Tissue *t);
protected:
   TissueReactor(Tissue *t);
};