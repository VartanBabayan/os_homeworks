#include "ParallelSheduler.h"

ParallelSheduler::ParallelSheduler(int numberOfThreads) 
	: value(numberOfThreads)
{
	// default initializing of mutex and cond_var
	fRunner = new pthread_mutex_t( PTHREAD_MUTEX_INITIALIZER);
	condConsumer = new pthread_cond_t(PTHREAD_COND_INITIALIZER); 
	
	// dynamic array of threads	
	threads = new pthread_t[value];

	// creating child threads		
	for(int i = 0; i < value; ++i)
	{
		int result = pthread_create(&threads[i], NULL, threadConsumer, this);

		if(result != 0)
		{
			std::cout << "Error creating a thread\n";
			exit(result);
		}
	}

}

// producer function
void ParallelSheduler::run(void(*start_routine)(void*), void* arg)
{	
	pthread_mutex_lock(fRunner); // enter critical zone
	
	threadFunctions.push(std::make_pair(start_routine, arg));

	pthread_mutex_unlock(fRunner); // quit critical zone 
	
	pthread_cond_broadcast(condConsumer); // signal for Consumer
}

// consumer function
void* ParallelSheduler::threadConsumer(void* arg)
{		
		ParallelSheduler* sheduler = (ParallelSheduler*)(arg);

		while(true)
		{					
			pthread_mutex_lock(sheduler->fRunner); // enter to critical zone

			while(sheduler->threadFunctions.empty())
			{			
				pthread_cond_wait(sheduler->condConsumer, sheduler->fRunner); // waiting functions 
			}
				
			void(*function)(void*) = sheduler->threadFunctions.front().first;
			void* arguments = sheduler->threadFunctions.front().second;
			
			sheduler->threadFunctions.pop(); // delete function from queue
			
			pthread_mutex_unlock(sheduler->fRunner); // quit critical zone

			function(arguments); // run function

		}
		
		return NULL;
}

void ParallelSheduler::terminateThreads()
{
	for(int i = 0; i < value; ++i)
	{
		void* retVal;

		pthread_join(threads[i], &retVal);
	}
}

// destroying all pthread objects
ParallelSheduler::~ParallelSheduler()
{	
	for(int i = 0; i < value; ++i)
	{
		pthread_cancel(threads[i]);
	}
	
	delete fRunner;
	delete condConsumer;	
	delete[] threads;
}