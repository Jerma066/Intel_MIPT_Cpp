CXX=g++
SOURCES = geo3d.cpp main.cpp
OPT_SOURCES = geo3d.cpp optimized_version.cpp
TEST14_SRC = geo3d.cpp check_14_test.cpp
TESTFLAGS = -std=c++1z
TEST_SOURCES=geo3d.cpp UnitTests/unit_tests.cpp

all:
	$(CXX) $(CXXFLAGS) -o main $(SOURCES)
	
optimized:
	$(CXX) $(CXXFLAGS) -o optimized $(OPT_SOURCES)
	
test:
	$(CXX) $(TESTFLAGS) -o unit_tests $(TEST_SOURCES)
	./unit_tests
	rm unit_tests
