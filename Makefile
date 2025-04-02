# Raylib paths
RAYLIB_DIR := ./src/vendor/raylib
RAYLIB_INCLUDE := $(RAYLIB_DIR)/include
RAYLIB_LIB := $(RAYLIB_DIR)/lib/libraylib.a  # Explicit static library path

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I$(RAYLIB_INCLUDE) -ggdb
LDFLAGS = 
LDLIBS = $(RAYLIB_LIB) -lm -ldl -lpthread -lX11 -lGL -lopenal

# Directories
BUILD_DIR = ./build
SRC_DIR = ./src
RESOURCE_DIR = $(SRC_DIR)/resources
BUILD_RESOURCE_DIR = $(BUILD_DIR)/resources

# Source files
SRCS = layout.c json_helper.c vendor/helper.c vendor/cJSON.c
OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

# Resource files
RESOURCE_FILES = $(wildcard $(RESOURCE_DIR)/*)

# Executable name
TARGET = $(BUILD_DIR)/layout

# Default target
all: $(TARGET) resources

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

# Compile source files to object files - handles vendor subdirectory
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Create the target directory structure
	$(CC) $(CFLAGS) -c -o $@ $<

# Specific header dependencies
$(BUILD_DIR)/layout.o: $(SRC_DIR)/json_helper.h
# $(BUILD_DIR)/vendor/helper.o: $(SRC_DIR)/vendor/pl_print.h

# Copy all resources to build directory
$(BUILD_RESOURCE_DIR)/%: $(RESOURCE_DIR)/%
	@mkdir -p $(@D)
	cp $< $@

resources: $(addprefix $(BUILD_RESOURCE_DIR)/,$(notdir $(RESOURCE_FILES)))

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean resources
