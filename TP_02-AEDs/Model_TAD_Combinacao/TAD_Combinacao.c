#include "TAD_Combinacao.h"

// Vai inicializar a lista com a celula cabeça
void iniciar_lista_vazia_combinacao (Lista_combinacao *lista){
    lista->primeiro = (Celula_Combinacao*) malloc(sizeof(Celula_Combinacao));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}

// Preenche a Celula com os valores apropriados
void inserir_combinacao_final(Lista_combinacao *lista, Celula **vetor_pacotes, int prioridade, int peso, int elementos){
    lista->ultimo->prox = (Celula_Combinacao*) malloc(sizeof(Celula_Combinacao));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->celula_pacotes = vetor_pacotes;
    lista->ultimo->peso_total = peso;
    lista->ultimo->prioridade_total = prioridade;
    lista->ultimo->num_elementos = elementos;
    lista->ultimo->prox = NULL;
}

// Remove da lista todas as Celula_Combinacao que contenham
// ao menos um pacote presente em melhor_combinacao.
void remover_combinacoes_com_intersecao(Lista_combinacao *lista, Celula_Combinacao *melhor_combinacao) {
    if (!lista || !lista->primeiro || !melhor_combinacao || !melhor_combinacao->celula_pacotes) return;

    Celula_Combinacao *anterior = lista->primeiro;
    Celula_Combinacao *atual = anterior->prox;

    while (atual) {
        int tem_interseccao = 0;

        for (int i = 0; !tem_interseccao && i < atual->num_elementos; i++) {
            for (int j = 0; !tem_interseccao && j < melhor_combinacao->num_elementos; j++) {
                if (atual->celula_pacotes[i] == melhor_combinacao->celula_pacotes[j]) {
                    tem_interseccao = 1;
                }
            }
        }

        if (tem_interseccao) {
            anterior->prox = atual->prox;
            if (atual == lista->ultimo) {
                lista->ultimo = anterior;
            }

            if (atual->celula_pacotes != NULL) {
                free(atual->celula_pacotes);
            }
            free(atual);
            atual = anterior->prox;
        } else {
            anterior = atual;
            atual = atual->prox;
        }
    }
}

// Remove uma combinação específica da lista
void remover_combinacao_especifica(Lista_combinacao *lista, Celula_Combinacao *celula_a_remover) {
    if (!lista || !lista->primeiro || !celula_a_remover || celula_a_remover == lista->primeiro) return;

    Celula_Combinacao *anterior = lista->primeiro;
    Celula_Combinacao *atual = anterior->prox;

    while (atual) {
        if (atual == celula_a_remover) {
            anterior->prox = atual->prox;

            if (atual == lista->ultimo) {
                lista->ultimo = anterior;
            }

            if (atual->celula_pacotes != NULL) {
                free(atual->celula_pacotes);
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

// Gera todas as combinações possíveis e retorna a melhor
Celula_Combinacao *gerar_combinacoes(Lista_combinacao *lista, Lista_pacote *lista_galpao, int peso_max_drone){
    Celula_Combinacao *melhor_opcao = NULL;

    int numero_de_elementos_da_combinacao = 0;
    Celula *aux = lista_galpao->primeiro->prox;
    while (aux != NULL) {
        numero_de_elementos_da_combinacao++;
        aux = aux->prox;
    }

    Celula **todos_pacotes = (Celula**) malloc(numero_de_elementos_da_combinacao * sizeof(Celula*));
    aux = lista_galpao->primeiro->prox;
    for(int i = 0; i < numero_de_elementos_da_combinacao; i++) {
        todos_pacotes[i] = aux;
        aux = aux->prox;
    }
    
    for (int tamanho = 1; tamanho <= numero_de_elementos_da_combinacao; tamanho++) {
        int *comb = (int*) malloc(tamanho * sizeof(int));
        for (int i = 0; i < tamanho; i++) comb[i] = i;
        
        while (1) {
            int peso_total = 0, prioridade_total = 0;
            for (int i = 0; i < tamanho; i++) {
                peso_total += todos_pacotes[comb[i]]->pacote.peso;
                prioridade_total += todos_pacotes[comb[i]]->pacote.prioridade;
            }

            if (peso_total <= peso_max_drone) {
                Celula **vetor_pacotes = (Celula**) malloc(tamanho * sizeof(Celula*));
                for (int i = 0; i < tamanho; i++) {
                    vetor_pacotes[i] = todos_pacotes[comb[i]];
                }

                inserir_combinacao_final(lista, vetor_pacotes, prioridade_total, peso_total, tamanho);

                if (melhor_opcao == NULL ||
                    prioridade_total > melhor_opcao->prioridade_total ||
                    (prioridade_total == melhor_opcao->prioridade_total && peso_total < melhor_opcao->peso_total)) {
                    melhor_opcao = lista->ultimo;
                }
            }

            int i = tamanho - 1;
            while (i >= 0 && comb[i] == numero_de_elementos_da_combinacao - tamanho + i) i--;
            if (i < 0) break;
            comb[i]++;
            for (int j = i + 1; j < tamanho; j++) comb[j] = comb[j - 1] + 1;
        }
        free(comb);
    }

    free(todos_pacotes);

    if (melhor_opcao == NULL) {
        printf("Nenhuma combinacao valida encontrada para o peso maximo do drone: %d\n", peso_max_drone);
    }
    return melhor_opcao;
}

Celula_Combinacao *escolher_melhor(Lista_combinacao *lista){
    if (lista == NULL || lista->primeiro == NULL || lista->primeiro->prox == NULL) {
        return NULL;
    }
    Celula_Combinacao *melhor_opcao = lista->primeiro->prox;
    Celula_Combinacao *aux = melhor_opcao->prox;
    while (aux) {
        if(aux->prioridade_total > melhor_opcao->prioridade_total){
            melhor_opcao = aux;
        }
        aux = aux->prox;
    }
    return melhor_opcao;
}

int lista_combinacao_eh_vazia (Lista_combinacao *lista){
    return (lista->primeiro == lista->ultimo);
}
