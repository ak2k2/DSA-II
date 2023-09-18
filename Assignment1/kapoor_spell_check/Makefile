# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# Include directory
INCLUDES = -Iinclude

# Source files
SRC = src/main.cpp src/DictionaryLoader.cpp src/hashTable.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable name
EXEC = main

# Default target
all: $(EXEC)

# Linking
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(EXEC)

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean
clean:
	rm -f $(OBJ) $(EXEC)
