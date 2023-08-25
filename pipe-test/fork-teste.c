#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0) {
		perror("fork");
		return 1;
	}

	if (pid == 0)
		printf("Filho %d\n", getpid());
	else
		printf("Pai %d\n", getpid());
	return (0);
}