#include "TAD_Combinacao.h"

// Vai inicializar a lista com a celula cabeça
void iniciar_lista_vazia_combinacao (Lista_combinacao *lista){
    lista->primeiro = (Celula_Combinacao*) malloc(sizeof(Celula_Combinacao));
    lista->ultimo = lista->primeiro;
    lista->primeiro->prox = NULL;
}

// Preenche a Celula com os valores apropriados
void inserir_combinacao_final(Lista_combinacao *lista, Celula **vetor_pacotes, int prioridade, int peso){
    lista->ultimo->prox = (Celula_Combinacao*) malloc(sizeof(Celula_Combinacao));
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->celula_pacotes = vetor_pacotes;
    lista->ultimo->peso_total = peso;
    lista->ultimo->prioridade_total = prioridade;
    lista->ultimo->prox = NULL;
}

int vetor_eh_vazia (Celula_Combinacao *celula){
    return (celula == NULL);
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
    int numero_de_elementos_da_combinacao = 3, prioridade_da_combinacao = 0, peso_da_combinacao = 0;
    Celula **vetor_pacotes = (Celula**) malloc(numero_de_elementos_da_combinacao * sizeof(Celula*));

    // ai vc insere de acordo com o indice, porem não vai ser desse jeito, lista_galpao->primeiro->prox
    // vai ser dentro de um for ou um while depende da implementação pra gerar as combinações que vc encontrar
    
    vetor_pacotes[0] = lista_galpao->primeiro->prox;
    vetor_pacotes[1] = lista_galpao->primeiro->prox->prox;

    // Ai aqui no meio vc verifica se o peso é maior que o peso_max_drone e ja descarta essa celula. vc da um free em vetor_pacotes
    // Não tenho ctz se é assim que descarta da uma jogada no chatgpt pra gente ter ctz

    // por fim vc manda a lista de combinações, prioridade total e o peso total
    inserir_combinacao_final(lista, vetor_pacotes, 5, 2);

    // Depois de verificar que a combinação não utrapassa o peso do drone vc vai comparar a prioridade da combinação 
    // com a melhor e caso seja melhor substituir o valor

    if(melhor_opcao == NULL || melhor_opcao->prioridade_total < prioridade_da_combinacao){
        //ultimo pois isso vai estar verificando enquanto insere na lista
        // melhor opção vai ser um ponteiro para o local da lista combinações que tem a melhor combinação
        melhor_opcao = lista->ultimo;
    }

    return melhor_opcao;

    

}

int escolher_melhor(){
    return 0;
}

