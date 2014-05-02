/*
	ThreadApp
*/
#include <stdio.h>
#include <stdlib.h>
#include "../common/fileHandler.h"
#include "../common/matrizHandler.h"
#include <pthread.h>


//Função que calcula um intervalo de linhas da matriz resultante
void* calculaMatriz(void *args){
	int i;
	int **param = (int*)args;

	for(i=param[5][0];i<=param[5][1];i++)
		computaLinha(param[0],param[1],param[2],param[3],i,param[4]);
	pthread_exit(NULL);
}

/*
	Divide as linhas da matriz resultante entre as threads/processos
*/
int divideLinhas(int** linhasThreads, int linhasMatriz, int numThreads){
	int qtdLinhas;
	int linhasRest;
	qtdLinhas = linhasMatriz / numThreads;
	linhasRest = linhasMatriz % numThreads;
	int linhasAux = 0;
	int i=0;
	
	if(numThreads<linhasMatriz)
		while(i<numThreads){
			int* intervaloLinhas = malloc(2*sizeof(int));
			intervaloLinhas[0] = linhasAux;
			if(i<numThreads-1){
				intervaloLinhas[1] = linhasAux+qtdLinhas-1;
				linhasAux = linhasAux+qtdLinhas;
			}
			else
			{
				intervaloLinhas[1] = linhasAux+qtdLinhas+linhasRest-1;
			}
			linhasThreads[i] = intervaloLinhas;
			i++;
		}
	else//numero de threads = linhas da matriz
		while(i<numThreads){
			if(linhasAux<linhasMatriz){
				int* intervaloLinhas = malloc(2*sizeof(int));
				intervaloLinhas[0] = linhasAux;
				intervaloLinhas[1] = linhasAux;
				linhasAux++;
				linhasThreads[i] = intervaloLinhas;
			}
			i++;
		}

	return 1;
}

int main(int argc, char *argv[])
{
	int metadadosA[2],metadadosB[2];
	char nomeArquivoMatrizA[] = "in1.txt";
	char nomeArquivoMatrizB[] = "in2.txt";
	char nomeArquivoSaida[] = "out.txt";
	int numThreads = atoi(argv[1]);
	int i,j;
	
	pthread_t th[numThreads];

	if(LerMetadadosMatriz(&nomeArquivoMatrizA,metadadosA) && LerMetadadosMatriz(&nomeArquivoMatrizB,metadadosB)){
		
		 if(metadadosA[1] != metadadosB[0]){
		 	printf("%d\n", metadadosA[1]);
		 	printf("%d\n", metadadosB[0]);
        	printf("Erro de entrada - Numero de colunas da primeira matriz eh diferente do numero de linhas da segunda matriz.\n");
        	return 0;
   		 }
    	
    	if(metadadosA[0] < numThreads){
        	printf("Erro de entrada - Numero de processos/threads nao pode ser maior que o numero de linhas da matriz resultante.\n");
        	return 0;
    	}

		//Cria as matrizes
		int **matrizA = malloc(sizeof(int)*metadadosA[0]*metadadosA[1]);
		int **matrizB = malloc(sizeof(int)*metadadosB[0]*metadadosB[1]);
		int **matrizResultante = malloc(sizeof(int)*metadadosA[0]*metadadosB[1]);

		//Faz a leitura dos arquivos e preenche as matrizes
		if(LerMatrizes(&nomeArquivoMatrizA,metadadosA[0],metadadosA[1],matrizA) && LerMatrizes(&nomeArquivoMatrizB,metadadosB[0],metadadosB[1],matrizB)){

		//set de todos os elementos da matriz em 0
		inicializaMatriz(metadadosA[0],metadadosB[1],matrizResultante);		
	
		int* linhas[numThreads];
		divideLinhas(linhas,metadadosA[0],numThreads);

		//argumento que será passado para a função que as threads executarão
		int *args[numThreads][6];

		for(i=0;i<numThreads;i++){
			args[i][0] = metadadosA;
			args[i][1] = metadadosB;
			args[i][2] = matrizA;
			args[i][3] = matrizB;
			args[i][4] = matrizResultante;
			args[i][5] = linhas[i];
			pthread_create(&th[i], NULL, calculaMatriz, (void *)args[i]);
		}
		for( i=0; i<numThreads; i++ ){ 
    		pthread_join( th[i], NULL );
    		free(linhas[i]);
    	}

		ImprimeMatriz(nomeArquivoSaida,metadadosA[0],metadadosB[1],matrizResultante);
	
		}
		else
			printf("Erro ao tentar ler matrizes\n");
	}
	else
		printf("Erro ao tentar ler as linhas e colunas das matrizes(metadados)\n");
	
	return 0;
}
