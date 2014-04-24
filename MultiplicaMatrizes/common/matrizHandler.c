#include <stdio.h>
#include "matrizHandler.h"

int computaLinha(int* metadadosA, int* metadadosB,int matrizA[metadadosA[0]][metadadosA[1]], int matrizB[metadadosB[0]][metadadosB[1]], int* bufferLinha, int nLinha){
	//int linhasA = metadadosA[0];
	int colunasA = metadadosA[1];
	//int linhasB = metadadosB[0];
	int colunasB = metadadosB[1];


	int i,j;

	for(j=0;j<=colunasB;j++){
		for(i=0;i<=colunasA;i++)
		{
			bufferLinha[j] = bufferLinha[j] + (matrizA[nLinha][i] * matrizB[i][j]);
		}
		printf("%d ", bufferLinha[j]); //print da linha da matriz resultante calculada
	}

}

void inicializaMatriz(int linhas,int colunas, int matriz[linhas][colunas]){
	int i,j;
	for(i=0;i<=linhas;i++)
		for(j=0;j<=colunas;j++)
			matriz[i][j] = 0;
}
