#include "ParallelSheduler.h"

int counter = 1;

void hello(void* arg)
{
	std::cout << "hello " << counter << " call\n";
	++counter;
}

int main()
{
	ParallelSheduler* sheduler = new ParallelSheduler(10);
	
	for(int i = 1; i <= 20; ++i)
	{
		sheduler->run(hello, NULL);
	}	
	
	sheduler->terminateThreads(); // infinity loop
	
	delete sheduler;
	std::cout << "end of main\n";		
	return 0;
}