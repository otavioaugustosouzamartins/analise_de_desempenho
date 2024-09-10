# Define the compiler
CC = gcc

# Define the linker flags
LDFLAGS = -lm

# Define the source file
SRC = simulacao.c

# Define the name of the final executable
TARGET = simulacao

# Default rule
all: $(TARGET)

# Rule to create the executable
$(TARGET): $(SRC)
	$(CC) $(SRC) $(LDFLAGS) -o $(TARGET)

# Rule to clean up the build
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean


