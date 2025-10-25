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
    lista->ultimo->celula_pacotes = (Celula**) malloc(elementos * sizeof(Celula*));
    for(int i = 0; i < elementos; i++){
        lista->ultimo->celula_pacotes[i] = vetor_pacotes[i];
    }
    lista->ultimo->peso_total = peso;
    lista->ultimo->prioridade_total = prioridade;
    lista->ultimo->num_elementos = elementos;
    lista->ultimo->prox = NULL;
}

// Remove da lista todas as Celula_Combinacao que contenham
// ao menos um pacote presente em melhor_combinacao.
void remover_combinacoes_com_intersecao(Lista_combinacao *lista, Celula_Combinacao *melhor_combinacao) {
    if (!lista || !lista->primeiro || !melhor_combinacao) return;

    // ponteiro para o nó "anterior" Começa na celula cabeça
    Celula_Combinacao *anterior = lista->primeiro;
    // ponteiro para o nó sendo examinado
    Celula_Combinacao *atual = anterior->prox;

    while (atual) {
        int tem_interseccao = 0;

        // percorre cada pacote da combinação atual
        for (int i = 0; !tem_interseccao && i < atual->num_elementos; i++) {
            // compara com cada pacote da melhor_combinacao
            for (int j = 0; !tem_interseccao && j < melhor_combinacao->num_elementos; j++) {
                if (atual->celula_pacotes[i] == melhor_combinacao->celula_pacotes[j]) {
                    tem_interseccao = 1; // achou pacote em comum vai da um "break" nos 2 for
                }
            }
        }

        if (tem_interseccao) {
            // Faz anterior apontar para o proximo do atual (Para não perdermos a lista)
            anterior->prox = atual->prox;

            // se estivermos removendo o último, atualiza lista->ultimo
            if (atual == lista->ultimo) {
                lista->ultimo = anterior;
            }

            // libera memória do vetor interno e da célula
            free(atual->celula_pacotes);
            free(atual);

            // segue a iteração a partir do próximo do anterior
            atual = anterior->prox;
        } else {
            // sem interseção: avança normalmente
            anterior = atual;
            atual = atual->prox;
        }
    }
}

/*
Essa função ela ja é resposnsavel por gerar todas as combinações e ja retorna para nos a melhor delas 
de acordo com aquela que tiver a maior prioridade
*/
Celula_Combinacao *gerar_combinacoes(Lista_combinacao *lista, Lista_pacote *lista_galpao, int peso_max_drone){
    Celula_Combinacao *melhor_opcao = NULL;

    // Conta número de pacotes disponíveis
    int numero_de_elementos_da_combinacao = 0;
    Celula *aux = lista_galpao->primeiro->prox;
    while (aux != NULL) {
        numero_de_elementos_da_combinacao++;
        aux = aux->prox;
    }

    // Array de acesso rápido aos pacotes atuais
    Celula **todos_pacotes = (Celula**) malloc(numero_de_elementos_da_combinacao * sizeof(Celula*));
    aux = lista_galpao->primeiro->prox;
    for(int i = 0; i < numero_de_elementos_da_combinacao; i++) {
        todos_pacotes[i] = aux;
        aux = aux->prox;
    }
    
    // Gera todas as combinações possíveis (de todos os tamanhos)
    for (int tamanho = 1; tamanho <= numero_de_elementos_da_combinacao; tamanho++) {
        // Array para armazenar os índices da combinação atual
        int *comb = (int*) malloc(tamanho * sizeof(int));
        
        // Inicializa com a primeira combinação possível
        for (int i = 0; i < tamanho; i++) {
            comb[i] = i;
        }
        
        while (1) {
            int peso_total = 0;
            int prioridade_total = 0;
            
            // Calcula peso e prioridade da combinação atual
            for (int i = 0; i < tamanho; i++) {
                peso_total += todos_pacotes[comb[i]]->pacote.peso;
                prioridade_total += todos_pacotes[comb[i]]->pacote.prioridade;
            }
            
            // Verifica se a combinação é válida (peso <= peso_max_drone)
            if (peso_total <= peso_max_drone) {
                // Cria vetor com os ponteiros para as células dos pacotes
                Celula **vetor_pacotes = (Celula**) malloc(tamanho * sizeof(Celula*));
                for (int i = 0; i < tamanho; i++) {
                    vetor_pacotes[i] = todos_pacotes[comb[i]];
                }
                
                // Insere combinação na lista
                inserir_combinacao_final(lista, vetor_pacotes, prioridade_total, peso_total, tamanho);
                
                // Atualiza melhor opção
                if (melhor_opcao == NULL || 
                    prioridade_total > melhor_opcao->prioridade_total ||
                    (prioridade_total == melhor_opcao->prioridade_total && peso_total < melhor_opcao->peso_total)) {
                    melhor_opcao = lista->ultimo;
                }

                free(vetor_pacotes);
            }

            // Gera próxima combinação
            int i = tamanho - 1;
            while (i >= 0 && comb[i] == numero_de_elementos_da_combinacao - tamanho + i) {
                i--;
            }
            
            if (i < 0) {
                break; // Todas as combinações deste tamanho foram geradas
            }
            
            comb[i]++;
            for (int j = i + 1; j < tamanho; j++) {
                comb[j] = comb[j - 1] + 1;
            }
        }
        
        free(comb);
    }

    free(todos_pacotes);
    return melhor_opcao;
}

Celula_Combinacao *escolher_melhor(Lista_combinacao *lista){
    
    // Pega o primeiro como a melhor opção
    Celula_Combinacao *melhor_opcao = lista->primeiro->prox;
    
    Celula_Combinacao *aux = lista->primeiro->prox->prox;
    while (aux) {
        if(aux->prioridade_total > melhor_opcao->prioridade_total){
            melhor_opcao = aux;
        }
        aux = aux->prox;
    }
    return melhor_opcao;
}

