# COMPILER
CX = g++

# -Wall: show ALL common warnings
#  -g  : debug information
CFLAGS = -Wall -g

# SILENCE MAKE RECURSIVE CALL
SILENCE = --no-print-directory

# SOURCE C FILE
SOURCE = 011-playing-with-network-structs.c

# TARGET C FILE
TARGET = run-me

# PRE-REQ
$(TARGET): $(SOURCE)
	@$(CX) $(CFLAGS) $(SOURCE) -o $(TARGET)

# MAKE ALL
run: $(TARGET)
	./$(TARGET)
	@$(MAKE) $(SILENCE) clean

# MAKE CLEAN
clean:
	@rm -f $(TARGET)
