FILENAME = heap_scheduler

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
LDFLAGS = -Wl,-rpath,./lib -L./lib -l_sched

VLG = valgrind --leak-check=yes --track-origins=yes

DEBUG_PATH = ../../bin/debug

OBJ_DIR = $(DEBUG_PATH)

SRC_FILES = $(FILENAME).c ../../test/$(FILENAME)_test.c
OBJ_FILES = $(SRC_FILES:.c=.o)
TARGET = $(OBJ_DIR)/$(FILENAME).out

LIBRARY = ./lib/lib_sched.so

INCLUDES = -I../../../ds/include/ -I../../include/

.PHONY: all clean run vlg gdb clean_all

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(MAKE) -C ./lib -f makefile
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ_FILES) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run:
	./$(TARGET)
	
vlg:
	$(VLG) ./$(TARGET)

gdb:
	gdb $(TARGET)
	
clean:
	rm -f $(OBJ_FILES) $(TARGET)

clean_all:
	rm -f $(OBJ_FILES) $(TARGET)
	$(MAKE) -C ./lib -f makefile clean
