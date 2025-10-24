#include "TAD_Pacote.h"

void inicializar_pacote(Pacote *pacote, char conteudo[50], char destinatario[50], int peso, int distancia, int prioridade){
    set_conteudo(pacote, conteudo);
    set_destinatario(pacote, destinatario);
    set_peso(pacote, peso);
    set_distancia_endereco(pacote, distancia);
    set_prioridade(pacote, prioridade);
}

void set_conteudo(Pacote *pacote, char conteudo[50]){
    strcpy(pacote->conteudo, conteudo);
}

void set_destinatario(Pacote *pacote, char destinatario[50]){
    strcpy(pacote->destinatario, destinatario);
}

void set_peso(Pacote *pacote, int peso){
    pacote->peso = peso;
}

void set_distancia_endereco(Pacote *pacote, int distancia){
    pacote->distancia = distancia;
}

void set_prioridade(Pacote *pacote, int prioridade){
    pacote->prioridade = prioridade;
}

const char *get_conteudo(const Pacote *pacote){
    return pacote->conteudo;
}

const char *get_destinatario(const Pacote *pacote){
    return pacote->destinatario;
}

int get_peso(const Pacote *pacote){
    return pacote->peso;
}

int get_distancia_endereco(const Pacote *pacote){
    return pacote->distancia;
}

int get_prioridade(const Pacote *pacote){
    return pacote->prioridade;
}
