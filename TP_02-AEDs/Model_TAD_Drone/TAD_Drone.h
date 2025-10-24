#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Model_TAD_Lista_Pacote/TAD_Lista_Pacotes.h"

#ifndef TAD_DRONE_H
#define TAD_DRONE_H

typedef struct
{
    
double peso_max;
double peso_carregado;
double distancia_total;
Lista_pacote lista_de_entrega;

}Drone;

// Inicia os valores do drone para não ter lixo de memoria,
// também inicializamos o valor maximo que ele consegue carregar.
void inicializar_drone (Drone *drone, int peso);

// Verifica se o drone aguenta mais peso
int carga_suportada(Drone *drone, int peso);

// Adiciona o pacote na lista, armazenando dentro do drone,
int carregamento_drone(Drone *drone, Pacote pacote);

// Retira da lista do drone as entregas a medida que as entregas vao sendo feitas
// e incrementa a distancia percorrida 
void realizar_entrega(Drone *drone);

// imprime as informações dos componentes do drone
void imprime_drone (Pacote pacote);

#endif