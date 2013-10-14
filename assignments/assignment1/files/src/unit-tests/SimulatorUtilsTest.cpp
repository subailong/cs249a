#include <string>
#include "gtest/gtest.h"
#include "SimulatorUtils.h"
using namespace std;


TEST(SimulatorUtils, buildsCoordinatesObject) {
  Cell::Coordinates coords1;
  coords1.x = 1;
  coords1.y = 2;
  coords1.z = 3;
  Cell::Coordinates coords2 = SimulatorUtils::coordinates(1, 2, 3);
  ASSERT_TRUE(coords1 == coords2);
}

TEST(SimulatorUtils, convertsSideStringToSideType) {
  CellMembrane::Side side;
  side = SimulatorUtils::side("north");
  ASSERT_TRUE(side == CellMembrane::north_);
  side = SimulatorUtils::side("south");
  ASSERT_TRUE(side == CellMembrane::south_);
  side = SimulatorUtils::side("east");
  ASSERT_TRUE(side == CellMembrane::east_);
  side = SimulatorUtils::side("west");
  ASSERT_TRUE(side == CellMembrane::west_);
  side = SimulatorUtils::side("up");
  ASSERT_TRUE(side == CellMembrane::up_);
  side = SimulatorUtils::side("down");
  ASSERT_TRUE(side == CellMembrane::down_);
}
