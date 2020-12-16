all: result

result: pipe.o
		g++ pipe.o -o result

pipe.o: pipe.cpp
		g++ -c pipe.cpp

clean:
	rm -rf *.o result