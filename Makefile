CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
TARGET := CLIWrapper

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

.PHONY: all clean run

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	@./$(BIN_DIR)/$(TARGET)

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
