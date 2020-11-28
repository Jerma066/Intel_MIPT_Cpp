CXX=g++
SOURCES = geo3d.cpp main.cpp
TESTFLAGS = -std=c++1z
TEST_SOURCES=geo3d.cpp UnitTests/unit_tests.cpp

all:
	$(CXX) $(CXXFLAGS) -o main $(SOURCES)
	
test:
	$(CXX) $(TESTFLAGS) -o unit_tests $(TEST_SOURCES)
	./unit_tests
	rm unit_tests
