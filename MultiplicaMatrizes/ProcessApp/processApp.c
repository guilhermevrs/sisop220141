/*
	ProcessApp
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */
#include "../common/fileHandler.h"
#include "../common/matrizHandler.h"

int criaProcessos(int qtdProcessos, int* matrizA, int* matrizB, int* metadados)
{
	int linha;
	int bufferLinha[*(metadados)];
	char *nomeArquivoOut = "out.txt";
	pid_t pid;
	for(linha = qtdProcessos-1; linha >= 0; linha--)
	{
		if(linha > 0)
			pid = fork();
		if(linha <= 0 || pid != 0) //Parent
		{
			//Computa linha
			computaLinha(matrizA, matrizB, metadados, bufferLinha, linha);
			//espera pelo pid criado, caso exista um pid criado
			if(pid != 0)
				waitpid(pid,0,0);
			//imprime
			ImprimeMatriz(nomeArquivoOut, bufferLinha, 1,*(metadados));
			break;
		}
	}
	exit(1);
}

int main()
{/*
	int metadados[2][2];
	int qtdProcessos = 0;
	char nomeArquivo[] = "nomeArquivo";
	pid_t pid;
	if(LerMetadadosMatriz(&nomeArquivo,metadados))
	{
		int matrizA[metadados[0][0]][metadados[0][1]];
		int matrizB[metadados[1][0]][metadados[1][1]];
		if(LerMatrizes(&nomeArquivo, matrizA, matrizB))
		{
			qtdProcessos = metadados[1][1];
			pid = fork();
			if(pid == 0)
				criaProcessos(qtdProcessos, matrizA, matrizB, metadados);
			waitpid(pid,0,0);
		}
		else
		{
			printf("Erro ao tentar ler matrizes");
		}
	}
	else
	{
		printf("Erro ao tentar ler os metadados");
	}
*/
	return 0;
}
