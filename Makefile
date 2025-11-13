# Compiler
CC = gcc

# Compiler flags
# -Wall: Enable all warnings
# -g:    Include debugging information
# -Isrc: Tell gcc to look for header files in the 'src' directory
CFLAGS = -Wall -g -Isrc

# Linker flags
# -lncurses: Link against the ncurses library
LDFLAGS = -lncurses

# Source files directory
SRC_DIR = src

# --- Main Application Build ---

# Target executable name
TARGET = planner

# Find all .c files in the source directory, excluding test files
SRCS = $(wildcard $(SRC_DIR)/*.c)
SRCS := $(filter-out $(wildcard $(SRC_DIR)/test_*.c), $(SRCS))

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)


# --- Test Build ---

# Find all test source files
TEST_SRCS := $(wildcard $(SRC_DIR)/test_*.c)

# Create test target names from source files (e.g., src/test_foo.c -> test_foo)
TEST_TARGETS := $(patsubst $(SRC_DIR)/test_%.c,test_%,$(TEST_SRCS))

# Application object files needed for tests (all OBJS except main.o)
APP_OBJS := $(filter-out $(SRC_DIR)/main.o, $(OBJS))


# --- Rules ---

# The default goal: build the main executable
all: $(TARGET)

# Rule to build all test executables
test: $(TEST_TARGETS)

# Rule to link the main application executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Generic rule to build any test executable
# Links the specific test source with all relevant application objects
$(TEST_TARGETS): % : $(SRC_DIR)/%.c $(APP_OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Pattern rule to compile any .c source file into a .o object file
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up the project directory
clean:
	rm -f $(TARGET) $(TEST_TARGETS) $(SRC_DIR)/*.o

# Phony targets are not real files
.PHONY: all test clean