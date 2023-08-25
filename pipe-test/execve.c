#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	char *args[3];

	args[0] = "/bin/ls";
	args[1] = "-l";
	args[2] = NULL;
	execve(args[0], args, NULL);
	printf("Executou\n");
}	