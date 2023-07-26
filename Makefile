# Define the C compiler to use
CC = gcc

# Define any compile-time flags
CFLAGS = -Wall -g

# Define the source file for the build
SOURCE = temperature.c

# Define the output binary
OUTPUT = temp

# The build target executable
TARGET = $(OUTPUT)

# Default rule, to compile the program
$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCE)

# Rule to clean the output and temporary files
clean:
	rm -f $(OUTPUT)

# Rule to install the program to the system
install: $(TARGET)
	cp $(OUTPUT) /usr/local/bin/