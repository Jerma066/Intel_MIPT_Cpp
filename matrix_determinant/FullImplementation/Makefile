CXX=g++
SOURCES = rational.cpp matrix.hpp main.cpp
TEST_SOURCES = matrix.hpp UnitTests/unit_tests.cpp
TESTFLAGS = -std=c++1z

all:
	$(CXX) $(CXXFLAGS) -o main $(SOURCES)

test:
	$(CXX) $(TESTFLAGS) -o unit_tests $(TEST_SOURCES)
	./unit_tests
