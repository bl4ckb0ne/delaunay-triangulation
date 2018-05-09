CXX = g++

EXE = delaunay
EXE_TESTS = tests_delaunay
BUILD_DIR = build

SRC = $(wildcard *.cpp) $(wildcard **/*.cpp)
OBJ = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

CXXFLAGS = -std=c++11 -Weffc++ -Wall -Wextra -Wfatal-errors -Wunused -pedantic -w -Winline -fno-rtti -ggdb -D_GLIBCXX_DEBUG -lsfml-graphics -lsfml-window -lsfml-system

CXXFLAGS_TESTS = -std=c++11 -Weffc++ -Wall -Wextra -Wfatal-errors -Wunused -pedantic -w -Winline
LDFLAGS_TESTS =

all: $(EXE)
test: dir $(EXE_TESTS)

$(EXE): dir main.o
	$(CXX) -o $@ $(BUILD_DIR)/main.o $(CXXFLAGS)

$(EXE_TESTS):tests.o
	$(CXX) -o $@ $(BUILD_DIR)/tests.o $(CXXFLAGS_TESTS) $(LDFLAGS_TESTS)

main.o:main.cpp
	$(CXX) -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS)

tests.o:tests/tests.cpp
	$(CXX) -isystem tests -I. -o $(BUILD_DIR)/$@ -c $< $(CXXFLAGS_TESTS)

dir:
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(EXE) $(EXE_TESTS) $(BUILD_DIR)
