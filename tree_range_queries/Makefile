CXX=g++
TEST_FLAGS= -std=c++1z -O2
SOURCES = tree.cpp main.cpp
USOURCES = tree.cpp UnitTests/unit_tests.cpp

all: 
	$(CXX) $(CXXFLAGS) -o main $(SOURCES)
	
test:
	$(CXX) $(TEST_FLAGS) -o unit_tests $(USOURCES)
	./unit_tests
