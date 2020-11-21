CC=g++

all: sheduler

sheduler: MainSheduler.o ParallelSheduler.o
			g++ MainSheduler.o ParallelSheduler.o -o sheduler  -pthread

MainSheduler.o: MainSheduler.cpp
			g++ -c  MainSheduler.cpp ParallelSheduler.h

ParallelSheduler.o: ParallelSheduler.cpp 
			g++ -c ParallelSheduler.cpp ParallelSheduler.h -pthread

sheduler.o: sheduler.cpp
			g++ -c sheduler.cpp

clean:
	rm -rf *.o sheduler