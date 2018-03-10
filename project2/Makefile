CC := g++
FLAGS := -std=c++11 -Wall -g
INC := -I./include/

SRC_DIR := src
BUILD_DIR := build
INC_DIR := include
BIN_DIR := bin

P1 := $(BIN_DIR)/P1
P2 := $(BIN_DIR)/P2
P3 := $(BIN_DIR)/P3

all: $(P1) $(P2) $(P3)


$(P1) : $(BUILD_DIR)/P1.o $(BUILD_DIR)/Plane.o $(BUILD_DIR)/Runway.o $(BUILD_DIR)/Random.o
	@mkdir -p data
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $^ -o $@

$(P2) : $(BUILD_DIR)/P2.o $(BUILD_DIR)/Plane.o $(BUILD_DIR)/Runway.o $(BUILD_DIR)/Random.o
	@mkdir -p data
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $^ -o $@

$(P3) : $(BUILD_DIR)/P3.o $(BUILD_DIR)/Plane.o $(BUILD_DIR)/Runway.o $(BUILD_DIR)/Random.o
	@mkdir -p data
	@mkdir -p $(BIN_DIR)
	$(CC) $(FLAGS) $^ -o $@

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FLAGS) $(INC) -c $< -o $@ 

clean: 
	@echo "Cleaning all build files..."
	@rm -rf $(BUILD_DIR) $(BIN_DIR)

clearData:
	@echo "Cleaning the data..."
	@rm -f data/summary.txt 