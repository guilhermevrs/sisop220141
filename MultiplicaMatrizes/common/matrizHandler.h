/*
	Handler de matriz para multiplicação
*/
#ifndef MATRIZ_HANDLER_H
#define MATRIZ_HANDLER_H

/*
	computaLinha : Computa uma linha da matriz resultante
	Parâmetros:
		matrizA = Primeira matriz da multiplicação
		matrizB = Segunda matriz da multiplicação
		metadados = Matriz 2x2 com as info de linha e coluna
		bufferLinha = Buffer que armazenará a linha computada
		nLinha = Número da linha (começando em 0) que deve ser calculada
	Retorno:
		1 = Operação feita com sucesso
		0 = Operação com erro
*/
int computaLinha(int* metadadosA, int* metadadosB,int matrizA[metadadosA[0]][metadadosA[1]], int matrizB[metadadosB[0]][metadadosB[1]],int nLinha, int bufferLinha[metadadosA[0]][metadadosB[1]]);
void inicializaMatriz(int linhas,int colunas, int matriz[linhas][colunas]);
#endif
