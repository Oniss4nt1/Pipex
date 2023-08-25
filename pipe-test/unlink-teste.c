#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	if (unlink("teste.txt") == 0)
		printf("Arquivo removido com sucesso\n");
	else
		printf("Erro ao remover arquivo\n");
	return (0);
}