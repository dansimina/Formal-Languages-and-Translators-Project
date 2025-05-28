CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lfl

# Source files
LEX_SOURCE = lex_source.l
YACC_SOURCE = yacc_source.y
ENGINE_SOURCE = game_engine.c

# Generated files
LEX_OUTPUT = lex.yy.c
YACC_OUTPUT = y.tab.c
YACC_HEADER = y.tab.h

# Object files
OBJECTS = $(LEX_OUTPUT:.c=.o) $(YACC_OUTPUT:.c=.o) $(ENGINE_SOURCE:.c=.o)

# Executable
TARGET = adventure_game

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(LEX_OUTPUT): $(LEX_SOURCE) $(YACC_HEADER)
	flex $(LEX_SOURCE)

$(YACC_OUTPUT) $(YACC_HEADER): $(YACC_SOURCE)
	yacc -d $(YACC_SOURCE)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(LEX_OUTPUT) $(YACC_OUTPUT) $(YACC_HEADER) $(TARGET)

