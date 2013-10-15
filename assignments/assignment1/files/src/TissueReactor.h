#include <fstream>
#include <stdlib.h>
#include <queue>
#include "Tissue.h"
using namespace std;

// class CellCount {
// public:
//    U64 value() const { return value_; }
//    bool operator==(CellCount _opArg) const;
//    bool operator!=(CellCount _opArg) const;
//    bool operator<(CellCount _opArg) const;
//    bool operator<=(CellCount _opArg) const;
//    bool operator>(CellCount _opArg) const;
//    bool operator>=(CellCount _opArg) const;
//    void valueIs(U64 _value) {
//       value_ = _value;
//    }
//    CellCount(U64 _value=0):
//          value_(_value) {
//    }
// protected:
//    U64 value_;
// };

class TissueReactor : public Tissue::Notifiee {
public:
   typedef Fwk::Ptr<TissueReactor const> PtrConst;
   typedef Fwk::Ptr<TissueReactor> Ptr;
   
   void onCellNew(Cell::Ptr);
   void onCellDel(Cell::Ptr);

   // CellCount numCytotoxicCells();
   U64 numCytotoxicCells();
   U64 numHelperCells();

   static TissueReactor *TissueReactorIs(Tissue *t);
protected:
   TissueReactor(Tissue *t);
   U64 numCytotoxicCells_;
   U64 numHelperCells_;
};