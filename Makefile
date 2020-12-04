CC = g++
CFLAGS = -Wall -g -lpthread
MEMDEBUGSET = -g -fsanitize=address -fstack-protector-strong -Wall -Wextra -Werror

all: main.cpp Ghost.o Map.o Menu.o
	$(CC) $(CFLAGS) main.cpp Ghost.o Map.o Menu.o -lncurses -o exec
Ghost.o: Ghost.cpp
	$(CC) Ghost.cpp -c
Map.o: Map.cpp
	$(CC) Map.cpp -lncurses -c
Menu.o: Menu.cpp
	$(CC) Menu.cpp -lncurses -c

run:
	 ./exec
clean:
	 rm -rf exec *.o
