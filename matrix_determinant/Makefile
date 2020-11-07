CXX=g++
SOURCES = rational.cpp matrix.cpp main.cpp
TEST_SOURCES = rational.cpp matrix.cpp UnitTests/unit_tests.cpp
TESTFLAGS = -std=c++1z

all:
	$(CXX) $(CXXFLAGS) -o main $(SOURCES)

test:
	$(CXX) $(TESTFLAGS) -o unit_tests $(TEST_SOURCES)
	./unit_tests
