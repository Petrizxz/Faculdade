#include "TAD_Galpao.h"
#include "../Model_TAD_Lista_Pacote/TAD_Lista_Pacotes.h"
#include "../Model_TAD_Drone/TAD_Drone.h"
#include "../Model_TAD_Combinacao/TAD_Combinacao.h"
#include <stdlib.h> // Para free()

void inicializar_galpao(Galpao *galpao){
    Lista_pacote lista;
    iniciar_lista_vazia(&lista);
    galpao->lista_de_pacotes = lista;
}

void receber_pacote_galpao(Galpao *galpao, Pacote pacote){
    inserir_pacote_final(&galpao->lista_de_pacotes, &pacote);
}

void carregamento_galpao(Galpao *galpao, Drone *drone){
    // Cria o tipo lista combinação
    Lista_combinacao lista_combinacao;
    iniciar_lista_vazia_combinacao(&lista_combinacao);
    
    // Gera as combinações e retorna a melhor opção
    Celula_Combinacao *melhor_combinacao = gerar_combinacoes(&lista_combinacao, &galpao->lista_de_pacotes, drone->peso_max);    
    int num_viagem = 1;
    
    // Verifica se foi encontrada uma combinação valida
    if (melhor_combinacao == NULL) {
        printf("Nenhuma combinacao valida encontrada!\n");
        return;
    }

    // Enquanto tiver pacotes no galpao
    while (!lista_eh_vazia(&galpao->lista_de_pacotes)){   
        
        printf("\nCarregando drone com os pacotes!\n" );
        
        // CORREÇÃO: Se melhor_combinacao for NULL, precisamos gerar novas combinações.
        // O fluxo original estava incorreto, pois só gerava na primeira vez.
        if (melhor_combinacao == NULL || lista_combinacao_eh_vazia(&lista_combinacao)) {
            // Limpa a lista de combinações anterior
            Celula_Combinacao *atual_limpeza = lista_combinacao.primeiro->prox; // Começa após a cabeça
            while (atual_limpeza != NULL) {
                Celula_Combinacao *proximo = atual_limpeza->prox;
                if (atual_limpeza->celula_pacotes != NULL) {
                    free(atual_limpeza->celula_pacotes);
                }
                free(atual_limpeza);
                atual_limpeza = proximo;
            }
            // Reinicia a lista (apenas a cabeça)
            lista_combinacao.ultimo = lista_combinacao.primeiro;
            lista_combinacao.primeiro->prox = NULL;
            
            // Gera novas combinações
            melhor_combinacao = gerar_combinacoes(&lista_combinacao, &galpao->lista_de_pacotes, drone->peso_max);
            
            if (melhor_combinacao == NULL) {
                printf("Nao ha mais combinacoes validas!\n");
                break;
            }
        }
        
        // VERIFICAÇÃO DE SEGURANÇA: Verifica se todos os ponteiros são válidos
        int combinacao_valida = 1;
        for(int i = 0; i < melhor_combinacao->num_elementos; i++){
            // O erro de Segmentation Fault acontecia aqui, porque o ponteiro era inválido.
            // A solução é garantir que a célula de pacote não seja liberada em remover_pacote_meio.
            if (melhor_combinacao->celula_pacotes[i] == NULL) {
                combinacao_valida = 0;
                printf("Erro: Ponteiro de pacote invalido na combinacao!\n");
                break;
            }
        }
        
        if (!combinacao_valida) {
            break;
        }
        
        for(int i = 0; i < melhor_combinacao->num_elementos; i++){
            // Instancia pacote para receber os dados do retirado a baixo
            Pacote pacote;
           
            // Remove pacote em qualquer lugar da lista
            // A função remover_pacote_meio NÃO deve liberar a célula.
            remover_pacote_meio(&galpao->lista_de_pacotes, melhor_combinacao->celula_pacotes[i], &pacote);

            // Insere o pacote no drone
            carregamento_drone(drone, pacote);
        }
        
        // Como ja foi escolhido a melhor opção remove da lista_combinacao todas as opções que não são mais validas
        remover_combinacoes_com_intersecao(&lista_combinacao, melhor_combinacao);

        // Libera o espaço de memoria alocada para a combinação
        if (melhor_combinacao->celula_pacotes != NULL) {
            free(melhor_combinacao->celula_pacotes);
            melhor_combinacao->celula_pacotes = NULL;
        }

        // Mostra o numero da viagem
        printf("\n-----------------------------------------\n");
        printf("\nViagem: %d\n", num_viagem++);
        
        // Realiza as entregas dos pacotes
        realizar_entrega(drone);
        
        // Reset para próxima iteração
        melhor_combinacao = NULL;
    }
    
    printf("\nTodas as entregas realizadas!\n" );
    printf("Total de Quilometros Percorridos no Dia: %.0fKm\n", drone->distancia_total);
    
    // LIMPEZA FINAL: Libera toda a lista de combinações
    Celula_Combinacao *atual = lista_combinacao.primeiro;
    while (atual != NULL) {
        Celula_Combinacao *proximo = atual->prox;
        if (atual != lista_combinacao.primeiro && atual->celula_pacotes != NULL) {
            free(atual->celula_pacotes);
        }
        free(atual);
        atual = proximo;
    }
}
