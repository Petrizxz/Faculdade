#include "TAD_Lista_Pacotes.h"

void iniciar_lista_vazia (Lista_pacote *lista){
    lista->primeiro = (Celula*) malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}

int lista_eh_vazia (Lista_pacote *lista){
    return (lista->primeiro == lista->ultimo);
}

void inserir_pacote_final (Lista_pacote *lista, Pacote *pacote){
    lista->ultimo->prox = (Celula*) malloc(sizeof(Celula));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->pacote = *pacote;
    lista->ultimo->prox = NULL;
}

//Recebe a lista a ter seu item removido e devolve esse item atravez do parametro pacote
int remover_pacote_inicio (Lista_pacote *lista, Pacote * pacote){
 Celula * aux;
 if (lista_eh_vazia(lista)){return 0;}
 *pacote = lista->primeiro->prox->pacote;
 aux = lista->primeiro;
 lista->primeiro = lista->primeiro->prox;
 free(aux);
 return 1;
}

void imprime_lista (Lista_pacote *lista){
    Celula * aux;
    aux = lista->primeiro->prox;
    while (aux != NULL)
    {
        printf("Conteudo: %s\n", aux-> pacote.conteudo);
        printf("Destinatario: %s\n", aux-> pacote.destinatario);
        printf("Distancia: %d\n", aux-> pacote.distancia);
        printf("Peso: %d\n", aux-> pacote.peso);
        printf("----------------------------------/n/n");
        aux = aux-> prox;
    }
}