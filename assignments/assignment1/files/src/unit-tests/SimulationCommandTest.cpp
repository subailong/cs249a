#include <string>
#include "gtest/gtest.h"
#include "SimulationCommand.h"
using namespace std;


TEST(SimulationCommand, buildsTissueNewCommand) {
  string inputLine = "Tissue tissueNew Tissue1";
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::tissueNew_);
  ASSERT_TRUE(cmd.tissueName == "Tissue1");
}

TEST(SimulationCommand, buildsCytotoxicCellNewCommand) {
  string inputLine = "Tissue Tissue1 cytotoxicCellNew 1 2 3";
  Cell::Coordinates coords;
  coords.x = 1;
  coords.y = 2;
  coords.z = 3;
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::cytotoxicCellNew_);
  ASSERT_TRUE(cmd.tissueName == "Tissue1");
  ASSERT_TRUE(cmd.coords == coords);
}

TEST(SimulationCommand, buildsHelperCellNewCommand) {
  string inputLine = "Tissue Tissue1 helperCellNew 1 2 3";
  Cell::Coordinates coords;
  coords.x = 1;
  coords.y = 2;
  coords.z = 3;
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::helperCellNew_);
  ASSERT_TRUE(cmd.tissueName == "Tissue1");
  ASSERT_TRUE(cmd.coords == coords);
}

TEST(SimulationCommand, buildsInfectionStartLocationIsCommand) {
  string inputLine = "Tissue Tissue1 infectionStartLocationIs 1 2 3 east 99";
  Cell::Coordinates coords;
  coords.x = 1;
  coords.y = 2;
  coords.z = 3;
  AntibodyStrength strength(99);
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::infectionStartLocationIs_);
  ASSERT_TRUE(cmd.tissueName == "Tissue1");
  ASSERT_TRUE(cmd.coords == coords);
  ASSERT_TRUE(cmd.direction == CellMembrane::east_);
  ASSERT_TRUE(cmd.strength == strength);
}

TEST(SimulationCommand, buildsInfectedCellsDelCommand) {
  string inputLine = "Tissue Tissue1 infectedCellsDel";
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::infectedCellsDel_);
  ASSERT_TRUE(cmd.tissueName == "Tissue1");
}

TEST(SimulationCommand, buildsCloneNewCommand) {
  string inputLine = "Cell Tissue1 1 2 3 cloneNew north";
  Cell::Coordinates coords;
  coords.x = 1;
  coords.y = 2;
  coords.z = 3;
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::cloneNew_);
  ASSERT_TRUE(cmd.tissueName == "Tissue1");
  ASSERT_TRUE(cmd.coords == coords);
  ASSERT_TRUE(cmd.direction == CellMembrane::north_);
}

TEST(SimulationCommand, buildsCloneCellsNewCommand) {
  string inputLine = "Tissue Tissue1 cloneCellsNew west";
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::cloneCellsNew_);
  ASSERT_TRUE(cmd.tissueName == "Tissue1");
  ASSERT_TRUE(cmd.direction == CellMembrane::west_);
}

TEST(SimulationCommand, buildsAntibodyStrengthIsCommand) {
  string inputLine = "Cell Tissue1 1 2 3 membrane east antibodyStrengthIs 50";
  Cell::Coordinates coords;
  coords.x = 1;
  coords.y = 2;
  coords.z = 3;
  AntibodyStrength strength(50);
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::antibodyStrengthIs_);
  ASSERT_TRUE(cmd.tissueName == "Tissue1");
  ASSERT_TRUE(cmd.coords == coords);
  ASSERT_TRUE(cmd.direction == CellMembrane::east_);
  ASSERT_TRUE(cmd.strength == strength);
}

TEST(SimulationCommand, buildsNoOpCommandForComment) {
  string inputLine = "# This is a comment";
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::noOp_);
}

TEST(SimulationCommand, buildsNoOpCommandForEmptyLine) {
  string inputLine = "";
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::noOp_);
}

TEST(SimulationCommand, buildsNoOpCommandForWronglyFormattedLine) {
  string inputLine = "Tissue Tissue1 1 2 3 cytotoxicCellNew";
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::noOp_);
}
 
TEST(SimulationCommand, buildsNoOpCommandForUnknownCommand) {
  string inputLine = "Tissue Tissue1 unkownCommand x y z";
  SimulationCommand cmd(inputLine);
  ASSERT_TRUE(cmd.type == SimulationCommand::noOp_);
}

