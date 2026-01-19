#ifndef ESCALONADOR_H
#define ESCALONADOR_H

#include "corrida.h"


struct Evento {
    double tempo;
    Corrida* corrida;
    
    Evento();
    Evento(double t, Corrida* c);
};

class Escalonador {
private:
    Evento* heap;
    int capacidade;
    int tamanho;
    void Trocar(int i, int j);
    void HeapifyUp(int idx);
    void HeapifyDown(int idx);
    void Redimensionar();

public:
    Escalonador(int cap = 1000);
    ~Escalonador();
    void InsereEvento(const Evento& evento);
    Evento RetiraProximoEvento();
    
    bool Vazio() const;
    int GetTamanho() const;
};

#endif 