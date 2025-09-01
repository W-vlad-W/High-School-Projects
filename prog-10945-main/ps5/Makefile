# Compiler settings
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
LDFLAGS = 

# Project name
TARGET = adventure_game

# Source files (you'll need to add your .c files here)
SRCS = main.c backpack.c item.c container.c room.c command.c parser.c game.c world.c

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADERS = backpack.h item.h container.h room.h command.h parser.h game.h world.h

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Compile .c files to .o files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: all clean run