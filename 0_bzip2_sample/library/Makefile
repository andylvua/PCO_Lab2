CXX = gcc
CXXFLAGS = -O3
PRG_NAME = libbzip2
VPATH = library
vpath %.c library
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = library
OBJ = $(patsubst $(LIB_DIR)/%.c, $(OBJ_DIR)/$(LIB_DIR)/%.o, $(wildcard $(LIB_DIR)/*.c))

all: $(BIN_DIR)/$(PRG_NAME)

$(OBJ_DIR)/$(LIB_DIR):
	mkdir -p $(OBJ_DIR)/$(LIB_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/$(PRG_NAME): $(OBJ_DIR)/$(LIB_DIR) $(BIN_DIR) $(OBJ)
	ar rcs $(BIN_DIR)/$(PRG_NAME).a $(OBJ)
	$(CXX) $(CXXFLAGS) -shared -fPIC $(OBJ) -o $(BIN_DIR)/$(PRG_NAME).so

$(OBJ_DIR)/$(LIB_DIR)/%.o: $(LIB_DIR)/%.c
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)