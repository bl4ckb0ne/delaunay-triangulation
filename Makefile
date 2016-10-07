CXX = g++

EXE = delaunay
BUILD_DIR = build

SRC = $(wildcard *.cpp) $(wildcard **/*.cpp)
OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

CXXFLAGS = -std=c++11 -Wall -Wextra -Wfatal-errors -pedantic -w -Winline -fno-rtti -ggdb -D_GLIBCXX_DEBUG -lsfml-graphics -lsfml-window -lsfml-system

all: $(EXE)

$(EXE): dir main.o delaunay.o triangle.o edge.o vector2.o
	$(CXX) -o $(EXE) $(OBJ) $(CXXFLAGS)

main.o:main.cpp
	$(CXX) -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS)

delaunay.o: delaunay.cpp	
	$(CXX) -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS)

triangle.o: triangle.cpp
	$(CXX) -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS)

edge.o: edge.h 
	$(CXX) -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS)

vector2.o: vector2.h
	$(CXX) -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS)

dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(EXE) $(BUILD_DIR)
