#include <stdio.h>
#include "fileHandler.h"
#define MAX_LINHA 11

int LerMetadadosMatriz(char* nomeArquivo, int* bufferMetadados){
	FILE *fp;
	int numLin;
	int numCol;

	fp = fopen(nomeArquivo,"r");
	if(fp == NULL) {
    	perror("Error opening file");
    	return(0);
   	}

	//Lê o número de linhas da matriz
	fseek(fp, MAX_LINHA-2, SEEK_SET);
	fscanf(fp,"%d", &numLin);
	
	//Lê o número de colunas da matriz
	fseek(fp, MAX_LINHA, SEEK_CUR);
	fscanf(fp,"%d", &numCol);

	if(numLin == NULL || numCol == NULL){
		fclose(fp);
		return 0;
	}

	bufferMetadados[0] = numLin-1;
	bufferMetadados[1] = numCol-1;

	fclose(fp);

	return 1;
}

int LerMatrizes(char* nomeArquivo, int linhas, int colunas, int matriz[linhas][colunas]){
	FILE *fp;
	int i=0;
	int j=0;
	char c[20];

	fp = fopen(nomeArquivo,"r");
	if(fp == NULL) {
    	perror("Error opening file");
    	return(0);
   	}

   	//Incrementa o ponteiro do arquivo em 2 linhas
   	fgets(&c,20,fp);
   	fgets(&c,20,fp);

   	printf("Matriz de %s:\n", nomeArquivo);
   	
   	while(i <= linhas){
   		while(j <= colunas){
   			fscanf(fp,"%d",&matriz[i][j]);
   		   	printf("%d ", matriz[i][j]);
   			j++;
   		}
   		printf("\n");
   		i++;
   		j=0;
   	}
	
	fclose(fp);

   	return 1;
}

int ImprimeMatriz(char * nomeArquivo, int* matriz, int nLinhas, int nColunas);

