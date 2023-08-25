#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd;

	fd = open("teste.txt", O_WRONLY | O_CREAT, 0666);
	if (fd < 0) {
		perror("open");
		return 1;
	}
	dup2(fd, 1);
	close(fd);
	printf("Batatinha Frita\n");

	//Troco de volta para o stdout

	return 0;
}

