#!/bin/bash

# Check if argument is provided
if [ $# -ne 1 ]; then
    echo "Usage: $0 <directory_name>"
    exit 1
fi

# Get directory name from the command line argument
main_folder="$1"

# Create the Makefile
cat > "$main_folder/Makefile" <<EOF
# Makefile for $main_folder

# Compiler and flags
CC = g++
CFLAGS = -std=c++11 -Wall

# Directories
SRC_DIR = src
INC_DIR = include
BIN_DIR = bin
TEST_DIR = test

# Source files
SRCS := \$(wildcard \$(SRC_DIR)/*.cpp)
OBJS := \$(patsubst \$(SRC_DIR)/%.cpp,\$(BIN_DIR)/%.o,\$(SRCS))

# Test source files
TEST_SRCS := \$(wildcard \$(TEST_DIR)/*.cpp)
TEST_BINS := \$(patsubst \$(TEST_DIR)/%.cpp,\$(BIN_DIR)/%_test,\$(TEST_SRCS))

# Include directories
INC := -I\$(INC_DIR)

# Targets
all: \$(BIN_DIR)/rcstring

debug: CFLAGS += -g
debug: \$(BIN_DIR)/rcstring_debug

test: \$(TEST_BINS)
	@for test_bin in \$(TEST_BINS); do \
		echo "Running \$$test_bin..."; \
		\$$test_bin; \
	done

\$(BIN_DIR)/rcstring: \$(OBJS)
	@mkdir -p \$(BIN_DIR)
	\$(CC) \$(CFLAGS) \$(INC) -o \$@ \$^

\$(BIN_DIR)/rcstring_debug: \$(OBJS)
	@mkdir -p \$(BIN_DIR)/debug
	\$(CC) \$(CFLAGS) \$(INC) -o \$@ \$^

\$(BIN_DIR)/%.o: \$(SRC_DIR)/%.cpp
	@mkdir -p \$(BIN_DIR)
	\$(CC) \$(CFLAGS) \$(INC) -c -o \$@ \$<

\$(BIN_DIR)/%_test: \$(TEST_DIR)/%.cpp
	@mkdir -p \$(BIN_DIR)
	\$(CC) \$(CFLAGS) \$(INC) -o \$@ \$< \$(filter-out \$(BIN_DIR)/rcstring.o, \$^)

clean:
	rm -rf \$(BIN_DIR)/*

.PHONY: all debug test clean
EOF

echo "Makefile created successfully in $main_folder."

