CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lpthread

all: main.cpp Ghost.o Map.o Menu.o
	$(CC) $(CFLAGS) main.cpp Ghost.o Map.o Menu.o -o exec $(LDLAGS)
Ghost.o: Ghost.cpp
	$(CC) Ghost.cpp -c
Map.o: Map.cpp
	$(CC) Map.cpp -c
Menu.o: Menu.cpp
	$(CC) Menu.cpp -c

run:
	 ./exec
clean:
	 rm -rf exec *.o
