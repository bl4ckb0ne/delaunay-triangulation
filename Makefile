CXX = g++

EXE = delaunay
EXE_TESTS = tests_delaunay
BUILD_DIR = build

SRC = $(wildcard *.cpp) $(wildcard **/*.cpp)
OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

CXXFLAGS = -std=c++11 -Weffc++ -Wall -Wextra -Wfatal-errors -Wunused -pedantic -w -Winline -fno-rtti -ggdb -D_GLIBCXX_DEBUG -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS_TESTS = -std=c++11 -Weffc++ -Wall -Wextra -Wfatal-errors -Wunused -pedantic -w -Winline

all: $(EXE)
test: dir $(EXE_TESTS)

$(EXE): dir main.o
	$(CXX) -o $@ $(BUILD_DIR)/main.o $(CXXFLAGS)

$(EXE_TESTS):tests.o gtests.o
	$(CXX) -o $@ $(BUILD_DIR)/tests.o $(BUILD_DIR)/gtests.o $(CXXFLAGS_TESTS)

main.o:main.cpp
	$(CXX) -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS)

tests.o:tests/tests.cpp
	$(CXX) -isystem googletest/googletest/include -I. -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS_TESTS)

gtests.o:googletest/googletest/src/gtest-all.cc
	$(CXX) -isystem googletest/googletest/include -isystem googletest/googletest -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS_TESTS)

dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(EXE) $(EXE_TESTS) $(BUILD_DIR)
