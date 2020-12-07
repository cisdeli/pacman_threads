CC = g++
CFLAGS = -Wall -g
MEMDEBUGSET = -g -fsanitize=address -fstack-protector-strong -Wall -Wextra -Werror
LDFLAGS = -lncurses -lpthread

all: main.cpp Map.o MapController.o Menu.o Game.o
	$(CC) $(CFLAGS) main.cpp Map.o MapController.o Menu.o Game.o $(LDFLAGS) -o exec
Map.o: sources/Map.cpp
	$(CC) sources/Map.cpp -c
MapController.o: sources/MapController.cpp
	$(CC) sources/MapController.cpp -c
Menu.o: sources/Menu.cpp
	$(CC) sources/Menu.cpp -c
Game.o: sources/Game.cpp
	$(CC) sources/Game.cpp -c

run:
	 ./exec
clean:
	 rm -rf exec *.o
