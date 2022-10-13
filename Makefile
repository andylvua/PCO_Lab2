CXX = g++
CXXFLAGS = -O3
LDFLAGS = -O3
PRG_NAME = example
OBJ_DIR := obj
BIN_DIR := bin
VPATH = ./examples ./library
SOURCES = ./examples/example.cpp ./library/mystring.cpp
OBJECTS = example.o mystring.o
LIBRARIES = libmystring.a

all: $(BIN_DIR)/$(PRG_NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(PRG_NAME): $(OBJ_DIR) $(BIN_DIR) $(OBJECTS) $(LIBRARIES)
	$(CXX) $(OBJ_DIR)/example.o -lmystring -L./$(BIN_DIR) -o $(BIN_DIR)/example
#
#$(OBJECTS): $(SOURCES)%.o: %.cpp
#	$(CXX) $(CXXFLAGS) -c $*.cpp -o $(OBJ_DIR)/$@
example.o: ./examples/example.cpp
	$(CXX) $(CXXFLAGS) -c ./examples/example.cpp -o $(OBJ_DIR)/example.o

mystring.o: ./library/mystring.cpp
	$(CXX) $(CXXFLAGS) -c ./library/mystring.cpp -o $(OBJ_DIR)/mystring.o

$(LIBRARIES): $(OBJECTS)
	ar rcs $(BIN_DIR)/libmystring.a $(OBJ_DIR)/mystring.o

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
