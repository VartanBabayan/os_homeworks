#include "ParallelSheduler.h"

ParallelSheduler::ParallelSheduler(int numberOfThreads) 
	: value(numberOfThreads)
{
	// default initializing of mutex and cond_var
	fRunner = PTHREAD_MUTEX_INITIALIZER;
	condConsumer = PTHREAD_COND_INITIALIZER; 

	// dynamic array of threads	
	threads = new pthread_t[value];

	std::cout << "Constructor..\n";
		
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
	std::cout << "in run...\n";
	
	pthread_mutex_lock(&fRunner);
	
	threadFunctions.push(std::make_pair(start_routine, arg));

	pthread_mutex_unlock(&fRunner);
	
	pthread_cond_broadcast(&condConsumer); // signal for Consumer
}

// consumer function
void* ParallelSheduler::threadConsumer(void* arg)
{
		std::cout << "in threadConsumer...\n";
		
		ParallelSheduler* sheduler = (ParallelSheduler*)(arg);
		
		while(true)
		{		
			std::cout << "in infinite loop..\n";
			
			pthread_mutex_lock(&sheduler->fRunner); // enter to critical zone
		
			while(sheduler->threadFunctions.empty())
			{
				pthread_cond_wait(&sheduler->condConsumer, &sheduler->fRunner); // waiting functions 
			}
				
			void(*function)(void*) = sheduler->threadFunctions.front().first;
			void* arguments = sheduler->threadFunctions.front().second;

			function(arguments); // run function
			
			sheduler->threadFunctions.pop();

			pthread_mutex_unlock(&sheduler->fRunner); // end critical zone
		}

		std::cout << "end of threadConsumer..\n";
		return NULL;
}

// destroying all pthread objects
ParallelSheduler::~ParallelSheduler()
{
	pthread_cond_destroy(&condConsumer);
	
	for(int i = 0; i < value; ++i)
	{
		pthread_cancel(threads[i]);
	}  
	
	std::cout << "Destructor..\n";
	
	delete[] threads;
}