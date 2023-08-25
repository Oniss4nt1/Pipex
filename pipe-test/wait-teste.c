#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (1);
	}

	else if (pid == 0)
	{
		printf("I am the child.\n");
		sleep(2);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("I am the parent.\n");
		wait(NULL);
		printf("Child process terminated after a 2s delay.\n");

	}
	return (0);
}