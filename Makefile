CXX = g++

EXE = delaunay
BUILD_DIR = build

SRC = $(wildcard *.cpp) $(wildcard **/*.cpp)
OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

CXXFLAGS = -std=c++11 -Weffc++ -Wall -Wextra -Wfatal-errors -Wunused -pedantic -w -Winline -fno-rtti -ggdb -D_GLIBCXX_DEBUG -lsfml-graphics -lsfml-window -lsfml-system

all: $(EXE)

$(EXE): dir main.o
	$(CXX) -o $(EXE) $(OBJ) $(CXXFLAGS)

main.o:main.cpp
	$(CXX) -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS)

dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(EXE) $(BUILD_DIR)
