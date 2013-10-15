#include <string>
#include "gtest/gtest.h"
#include "InfectionSimulator.h"
using namespace std;


TEST(InfectionSimulator, newTissueCreatesTissueAndTissueReactor) {
  InfectionSimulator simulator;
  simulator.tissueNew(SimulationCommand("Tissue tissueNew Tissue1"));
  
  ASSERT_TRUE(simulator.tissue("Tissue1").ptr() != NULL);
  ASSERT_TRUE(simulator.tissueReactor("Tissue1").ptr() != NULL);
}

TEST(InfectionSimulator, cytotoxicCellNewCreatesCytotoxicCell) {
  InfectionSimulator simulator;
  simulator.tissueNew(SimulationCommand("Tissue tissueNew Tissue1"));
  Tissue::Ptr tissue = simulator.tissue("Tissue1");
  TissueReactor::Ptr tissueReactor = simulator.tissueReactor("Tissue1");
  ASSERT_TRUE(tissueReactor->numCytotoxicCells() == 0);
  SimulationCommand cmd = SimulationCommand("Tissue Tissue1 cytotoxicCellNew 1 2 3");
  simulator.cytotoxicCellNew(cmd);
  
  ASSERT_TRUE(tissueReactor->numCytotoxicCells() == 1);
  Cell::Ptr cell = tissue->cell(cmd.coords());  
  ASSERT_TRUE(cell->name() == "(1,2,3)");
  ASSERT_TRUE(cell->location() == cmd.coords());
  ASSERT_TRUE(cell->cellType() == Cell::cytotoxicCell());
}

TEST(InfectionSimulator, cytotoxicCellNewCreatesCellMembranes) {
  InfectionSimulator simulator;
  simulator.tissueNew(SimulationCommand("Tissue tissueNew Tissue1"));
  Tissue::Ptr tissue = simulator.tissue("Tissue1");
  TissueReactor::Ptr tissueReactor = simulator.tissueReactor("Tissue1");
  SimulationCommand cmd = SimulationCommand("Tissue Tissue1 cytotoxicCellNew 1 2 3");
  simulator.cytotoxicCellNew(cmd);
  Cell::Ptr cell = tissue->cell(cmd.coords());  
  
  CellMembrane::Ptr mem = cell->membrane(CellMembrane::north());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 100);
  mem = cell->membrane(CellMembrane::south());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 100);
  mem = cell->membrane(CellMembrane::east());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 100);
  mem = cell->membrane(CellMembrane::west());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 100);
  mem = cell->membrane(CellMembrane::up());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 100);
  mem = cell->membrane(CellMembrane::down());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 100);  
}

TEST(InfectionSimulator, helperCellNewCreatesHelperCell) {
  InfectionSimulator simulator;
  simulator.tissueNew(SimulationCommand("Tissue tissueNew Tissue1"));
  Tissue::Ptr tissue = simulator.tissue("Tissue1");
  TissueReactor::Ptr tissueReactor = simulator.tissueReactor("Tissue1");
  ASSERT_TRUE(tissueReactor->numHelperCells() == 0);
  SimulationCommand cmd = SimulationCommand("Tissue Tissue1 helperCellNew 1 2 3");
  simulator.helperCellNew(cmd);
  
  ASSERT_TRUE(tissueReactor->numHelperCells() == 1);
  Cell::Ptr cell = tissue->cell(cmd.coords());  
  ASSERT_TRUE(cell->name() == "(1,2,3)");
  ASSERT_TRUE(cell->location() == cmd.coords());
  ASSERT_TRUE(cell->cellType() == Cell::helperCell());
}

TEST(InfectionSimulator, helperCellNewCreatesCellMembranes) {
  InfectionSimulator simulator;
  simulator.tissueNew(SimulationCommand("Tissue tissueNew Tissue1"));
  Tissue::Ptr tissue = simulator.tissue("Tissue1");
  SimulationCommand cmd = SimulationCommand("Tissue Tissue1 helperCellNew 1 2 3");
  simulator.helperCellNew(cmd);
  Cell::Ptr cell = tissue->cell(cmd.coords());  
  
  CellMembrane::Ptr mem = cell->membrane(CellMembrane::north());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 0);
  mem = cell->membrane(CellMembrane::south());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 0);
  mem = cell->membrane(CellMembrane::east());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 0);
  mem = cell->membrane(CellMembrane::west());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 0);
  mem = cell->membrane(CellMembrane::up());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 0);
  mem = cell->membrane(CellMembrane::down());
  ASSERT_TRUE(mem.ptr() != NULL);
  ASSERT_TRUE(mem->antibodyStrength() == 0);  
}



TEST(InfectionSimulator, infectedCellsDel) {
  InfectionSimulator simulator;
  simulator.tissueNew(SimulationCommand("Tissue tissueNew Tissue1"));
  Tissue::Ptr tissue = simulator.tissue("Tissue1");
  TissueReactor::Ptr tissueReactor = simulator.tissueReactor("Tissue1");
  SimulationCommand cmd_c1 = SimulationCommand("Tissue Tissue1 cytotoxicCellNew 1 2 3");
  simulator.cytotoxicCellNew(cmd_c1);
  SimulationCommand cmd_c2 = SimulationCommand("Tissue Tissue1 cytotoxicCellNew 2 3 4");
  simulator.cytotoxicCellNew(cmd_c2);
  (tissue->cell(cmd_c2.coords()))->healthIs(Cell::infected());
  SimulationCommand cmd_h1 = SimulationCommand("Tissue Tissue1 helperCellNew 3 4 5");
  simulator.helperCellNew(cmd_h1);
  SimulationCommand cmd_h2 = SimulationCommand("Tissue Tissue1 helperCellNew 4 5 6");
  simulator.helperCellNew(cmd_h2);
  (tissue->cell(cmd_h2.coords()))->healthIs(Cell::infected());
  
  ASSERT_TRUE(tissueReactor->numCytotoxicCells() == 2);
  ASSERT_TRUE(tissueReactor->numHelperCells() == 2);
  
  simulator.infectedCellsDel(SimulationCommand("Tissue Tissue1 infectedCellsDel"));
  
  ASSERT_TRUE((tissue->cell(cmd_c2.coords())).ptr() == NULL);
  ASSERT_TRUE((tissue->cell(cmd_h2.coords())).ptr() == NULL);
  ASSERT_TRUE((tissue->cell(cmd_c1.coords())).ptr() != NULL);
  ASSERT_TRUE((tissue->cell(cmd_h1.coords())).ptr() != NULL);
  ASSERT_TRUE(tissueReactor->numCytotoxicCells() == 1);
  ASSERT_TRUE(tissueReactor->numHelperCells() == 1);
}
