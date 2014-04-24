#ifndef TABLE_HANDLER_H
#define TABLE_HANDLER_H

/* InicializaFila: Inicializa a fila atribuindo o estado inicial de cada filósofo
	Parâmetros:
		filosofos = array de filosofos
	Retorno:
		1 = Operação com sucesso
		0 = Operação com erros
*/
int InicializaFila(char *filosofos);

/*
	ImprimeEstados: Imprime o estado de cada filósofo
	Parâmetros:
		filosofos = array de filosofos
	Retorno:
		1 = Operação com sucesso
		0 = Operação com erros
*/
int ImprimeEstados(char *filosofo);

/*
	TrocaEstado: Troca o estado de um filósofo
	Parâmetros:
		filosofo = um filósofo
		novoEstado = estado pode ser "E" (para eating), "T" (para thinking) e "H" (para hungry)
	Retorno:
		1 = Operação com sucesso
		0 = Operação com erros
*/
int TrocaEstado(char *filosofos, char novoEstado);


#endif
