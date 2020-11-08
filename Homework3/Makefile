CC=g++

all: MiniShell

MiniShell: shell.o
			g++ shell.o -o MiniShell

shell.o: shell.cpp
			g++ -c shell.cpp

clean:
	rm -rf *.o MiniShell