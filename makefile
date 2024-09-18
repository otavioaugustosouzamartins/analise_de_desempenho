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
	rm -f out/en/*.txt
	rm -f out/erro_little/*.txt
	rm -f out/ew/*.txt
	rm -f out/ocupacao/*.txt
	rm -f out/lambda/*.txt
	rm -f out/*.txt

# Phony targets
.PHONY: all clean


