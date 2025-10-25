#include "TAD_Drone.h"

void inicializar_drone (Drone *drone, int peso){
    drone->peso_max = peso;
    drone->peso_carregado = 0;
    drone->distancia_total = 0;
    Lista_pacote lista;
    iniciar_lista_vazia(&lista);
    drone->lista_de_entrega = lista;
}


int carga_suportada(Drone *drone, int peso){
    if ((drone->peso_carregado + peso) > drone->peso_max && lista_eh_vazia(&drone->lista_de_entrega)){
        printf("\nO drone nao suporta a carga!\n\n");
        exit(1);
    }

    if ((drone->peso_carregado + peso) > drone->peso_max){
        printf("\nDrone esta cheio e pronto para a entrega!\n");
        return 0;
    }
    return 1;
}

// antes da função ser chamada deve ser verificado se a carga é suportada
int carregamento_drone(Drone *drone, Pacote pacote){

    //Adiciona o pacote no drone
    inserir_pacote_final(&drone->lista_de_entrega, &pacote);

    //Adiciona o peso do pacote ao drone
    drone->peso_carregado += get_peso(&pacote);
    
    return 1;
}

void realizar_entrega(Drone *drone){
    // Utilizado para marcar posição atual do drone em relação a ultima entrega/galpao
    int posicao_atual = 0, temp_dist = 0;
           // Enquanto o drone ainda tiver entregas para fazer
    while (!lista_eh_vazia(&drone->lista_de_entrega))
    {   
        // Remove o pacote do drone, para realizar entrega
        Pacote pacote;
        remover_pacote_inicio(&drone->lista_de_entrega, &pacote);
        
        // Distancia que o drone percorre partindo da base ou da última entrega para a próxima
        posicao_atual = get_distancia_endereco(&pacote) - posicao_atual;
        
        // Somamos o modulo, pois, ele pode percorrer direções opostas à ultima entrega/galpão
        drone->distancia_total += (posicao_atual < 0) ? -(posicao_atual) : posicao_atual;
        // Armazena a distancia temporaria do pacote 
        temp_dist += (posicao_atual < 0) ? -(posicao_atual) : posicao_atual;

        // Atualiza a posição do drone de acordo com a entrega realizada
        posicao_atual = get_distancia_endereco(&pacote);

        
        // Imprime qual foi a entrega realizada
        imprime_drone(pacote);
    }
    // Atualiza a distancia temporaria do pacote 
    temp_dist += posicao_atual;
    
    // Printa distancia total dessa viagem
    printf ("Distancia total: %dKm\n", temp_dist);
    printf("\n-----------------------------------------\n" ); 
    // O drone retorna para o galpão ao final do percurso
    drone->distancia_total += posicao_atual;
    //todas as entregas foram realizadas
    drone->peso_carregado = 0;

    printf("\nVoltando para o galpao!\n" );
    
}

void imprime_drone(Pacote pacote){
    printf("Entrega: '%s' para '%s'\n", get_conteudo(&pacote), get_destinatario(&pacote)); 
}