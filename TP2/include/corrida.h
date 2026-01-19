#ifndef CORRIDA_H
#define CORRIDA_H

#include "demanda.h"
#include "trecho.h"
#include "parada.h"


class Corrida {
private:

    struct NoDemanda {
        Demanda* demanda;
        NoDemanda* prox;
        NoDemanda(Demanda* d);
    };
    
    struct NoParada {
        Parada* parada;
        NoParada* prox;
        NoParada(Parada* p);
    };
    
    struct NoTrecho {
        Trecho* trecho;
        NoTrecho* prox;
        NoTrecho(Trecho* t);
    };
    
    NoDemanda* cabecaDemandas;
    NoParada* cabecaParadas;
    NoTrecho* cabecaTrechos;
    
    int numDemandas;
    double distanciaTotal;
    double duracaoTotal;
    double eficiencia;
    double tempoInicio;
    double velocidade;

public:
    Corrida(Demanda* demandaInicial, double vel);
    ~Corrida();
    void AdicionarDemanda(Demanda* demanda);
    void ConstruirRota();
    double CalcularEficiencia();
    bool VerificarDistancia(Demanda* demanda, double alfa, double beta);
    bool PodeAdicionarDemanda(Demanda* demanda, double lambda, 
                             double alfa, double beta);
    
    void RemoverUltimaDemanda();
    void ImprimirResultado() const;
    int GetNumDemandas() const;
    double GetTempoInicio() const;
    double GetDuracaoTotal() const;
};

#endif 