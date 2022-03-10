CC = gcc
SRC = src
OBJ = obj
INC = include
CFLAGS = -Wall -I$(INC)
SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE = app

all: create_obj $(OBJECTS) $(EXECUTABLE)

create_obj: 
	mkdir -p $(OBJ)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ -o $@

clean:
	rm -rf $(OBJ) $(EXECUTABLE)


