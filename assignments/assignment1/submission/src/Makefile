CPPFLAGS = -I.
CXXFLAGS = -Wall -g

OBJECTS = Tissue.o InfectionSimulator.o SimulatorUtils.o SimulationCommand.o TissueReactor.o main.o
LIBS = fwk/BaseCollection.o fwk/BaseNotifiee.o fwk/Exception.o

asgn1:	$(OBJECTS) $(LIBS)
	$(CXX) $(CXXFLAGS) -o asgn1 $(OBJECTS) $(LIBS)

clean:
	rm -f asgn1 $(OBJECTS) $(LIBS) *~

Tissue.o: Tissue.cpp Tissue.h 
InfectionSimulator.o: InfectionSimulator.cpp InfectionSimulator.h
SimulatorUtils.o: SimulatorUtils.cpp SimulatorUtils.h
SimulationCommand.o: SimulationCommand.cpp SimulationCommand.h
TissueReactor.o: TissueReactor.cpp TissueReactor.h
main.o: main.cpp
