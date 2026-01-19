#ifndef TRECHO_H
#define TRECHO_H

#include "parada.h"

class Trecho {
public:
    enum NaturezaTrecho { COLETA, ENTREGA, DESLOCAMENTO };

private:
    Parada* origem;
    Parada* destino;
    double distancia;
    double tempo;
    NaturezaTrecho natureza;
    
    void DeterminarNatureza();

public:
    Trecho(Parada* ori, Parada* dest, double velocidade);
    ~Trecho();
    
    Parada* GetOrigem() const;
    Parada* GetDestino() const;
    double GetDistancia() const;
    double GetTempo() const;
    NaturezaTrecho GetNatureza() const;
};

#endif 