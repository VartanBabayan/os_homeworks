#include <iostream>
#include <queue>
#include <utility>
#include <pthread.h>
#include <semaphore.h>

class ParallelSheduler {
private:	
	int value;

	std::queue< std::pair<void(*)(void*), void*> >threadFunctions;

	pthread_t* threads;
	
	pthread_mutex_t fRunner;
	
	pthread_cond_t condConsumer;
			
public:
	ParallelSheduler(int val);
			
	void run(void(*start_routine)(void*), void* arg);	

	static void* threadConsumer(void* arg);
			
	~ParallelSheduler();
};