all: sheduler

sheduler: MainSheduler.o ParallelSheduler.o
			g++ -g -pthread MainSheduler.o ParallelSheduler.o -o sheduler 

MainSheduler.o: MainSheduler.cpp 
			g++ -g -c -pthread MainSheduler.cpp ParallelSheduler.h  

ParallelSheduler.o: ParallelSheduler.cpp
			g++ -g -c -pthread ParallelSheduler.cpp ParallelSheduler.h  

clean:
	rm -rf *.o sheduler