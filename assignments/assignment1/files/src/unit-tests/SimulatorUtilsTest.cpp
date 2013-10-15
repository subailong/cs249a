#include <string>
#include "gtest/gtest.h"
#include "SimulatorUtils.h"
using namespace std;


TEST(SimulatorUtils, buildsCoordinatesObject) {
  Cell::Coordinates coords1;
  coords1.x = 1;
  coords1.y = 2;
  coords1.z = 3;
  Cell::Coordinates coords2 = SimulatorUtils::toCoordinates(1, 2, 3);
  ASSERT_TRUE(coords1 == coords2);
}

TEST(SimulatorUtils, convertsSideStringToSideType) {
  CellMembrane::Side side;
  side = SimulatorUtils::toSide("north");
  ASSERT_TRUE(side == CellMembrane::north());
  side = SimulatorUtils::toSide("south");
  ASSERT_TRUE(side == CellMembrane::south());
  side = SimulatorUtils::toSide("east");
  ASSERT_TRUE(side == CellMembrane::east());
  side = SimulatorUtils::toSide("west");
  ASSERT_TRUE(side == CellMembrane::west());
  side = SimulatorUtils::toSide("up");
  ASSERT_TRUE(side == CellMembrane::up());
  side = SimulatorUtils::toSide("down");
  ASSERT_TRUE(side == CellMembrane::down());
}

TEST(SimulatorUtils, returnsSidesArray) {
  vector<CellMembrane::Side> sides = SimulatorUtils::sides();
  ASSERT_TRUE(sides.size() == 6);
  ASSERT_TRUE(sides[0] == CellMembrane::north());
  ASSERT_TRUE(sides[1] == CellMembrane::south());
  ASSERT_TRUE(sides[2] == CellMembrane::east());
  ASSERT_TRUE(sides[3] == CellMembrane::west());
  ASSERT_TRUE(sides[4] == CellMembrane::up());
  ASSERT_TRUE(sides[5] == CellMembrane::down());
}
