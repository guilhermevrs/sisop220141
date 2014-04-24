#include <stdio.h>
#include "tableHandler.h"

int InicializaFila(char *filosofos, int qtd)
{
    int i = 0;
    for(i = 0; i<qtd; i++)
        *(filosofos++) = 'T';
}
int ImprimeEstados(char *filosofo, int qtd)
{
    int i = 0;
    for(i = 0; i<qtd; i++)
        printf("%c ", *(filosofo++));
    printf("\n");
}
int TrocaEstado(char *filosofos, char novoEstado)
{
    *filosofos = novoEstado;
}
