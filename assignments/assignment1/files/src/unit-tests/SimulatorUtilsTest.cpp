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

TEST(SimulatorUtils, computesAdjecentCoordinates) {
  Cell::Coordinates c;
  c.x = 0;
  c.y = 0;
  c.z = 0;
  
  Cell::Coordinates cx1;
  cx1.x = 1;
  cx1.y = 0;
  cx1.z = 0;

  Cell::Coordinates cx2;  
  cx2.x = -1;
  cx2.y = 0;
  cx2.z = 0;

  Cell::Coordinates cy1;  
  cy1.x = 0;
  cy1.y = 1;
  cy1.z = 0;

  Cell::Coordinates cy2;  
  cy2.x = 0;
  cy2.y = -1;
  cy2.z = 0;

  Cell::Coordinates cz1;  
  cz1.x = 0;
  cz1.y = 0;
  cz1.z = 1;

  Cell::Coordinates cz2;  
  cz2.x = 0;
  cz2.y = 0;
  cz2.z = -1;

  ASSERT_TRUE(SimulatorUtils::adjacentCoordinates(c, CellMembrane::north()) == cy1);
  ASSERT_TRUE(SimulatorUtils::adjacentCoordinates(c, CellMembrane::south()) == cy2);
  ASSERT_TRUE(SimulatorUtils::adjacentCoordinates(c, CellMembrane::east()) == cx1);
  ASSERT_TRUE(SimulatorUtils::adjacentCoordinates(c, CellMembrane::west()) == cx2);
  ASSERT_TRUE(SimulatorUtils::adjacentCoordinates(c, CellMembrane::up()) == cz1);
  ASSERT_TRUE(SimulatorUtils::adjacentCoordinates(c, CellMembrane::down()) == cz2);
}
