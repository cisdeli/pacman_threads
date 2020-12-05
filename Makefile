CC = g++
CFLAGS = -Wall -g
MEMDEBUGSET = -g -fsanitize=address -fstack-protector-strong -Wall -Wextra -Werror
LDFLAGS = -lncurses -lpthread

all: main.cpp Ghost.o Map.o Menu.o Game.o
	$(CC) $(CFLAGS) main.cpp Ghost.o Map.o Menu.o Game.o $(LDFLAGS) -o exec
Ghost.o: Ghost.cpp
	$(CC) Ghost.cpp -c
Map.o: Map.cpp
	$(CC) Map.cpp -c
Menu.o: Menu.cpp
	$(CC) Menu.cpp -c
Game.o: Game.cpp
	$(CC) Game.cpp -c

run:
	 ./exec
clean:
	 rm -rf exec *.o
