#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef TAD_PACOTE_H
#define TAD_PACOTE_H


typedef struct{

    char conteudo[50];
    char destinatario[50];
    int peso;
    int distancia;

}Pacote;

//Inicialização do TAD Pacote
void inicializar_pacote(Pacote *pacote, char conteudo[50], char destinatario[50], int peso, int distancia);

//Atribuições de valores
void set_conteudo(Pacote *pacote, char conteudo[50]);
void set_destinatario(Pacote *pacote, char destinatario[50]);
void set_peso(Pacote *pacote, int peso);
void set_distancia_endereco(Pacote *pacote, int distancia);

//Obtenções de valores
//const para não ter risco de alterar e ponteiro para não precisar copiar a struct completa
const char *get_conteudo(const Pacote *pacote);
const char *get_destinatario(const Pacote *pacote);
int get_peso(const Pacote *pacote);
int get_distancia_endereco(const Pacote *pacote);

#endif