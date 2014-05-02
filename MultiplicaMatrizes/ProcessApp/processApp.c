/*
	ProcessApp
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "../common/fileHandler.h"
#include "../common/matrizHandler.h"

/*
	Divide as linhas da matriz resultante entre as threads/processos
*/
int divideLinhas(int** linhasProc, int linhasMatriz, int qtdProcessos){
	int qtdLinhas;
	int linhasRest;
	qtdLinhas = linhasMatriz / qtdProcessos;
	linhasRest = linhasMatriz % qtdProcessos;
	int linhasAux = 0;
	int i=0;

	if(qtdProcessos<linhasMatriz)
		while(i<qtdProcessos){
			int* intervaloLinhas = malloc(2*sizeof(int));
			intervaloLinhas[0] = linhasAux;
			if(i<qtdProcessos-1){
				intervaloLinhas[1] = linhasAux+qtdLinhas-1;
				linhasAux = linhasAux+qtdLinhas;
			}
			else
			{
				intervaloLinhas[1] = linhasAux+qtdLinhas+linhasRest-1;
			}
			linhasProc[i] = intervaloLinhas;
			i++;
		}
	else//numero de threads = linhas da matriz
		while(i<qtdProcessos){
			if(linhasAux<linhasMatriz){
				int* intervaloLinhas = malloc(2*sizeof(int));
				intervaloLinhas[0] = linhasAux;
				intervaloLinhas[1] = linhasAux;
				linhasAux++;
				linhasProc[i] = intervaloLinhas;
			}
			i++;
		}

	return 1;
}

int main(int argc, char *argv[])
{

	char nomeArquivoMatrizA[] = "in1.txt";
	char nomeArquivoMatrizB[] = "in2.txt";
	char nomeArquivoSaida[] = "out.txt";
	int metadadosA[2],metadadosB[2];
	int qtdProcessos = atoi(argv[1]);
	int i,j,k;

	if(LerMetadadosMatriz(&nomeArquivoMatrizA,metadadosA) && LerMetadadosMatriz(&nomeArquivoMatrizB,metadadosB))
	{
		if(metadadosA[1] != metadadosB[0]){
        	printf("Erro de entrada - Numero de colunas da primeira matriz eh diferente do numero de linhas da segunda matriz.\n");
        	return 0;
   		 }
    	
    	if(metadadosA[0] < qtdProcessos){
        	printf("Erro de entrada - Numero de processos/threads nao pode ser maior que o numero de linhas da matriz resultante.\n");
        	return 0;
    	}

		int **matrizA = malloc(sizeof(int)*metadadosA[0]*metadadosA[1]);
		int **matrizB = malloc(sizeof(int)*metadadosB[0]*metadadosB[1]);

	//Criando espaco de memoria compartilhada
    int md = shmget(IPC_PRIVATE, sizeof(int)*metadadosA[0]*metadadosB[1], IPC_CREAT|0666);
    //Pai se anexa a essa memoria compartilhada tambem
    int **matrizResultante = (int*)shmat(md, NULL, 0);
    //Limpando garbage
    bzero(matrizResultante, sizeof(int)*metadadosA[0]*metadadosB[1]);	

	if(LerMatrizes(&nomeArquivoMatrizA,metadadosA[0],metadadosA[1],matrizA) && LerMatrizes(&nomeArquivoMatrizB,metadadosB[0],metadadosB[1],matrizB))
		{
			int* linhas[qtdProcessos];
			divideLinhas(linhas,metadadosA[0],qtdProcessos);

			for(i=0; i<qtdProcessos; i++){
				pid_t pid = fork();
			//Se sou processo filho
			if(pid == 0){
				for(j=linhas[i][0];j<=linhas[i][1];j++){
					computaLinha(metadadosA, metadadosB, matrizA, matrizB, j, matrizResultante);
				}
      			return 0;
      		}
			}
			//Pai espera o final de todos os processos para executar
			for (i = 0; i < qtdProcessos; ++i)
			{
				waitpid(0, NULL, 0);
			}

			ImprimeMatriz(nomeArquivoSaida,metadadosA[0],metadadosB[1],matrizResultante);
			
			for (i = 0; i < qtdProcessos; ++i)
			{
				free(linhas[i]);
			}

			//Liberando memoria compartilhada
			shmctl(md, IPC_RMID, NULL);
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
