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
    // OTAVIO: TOM: aqui foi a segunda modificação gerar as combinação
    //Gera as combinações e armazena elas na lista_combinação
    // otavio essa é pra vc 
    
    // Enquanto tiver item no galpão
    int num_viagem = 1;
    
    //Enquanto tiver pacotes no galpao
    while (!lista_eh_vazia(&galpao->lista_de_pacotes)){   
        Celula_Combinacao *melhor_combinacao = gerar_combinacoes(&lista_combinacao, &galpao->lista_de_pacotes, drone->peso_carregado);    

        printf("\nCarregando drone com os pacotes!\n" );
        
        // Caso não tenha a melhor combinação ele vai percorrer as opções verificando a melhor
        if (melhor_combinacao->celula_pacotes == NULL) melhor_combinacao = escolher_melhor(&lista_combinacao);
        printf("teste: pos escolher melhor combinacao");
        // Verifica enquanto tiver pacote e o drone suportar, ou seja restringe as viagens do drone
        // TOM: Verifica as condições
        // carga suportada acredito que não seja mais necessaria pois dentro de gerar combinações o otavio ja verifica se as combinações não excedem o pesso do drone
        // Tenho uns 90% de certeza que pode arrancar a carga_suportada dali
        // Tem que verificar em que momento esse vetor fica vazio mas pra isso precisa implementar o remover pacote meio
        for(int i = 0; i < melhor_combinacao->num_elementos;i++){
            // Instancia pacote para receber os dados do retirado a baixo
            Pacote pacote;
            // TOM: 
            // Retira o pacote do galpao
            // Essa função vai receber o ponteiro da celula que vai ser retirada e utilizando o anterior vai ligar com o prox
            // ex: apagar p2
            // p2: tem os dados anterior: p1  e proximo p3
            // p2.anterior.prox   (Esse é o p1) = p2.prox (Esse é o p3)
            // *pacote = p2.pacote
            // free(p2)
            // Acho que seria algo assim
            remover_pacote_meio(&galpao->lista_de_pacotes,melhor_combinacao->celula_pacotes[i], &pacote);
            imprime_galpao(galpao);
            // Insere o pacote no drone
            carregamento_drone(drone, pacote);
        }
        
        // Como ja foi escolhido a melhor opção remove da lista_combinacao todas as opções que não são mais validas
        remover_combinacoes_com_intersecao(&lista_combinacao, melhor_combinacao);

        // Libera o espaço de memoria alocada para a combinação
        free(melhor_combinacao->celula_pacotes);
        melhor_combinacao->celula_pacotes = NULL;
        // Mostra o numero da viagem
        printf("\n-----------------------------------------\n");
        printf("\nViagem: %d\n", num_viagem++);
        // Realiza as entregas dos pacotes
        realizar_entrega(drone);
    }
    printf("\nTodas as entregas realizadas!\n" );
    printf("Total de Quilometros Percorridos no Dia: %.0fKm", drone->distancia_total);
}

void imprime_galpao(Galpao *galpao){
    //apenas teste para parar de dar erro
    
    printf(get_conteudo(&galpao->lista_de_pacotes.primeiro->pacote));
}
