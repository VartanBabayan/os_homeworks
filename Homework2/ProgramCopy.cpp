#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>


int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		std::cout << "Something went wrong, program take only 2 arguments \n";
		exit(1);
	}

	
	//open source file	
	int readfd = open(argv[1], O_RDONLY);
	if(readfd == -1)
	{
		std::cout << "Something went wrong, Error:1 " << errno << "\n";
		exit(errno);
	}

	//to show Phys and Log sizes of source file
	//display_size(readfd, argv[1]);
	
	//open destination file
	int writefd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | O_TRUNC);
	if(writefd == -1)
	{
		std::cout << "Something went wrong, Error: 2\n";
		exit(errno);
	}
	
	long readHole = 0;
	long readData = 0;

	char* mybuffer =  new char[0];
	
	long offset = 0;
	long bufferSize = 0; 

	//for count logical and physical of source file
	long logicalSize1 = 0, logicalSize2 = 0;

	//for count logical and physical of destination file
	long physicalSize1 = 0, physicalSize2 = 0;

	while(true)
	{
		//return Hole
		readHole = lseek(readfd, offset, SEEK_HOLE);
		logicalSize1 += readHole - readData;
		
		offset = readHole;
		
		bufferSize = readHole - readData;
		
		mybuffer = new char[bufferSize];
		
		//cursor to previous position to read
		lseek(readfd, -bufferSize, SEEK_CUR);

		logicalSize2 += write(writefd, mybuffer, bufferSize);

		//if we do SEEK_DATA when data ended and other error
		readData = lseek(readfd, offset, SEEK_DATA);
		
		if(readData == -1)
		{
			if(errno == ENXIO)
			{
				readData = lseek(readfd, 0, SEEK_END);
				lseek(writefd, readData - readHole, SEEK_END);
				physicalSize2 += readData - readHole;
				break;	
			}
			else
			{
				std::cout << "Something went wrong, Error:3 ";
				return -1;
			}
		}
		physicalSize1 += readData - readHole;
		
		
		offset = readData;
		lseek(writefd, readData - readHole, SEEK_END);
		physicalSize2 += readData - readHole;
		//to count logical size
		
	}
	 
	close(readfd); //close source file
	close(writefd); //close destination file

	std::cout << "Source physical: " << physicalSize1 << ", Source logical: " << logicalSize1 << "\n";
	std::cout << "Destination physical: " << physicalSize2 << ", Destination logical: " << logicalSize2 << "\n";
	
	delete mybuffer; 
	return 0;
}
