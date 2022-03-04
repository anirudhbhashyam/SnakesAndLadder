CC = gcc
CFLAGS = -Wall
OBJECTS = snakes_and_ladders.o main.o

all: snl main app

snl: snakes_and_ladders.c snakes_and_ladders.h
	$(CC) $(CFLAGS) -c snakes_and_ladders.c

main: main.c snakes_and_ladders.h
	$(CC) $(CFLAGS) -c main.c

app:
	$(CC) $(OBJECTS) -o app

clean:
	rm -rf $(OBJECTS) app 


