#include "TAD_Lista_Pacotes.h"

// TOM: Tom pra vc inserir o anterior aqui acredito que vc vai precisar mexer em iniciar lista vazia
// inserir_pacote_final, precisa acrescentar aque sempre que inserir um novo vamos armazenar o endereço do anterior no novo
void iniciar_lista_vazia (Lista_pacote *lista){
    lista->primeiro = (Celula*) malloc(sizeof(Celula));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
    lista->ultimo = lista->primeiro;
}

int lista_eh_vazia (Lista_pacote *lista){
    return (lista->primeiro == lista->ultimo);
}

// TOM: Antes de fazer ultimo receber o novo tem que pegar o endereço dele para armazenar no anterior
void inserir_pacote_final (Lista_pacote *lista, Pacote *pacote){
    Celula *nova = (Celula *) malloc(sizeof(Celula));
    nova->pacote = *pacote;
    nova->prox = NULL;
    nova->anterior = lista->ultimo;
    lista->ultimo->prox = nova;
    lista->ultimo = nova;

}

//Recebe a lista a ter seu item removido e devolve esse item atravez do parametro pacote
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

// TOM: Aqui vc vai implementar o racionio do remover do meio
// Deixei pacote = celula.pacote pra eu conseguir tester mais coisas


void remover_pacote_meio(Lista_pacote *lista, Celula *celula, Pacote *pacote) {
    if (lista_eh_vazia(lista) || celula == NULL || celula == lista->primeiro) {
        printf("Erro: célula inválida para remoção.\n");
        return;
    }
    
    // Ponteiro auxiliar para percorrer a lista
    Celula *anterior = lista->primeiro;
    
    // Encontra o nó anterior à célula que será removida
    while (anterior->prox != NULL && anterior->prox != celula) {
        anterior = anterior->prox;
    }

    // Se não encontrou a célula na lista
    if (anterior->prox == NULL) {
        printf("Erro: célula não encontrada na lista.\n");
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

    free(celula);
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