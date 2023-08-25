#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int result;

	result = access("teste.txt", F_OK);
	if (result == -1){
		printf("Arquivo não existe\n");
		printf("%d\n", result);
	}
	else{
		printf("Arquivo existe\n");
		printf("%d\n", result);
	}

	if (access("teste.txt", R_OK) == -1)
		printf("Arquivo não tem permissão de leitura\n");
	else
		printf("Arquivo tem permissão de leitura\n");

	if (access("teste.txt", W_OK) == -1)
		printf("Arquivo não tem permissão de escrita\n");
	else
		printf("Arquivo tem permissão de escrita\n");

	if (access("teste.txt", X_OK) == -1)
		printf("Arquivo não tem permissão de execução\n");
	else
		printf("Arquivo tem permissão de execução\n");
}