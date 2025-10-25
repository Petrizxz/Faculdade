#include "Model_TAD_Pacote/TAD_Pacote.h"
#include "Model_TAD_Drone/TAD_Drone.h"
#include "Model_TAD_Galpao/TAD_Galpao.h"

int main(){
    // Declaração de variaveis
    int peso_max_drone = 0, quantidade_pacotes = 0, escolha = 0;

    //iniciaização de galpao
    Galpao galpao;
    inicializar_galpao(&galpao);

    Drone drone;

    // Escolha manual ou por arquivo
    printf("Escolha a forma de entrada de dados\n[1] Manual\n[2] Arquivo\n");
    //scanf("%d", &escolha);
    escolha = 2;

    switch (escolha){
        case 1: {// caso seja escolhido manual
            printf("\nDigite o peso maximo do drone: ");
            scanf("%d", &peso_max_drone);
            
            printf("Digite a quantidade de pacotes: ");
            scanf("%d", &quantidade_pacotes);
            
            // Inicializando drone
            inicializar_drone(&drone, peso_max_drone);
            
            // Preenchimento do galpão com pacotes de forma manual
            for (int i = 0; i < quantidade_pacotes; i++) {
                Pacote pacote;
                
                char conteudo[50], destinatario[50];
                int peso  = 0, distancia = 0, prioridade = 0;

                printf("\nPacote %d:\n", i+1);
                printf("Conteudo: ");
                scanf("%s", conteudo);
                printf("Destinatario: ");
                scanf("%s", destinatario);
                printf("Peso: ");
                scanf("%d", &peso);
                printf("Distancia: ");
                scanf("%d", &distancia);
                printf("Prioridade: ");
                scanf("%d", &prioridade);

                //inicializamos o pacote com os dados
                inicializar_pacote(&pacote, conteudo, destinatario, peso, distancia, prioridade);

                
                // Recebimento dos pacotes
                receber_pacote_galpao(&galpao, pacote);
            }
            
            //Sistema de Gerenciamento de Entregas
            carregamento_galpao(&galpao, &drone);
            break;
        }
        case 2: {// Caso seja escolhido entrada por arquivo
            char arquivo[20];

            printf("\nDigite o nome do arquivo desejado:\n(teste1.txt ou teste2.txt)\n");
            //scanf("%s", arquivo);
            strcpy(arquivo, "teste1.txt");
            // Manipulação de arquivos
            FILE *file = fopen(arquivo, "r");
            if(file == NULL){
                printf("Arquivo nao identificado\n");
                return 0;
            }

            // Os 2 primeiros valores serão para inicialização de drones e preenchimento dos pacotes
            fscanf(file, "%d", &peso_max_drone);
            fscanf(file, "%d", &quantidade_pacotes);
            
            // inicializando drone
            inicializar_drone(&drone, peso_max_drone);
            
            // Preenchimento do galpão com pacotes lidos em arquivo
            for (int i = 0; i < quantidade_pacotes; i++){
                Pacote pacote;

                // Utilizando os sets
                char conteudo[50], destinatario[50];
                int peso  = 0, distancia = 0, prioridade = 0;
                fscanf(file, "%s %s %d %d %d", conteudo, destinatario, &peso, &distancia, &prioridade);

                //inicializamos o pacote com os dados
                inicializar_pacote(&pacote, conteudo, destinatario, peso, distancia, prioridade);

                // Recebimento do pacote por galpao
                receber_pacote_galpao(&galpao, pacote);
            }
            
            //Sistema de Gerenciamento de Entregas
            carregamento_galpao(&galpao, &drone);
        
            fclose(file);
            break;
        }
        default: {
            printf("Escolha nao identificada\n");
            return 1;
    }
    }
    return 0;
}