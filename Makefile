CC = gcc
OBJECTS = snakes_and_ladders.o main.o

all: snl main app

snl: snakes_and_ladders.c snakes_and_ladders.h
	$(CC) -c snakes_and_ladders.c

main: main.c snakes_and_ladders.h
	$(CC) -c main.c

app:
	$(CC) $(OBJECTS) -o app

clean:
	rm -rf snl main app 


