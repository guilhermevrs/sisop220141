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
	int i,j;
	char c[20];

	fp = fopen(nomeArquivo,"r");
	if(fp == NULL) {
    	perror("Error opening file");
    	return(0);
   	}

   	//Incrementa o ponteiro do arquivo em 2 linhas
   	fgets(&c,20,fp);
   	fgets(&c,20,fp);

   	for(i=0;i<=linhas;i++)
   		for(j=0;j<=colunas;j++)
   			fscanf(fp,"%d",&matriz[i][j]);

	fclose(fp);

   	return 1;
}

int ImprimeMatriz(char* nomeArquivo, int nLinhas, int nColunas, int matriz[nLinhas][nColunas]){
	FILE *fp;
	int i,j;

	fp = fopen(nomeArquivo,"w");
	if(fp == NULL) {
    	perror("Error opening file");
    	return(0);
   	}
	
   	fprintf(fp, "LINHAS = %d\nCOLUNAS = %d\n", nLinhas, nColunas);
	
	for(i=0;i<=nLinhas;i++){
   		for(j=0;j<=nColunas;j++){
 	   		if(j!=0)
 	   			fprintf(fp," ");		
 	   		fprintf(fp,"%d", matriz[i][j]);
   		}
		fprintf(fp,"\n");
 	}
	
 	fclose(fp);   	
}
	


