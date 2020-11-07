#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// here create a child proccess for exec fuction
int mainLaunchShell(char** tokens)
{
	if(tokens[0] == NULL)
	{
		// was inputed empty string
		return 1;
	}
	
	if(strcmp(tokens[0], "exit") == 0)
	{
		// close shell
		return 0;
	}

	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{					
		if (tokens[0][0] == '/') // if in input path of the file
		{
			if (execv(tokens[0], tokens) == -1)
			{
				perror("lsh");
			}
			exit(EXIT_FAILURE);
		}
		else // if in input name of the file
		{
			if (execvp((char*)tokens[0], tokens) == -1)
			{
				perror("lsh");
			}	
			exit(EXIT_FAILURE);
		}
	}

	if(pid > 0)
	{
		wpid = waitpid(pid, &status, WUNTRACED); 	
	}

	return 1;
}

#define tokenSize 64
#define delimiters "  \t\r\n\a"
char** splitLine(char* line)
{
	char** tokens = new char*[tokenSize]; // will contain all words splitted by delimiters
	char* token;
	int position = 0;
	int buffsize = tokenSize;
	
	// check if memory allocated or not
	if(!tokens)
	{
		fprintf(stderr, "memory allocation error\n");
		exit(EXIT_FAILURE);
	}
	
	// getting all words avoiding delimiters
	token = strtok(line, delimiters);
	while (token != NULL)
	{
		tokens[position] = token;
		++position;

		if(position >= buffsize)
		{	
			if(std::realloc(tokens, tokenSize * 2) == nullptr)
			{
				fprintf(stderr, "memory reallocation error\n");
				exit(EXIT_FAILURE);
			}	
		}
		
		token = strtok(NULL, delimiters);
	}

	tokens[position] = NULL;		
	return tokens;
}

#define buffSize 512
char* readLine()
{
	char* tempLine = new char[buffSize];
	int position = 0;

	int c; // return ASCII decimal code of each letter in stdin

	// reading what was inputed to stdin
	while (true)
	{
		c = getchar();

		if (c == EOF || c == '\n')
		{
			tempLine[position] = '\0';				
			return tempLine;
		}
		else
		{
			tempLine[position] = c;
		}
		position++;
	}
	
	// realloc if memory does not enough
	if (position >= buffSize)
	{
		if (std::realloc(tempLine, buffSize * 2) == nullptr)
		{
			fprintf(stderr, "lsh: Error on reallocation memory\n");
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char* argv[])
{

	char* line; // to read all string in stdin
	char**  AllTokens; // here will be all words splited by space (array of strings)
	int status = 1;

	while(status)
	{
		std::cout << "shell> ";
	
		line = readLine();
	
		AllTokens = splitLine(line);			
		
		status = mainLaunchShell(AllTokens);	
	}
	
}
