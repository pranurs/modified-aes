# Compiler specifications
CXX = g++

# For developer
# CXXFLAGS = -g -Wall -std=c++17

# For release
CXXFLAGS = -std=c++17 -O2 

# Directory containing include files
INCLUDE = include

# Directory containing build files
BUILD = build

# Directory containing source files
SRC = src


demo: demo.o
	$(CXX) $(BUILD)/demo.o $(BUILD)/aes.o $(BUILD)/utils.o -o demo

demo.o: $(SRC)/demo.cpp aes.o utils.o
	$(CXX) -c $(CXXFLAGS) -I $(INCLUDE) $(SRC)/demo.cpp -o $(BUILD)/demo.o

aes.o: $(SRC)/aes.cpp utils.o
	$(CXX) -c $(CXXFLAGS) -I $(INCLUDE) $(SRC)/aes.cpp -o $(BUILD)/aes.o

utils.o: $(SRC)/utils.cpp 
	$(CXX) -c $(CXXFLAGS) -I $(INCLUDE) $(SRC)/utils.cpp -o $(BUILD)/utils.o 

.PHONY: clean

clean:
	$(RM) demo $(BUILD)/*