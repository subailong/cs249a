#include <string>
#include "gtest/gtest.h"
#include "InfectionSimulator.h"
using namespace std;


TEST(InfectionSimulator, newTissueCreatesTissueAndTissueReactor) {
  InfectionSimulator simulator;
  SimulationCommand cmd = SimulationCommand("Tissue tissueNew Tissue1");
  simulator.tissueNew(cmd);
  ASSERT_TRUE(simulator.tissue("Tissue1").ptr() != NULL);
  ASSERT_TRUE(simulator.tissueReactor("Tissue1").ptr() != NULL);
}