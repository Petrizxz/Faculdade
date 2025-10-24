#include "TAD_Galpao.h"
#include "../Model_TAD_Lista_Pacote/TAD_Lista_Pacotes.h"
#include "../Model_TAD_Drone/TAD_Drone.h"
#include "../Model_TAD_Combinacao/TAD_Combinacao.h"

// Vamos iniciar a lista e chamamos a funcao inicializar lista vazia
void inicializar_galpao(Galpao *galpao){
    Lista_pacote lista;
    iniciar_lista_vazia(&lista);
    galpao->lista_de_pacotes = lista;
}

void receber_pacote_galpao(Galpao *galpao, Pacote pacote){

    // Vai organizando os pacotes, por ordem de chegada, a medida que vai chegando pacotes
    inserir_pacote_final(&galpao->lista_de_pacotes, &pacote);
    
}

void carregamento_galpao(Galpao *galpao, Drone *drone){

    // OTAVIO: TOM: Essa foi a primeira modificação, criar o tipo lista combinação
    Lista_combinacao lista_combinacao;
    iniciar_lista_vazia_combinacao(&lista_combinacao);

    // Enquanto tiver item no galpão
    int num_viagem = 1;

    //Enquanto tiver pacotes no galpao
    while (!lista_eh_vazia(&galpao->lista_de_pacotes))
    {   // OTAVIO: TOM: aqui foi a segunda modificação gerar as combinação
        //Gera as combinações e armazena elas na lista_combinação
        // otavio essa é pra vc 
        gerar_combinacoes(&lista_combinacao, &galpao->lista_de_pacotes, drone->peso_carregado);      
        printf("\nCarregando drone com os pacotes!\n" );

        // Verifica enquanto tiver pacote e o drone suportar, ou seja restringe as viagens do drone
        while (!lista_eh_vazia(&galpao->lista_de_pacotes) && carga_suportada(drone, galpao->lista_de_pacotes.primeiro->prox->pacote.peso))
        {   // Instancia pacote para receber os dados do retirado a baixo
            Pacote pacote;
            // Retira o pacote do galpao
            remover_pacote_inicio(&galpao->lista_de_pacotes, &pacote);
            
            // Insere o pacote no drone
            carregamento_drone(drone, pacote);
        }

        // Mostra o numero da viagem
        printf("\n-----------------------------------------\n");
        printf("\nViagem: %d\n", num_viagem++);
        // Realiza as entregas dos pacotes
        realizar_entrega(drone);
    }
    printf("\nTodas as entregas realizadas!\n" );
    printf("Total de Quilometros Percorridos no Dia: %.0fKm", drone->distancia_total);
}

void imprimi_galpao(Galpao *galpao){
    //apenas teste para para de dar erro
    printf(galpao->lista_de_pacotes.primeiro->pacote.conteudo);
}
