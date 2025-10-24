#include "../Model_TAD_Lista_Pacote/TAD_Lista_Pacotes.h"

#ifndef TAD_COMBINACAO_H
#define TAD_COMBINACAO_H

typedef struct Celula_Combinacao_str
{
    // vetor contendo os ponteiros das celulas de combinação
    Celula **celula_pacotes;
    int prioridade_total;
    int peso_total;
    int num_elementos;

    struct Celula_Combinacao_str *prox;

}Celula_Combinacao;

typedef struct Lista_combinacao_str
{
    Celula_Combinacao *primeiro;
    Celula_Combinacao *ultimo;

} Lista_combinacao;

//irá inicializar a lista vazia do tipo combinacao, retirando o lixo de memoria
void iniciar_lista_vazia_combinacao (Lista_combinacao *lista);

void inserir_combinacao_final(Lista_combinacao *lista, Celula **vetor_pacotes, int prioridade, int peso, int elementos);

void remover_combinacoes_com_intersecao(Lista_combinacao *lista, Celula_Combinacao *melhor);

int remover_pacote_celula(Celula *celula, Pacote *pacote);

// Gera todas as combinações possiveis dado os pacotes que estão no galpao e armazena em lista
Celula_Combinacao *gerar_combinacoes(Lista_combinacao *lista, Lista_pacote *lista_galpao, int peso_max_drone);

// Adiciona o pacote na lista, armazenando dentro do drone,
Celula_Combinacao *escolher_melhor(Lista_combinacao *lista);


#endif