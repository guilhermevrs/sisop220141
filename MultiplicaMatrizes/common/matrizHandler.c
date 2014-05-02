#include <stdio.h>
#include "matrizHandler.h"

//Calcula uma linha da matriz resultante
int computaLinha(int* metadadosA, int* metadadosB,int matrizA[metadadosA[0]][metadadosA[1]], int matrizB[metadadosB[0]][metadadosB[1]], int nLinha, int bufferLinha[metadadosA[0]][metadadosB[1]]){
	int colunasA = metadadosA[1];
	int colunasB = metadadosB[1];

	int i,j;

	for(j=0;j<colunasB;j++){
		for(i=0;i<colunasA;i++)
		{
			bufferLinha[nLinha][j] = bufferLinha[nLinha][j] + (matrizA[nLinha][i] * matrizB[i][j]);
		}
	}
}

//Inicializa todos os valores da matriz em "0"
void inicializaMatriz(int linhas,int colunas, int matriz[linhas][colunas]){
	int i,j;
	for(i=0;i<linhas;i++)
		for(j=0;j<colunas;j++)
			matriz[i][j] = 0;
}
