CC := g++
FLAGS := -std=c++11 -Wall -g
INC := -I./include/

SRC_DIR := src
BUILD_DIR := build
INC_DIR := include
BIN_DIR := bin

P1 := $(BIN_DIR)/P1

all: $(P1)


$(P1) : $(BUILD_DIR)/main1.o $(BUILD_DIR)/Plane.o $(BUILD_DIR)/Runway.o $(BUILD_DIR)/Random.o
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