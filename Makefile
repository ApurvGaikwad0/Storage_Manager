# Define the compiler and compiler flags
CC = gcc
CFLAGS = -Wall -g0

# Default target is 'all', which depends on 'test_assign1'
.PHONY: all
all: test_assign1 test_assign2

# Target 'test_assign1' depends on source files and is built using gcc
test_assign1: test_assign1_1.c storage_mgr.c dberror.c
	$(CC) $(CFLAGS) -o test_assign1 test_assign1_1.c storage_mgr.c dberror.c -lm

# Target 'test_assign2' depends on source files and is built using gcc
test_assign2: test_assign1_2.c storage_mgr.c dberror.c
	$(CC) $(CFLAGS) -o test_assign2 test_assign1_2.c storage_mgr.c dberror.c -lm


# Clean target to remove the compiled executables
.PHONY: clean
clean:
	rm -f test_assign1 test_assign2


