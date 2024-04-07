# Makefile

CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -g
SRC_DIR := src
INCLUDE_DIR := include
OBJ_DIR := obj
BIN_DIR := bin
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(wildcard $(INCLUDE_DIR)/*.hpp)

all: $(BIN_DIR)/app

$(BIN_DIR)/app: $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

.PHONY: clean run

clean:
	rm -f $(OBJS) $(BIN_DIR)/app

run: $(BIN_DIR)/app
	./$<
