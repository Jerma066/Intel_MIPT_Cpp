CXX=g++

SOURCES = matrix.hpp main.cpp
TEST_SOURCES = matrix.hpp UnitTests/unit_tests.cpp
TESTFLAGS = -std=c++1z

all:
	$(CXX) $(CXXFLAGS) -std=c++1z -o main $(SOURCES)

test:
	$(CXX) $(TESTFLAGS) -o unit_tests $(TEST_SOURCES)
	./unit_tests
	rm unit_tests
