# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -Isrc
LEX = flex
YACC = bison
YACCFLAGS = -d -v

# Directories
SRC_DIR = src
BUILD_DIR = build
OUTPUT_DIR = outputs

# Target executable
TARGET = compiler

# Object files
OBJS = $(BUILD_DIR)/lexer.o $(BUILD_DIR)/parser.tab.o $(BUILD_DIR)/ast.o \
       $(BUILD_DIR)/symbol.o $(BUILD_DIR)/semantic.o $(BUILD_DIR)/tac.o \
       $(BUILD_DIR)/codegen.o

# Default target
all: $(TARGET)

# Link the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Generate parser from yacc file
$(BUILD_DIR)/parser.tab.cpp $(BUILD_DIR)/parser.tab.h: $(SRC_DIR)/parser.y
	mkdir -p $(BUILD_DIR)
	$(YACC) $(YACCFLAGS) -d -o $(BUILD_DIR)/parser.tab.cpp $<

# Generate lexer from lex file
$(BUILD_DIR)/lexer.cpp: $(SRC_DIR)/lexer.l $(BUILD_DIR)/parser.tab.h
	$(LEX) -o $(BUILD_DIR)/lexer.cpp $<

# Compile object files
$(BUILD_DIR)/lexer.o: $(BUILD_DIR)/lexer.cpp $(BUILD_DIR)/parser.tab.h $(SRC_DIR)/ast.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/parser.tab.o: $(BUILD_DIR)/parser.tab.cpp $(SRC_DIR)/ast.h $(SRC_DIR)/symbol.h \
                          $(SRC_DIR)/semantic.h $(SRC_DIR)/tac.h $(SRC_DIR)/codegen.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/ast.o: $(SRC_DIR)/ast.cpp $(SRC_DIR)/ast.h $(SRC_DIR)/symbol.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/symbol.o: $(SRC_DIR)/symbol.cpp $(SRC_DIR)/symbol.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/semantic.o: $(SRC_DIR)/semantic.cpp $(SRC_DIR)/semantic.h $(SRC_DIR)/ast.h $(SRC_DIR)/symbol.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/tac.o: $(SRC_DIR)/tac.cpp $(SRC_DIR)/tac.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/codegen.o: $(SRC_DIR)/codegen.cpp $(SRC_DIR)/codegen.h $(SRC_DIR)/tac.h $(SRC_DIR)/ast.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf $(BUILD_DIR) $(TARGET) ast.dot output.tac

# Test target
test: $(TARGET)
	./$(TARGET) test.c

.PHONY: all clean test
