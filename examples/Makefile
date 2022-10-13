CXX = g++
CXXFLAGS = -O3
PRG_NAME = example
VPATH = examples bin
vpath %.cpp examples
OBJ_DIR := ./obj
BIN_DIR := ./bin
OBJ = example.o
LIB = mystring.so

all: $(BIN_DIR)/$(PRG_NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(PRG_NAME): $(OBJ_DIR) $(BIN_DIR) $(OBJ_DIR)/$(OBJ) $(BIN_DIR)/$(LIB)
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)/$(OBJ) $(BIN_DIR)/mystring.so -o $(BIN_DIR)/$(PRG_NAME)

$(OBJ_DIR)/$(OBJ): $(PRG_NAME).cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

$(BIN_DIR)/$(LIB):
	make -f ./library/Makefile all

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/$(OBJ) $(BIN_DIR)/$(PRG_NAME)