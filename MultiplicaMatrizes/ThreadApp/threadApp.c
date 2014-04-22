/*
	ThreadApp
*/
#include <stdio.h>
#include "../common/fileHandler.h"
#include "../common/fileHandler.c"
#include "../common/matrizHandler.h"
#include "../common/matrizHandler.c"

int main()
{
	int metadadosA[1],metadadosB[1];
	char nomeArquivoMatrizA[] = "in1";
	char nomeArquivoMatrizB[] = "in2";
	char nomeArquivoSaida[] = "out";
	int threadLinha = 0;
	
	LerMetadadosMatriz(&nomeArquivoMatrizA,&metadadosA);
	LerMetadadosMatriz(&nomeArquivoMatrizB,&metadadosB);
	
	//Cria as matrizes dinâmicas
	int matrizA[metadadosA[0]][metadadosA[1]];
	int matrizB[metadadosB[0]][metadadosB[1]];
	int matrizResultante[metadadosA[0]][metadadosB[1]];

	LerMatrizes(&nomeArquivoMatrizA,metadadosA[0],metadadosA[1],matrizA);
	LerMatrizes(&nomeArquivoMatrizB,metadadosB[0],metadadosB[1],matrizB);
	
	computaLinha(&metadadosA,&metadadosB,matrizA,matrizB,&matrizResultante[threadLinha],threadLinha);
	//ImprimeMatriz(&nomeArquivoSaida,metadadosA[0],metadadosB[1],matrizResultante);
	
	return 0;
}
