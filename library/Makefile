CXX = g++
CXXFLAGS =
PRG_NAME = mystring
VPATH = library
vpath %.cpp library
BUILD_DIR = build
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
OBJ = mystring.o

all: $(BIN_DIR)/$(PRG_NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(PRG_NAME): $(OBJ_DIR) $(BIN_DIR) $(OBJ_DIR)/$(OBJ)
	ar rcs $(BIN_DIR)/lib$(PRG_NAME).a $(OBJ_DIR)/$(OBJ)
	$(CXX) $(CXXFLAGS) -shared -fPIC $(OBJ_DIR)/$(OBJ) -o $(BIN_DIR)/$(PRG_NAME).so

$(OBJ_DIR)/$(OBJ): $(PRG_NAME).cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

release: CXXFLAGS += -O3
release: all

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)