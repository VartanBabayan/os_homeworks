#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/wait.h>
#include <cerrno>

int main()
{
	srand(time(NULL)); 
	
	std::cout << "Enter number of elements you want to sum:  ";
	int N;
	std::cin >> N;

	std::vector<int> array(N);
	int waitingSum = 0;
	for(int i = 0; i < N; ++i)
	{
		array[i] = rand() % 10 + 1;
		std::cout << array[i] << " ";
		waitingSum += array[i];
	}

	std::cout << "\nEnter number of workers who calculate the total sum:  ";
	int M;
	std::cin >> M;
	
	// set indexes to read in range [i j] each iteration
	int i = 0; 
	int j = N / M; 
	
	if(N % M != 0)
	{
		j = N%M + N/M;
	}
	
	int currentStartAndEnd[2]{i, j};
		
	int tempSum = 0;
	int result = 0;

	for(int t = 0; t < M; ++t)
	{
		int _1pipefd[2];
		int _2pipefd[2];
		
		int pipeResult1 = pipe(_1pipefd);
		int pipeResult2 = pipe(_2pipefd);
		
		if(pipeResult1 != 0 && pipeResult2 != 0) // chech if error while creating pipes
			exit(errno);
		
		// creating child
		int child = fork();
		
		if(child == -1)
			exit(errno);
		
		if(child == 0)
		{
			int StartAndEnd[2]; // range[Start End]
			
			close(_1pipefd[0]); 
			close(_2pipefd[1]); 
			
			int readBytes = read(_2pipefd[0], &StartAndEnd, sizeof(int) * 2); // read from Parent to define the range [Start End]
			if(readBytes == -1)
				exit(errno);
			
			int tempSum = 0;
			
			for(int k = StartAndEnd[0]; k < StartAndEnd[1]; ++k) // sum all in range [Start End]
				tempSum += array[k];
			
			std::cout << "sum in range [" << StartAndEnd[0] << " " <<  StartAndEnd[1] << "] : " << tempSum << "\n";
			
			int writeBytes = write(_1pipefd[1], &tempSum, sizeof(int)); // share to Parent our tempSum
			if(writeBytes == -1)
				exit(errno);
			
			kill(getpid(), SIGKILL); // child did what we wanted that's why we kill him :D
		}
		else
		{
			close(_1pipefd[1]); 
			close(_2pipefd[0]); 
				
			int writeBytes = write(_2pipefd[1], &currentStartAndEnd, sizeof(int) * 2); // share to Child our range
			if(writeBytes == -1)
				exit(errno);
			
			int currentSum = 0;
			int readBytes = read(_1pipefd[0], &currentSum, sizeof(int)); // read from Parent our tempSum
			if(readBytes == -1)
				exit(errno);
			
			result += currentSum; // sum every tempSum
			
			// changing the range
			currentStartAndEnd[0] = currentStartAndEnd[1];
			currentStartAndEnd[1] += N / M;
			
			wait(NULL);
		}
	}
	
	std::cout  << "ResultSum : " << result << "\n";
	
	std::cout << "WaitedSum : " << waitingSum << "\n";
}