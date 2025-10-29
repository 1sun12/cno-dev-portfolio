# COMPILER
CX = g++

# FLAGS
FLAGS = -Wall -g

# SOURCE
SOURCE = webserver.c 

# TARGET
TARGET = webserver

# SIlENCE
SILENCE = --no-print-directory

# MAKE COMMANDS
$(TARGET) : $(SOURCE)
	@$(CX) $(FLAGS) $(SOURCE) -o $(TARGET)

run : $(TARGET)
	./$(TARGET)
	@$(MAKE) $(SILENCE) clean

clean:
	@rm -f $(TARGET)
