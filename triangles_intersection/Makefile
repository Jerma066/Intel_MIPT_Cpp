CXX=g++
TESTFLAGS = -std=c++1z
SOURCES=geo3d.cpp UnitTests/unit_tests.cpp

all:
	$(CXX) $(CXXFLAGS) -o main $(SOURCES)
	
test:
	$(CXX) $(TESTFLAGS) -o unit_tests $(SOURCES)
	./unit_tests
