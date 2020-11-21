#include "ParallelSheduler.h"

void hello(void* arg)
{
	int* argument = (int*)arg; 

	std::cout << "hello: " << *argument << " call\n";
}

int main()
{
	ParallelSheduler* sheduler = new ParallelSheduler(5);
	
	for(int i = 1; i <= 10; ++i)
	{
		sheduler->run(hello, &i);
	}

	sheduler->~ParallelSheduler();
	delete sheduler;
	std::cout << "end of main\n";
}