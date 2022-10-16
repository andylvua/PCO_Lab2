CXX = gcc
CXXFLAGS =
PRG_NAME = bzip2 bzip2recover
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
EX_DIR = examples
LIB = libbzip2.so
OBJ = $(patsubst %, $(OBJ_DIR)/$(EX_DIR)/%.o, $(PRG_NAME))
TARGETS = $(patsubst %, $(BIN_DIR)/%, $(PRG_NAME))

all: $(TARGETS)

$(OBJ_DIR)/$(EX_DIR):
	mkdir -p $(OBJ_DIR)/$(EX_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(OBJ_DIR)/$(EX_DIR) $(BIN_DIR) $(OBJ_DIR)/$(EX_DIR)/%.o $(BIN_DIR)/$(LIB)
	$(CXX) $(CXXFLAGS) $(OBJ_DIR)/$(EX_DIR)/$(@F).o $(BIN_DIR)/$(LIB) -o $@

$(OBJ_DIR)/$(EX_DIR)/%.o: $(EX_DIR)/%.c
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

.PRECIOUS: $(OBJ_DIR)/$(EX_DIR)/%.o

$(BIN_DIR)/$(LIB):
	make -f ./library/Makefile all

release: CXXFLAGS += -O3
release: all

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)/$(EX_DIR) $(TARGETS)