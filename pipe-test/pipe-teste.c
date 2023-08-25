#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int fd[2];
	pid_t pid;
	char buffer[14];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (1);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}

	if (pid == 0)
	{
		close(fd[0]); // Close read end
		write(fd[1], "Hello parent!", 14); // Write to write end
		close(fd[1]); // Close write end
		return (0);
	}
	else
	{
		close(fd[1]); // Close write end
		read(fd[0], buffer, 14); // Read from read end
		close(fd[0]); // Close read end
		printf("Message from child: '%s'\n", buffer);
		return (0);
	}
}