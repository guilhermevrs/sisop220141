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
int computaLinha(int* matrizA, int* matrizB, int* metadados, int* bufferLinha, int nLinha);

#endif
