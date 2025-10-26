#include "TAD_Lista_Pacotes.h"

void iniciar_lista_vazia (Lista_pacote *lista){
    lista->primeiro = (Celula*) malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
    lista->ultimo = lista->primeiro;
}

int lista_eh_vazia (Lista_pacote *lista){
    return (lista->primeiro == lista->ultimo);
}

void inserir_pacote_final (Lista_pacote *lista, Pacote *pacote){
    Celula *nova = (Celula *) malloc(sizeof(Celula));
    nova->pacote = *pacote;
    nova->prox = NULL;
    nova->anterior = lista->ultimo;
    lista->ultimo->prox = nova;
    lista->ultimo = nova;
}

int remover_pacote_inicio (Lista_pacote *lista, Pacote * pacote){
    if (lista_eh_vazia(lista)) return 0;

    Celula *remover = lista->primeiro->prox;
    *pacote = remover->pacote;

    lista->primeiro->prox = remover->prox;

    if (remover->prox != NULL)
        remover->prox->anterior = lista->primeiro;
    else
        lista->ultimo = lista->primeiro;  // lista ficou vazia

    free(remover);
    return 1;
}

void remover_pacote_meio(Lista_pacote *lista, Celula *celula, Pacote *pacote) {
    if (lista_eh_vazia(lista) || celula == NULL || celula == lista->primeiro) {
        printf("Erro: celula invalida para remocao.\n");
        return;
    }
    
    // Copia os dados do pacote que vai ser removido
    *pacote = celula->pacote;

    // ajusta ligações
    if (celula->anterior != NULL)
        celula->anterior->prox = celula->prox;

    if (celula->prox != NULL)
        celula->prox->anterior = celula->anterior;
    else
        lista->ultimo = celula->anterior; // era o último

    // A célula NÃO deve ser liberada aqui, pois o ponteiro para ela é usado nas combinações.
    // A liberação deve ser feita em TAD_Galpao.c, APÓS o uso da combinação.
    // free(celula); // Comentado para evitar o dangling pointer.
}

void imprime_lista (Lista_pacote *lista){
    Celula * aux;
    aux = lista->primeiro->prox;
    while (aux != NULL)
    {   
        printf("Conteudo: %s\n", get_conteudo(&aux->pacote));
        printf("Destinatario: %s\n", get_destinatario(&aux->pacote));
        printf("Distancia: %d\n", get_distancia_endereco(&aux->pacote));
        printf("Peso: %d\n", get_peso(&aux->pacote));
        printf("----------------------------------\n\n");
        aux = aux-> prox;
    }
}



