#ifndef CENA_H
#define CENA_H

#include "objeto.h"

struct Segmento {
    int tempo;
    int id_objeto;
    double inicio;
    double fim;
};

struct Cena {
    Segmento* segmentos;       //array dinâmico
    int numSegmentos;          //quantidade de segmentos na cena atual 
    int capacidade;            //capacidade max atual 
};

Cena criaCena(int capacidade);
void adicionaSegmento(Cena &cena, int tempo, const Objeto &obj, double ini, double fim);
void ordenaPorY(Objeto *objetos, int numObj);
void geraCena(Objeto *objetos, int numObj, Cena &cena, int tempo);
void ordenaSegmentosPorId(Cena &cena);

#endif