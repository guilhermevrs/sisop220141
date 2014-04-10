/*
	Handler para leitura e escrita de arquivos
*/
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

/*
	LerMetadadosMatriz: Lê do arquivo a quantidade de linhas e quantidade de colunas das matrizes, armazenando no buffer
	Parâmetros:
		nomeArquivo = String com o caminho para o arquivo
		bufferMetadados = Ponteiro para matriz que armazenará os metadados
	Retorno:
		1 = Operação com sucesso
		0 = Operação com erros
*/
int LerMetadadosMatriz(char* nomeArquivo, int* bufferMetadados);

/*
	LerMatrizes: Ler as matrizes A e B
	Parâmetros:
		nomeArquivo = Nome do arquivo
		matrizA = ponteiro para armezenar a matrizA lida
		matrizB = ponteiro para armazenar a matrizB lida
	Retorno:
		1 = sucesso
		0 = erro
*/
int LerMatrizes(char* nomeArquivo, int*matrizA, int* matrizB);

/*
	ImprimeMatriz: Imprime uma matriz em arquivo
	Parâmetros:
		nomeArquivo = String com o caminho para o arquivo
		matriz = ponteiro para a matriz
		nLinhas = quantidade de linhas da matriz
		nColunas = quantidade de colunas da matriz
	Retorno:
		1 = operação com sucesso
		0 = operação com erros
*/
int ImprimeMatriz(char * nomeArquivo, int* matriz, int nLinhas, int nColunas);

#endif
