CXX=g++
TEST_FLAGS= -std=c++1z

all: 
	$(CXX) $(CXXFLAGS) -o main main_ete.cpp
	
test:
	$(CXX) $(TEST_FLAGS) -o test main_mt.cpp
	./test
