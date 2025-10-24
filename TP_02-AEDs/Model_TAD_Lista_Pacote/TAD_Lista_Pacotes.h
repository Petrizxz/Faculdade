#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../Model_TAD_Pacote/TAD_Pacote.h"

#ifndef TAD_LISTA_PACOTES_H
#define TAD_LISTA_PACOTES_H

typedef struct Celula_str
{
    Pacote pacote;
    struct Celula_str *prox;
    
} Celula;

typedef struct
{
    Celula *primeiro;
    Celula *ultimo;

} Lista_pacote;


//irá inicializar a lista vazia do tipo pacote, retirando o lixo de memoria
void iniciar_lista_vazia (Lista_pacote *lista);

//vai ler a lista vazia
int lista_eh_vazia (Lista_pacote *lista);

//Esta função irá inserir um pacote adicional ao final da lista
void inserir_pacote_final (Lista_pacote *lista, Pacote *pacote);

//Esta função irá remover o pacote que esta no inicio da lista
int remover_pacote_inicio (Lista_pacote *lista, Pacote *pacote);

void remover_pacote_meio(Celula *celula, Pacote *pacote);

//devera imprimir os dados dos pacotes que estão presentes na lista
void imprime_lista (Lista_pacote *lista);

#endif