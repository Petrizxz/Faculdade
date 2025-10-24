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



//OTAVIO: Aqui vai ser onde vc vai implementar as combinações vou deixar explicado em comentario como
// Recomendo que vc entenda como esta estruturado o tad combinação para ver o como vc vai armazenar
// Mas basicamente vc vai armazenar os ponteiros no vetor e somar as prioridades e peso deles
// Essa função ela ja é resposnsavel por gerar todas as combinações e ja retorna para nos a melhor delas
// de acordo com aquela que tiver a maior prioridade
Celula_Combinacao *gerar_combinacoes(Lista_combinacao *lista, Lista_pacote *lista_galpao, int peso_max_drone){

    Celula_Combinacao *melhor_opcao = NULL;
    //OTAVIO: Esse exemplo a baixo é como vc vai inserir as os ponteiros no novo vetor de celulas 
    // Você precisass saber o numero de elementoos da combinação
    // Gera as combinações ex: {p1} , {p2}, {p3}, {p1, p2}, {p1, p3}, {p2, p3}, {p1, p2, p3}
    //                           1  ,   1 ,   1 ,     2   ,     2   ,     2   ,       3
    int numero_de_elementos_da_combinacao = 2, prioridade_da_combinacao = 0, peso_da_combinacao = 0;
    Celula **vetor_pacotes = (Celula**) malloc(numero_de_elementos_da_combinacao * sizeof(Celula*));

    // ai vc insere de acordo com o indice, porem não vai ser desse jeito, lista_galpao->primeiro->prox
    // vai ser dentro de um for ou um while depende da implementação pra gerar as combinações que vc encontrar
    
    vetor_pacotes[0] = lista_galpao->primeiro->prox;
    vetor_pacotes[1] = lista_galpao->primeiro->prox->prox;

    // Ai aqui no meio vc verifica se o peso é maior que o peso_max_drone e ja descarta essa celula. vc da um free em vetor_pacotes
    // Não tenho ctz se é assim que descarta da uma jogada no chatgpt pra gente ter ctz

    // por fim vc manda a lista de combinações, prioridade total e o peso total
    inserir_combinacao_final(lista, vetor_pacotes, 5, 2,numero_de_elementos_da_combinacao);

    // Depois de verificar que a combinação não utrapassa o peso do drone vc vai comparar a prioridade da combinação 
    // com a melhor e caso seja melhor substituir o valor

    if(melhor_opcao == NULL || melhor_opcao->prioridade_total < prioridade_da_combinacao){
        //ultimo pois isso vai estar verificando enquanto insere na lista
        // melhor opção vai ser um ponteiro para o local da lista combinações que tem a melhor combinação
        melhor_opcao = lista->ultimo;
    }

    return melhor_opcao;

}

Celula_Combinacao *escolher_melhor(Lista_combinacao *lista){

    // Pega o primeiro como a melhor opção
    Celula_Combinacao *melhor_opcao = lista->primeiro->prox;

    Celula_Combinacao *aux = lista->primeiro->prox->prox;
    while (aux) {
        if(aux->num_elementos > melhor_opcao->num_elementos){
            melhor_opcao = aux;
        }
        aux = aux->prox;
    }
    return melhor_opcao;
}

