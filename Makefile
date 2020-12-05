CC = g++
CFLAGS = -Wall -g
MEMDEBUGSET = -g -fsanitize=address -fstack-protector-strong -Wall -Wextra -Werror
LDFLAGS = -lncurses -lpthread

all: main.cpp Ghost.o Map.o Menu.o Game.o
	$(CC) $(CFLAGS) main.cpp Ghost.o Map.o Menu.o Game.o $(LDFLAGS) -o exec
Ghost.o: sources/Ghost.cpp
	$(CC) sources/Ghost.cpp -c
Map.o: sources/Map.cpp
	$(CC) sources/Map.cpp -c
Menu.o: sources/Menu.cpp
	$(CC) sources/Menu.cpp -c
Game.o: sources/Game.cpp
	$(CC) sources/Game.cpp -c

run:
	 ./exec
clean:
	 rm -rf exec *.o
