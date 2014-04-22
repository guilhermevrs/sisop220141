/*
	ThreadApp
*/
#include <stdio.h>
#include "../common/fileHandler.h"
#include "../common/fileHandler.c"
#include "../common/matrizHandler.h"

int main()
{
	int metadadosA[1],metadadosB[1];
	char nomeArquivoMatrizA[] = "in1";
	char nomeArquivoMatrizB[] = "in2";
	
	if(LerMetadadosMatriz(&nomeArquivoMatrizA,&metadadosA))
		if(LerMetadadosMatriz(&nomeArquivoMatrizB,&metadadosB))
		{
			//Cria as matrizes dinâmicas
			int matrizA[metadadosA[0]][metadadosA[1]];
			int matrizB[metadadosB[0]][metadadosB[1]];
				if(LerMatrizes(&nomeArquivoMatrizA,metadadosA[0],metadadosA[1],matrizA))
					if(LerMatrizes(&nomeArquivoMatrizB,metadadosB[0],metadadosB[1],matrizB))
					{
						printf("Leitura finalizada\n");
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
	
	return 0;
}
