CXX = clang++
#CXX = g++

EXE = delaunay
BUILD_DIR = build

SRC = $(wildcard *.cpp) $(wildcard **/*.cpp)
SRC := $(filter-out test.cpp, $(SRC))
OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

CXXFLAGS = -std=c++11 -Wall -Wextra -Wfatal-errors -pedantic -w -Winline -fno-rtti -ggdb -D_GLIBCXX_DEBUG -lsfml-graphics -lsfml-window -lsfml-system

all: $(EXE)

$(EXE): dir main.o delaunay.o triangle.o edge.o vector2.o vector3.o
	$(CXX) $(CXXFLAGS) -o $(EXE) $(OBJ)

main.o:main.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ -c $<

delaunay.o: delaunay.cpp	
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ -c $<

triangle.o: triangle.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ -c $<

edge.o: edge.h 
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ -c $<

vector2.o: vector2.h
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ -c $<

vector3.o:  vector3.h
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$@ -c $<

dir:
	mkdir -p $(BUILD_DIR)

test:
	$(CXX) -std=c++1z test.cpp triangle.cpp delaunay.cpp -o test
	./test
	rm test

clean:
	rm -rf $(EXE) $(BUILD_DIR) test
