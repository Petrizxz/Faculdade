#include "TAD_Lista_Pacotes.h"

// TOM: Tom pra vc inserir o anterior aqui acredito que vc vai precisar mexer em iniciar lista vazia
// inserir_pacote_final, precisa acrescentar aque sempre que inserir um novo vamos armazenar o endereço do anterior no novo
void iniciar_lista_vazia (Lista_pacote *lista){
    lista->primeiro = (Celula*) malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}

int lista_eh_vazia (Lista_pacote *lista){
    return (lista->primeiro == lista->ultimo);
}

// TOM: Antes de fazer ultimo receber o novo tem que pegar o endereço dele para armazenar no anterior
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

// TOM: Aqui vc vai implementar o racionio do remover do meio
// Deixei pacote = celula.pacote pra eu conseguir tester mais coisas
void remover_pacote_meio (Celula *celula, Pacote * pacote){
    *pacote = celula->pacote;
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
        printf("----------------------------------/n/n");
        aux = aux-> prox;
    }
}